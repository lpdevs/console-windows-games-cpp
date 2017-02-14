#ifndef _CONSTANTS_H
#define _CONSTANTS_H

enum Status
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum type_gift
{
	MONEY,
	SLOW,
	FAST,
	HEART,
	NOTHING
};

namespace Window
{
	const int HEIGHT = 480;
	const int WIDTH = 640;
}

namespace ASCII
{
	const char ch_default = 42;
	const char ch_face = 1;
	const char ch_heart = 3;
	const char ch_vertical = 179;
	const char ch_enter = 13;
	const char ch_space = 32;
	const char ch_beep = 7;
}

namespace Result
{
	const int NORMAL = 0;
	const int LOSE = -1;
}

namespace Board
{
	const int HEIGHT = 480;
	const int WIDTH = 420;
}

namespace SizeCar
{
	const int HEIGHT = 60;
	const int WIDTH = 60;
}

namespace Color
{
	const unsigned char Black[] = { 0, 0, 0 };
	const unsigned char Red[] = { 255, 0, 0 };
	const unsigned char Green[] = { 0, 255, 0 };
	const unsigned char Blue[] = { 0, 0, 255 };
	const unsigned char White[] = { 255, 255, 255 };
	const unsigned char Yellow[] = { 255, 255, 0 };
	const unsigned char Pink[] = { 255, 0, 255 };
}

#endif