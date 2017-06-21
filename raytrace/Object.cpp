#include "Object.h"



Object::Object()
{
	reflect_coefficient = 0;
	refract_coefficient = 0;
}

object_feature Object::get_feature(vector3<double> target_pos)
{
	return feature;
}

Object::~Object()
{
}