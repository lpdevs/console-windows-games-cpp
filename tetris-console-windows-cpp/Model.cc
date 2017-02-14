#include "Model.h"

Model::Model()
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			Matrix[i][j] = 0;

	Row = Col = 0;
	x = y = 0;
	id = -1;
}

void Model::SetShape(int _id)
{
	id = _id;

	switch(id)
	{
	case 0:
		// ** 
		// **
		Row = 2;
		Col = 2;
		Matrix[0][0] = Matrix[0][1] = Matrix[1][0] = Matrix[1][1] = 1;
		break;

	case 1:
		// *
		// *
		// * *
		Row = 3;
		Col = 2;
		Matrix[0][0] = Matrix[1][0] = Matrix[2][0] = Matrix[2][1] = 1;
		break;

	case 2:
		//   *
		//   *
		// * *
		Row = 3;
		Col = 2;
		Matrix[0][1] = Matrix[1][1] = Matrix[2][1] = Matrix[2][0] = 1;
		break;

	case 3:
		// *
		// *
		// *
		// *
		Row = 4;
		Col = 1;
		Matrix[0][0] = Matrix[1][0] = Matrix[2][0] = Matrix[3][0] = 1;
		break;

	case 4:
		// *
		// * *
		//   *
		Row = 3;
		Col = 2;
		Matrix[0][0] = Matrix[1][0] = Matrix[1][1] = Matrix[2][1] = 1;
		break;

	case 5:
		//   *
		// * *
		// *
		Row = 3;
		Col = 2;
		Matrix[0][1] = Matrix[1][0] = Matrix[1][1] = Matrix[2][0] = 1;
		break;
	case 6:
		//   *
		// * * *
		Row = 2;
		Col = 3;
		Matrix[0][1] = Matrix[1][0] = Matrix[1][1] = Matrix[1][2] = 1;
		break;

	default:
		break;
	}
}
