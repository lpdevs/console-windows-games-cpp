#ifndef _FRUIT_H
#define _FRUIT_H
#include "console.h"
#include "Constants.h"

class Fruit{
private:
	int m_X, m_Y;
	int m_Color;
	char m_Symbol;
public:
	Fruit(int x = 10, int y = 10, int color = ColorCode_Red, char symbol = ASCII::ch_heart)
	{
		m_X = x;
		m_Y = y;
		m_Color = color;
		m_Symbol = symbol;
	}
	~Fruit(){}
	
	void setX(int x);
	void setY(int y);
	void setColor(int color);
	void setSymbol(char symbol);

	int getX();
	int getY();
	int getColor();
	char getSymbol();

	void display();
};

#endif 