#include "Triangle.h"



Triangle::Triangle()
{
	init();
}


Triangle::~Triangle()
{
}

void Triangle::init()
{
	object_type = Object_type::Triangle;
}

Triangle::Triangle(vector3<double> vertex1, vector3<double> vertex2, vector3<double> vertex3)
{
	init();
	vertex[0] = vertex1;
	vertex[1] = vertex2;
	vertex[2] = vertex3;
}

bool Triangle::intersect(Ray input_ray, vector3<double> &intersect_point)
{

}