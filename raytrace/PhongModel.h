#pragma once
#include "drawer.h"
#include "Point.h"
#include "Ray.h"
class PhongModel
{
public:
	static int reflect_parameter;
	static double amplify_parameter;
	static Color reflect_color(Single_Light light, vector3<double> normal_vector, vector3<double> view_direction, Material_feature feature);
	static double PhongBRDF(vector3<double> normal_vector, vector3<double> in_direction, vector3<double> view_direction, double pd, double ps);          //反射光和镜面反射光的反射率
	PhongModel();
	~PhongModel();
};