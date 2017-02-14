#include "car.h"
#include "Constants.h"
#include <iostream>
using namespace cimg_library;

int Car::getX(){ return m_X; }
int Car::getY(){ return m_Y; }
int Car::getWidth(){ return m_Width; }
int Car::getHeight(){ return m_Height; }
CImg<> Car::getData(){ return m_Data; }

void Car::setX(int x){ m_X = x; }
void Car::setY(int y){ m_Y = y; }
void Car::setWidth(int width){ m_Width = width; }
void Car::setHeight(int height){ m_Height = height; }
void Car::setData(CImg<> data){ m_Data = data; }

void Car::createSharp(){
	m_Data.assign(m_Width, m_Height, 1, 3, 0);
	m_Data.draw_circle(m_Width / 6, m_Height / 6, m_Width / 6 - 1, Color::Red);
	m_Data.draw_circle(5*m_Width / 6, m_Height / 6, m_Width / 6 - 1, Color::Red);
	m_Data.draw_circle(m_Width / 6, 5*m_Height / 6, m_Width / 6 - 1, Color::Red);
	m_Data.draw_circle(5*m_Width / 6, 5*m_Height / 6, m_Width / 6 - 1, Color::Red);
	m_Data.draw_rectangle(m_Width / 6, m_Height / 6, 5 * m_Width / 6, 5 * m_Height / 6, Color::Blue);
	m_Data.draw_line(m_Width / 2, m_Height/6, m_Width / 2, 5*m_Height / 6, Color::Yellow);
}
