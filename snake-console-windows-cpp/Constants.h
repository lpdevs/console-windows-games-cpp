#ifndef _CONSTANTS_H
#define _CONSTANTS_H

enum Status
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

namespace Console
{
	const int HEIGHT = 25;
	const int WIDTH	= 80;
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
	const int HEIGHT = 25;
	const int WIDTH = 40;
}

#endif