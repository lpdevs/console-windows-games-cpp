#include "console.h"
#include <conio.h>
#include "snake.h"
#include "fruit.h"
#include <time.h>
#include <Windows.h>
#include <iostream>
#include <fstream>

void initialSnake(Snake &snake);
void display(Snake snake, Fruit fruit, int score, int highScore);
void control_move(Snake &snake);
int resolve(Snake &snake, Fruit &fruit, int &timeSleep_ms, int &score);
int randomColor();
int getHighScore(std::string fileName);
void saveHighScore(int score,std::string fileName);

int main(){
	std::string fileResult = "highscore.txt";
	while (true){
		srand(time(NULL));
		int timeSleep_ms = 120;
		int score = 0;
		int highScore = getHighScore(fileResult);

		Snake snake;
		Fruit fruit(rand() % Board::WIDTH, rand() % Board::HEIGHT);
		initialSnake(snake);

		int key_state;


		while (true){
			display(snake, fruit, score, highScore);
			control_move(snake);
			int code = resolve(snake, fruit, timeSleep_ms, score);
			if (code == Result::LOSE){
				if (score > highScore) saveHighScore(score,fileResult);

				gotoXY((Board::WIDTH + Console::WIDTH - 10) / 2, Board::HEIGHT / 2);
				std::cout << "Game over!";
				gotoXY((Board::WIDTH + Console::WIDTH - 23) / 2, Board::HEIGHT / 2 + 1);
				std::cout << "Press Enter to quit game!";
				gotoXY((Board::WIDTH + Console::WIDTH - 23) / 2, Board::HEIGHT / 2 + 2);
				std::cout << "Press Space to play again!";
				while (true){
					key_state = _getch();
					if (key_state == ASCII::ch_enter || key_state == ASCII::ch_space) break;
					Sleep(100);
				}
				break;
			}
			Sleep(timeSleep_ms);
		}
		if (key_state == ASCII::ch_enter) break;
	}
	return 0;
}

void initialSnake(Snake &snake)
{
	snake.addDot(Dot(0, 0, ColorCode_Green, ASCII::ch_face));
	snake.setStatus(DOWN);
}

void display(Snake snake, Fruit fruit,int score, int highScore)
{
	clrscr();

	TextColor(default_ColorCode);
	for (int i = 0; i < Board::HEIGHT; i++)
	{
		gotoXY(Board::WIDTH, i);
		std::cout << ASCII::ch_vertical;
	}

	gotoXY(Board::WIDTH + 1,0);
	std::cout << "CONSOLE SNAKE v1.0 ";
	gotoXY(Board::WIDTH + 1, 1);
	std::cout << "Designed by LamPV";

	gotoXY(Board::WIDTH + 1, 3);
	std::cout << "High Score: " << highScore;

	gotoXY(Board::WIDTH + 1,4);
	std::cout << "Score: " << score;

	

	gotoXY(Board::WIDTH + 1, Console::HEIGHT - 7);
	std::cout << "LEFT : A";
	gotoXY(Board::WIDTH + 1, Console::HEIGHT - 6);
	std::cout << "DOWN : S";
	gotoXY(Board::WIDTH + 1, Console::HEIGHT - 5);
	std::cout << "RIGHT: D";
	gotoXY(Board::WIDTH + 1, Console::HEIGHT - 4);
	std::cout << "UP   : W";
	gotoXY(Board::WIDTH + 1, Console::HEIGHT - 2);
	std::cout << "PAUSE/RESUME : SPACE";

	snake.display();
	fruit.display();
}

