#include "snake.h"

Snake::Snake(std::vector<Dot> body, Status status){
	m_Body = body;
	m_Status = status;
}

std::vector<Dot>& Snake::getBody(){ return m_Body; }
Status Snake::getStatus(){ return m_Status; }

void Snake::setBody(std::vector<Dot> body){ m_Body = body; }
void Snake::setStatus(Status status){ m_Status = status; }

void Snake::addDot(Dot dot){
	m_Body.push_back(dot);
}

void Snake::display(){
	for (unsigned int iii = 0; iii < m_Body.size(); iii++){
		m_Body[iii].display();
	}
}