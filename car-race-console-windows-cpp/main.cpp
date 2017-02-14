#include "car.h"
#include <iostream>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <fstream>
#include "gift.h"
#include <MMSystem.h>
#include "CImg.h"
#include <string>

using namespace cimg_library;

void displayBackground(CImg<> &buffer, int highScore, int score, int heart, int speed);
void display(CImg<> &buffer,Car user_car,Car* friend_car, int score, int highScore,int heart,Gift *gift,int speed);
void control(CImg<> &buffer,CImgDisplay &window,Car &userCar,Car *friendCar, Gift *gift, int speed);
int resolve(Car &userCar, Car *friendCar, int &score, int &heart, Gift *gift, int &speed, int &count);
int getHighScore(std::string fileName);
void saveHighScore(int score, std::string fileName);

#define numOfFriend 4

int main()
{
	std::string fileResult = "highscore.txt";
	
	while (true){
		srand(time(NULL));

		int speed = 2;
		int key_state;
		int count = 0;
		int score = 0;
		int heart = 10;
		int highScore = getHighScore(fileResult);


		// init user_Car
		Car user_car;
		user_car.createSharp();
		user_car.setX(SizeCar::WIDTH / 2);

		// init friend_Car
		Car friend_car[numOfFriend];
		for (int i = 0; i < numOfFriend; i++){
			friend_car[i].createSharp();
			friend_car[i].setX(friend_car[i].getWidth() / 2 + friend_car[i].getWidth() * 2 *i);

			if (i % 3 == 0) friend_car[i].setY(-60);
			else if (i % 3 == 1) friend_car[i].setY(-100 - rand() % 100);
			else friend_car[i].setY(-200);
		}

		// initial gift
		Gift gift[numOfFriend];
		for (int iii = 0; iii < numOfFriend; iii++)
		{
			gift[iii].setType(type_gift::MONEY);
			gift[iii].createSharp();
			gift[iii].setX(friend_car[iii].getWidth() / 2 + friend_car[iii].getWidth() * 2 * iii);
			gift[iii].setY(friend_car[iii].getY() - rand() % (2*friend_car[iii].getHeight()) - friend_car[iii].getHeight()*2);
		}

		CImg<> buffer(Window::WIDTH, Window::HEIGHT,1,3,0);
		CImgDisplay window(Window::WIDTH, Window::HEIGHT);

		while (!window.is_closed())
		{
			display(buffer,user_car, friend_car, score, highScore, heart, gift, speed);
			window.display(buffer);
			control(buffer,window,user_car, friend_car, gift,speed);
			int code = resolve(user_car, friend_car, score, heart, gift, speed, count);	

			if (code == Result::LOSE){
				if (score > highScore) saveHighScore(score, fileResult);
				
				PlaySound(TEXT("vehicle156.wav"), NULL, SND_ALIAS);
				
				buffer.draw_text(Board::WIDTH / 2, 0, "Game Over", Color::White);
				buffer.draw_text(Board::WIDTH / 2, 10, "Press Enter to quit game!", Color::White);
				buffer.draw_text(Board::WIDTH / 2, 20, "Press Space to play again!", Color::White);
				window.display(buffer);
				while (true){
					key_state = window.key();
					if (key_state > 0){
						window.flush();
						if (key_state == ASCII::ch_enter || key_state == ASCII::ch_space) break;
					}
				}
				break;
			}
		}
		if (key_state == ASCII::ch_enter) break;
	}
	return 0;
}

void displayBackground(CImg<> &buffer,int highScore, int score, int heart, int speed)
{
	// draw bounds
	for (int i = 1; i < 4; i++)
		buffer.draw_line(Board::WIDTH + i, 0, Board::WIDTH + i, Board::HEIGHT, Color::White);
	
	//draw instructions
	buffer.draw_text(Board::WIDTH + 5, 0, "Car Race v2.0", Color::White);
	buffer.draw_text(Board::WIDTH + 5, 15, "Designed by LamPV", Color::White);

	// convert int to char*
	static char hScore[20] = "HighScore: ";
	char buff1[11] = "";
	itoa(highScore, buff1, 10);
	strcpy(hScore + 11, buff1);
	buffer.draw_text(Board::WIDTH + 5, 30,hScore,Color::White);
	
	// convert int to char*
	static char _score[20] = "Score: ";
	char buff2[11] = "";
	itoa(score, buff2, 10);
	strcpy(_score + 7, buff2);
	buffer.draw_text(Board::WIDTH + 5, 45, _score, Color::White);

	static char _heart[20] = "Heart: ";
	char buff3[11] = "";
	itoa(heart, buff3, 10);
	strcpy(_heart + 7, buff3);
	buffer.draw_text(Board::WIDTH + 5, 60, _heart, Color::White);

	static char _speed[20] = "Speed: ";
	char buff4[11] = "";
	itoa(speed, buff4, 10);
	strcpy(_speed + 7, buff4);
	buffer.draw_text(Board::WIDTH + 5, 75, _speed, Color::White);

	buffer.draw_text(Board::WIDTH + 5, Window::HEIGHT - 50, "A : LEFT", Color::White);
	buffer.draw_text(Board::WIDTH + 5, Window::HEIGHT - 35, "D : RIGHT", Color::White);
	buffer.draw_text(Board::WIDTH + 5, Window::HEIGHT - 20, "SPACE: PAUSE/RESUME", Color::White);
}

