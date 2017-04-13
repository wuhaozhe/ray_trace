#include "Beizer_Surface.h"





Beizer_Surface::~Beizer_Surface()
{
	for (int i = 0; i < line; i++)
	{
		delete[] controlled_points[i];
	}
	delete[] controlled_points;
}


Beizer_Surface::Beizer_Surface(int input_line, int input_row): line(input_line), row(input_row)
{
	controlled_points = new vector3<double>*[line];
	for (int i = 0; i < line; i++)
	{
		controlled_points[i] = new vector3<double>[row];
	}
}

void Beizer_Surface::set_control_point(int x, int y, vector3<double> input)
{
	controlled_points[x][y] = input;
}