#include "Sphere.h"


void Sphere::init()
{
	object_type = Object_type::Sphere;
}
Sphere::Sphere()
{
	init();
}
Sphere::Sphere(vector3<double> input_center, double input_radius): sphere_center(input_center), radius(input_radius)
{
	init();
	color_feature.Kdr = 0.2;
	color_feature.Ksr = 0.75;
}

Sphere::~Sphere()
{
}