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
	n = 0;
}

Plane::~Plane()
{
}

void Plane::init()
{
	object_type = Object_type::_Plane;
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
		if (t < limit_zero)
		{
			return false;
		}
		else
		{
			intersect_point = input_ray.start_point + input_ray.direction * t;
			return true;
		}
	}
}

double Plane::signed_distance(Ray input_ray)
{
	double denominator = input_ray.direction * normal_vector;
	if (fabs(denominator) < limit_zero)
	{
		return std::numeric_limits<double>::infinity();
	}
	else
	{
		double numerator = input_ray.start_point * normal_vector + D;
		double t = (-1 * numerator) / denominator;
		return t;            //标准化的直线参数方程中,t即为距离
	}
}

object_feature Plane::get_feature(vector3<double> target_pos)
{
	if (has_texture)
	{
		//返回纹理对应的颜色
		vector3<double> relative = target_pos - min_point;           //到最小点的相对位置
		double temp_u_length = relative * u_direction;
		double temp_v_length = relative * v_direction;
		double u = temp_u_length / u_length;
		double v = temp_v_length / v_length;
		int u_point = (double)texture.width * u;
		int v_point = (double)texture.height * (1 - v) - 1;
		Color temp_color = texture.color_image[v_point * texture.width + u_point];
		object_feature temp_feature(feature);
		temp_feature.reflect_blue = (double)temp_color.b / 255.0;
		temp_feature.reflect_green = (double)temp_color.g / 255.0;
		temp_feature.reflect_red = (double)temp_color.r / 255.0;
		return temp_feature;
	}
	else
	{
		return feature;
	}
}

Color Plane::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)
{
	light.direction = (target_pos - light.start_point).normallize();
	in = normal_vector.normallize();
	return PhongModel::reflect_color(light, normal_vector, view_direction, get_feature(target_pos));
}

vector3<double> Plane::get_normalvec(vector3<double> target_pos, vector3<double> view_direction)
{
	return normal_vector.normallize();
}