#include "Ray.h"



Ray::Ray(vector3<double> input_point, vector3<double> input_direction)
{
	start_point = input_point;
	direction = input_direction.normallize();
}


Ray::~Ray()
{
}
