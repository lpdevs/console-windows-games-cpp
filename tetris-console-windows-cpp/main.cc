#include "console.h"
#include "Model.h"

#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
using namespace std;

// console 25 x 80

const int MAX_ROW  = 30;
const int MAX_COL  = 20;
const int MAX_TYPE = 7;

const int LEFT    = 4;
const int TOP     = 4;
const int RIGHT   = 15;
const int DOWN    = 23;

const int GO_DOWN  = 0;
const int GO_LEFT  = 1;
const int GO_RIGHT = 2;

int Board[MAX_ROW][MAX_COL], Score, Level = 1;
Model AllModels[MAX_TYPE];
Model *pModel;

void DrawBoard()
{
	for(int i = LEFT; i <= RIGHT; i++)
		for(int j = TOP; j <= DOWN; j++)
        {
            if((j == TOP || j == DOWN) && i > LEFT && i < RIGHT)
            {
                gotoxy(i, j);
				textcolor(GREEN);
				printf("%c",205);
            }

            if((i == LEFT || i == RIGHT) && j > TOP && j < DOWN)
            {
                gotoxy(i, j);
				textcolor(GREEN);
				printf("%c",186);
            }   
        }
        gotoxy(LEFT, TOP);
		textcolor(LIGHTYELLOW);
		printf("%c",201);

		gotoxy(RIGHT, TOP);
		textcolor(LIGHTYELLOW);
		printf("%c",187);

        gotoxy(LEFT, DOWN);
		textcolor(LIGHTYELLOW);
		printf("%c",200);

		gotoxy(RIGHT, DOWN);
		textcolor(LIGHTYELLOW);
		printf("%c",188);

		gotoxy(RIGHT + 2, TOP + 18);
		printf("%s\n", "Tetris vConsole");

		gotoxy(RIGHT + 2, TOP + 19);
		printf("%s\n", "Copyright by Pham Van Lam");
}

void DisplayGame()
{
	for(int y = TOP + 1; y < DOWN; y++)
		for(int x = LEFT + 1; x < RIGHT; x++)
			if(Board[y][x] == 1)
			{
				gotoxy(x, y);
				textcolor(LIGHTWHITE);
				printf("%c", 2);
			}
			else
			{
				gotoxy(x, y);
				textcolor(BLACK);
				printf(" ");
			}

	gotoxy(LEFT, DOWN + 1);
}

void UpdateScore()
{
	textcolor(LIGHTWHITE);

	gotoxy(RIGHT + 2, TOP + 2);
	printf("%s\n", "Score: ");

	gotoxy(RIGHT + 10, TOP + 2);
	printf("%d\n", Score);

	gotoxy(RIGHT + 2, TOP + 4);
	printf("%s\n", "Level: ");

	gotoxy(RIGHT + 10, TOP + 4);
	printf("%d\n", Level);
}

void UpdateCompletedRow(Model *pModel)
{
	int r = pModel->Row + pModel->y - 1;
	while(r >= 0)
	{
		bool check = true;
		for(int j = LEFT + 1; j < RIGHT; j++)
			if(Board[r][j] == 0) 
			{
				check = false;
				break;
			}

		if(check)
		{
			for(int i = r; i > TOP; i--)
				for(int j = LEFT + 1; j < RIGHT; j++)
					Board[i][j] = Board[i-1][j];	

			DisplayGame();

			Score++;
			if(Score % 10 == 0) Level++;
			UpdateScore();
		}
		else r--;
	}
}

void InitShape()
{
	for(int i = 0; i < MAX_TYPE; i++)
		AllModels[i].SetShape(i);
}

int Random(int n)
{
	time_t seconds;
	seconds = time (NULL);
	return (seconds % n);
}

void DrawShape(Model *pModel)
{
	for(int i = 0; i < pModel->Row; i++)
		for(int j = 0; j < pModel->Col; j++)
		{
			int t = pModel->Matrix[i][j];
			if(t == 1) Board[i + pModel->y][j + pModel->x] = t; 
			
			if(i + pModel->y > TOP && t == 1)
			{
				gotoxy(j + pModel->x, i + pModel->y);
				textcolor(LIGHTWHITE);
				printf("%c", 2);
			}
		}
}

void EraseShape(Model *pModel)
{
	for(int i = 0; i < pModel->Row; i++)
		for(int j = 0; j < pModel->Col; j++)
		{
			int t = pModel->Matrix[i][j];
			if(t == 1) Board[i + pModel->y][j + pModel->x] = 0;

			if(i + pModel->y > TOP && t == 1)
			{
				gotoxy(j + pModel->x, i + pModel->y);
				textcolor(BLACK);
				printf(" ");
			}
		}
}

