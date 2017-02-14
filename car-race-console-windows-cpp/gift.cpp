#include "gift.h"
#include "console.h"
using namespace cimg_library;

void Gift::setX(int x){ m_X = x; }
void Gift::setY(int y){ m_Y = y; }
void Gift::setType(int type){ m_Type = type; }
void Gift::setWidth(int width){ m_Width = width; }
void Gift::setHeight(int height){ m_Height = height; }
void Gift::setData(CImg<> data){ m_Data = data; }

int Gift::getX(){ return m_X; }
int Gift::getY(){ return m_Y; }
int Gift::getType(){ return m_Type; }
int Gift::getWidth(){ return m_Width; }
int Gift::getHeight(){ return m_Height; }
CImg<> Gift::getData(){ return m_Data; }

void Gift::createSharp()
{
	switch (m_Type){
	case type_gift::MONEY:
		m_Data.assign(m_Width, m_Height, 1, 3, 0);
		m_Data.draw_line(m_Width / 2, 0, m_Width / 2, m_Height, Color::Yellow);
		m_Data.draw_line(m_Width / 2 - 1, 0, m_Width / 2 - 1, m_Height, Color::Yellow);
		m_Data.draw_line(m_Width / 2 + 1, 0, m_Width / 2 + 1, m_Height, Color::Yellow);
		m_Data.draw_text(m_Width / 2 , m_Height / 2, "S", Color::Yellow);
		break;
	case type_gift::HEART:
		m_Data.assign(m_Width, m_Height, 1, 3, 0);
		m_Data.draw_rectangle(0, 0, m_Width, m_Height, Color::Red);
		break;
	case type_gift::FAST:
		m_Data.assign(m_Width, m_Height, 1, 3, 0);
		m_Data.draw_rectangle(0, 0, m_Width, m_Height, Color::Blue);
		break;
	case type_gift::SLOW:
		m_Data.assign(m_Width, m_Height, 1, 3, 0);
		m_Data.draw_rectangle(0, 0, m_Width, m_Height, Color::Green);
		break;
	default:
		m_Data.assign(m_Width, m_Height, 1, 3, 0);
		m_Data.draw_rectangle(0, 0, m_Width, m_Height, Color::Black);
		break;
	}
	
}
