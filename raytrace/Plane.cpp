#include "Plane.h"
#include "PhongModel.h"
#include <iostream>
using namespace std;


Plane::Plane()
{
	init();
	A = 0, B = 0, C = 0, D = 0;
}
Plane::Plane(vector3<double> in_point, vector3<double> input_normal_vector)
{
	init();
	passed_point = in_point;
	normal_vector = input_normal_vector.normallize();
	A = normal_vector.x;
	B = normal_vector.y;
	C = normal_vector.z;
	D = -1 * (A * passed_point.x + B * passed_point.y + C * passed_point.z);
	color_feature.Kdg = 0.2;
	color_feature.Ksg = 0.5;
	color_feature.Kag = 0.2;
	n = 0;
}

Plane::~Plane()
{
}

void Plane::init()
{
	object_type = Object_type::Plane;
}

bool Plane::intersect(Ray input_ray, vector3<double> &intersect_point)
{
	double denominator = input_ray.direction * normal_vector;
	double numerator = input_ray.start_point * normal_vector + D;
	if (fabs(denominator) <= limit_zero)              //直线与平面平行
	{
		return false;
	}
	else
	{
		double t = (-1 * numerator) / denominator;
		if (t < 0)
		{
			return false;
		}
		else
		{
			intersect_point = input_ray.start_point + input_ray.direction * t;
			//cout <<"direction"<< input_ray.direction.x << " " << input_ray.direction.y << " " << input_ray.direction.z << endl;
			//cout <<"start"<< input_ray.start_point.x << " " << input_ray.start_point.y << " " << input_ray.start_point.z << endl;
			//cout << "intersect" << intersect_point.x << " " << intersect_point.y << " " << intersect_point.z << endl;
			return true;
		}
	}
}

Color Plane::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Light light, vector3<double> &in)
{
	light.direction = (target_pos - light.start_point).normallize();
	in = normal_vector.normallize();
	return PhongModel::reflect_color(light, normal_vector, view_direction, color_feature);
}