void Go(Model *pModel, int direct)
{
	if(direct == GO_DOWN) pModel->y++;
	else if(direct == GO_LEFT) pModel->x--;
	else if(direct == GO_RIGHT) pModel->x++;
}

bool IsTouch(Model *pModel, int direct)
{
	for(int i = 0; i < pModel->Row; i++)
		for(int j = 0; j < pModel->Col; j++)
		{
			int t = pModel->Matrix[i][j];

			if(t == 1)
			{
				if(direct == GO_DOWN && (i + pModel->y + 1 == DOWN || Board[i + pModel->y + 1][j + pModel->x] == 1)) return true;
				else if(direct == GO_LEFT && (j + pModel->x - 1 == LEFT || Board[i + pModel->y][j + pModel->x - 1] == 1)) return true;
				else if(direct == GO_RIGHT && (j + pModel->x + 1 == RIGHT || Board[i + pModel->y][j + pModel->x + 1] == 1)) return true;
			}
		}

	return false;
}

void Rotate(Model *pModel)
{
	int temp = pModel->Col;
	pModel->Col = pModel->Row;
	pModel->Row = temp;

	int Matrix[4][4];
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			Matrix[i][j] = 0;

	int touch = false;

	for(int i = 0; i < pModel->Row; i++)
		for(int j = 0; j < pModel->Col; j++)
		{
			Matrix[i][j] = pModel->Matrix[pModel->Col - j - 1][i];
			if(Matrix[i][j] == 1)
			{
				if (i + pModel->y >= DOWN ||
					j + pModel->x >= RIGHT||
					j + pModel->x <= LEFT ||
					Board[i + pModel->y][j + pModel->x] == 1) touch = true;
			}
		}

	for(int i = 0; i < pModel->Col; i++)
		for(int j = 0; j < pModel->Row; j++)
			pModel->Matrix[i][j] = 0;

	if(touch == false)
	{
		for(int i = 0; i < pModel->Row; i++)
			for(int j = 0; j < pModel->Col; j++)
				pModel->Matrix[i][j] = Matrix[i][j];
	}
}

void StartGame()
{
	clrscr();
	DrawBoard();

	bool Gameover = false;
	InitShape();

	Score = 0;
	Level = 1;
	UpdateScore();

	while(Gameover == false)
	{
		// random shape
		int id = Random(MAX_TYPE);
		pModel = &AllModels[id];

		// set x, y
		pModel->x = (LEFT + RIGHT) / 2;
		pModel->y = 0;

		// random type
		int t  = Random(4);
		for(int i = 0; i < t; i++)
			Rotate(pModel);

		char choose = ' ';

		// move
		while(true)
		{
			EraseShape(pModel);

			// control
			if(_kbhit())
            {
                choose = toupper(getch());
                switch(choose)
                {
                case 'A':
					if(IsTouch(pModel, GO_LEFT) == false) Go(pModel, GO_LEFT);
                    break;
                case 'D':
					if(IsTouch(pModel, GO_RIGHT) == false) Go(pModel, GO_RIGHT);
                    break;
                case 'S':
                    break;
				case 'W':
					Rotate(pModel);
					break;
                }
            }

			if(IsTouch(pModel, GO_DOWN))
			{
				choose = ' ';
				DrawShape(pModel);
				if(pModel->x <= TOP) Gameover = true;
				break;
			}

			// moving
			Go(pModel, GO_DOWN);
			DrawShape(pModel);

			if(choose != 'S') delay(350 - (Level - 1) * 10);
			else delay(100 - (Level - 1) * 40);
		}

		// process
		UpdateCompletedRow(pModel);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	DrawBoard();

	while(true)
	{
		textcolor(LIGHTWHITE);

		gotoxy(RIGHT + 2, TOP + 5);
		printf(" ");

		gotoxy(RIGHT + 2, TOP + 2);
		printf("%s\n", "Do you want to play the game?");
		
		gotoxy(RIGHT + 2, TOP + 3);
		printf("%s\n", "1. Press 'y' to start");

		gotoxy(RIGHT + 2, TOP + 4);
		printf("%s\n", "2. Press 'n' to exit");

		textcolor(LIGHTYELLOW);

		gotoxy(RIGHT + 2, TOP + 18);
		printf("%s\n", "Tetris vConsole");

		gotoxy(RIGHT + 2, TOP + 19);
		printf("%s\n", "Copyright by Pham Van Lam");

		gotoxy(RIGHT + 2, TOP + 5);
		printf(" ");

		char ch = 'n';
		cin >> ch;
		if(ch == 'y')
		{
			StartGame();
		}
		else if(ch == 'n') break;
	}

	clrscr();
	gotoxy(RIGHT + 2, TOP + 6);

	return 0;
}
