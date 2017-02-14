#ifndef _SNAKE_H
#define _SNAKE_H
#include <vector>
#include "dot.h"
#include "Constants.h"

class Snake{
private:
	std::vector<Dot> m_Body;
	Status m_Status;
public:
	Snake(std::vector<Dot> body, Status status);
	Snake(){}
	~Snake(){}
	
	std::vector<Dot>& getBody();
	Status getStatus();

	void setBody(std::vector<Dot> body);
	void setStatus(Status status);

	void addDot(Dot dot);

	void display();
};

#endif