#ifndef _GSNAKE_H
#define _GSNAKE_H
#include "snake.h"

class GSnake{
private:
	Snake snake;
	int timeSleepMS;
public:
	GSnake();
	~GSnake(){}

	Snake getSnake();
	int getTimeSleepMS();

	void setSnake();
	void setTimeSleepMS();

	void display();
	void control();
	void resolve();

};

#endif