void display(CImg<> &buffer, Car user_car,Car *friend_car, int score, int highScore, int heart, Gift *gift,int speed)
{
	buffer.fill(0);

	displayBackground(buffer,highScore,score,heart,speed);

	// display gift
	for (int iii = 0; iii < numOfFriend; iii++){
		buffer.draw_image
			(gift[iii].getX() - gift[iii].getWidth() / 2,
			gift[iii].getY() - gift[iii].getHeight() / 2,
			gift[iii].getData());
	}

	// display friend cars
	for (int i = 0; i < numOfFriend; i++){
		buffer.draw_image
			(friend_car[i].getX() - friend_car[i].getWidth() / 2,
			friend_car[i].getY() - friend_car[i].getHeight() / 2,
			friend_car[i].getData());
	}

	// display user car
	buffer.draw_image
		(user_car.getX() - user_car.getWidth() / 2,
		user_car.getY() - user_car.getHeight() / 2,
		user_car.getData());
}

void control(CImg<> &buffer,CImgDisplay &window,Car &userCar, Car *friendCar, Gift *gift,int speed)
{
	// control when user press keyboard
	int key = window.key();

	if (key>0)
	{
		window.flush();
		if ((key == 'A' || key == 'a') && userCar.getX()>userCar.getWidth())
		{
			userCar.setX(userCar.getX() - userCar.getWidth());
		}
		else if ((key == 'D' || key == 'd') && userCar.getX()<Board::WIDTH-userCar.getWidth())
		{
			userCar.setX(userCar.getX() + userCar.getWidth());
		}
		else if (key == ASCII::ch_space){
			while (true)
			{
				buffer.draw_text(Board::WIDTH + 10, Board::HEIGHT / 2, "Paused!", Color::White);
				window.display(buffer);
				int k = window.key();
				if (k>0){
					window.flush();
					if (k == ASCII::ch_space) break;
				}
			}
		}
	}

	// increase y for friend cars
	for (int i = 0; i < numOfFriend; i++){
		friendCar[i].setY(friendCar[i].getY() + speed);
	}

	// increase y for gifts
	for (int iii = 0; iii < numOfFriend; iii++){
		gift[iii].setY(gift[iii].getY() + 1);
	}

}

int resolve(Car &userCar, Car *friendCar, int &score, int &heart, Gift *gift, int &speed, int &count)
{
	// friend cars
	int f_x[numOfFriend];
	int f_y[numOfFriend];
	
	// gifts
	int g_x[numOfFriend];
	int g_y[numOfFriend];
	
	// get x,y of friend cars and gifts
	for (int i = 0; i < numOfFriend; i++){
		f_x[i] = friendCar[i].getX();
		f_y[i] = friendCar[i].getY();
		
		g_x[i] = gift[i].getX();
		g_y[i] = gift[i].getY();
		
	}
	
	// user car
	int u_x = userCar.getX();
	int u_y = userCar.getY();

	
	// eat something
	for (int i = 0; i < numOfFriend; i++)
	{
		int d_x = abs(u_x - g_x[i]);
		int d_y = abs(u_y - g_y[i]);
		if (d_y <= gift[i].getHeight() && d_x <= gift[i].getWidth()) {
			//std::cout << ASCII::ch_beep;
			switch (gift[i].getType())
			{
			case type_gift::MONEY:
				score++;
				heart++;
				break;
			case type_gift::HEART:
				heart += 5;
				break;
			case type_gift::FAST:
				if (speed<4) speed += 1;
				break;
			case type_gift::SLOW:
				if (speed>2) speed -= 1;
				break;
			default:
				break;
			}
			gift[i].setType(type_gift::NOTHING);
			gift[i].createSharp();
		}
	}
	
	// when friend car or money,heart... reach the bound
	for (int i = 0; i < numOfFriend; i++)
	{
		if (f_y[i] >= Board::HEIGHT + friendCar[i].getHeight()/2){
			friendCar[i].setX(friendCar[i].getWidth() / 2 + friendCar[i].getWidth() * 2 * i);

			if (i % 3 == 0) friendCar[i].setY(-60);
			else if (i % 3 == 1) friendCar[i].setY(-100 - rand() % 100);
			else friendCar[i].setY(-200);
			
			count++;
			if (count%30 == 0)
			{
				int j = rand() % numOfFriend;
				gift[j].setType(type_gift::HEART);
				gift[j].createSharp();
			}
			else if (count % 25 == 0)
			{
				int j = rand() % numOfFriend;
				gift[j].setType(type_gift::SLOW);
				gift[j].createSharp();
			}
			else if (count % 15 == 0)
			{
				int j[3];
				j[0] = rand() % numOfFriend;
				while (true)
				{
					j[1] = rand() % numOfFriend;
					if ( j[1]!=j[0] ) break;
				}
				while (true)
				{
					j[2] = rand() % numOfFriend;
					if (j[2] != j[1] && j[2] != j[0]) break;
				}

				for (int iii = 0; iii < 3; iii++)
				{
					if (gift[j[iii]].getY() < 0){
						gift[j[iii]].setType(type_gift::FAST);
						gift[j[iii]].createSharp();
					}	
				}	
			}
		}
		
		if (g_y[i] >= Board::HEIGHT + gift[i].getHeight()/2){
			switch (gift[i].getType()){
			case type_gift::MONEY:
				heart--;
				break;
			default:
				break;
			}
			gift[i].setX(friendCar[i].getWidth() / 2 + friendCar[i].getWidth() * 2 * i);
			gift[i].setY(-rand() % (2 * friendCar[i].getHeight()) - friendCar[i].getHeight() * 4);
			gift[i].setType(type_gift::MONEY);
			gift[i].createSharp();
		}
	}
	
	// hit other cars
	for (int i = 0; i < numOfFriend; i++)
	{
		int d_x = abs(u_x - f_x[i]);
		int d_y = abs(f_y[i] - u_y);
		if (d_y < friendCar[i].getHeight() && d_x < friendCar[i].getWidth()){
			return Result::LOSE;
		}
	}

	if (heart == 0) return Result::LOSE;

	return Result::NORMAL;
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
