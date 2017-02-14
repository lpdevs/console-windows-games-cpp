#ifndef _GIFT_H
#define _GIFT_H
#include "Constants.h"
#include "CImg.h"
using namespace cimg_library;

class Gift
{
private:
	int m_X, m_Y;
	int m_Type;
	int m_Width, m_Height;
	CImg<> m_Data;
public:
	Gift(int type = type_gift::MONEY, int width = SizeCar::WIDTH / 2, int height = SizeCar::HEIGHT / 2, int x = 0, int y = 0)
	{
		m_Width = width;
		m_Height = height;
		m_X = x;
		m_Y = y;
		m_Type = type;
	}

	~Gift(){}

	void setX(int x);
	void setY(int y);
	void setType(int type);
	void setWidth(int width);
	void setHeight(int height);
	void setData(CImg<> data);

	
	int getX();
	int getY();
	int getType();
	int getWidth();
	int getHeight();
	CImg<> getData();

	void createSharp();

};

#endif