void control_move(Snake &snake)
{
	// update for old dots
	snake.getBody()[0].setColor(randomColor());
	snake.getBody()[0].setSymbol(ASCII::ch_default);
	for (int iii = snake.getBody().size() - 1; iii > 0; iii--)
	{
		snake.getBody()[iii] = snake.getBody()[iii - 1];
	}
	snake.getBody()[0].setColor(ColorCode_Green);
	snake.getBody()[0].setSymbol(ASCII::ch_face);

	// check if any key pressed
	if (_kbhit())
	{
		int key = _getch();

		if ((key == 'A' || key == 'a') && snake.getStatus() != RIGHT )
			snake.setStatus(LEFT);
		else if ((key == 'D' || key == 'd') && snake.getStatus() != LEFT)
			snake.setStatus(RIGHT);
		else if ((key == 'W' || key == 'w') && snake.getStatus() != DOWN)
			snake.setStatus(UP);
		else if ((key == 'S' || key == 's') && snake.getStatus() != UP)
			snake.setStatus(DOWN);
		else if (key == ASCII::ch_space){
			while (true)
			{
				gotoXY((Board::WIDTH + Console::WIDTH - 7) / 2, Board::HEIGHT / 2);
				std::cout << "Paused!";
				int k = _getch();
				if (k == ASCII::ch_space) break;
			}
		}
	}

	if (snake.getStatus() == UP)
		snake.getBody()[0].setY(snake.getBody()[0].getY() - 1);
	else if (snake.getStatus() == DOWN)
		snake.getBody()[0].setY(snake.getBody()[0].getY() + 1);
	else if (snake.getStatus() == LEFT)
		snake.getBody()[0].setX(snake.getBody()[0].getX() - 1);
	else if (snake.getStatus() == RIGHT)
		snake.getBody()[0].setX(snake.getBody()[0].getX() + 1);
}

int resolve(Snake &snake, Fruit &fruit, int &timeSleep_ms, int &score)
{
	// reach to bound
	if (snake.getBody()[0].getX() < 0 || snake.getBody()[0].getX() >= Board::WIDTH ||
		snake.getBody()[0].getY() < 0 || snake.getBody()[0].getY() >= Board::HEIGHT)
		return Result::LOSE;

	// eat its self
	for (unsigned int iii = 1; iii < snake.getBody().size(); iii++)
	{
		if (snake.getBody()[iii].getX() == snake.getBody()[0].getX() &&
			snake.getBody()[iii].getY() == snake.getBody()[0].getY())
			return Result::LOSE;
	}

	// eat fruit
	if (snake.getBody()[0].getX() == fruit.getX() &&
		snake.getBody()[0].getY() == fruit.getY())
	{
		// add dot and update
		snake.addDot(Dot());

		// beep
		std::cout << ASCII::ch_beep;

		snake.getBody()[0].setColor(default_ColorCode);
		snake.getBody()[0].setSymbol(ASCII::ch_default);
		for (int iii = snake.getBody().size() - 1; iii > 0; iii--)
		{
			snake.getBody()[iii] = snake.getBody()[iii - 1];
		}
		snake.getBody()[0].setColor(ColorCode_Green);
		snake.getBody()[0].setSymbol(ASCII::ch_face);

		// move fruit
		while(true){
			int check = 1;
			fruit.setX(rand() % Board::WIDTH);
			fruit.setY(rand() % Board::HEIGHT);
			for (unsigned int i = 0; i<snake.getBody().size(); i++){
				if (fruit.getX() == snake.getBody()[i].getX() &&
					fruit.getY() == snake.getBody()[i].getY())
				{
					check = -1;
					break;
				}
			}
			if (check == 1) break;
		}

		// speed up
		if (timeSleep_ms > 30){
			if (snake.getBody().size() % 10 == 0) timeSleep_ms -= 30;
		}

		// increase score
		score++;
	}
	return Result::NORMAL;
}

int randomColor(){
	int rColor = default_ColorCode;
	do{
		rColor = rand() % 15;
	} while (rColor == ColorCode_Black);
	return rColor;
}

int getHighScore(std::string fileName){
	int highScore = 0;
	std::ifstream myFile;
	myFile.open(fileName);
	if (myFile.is_open())
	{
		myFile >> highScore;
	}
	return highScore;
}

void saveHighScore(int score, std::string fileName)
{
	std::ofstream myFile;
	myFile.open(fileName);
	if (myFile.is_open())
	{
		myFile << score;
	}
	myFile.close();
}