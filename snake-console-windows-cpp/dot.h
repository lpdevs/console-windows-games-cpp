#ifndef _DOT_H
#define _DOT_H
#include "Constants.h"
#include "console.h"

class Dot{
private:
	int m_X, m_Y;
	int m_Color;
	char m_Symbol;
public:
	Dot(int x = 0, int y = 0, int color = default_ColorCode, char symbol = ASCII::ch_default) // (0,0), gray, *
	{
		m_X = x;
		m_Y = y;
		m_Color = color;
		m_Symbol = symbol;
	}
	~Dot(){}

	int getX();
	int getY();
	int getColor();
	char getSymbol();

	void setX(int x);
	void setY(int y);
	void setColor(int color);
	void setSymbol(char symbol);

	void display();

	Dot& operator=(const Dot &dot);
};

#endif