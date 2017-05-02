#include "Beizer_Rotate_Object.h"



Beizer_Rotate_Object::Beizer_Rotate_Object(vector3<double> point_array[])
{
	
}


Beizer_Rotate_Object::~Beizer_Rotate_Object()
{
}

void Beizer_Rotate_Object::init()
{
	object_type = Object_type::_Beizer_Rotate;
}

bool Beizer_Rotate_Object::intersect(Ray input_ray, vector3<double> &intersect_point)
{
	return true;
}

Color Beizer_Rotate_Object::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)
{
	return Color();
}