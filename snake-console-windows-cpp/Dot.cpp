#include "dot.h"
#include "console.h"
#include <iostream>
int Dot::getX(){ return m_X; }
int Dot::getY(){ return m_Y; }
int Dot::getColor(){ return m_Color; }
char Dot::getSymbol(){ return m_Symbol; }

void Dot::setX(int x){ m_X = x; }
void Dot::setY(int y){ m_Y = y; }
void Dot::setColor(int color){ m_Color = color; }
void Dot::setSymbol(char symbol){ m_Symbol = symbol; }

void Dot::display(){
	gotoXY(m_X, m_Y);
	TextColor(m_Color);
	std::cout << m_Symbol;
}

Dot& Dot::operator=(const Dot &dot)
{
	m_X = dot.m_X;
	m_Y = dot.m_Y;
	m_Color = dot.m_Color;
	m_Symbol = dot.m_Symbol;
	return *this;
}
