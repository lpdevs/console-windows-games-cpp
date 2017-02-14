#ifndef _CAR_H
#define _CAR_H
#include "Constants.h"
#include "CImg.h"

using namespace cimg_library;

class Car
{
private:
	int m_X, m_Y;
	int m_Width, m_Height;
	CImg<> m_Data;
public:
	Car(int width = SizeCar::WIDTH,int height = SizeCar::HEIGHT, int x = Board::WIDTH / 2, int y = Board::HEIGHT - SizeCar::HEIGHT/2){
		m_Width = width;
		m_Height = height;
		m_X = x;
		m_Y = y;
	}
	~Car(){}
	
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	CImg<> getData();

	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
	void setData(CImg<> data);

	void createSharp();
};

#endif