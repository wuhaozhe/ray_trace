#include "BoundingBox.h"
#include "PhongModel.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

void BoundingBox::init()
{
	object_type = Object_type::BoundingBox;
}

BoundingBox::BoundingBox(): length(std::numeric_limits<double>::min(), std::numeric_limits<double>::min(), std::numeric_limits<double>::min()), 
start_point(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity())
{
	init();
}
BoundingBox::BoundingBox(vector3<double> input_length, vector3<double> input_point) : length(input_length), start_point(input_point)
{
	init();
	color_feature.Kdr = 0.3;
	color_feature.Ksr = 0.65;
	color_feature.Kar = 0.05;
}
BoundingBox::~BoundingBox()
{
}

bool BoundingBox::intersect(Ray input_ray, vector3<double> &intersect_point)       //woo算法
{
	double tx1, tx2, ty1, ty2, tz1, tz2;
	double tx_min, ty_min, tz_min, tx_max, ty_max, tz_max;
	if (fabs(input_ray.direction.x) < limit_zero)
	{
		tx_min = std::numeric_limits<double>::min();
		tx_max = std::numeric_limits<double>::max();
		if (input_ray.start_point.x < (start_point.x - limit_zero) || input_ray.start_point.x > (start_point.x + length.x + limit_zero))
		{
			return false;
		}
	}
	else
	{
		double tx1 = (start_point.x - input_ray.start_point.x) / input_ray.direction.x;             //与x面交点的t值
		double tx2 = (start_point.x + length.x - input_ray.start_point.x) / input_ray.direction.x;             //与另一x面交点的t值
		tx_min = std::min(tx1, tx2);
		tx_max = std::max(tx1, tx2);
	}
	if (fabs(input_ray.direction.y) < limit_zero)
	{
		ty_min = std::numeric_limits<double>::min();
		ty_max = std::numeric_limits<double>::max();
		if (input_ray.start_point.y < (start_point.y - limit_zero) || input_ray.start_point.y > (start_point.y + length.y + limit_zero))
		{
			return false;
		}
	}
	else
	{
		double ty1 = (start_point.y - input_ray.start_point.y) / input_ray.direction.y;
		double ty2 = (start_point.y + length.y - input_ray.start_point.y) / input_ray.direction.y;
		ty_min = std::min(ty1, ty2);
		ty_max = std::max(ty1, ty2);
	}
	if (fabs(input_ray.direction.z) < limit_zero)
	{
		tz_min = std::numeric_limits<double>::min();
		tz_max = std::numeric_limits<double>::max();
		if (input_ray.start_point.z < (start_point.z - limit_zero) || input_ray.start_point.z >(start_point.z + length.z + limit_zero))
		{
			return false;
		}
	}
	else
	{
		double tz1 = (start_point.z - input_ray.start_point.z) / input_ray.direction.z;
		double tz2 = (start_point.z + length.z - input_ray.start_point.z) / input_ray.direction.z;
		tz_min = std::min(tz1, tz2);
		tz_max = std::max(tz1, tz2);
	}
	double t_min = std::max(tx_min, std::max(ty_min, tz_min)), t_max = std::min(tx_max, std::min(ty_max, tz_max));
	if (t_min <= t_max)
	{
		if (t_min >= -1 * limit_zero)
		{
			intersect_point = input_ray.start_point + input_ray.direction * t_min;             //求得最近的交点
			return true;
		}
		else if (t_max >= -1 * limit_zero)
		{
			intersect_point = input_ray.start_point + input_ray.direction * t_max;             //求得最近的交点
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

Color BoundingBox::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)
{
	light.direction = (target_pos - light.start_point).normallize();
	if (fabs(target_pos.x - start_point.x) < limit_zero)
	{
		in = vector3<double>(-1, 0, 0);
	}
	else if (fabs(target_pos.x - length.x - start_point.x) < limit_zero)
	{
		in = vector3<double>(1, 0, 0);
	}
	else if (fabs(target_pos.y - start_point.y) < limit_zero)
	{
		in = vector3<double>(0, -1, 0);
	}
	else if (fabs(target_pos.y - length.y - start_point.y) < limit_zero)
	{
		in = vector3<double>(0, 1, 0);
	}
	else if (fabs(target_pos.z - start_point.z) < limit_zero)
	{
		in = vector3<double>(0, 0, 1);
	}
	else if (fabs(target_pos.z - length.z - start_point.z) < limit_zero)
	{
		in = vector3<double>(0, 0, -1);
	}
	return PhongModel::reflect_color(light, in, view_direction, color_feature);
}