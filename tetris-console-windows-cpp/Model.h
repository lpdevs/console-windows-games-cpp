#ifndef MODEL_H
#define MODEL_H

class Model
{
public:
	int Matrix[4][4];
	int Row, Col;
	int x, y;
	int id;
	
public:
	Model();
	void SetShape(int _id);
};

#endif
