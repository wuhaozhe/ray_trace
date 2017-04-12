#pragma once
#include "drawer.h"
#include "Point.h"
#include "Ray.h"
class PhongModel
{
public:
	static int reflect_parameter;
	static Color reflect_color(Single_Light light, vector3<double> normal_vector, vector3<double> view_direction, Material_feature feature);
	PhongModel();
	~PhongModel();
};

