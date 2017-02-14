#include "fruit.h"
#include "console.h"
#include <iostream>

int Fruit::getX(){ return m_X; }
int Fruit::getY(){ return m_Y; }
int Fruit::getColor(){ return m_Color; }
char Fruit::getSymbol(){ return m_Symbol; }

void Fruit::setX(int x){ m_X = x; }
void Fruit::setY(int y){ m_Y = y; }
void Fruit::setColor(int color){ m_Color = color; }
void Fruit::setSymbol(char symbol){ m_Symbol = symbol; }

void Fruit::display(){
	gotoXY(m_X, m_Y);
	TextColor(m_Color);
	std::cout << m_Symbol;
}