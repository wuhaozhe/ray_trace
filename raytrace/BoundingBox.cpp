#include "BoundingBox.h"
#include "PhongModel.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

void BoundingBox::init()
{
	object_type = Object_type::_BoundingBox;
}

BoundingBox::BoundingBox() : min_point(0, 0, 0), max_point(50, 50, 50)
{
	init();
}
BoundingBox::BoundingBox(vector3<double> in_min_point, vector3<double> in_max_point) : min_point(in_min_point), max_point(in_max_point)
{
	init();
}
BoundingBox::~BoundingBox()
{
}

bool BoundingBox::contain(vector3<double> input)
{
	if (input.x < max_point.x + limit_zero && input.y < max_point.y + limit_zero && input.z < max_point.z + limit_zero)
	{
		if (input.x > min_point.x - limit_zero && input.y > min_point.y - limit_zero && input.z > min_point.z - limit_zero)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool BoundingBox::intersect(Ray input_ray, vector3<double> &intersect_point, double &in_t_min, double &in_t_max)
{
	double tx_min, ty_min, tz_min, tx_max, ty_max, tz_max;
	if (fabs(input_ray.direction.x) < limit_zero)
	{
		tx_min = std::numeric_limits<double>::min();
		tx_max = std::numeric_limits<double>::max();
		if (input_ray.start_point.x < (min_point.x - limit_zero) || input_ray.start_point.x >(max_point.x + limit_zero))
		{
			return false;
		}
	}
	else
	{
		double tx1 = (min_point.x - input_ray.start_point.x) / input_ray.direction.x;             //与x面交点的t值
		double tx2 = (max_point.x - input_ray.start_point.x) / input_ray.direction.x;             //与另一x面交点的t值
		tx_min = std::min(tx1, tx2);
		tx_max = std::max(tx1, tx2);
	}
	if (fabs(input_ray.direction.y) < limit_zero)
	{
		ty_min = std::numeric_limits<double>::min();
		ty_max = std::numeric_limits<double>::max();
		if (input_ray.start_point.y < (min_point.y - limit_zero) || input_ray.start_point.y >(max_point.y + limit_zero))
		{
			return false;
		}
	}
	else
	{
		double ty1 = (min_point.y - input_ray.start_point.y) / input_ray.direction.y;
		double ty2 = (max_point.y - input_ray.start_point.y) / input_ray.direction.y;
		ty_min = std::min(ty1, ty2);
		ty_max = std::max(ty1, ty2);
	}
	if (fabs(input_ray.direction.z) < limit_zero)
	{
		tz_min = std::numeric_limits<double>::min();
		tz_max = std::numeric_limits<double>::max();
		if (input_ray.start_point.z < (min_point.z - limit_zero) || input_ray.start_point.z >(max_point.z + limit_zero))
		{
			return false;
		}
	}
	else
	{
		double tz1 = (min_point.z - input_ray.start_point.z) / input_ray.direction.z;
		double tz2 = (max_point.z - input_ray.start_point.z) / input_ray.direction.z;
		tz_min = std::min(tz1, tz2);
		tz_max = std::max(tz1, tz2);
	}
	double t_min = std::max(tx_min, std::max(ty_min, tz_min)), t_max = std::min(tx_max, std::min(ty_max, tz_max));
	if (t_min <= t_max + limit_zero)
	{
		in_t_min = t_min;
		in_t_max = t_max;
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

bool BoundingBox::intersect(Ray input_ray, vector3<double> &intersect_point)       //woo算法
{
	double temp_a, temp_b;
	return intersect(input_ray, intersect_point, temp_a, temp_b);
}

Color BoundingBox::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)
{
	light.direction = (target_pos - light.start_point).normallize();
	in = get_normalvec(target_pos, view_direction);
	return PhongModel::reflect_color(light, in, view_direction, feature);
}

vector3<double> BoundingBox::get_normalvec(vector3<double> target_pos, vector3<double> view_direction)
{
	if (fabs(target_pos.x - min_point.x) < limit_zero)
	{
		return vector3<double>(-1, 0, 0);
	}
	else if (fabs(target_pos.x - max_point.x) < limit_zero)
	{
		return vector3<double>(1, 0, 0);
	}
	else if (fabs(target_pos.y - min_point.y) < limit_zero)
	{
		return vector3<double>(0, -1, 0);
	}
	else if (fabs(target_pos.y - max_point.y) < limit_zero)
	{
		return vector3<double>(0, 1, 0);
	}
	else if (fabs(target_pos.z - min_point.z) < limit_zero)
	{
		return vector3<double>(0, 0, 1);
	}
	else if (fabs(target_pos.z - max_point.z) < limit_zero)
	{
		return vector3<double>(0, 0, -1);
	}
}

bool BoundingBox::sphere_aabb_overlap(vector3<double> sphere_center, double radius, vector3<double> in_min_point, vector3<double> in_max_point)
{
	double d = 0;
	double temp1[3] = { sphere_center.x, sphere_center.y, sphere_center.z };
	double temp2[3] = { in_min_point.x, in_min_point.y, in_min_point.z };
	double temp3[3] = { in_max_point.x, in_max_point.y, in_max_point.z };
	for (int i = 0; i < 3; i++)
	{
		if (temp1[i] < temp2[i])
		{
			d += (temp1[i] - temp2[i]) * (temp1[i] - temp2[i]);
		}
		else if (temp1[i] > temp3[i])
		{
			d += (temp1[i] - temp3[i]) * (temp1[i] - temp3[i]);
		}
	}
	if (d <= radius * radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BoundingBox::plane_aabb_overlap(double a, double b, double c, double d, vector3<double> in_min_point, vector3<double> in_max_point)
{
	vector3<double> center = (in_max_point + in_min_point) / 2;
	vector3<double> extents = in_max_point - center;
	double r = extents.x * fabs(a) + extents.y * fabs(b) + extents.z * fabs(c);
	double s = fabs(center.x * a + center.y * b + center.z * c + d);
	return s <= r + limit_zero;
}
bool BoundingBox::aabb_overlap_1d(double x_min1, double x_max1, double x_min2, double x_max2)
{
	if (x_max1 + limit_zero >= x_min2 && x_max2 + limit_zero >= x_min1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool BoundingBox::aabb_aabb_overlap(vector3<double> min_point1, vector3<double> max_point1, vector3<double> min_point2, vector3<double> max_point2)
{
	if (aabb_overlap_1d(min_point1.x, max_point1.x, min_point2.x, max_point2.x) && aabb_overlap_1d(min_point1.y, max_point1.y, min_point2.y, max_point2.y) &&
		aabb_overlap_1d(min_point1.z, max_point1.z, min_point2.z, max_point2.z))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BoundingBox::triangle_aabb_overlap(vector3<double> a, vector3<double> b, vector3<double> c, vector3<double> in_min_point, vector3<double> in_max_point)
{
	double p0, p1, p2, r, three_max, three_min;
	//center and extents of AABoundingBox
	vector3<double> center = (in_max_point + in_min_point) / 2;
	vector3<double> extents = in_max_point - center;

	//Translate triangle as conceptually moving AABB to origin
	vector3<double> v0 = a - center;
	vector3<double> v1 = b - center;
	vector3<double> v2 = c - center;

	//compute edge vectors for triangle
	vector3<double> f0 = v1 - v0;
	vector3<double> f1 = v2 - v1;
	vector3<double> f2 = v0 - v2;

	//test axes a00..a2(category 3)
	vector3<double> a00(0, -1 * f0.z, f0.y);
	vector3<double> a01(0, -1 * f1.z, f1.y);
	vector3<double> a02(0, -1 * f2.z, f2.y);
	vector3<double> a10(f0.z, 0, -1 * f0.x);
	vector3<double> a11(f1.z, 0, -1 * f1.x);
	vector3<double> a12(f2.z, 0, -1 * f2.x);
	vector3<double> a20(-1 * f0.y, f0.x, 0);
	vector3<double> a21(-1 * f1.y, f1.x, 0);
	vector3<double> a22(-1 * f2.y, f2.x, 0);

	//test axis a00
	p0 = v0 * a00;
	p1 = v1 * a00;
	p2 = v2 * a00;
	r = extents.y * fabs(f0.z) + extents.z * fabs(f0.y);
	three_max = max(p0, max(p1, p2));
	three_min = min(p0, min(p1, p2));
	if (max(-1 * three_max, three_min) > r + limit_zero)
	{
		return false;
	}

	//test axis a01
	p0 = v0 * a01;
	p1 = v1 * a01;
	p2 = v2 * a01;
	r = extents.y * fabs(f1.z) + extents.z * fabs(f1.y);
	three_max = max(p0, max(p1, p2));
	three_min = min(p0, min(p1, p2));
	if (max(-1 * three_max, three_min) > r + limit_zero)
	{
		return false;
	}

	//test axis a02
	p0 = v0 * a02;
	p1 = v1 * a02;
	p2 = v2 * a02;
	r = extents.y * fabs(f2.z) + extents.z * fabs(f2.y);
	three_max = max(p0, max(p1, p2));
	three_min = min(p0, min(p1, p2));
	if (max(-1 * three_max, three_min) > r + limit_zero)
	{
		return false;
	}

	//test axis a10;
	p0 = v0 * a10;
	p1 = v1 * a10;
	p2 = v2 * a10;
	r = extents.x * fabs(f0.z) + extents.z * fabs(f0.x);
	three_max = max(p0, max(p1, p2));
	three_min = min(p0, min(p1, p2));
	if (max(-1 * three_max, three_min) > r + limit_zero)
	{
		return false;
	}

	//test axis a11
	p0 = v0 * a11;
	p1 = v1 * a11;
	p2 = v2 * a11;
	r = extents.x * fabs(f1.z) + extents.z * fabs(f1.x);
	three_max = max(p0, max(p1, p2));
	three_min = min(p0, min(p1, p2));
	if (max(-1 * three_max, three_min) > r + limit_zero)
	{
		return false;
	}

	//test axis a12
	p0 = v0 * a12;
	p1 = v1 * a12;
	p2 = v2 * a12;
	r = extents.x * fabs(f2.z) + extents.z * fabs(f2.x);
	three_max = max(p0, max(p1, p2));
	three_min = min(p0, min(p1, p2));
	if (max(-1 * three_max, three_min) > r + limit_zero)
	{
		return false;
	}

	//test axis a20
	p0 = v0 * a20;
	p1 = v1 * a20;
	p2 = v2 * a20;
	r = extents.x * fabs(f0.y) + extents.y * fabs(f0.x);
	three_max = max(p0, max(p1, p2));
	three_min = min(p0, min(p1, p2));
	if (max(-1 * three_max, three_min) > r + limit_zero)
	{
		return false;
	}

	//test axis a21
	p0 = v0 * a21;
	p1 = v1 * a21;
	p2 = v2 * a21;
	r = extents.x * fabs(f1.y) + extents.y * fabs(f1.x);
	three_max = max(p0, max(p1, p2));
	three_min = min(p0, min(p1, p2));
	if (max(-1 * three_max, three_min) > r + limit_zero)
	{
		return false;
	}

	//test axis a22
	p0 = v0 * a22;
	p1 = v1 * a22;
	p2 = v2 * a22;
	r = extents.x * fabs(f2.y) + extents.y * fabs(f2.x);
	three_max = max(p0, max(p1, p2));
	three_min = min(p0, min(p1, p2));
	if (max(-1 * three_max, three_min) > r + limit_zero)
	{
		return false;
	}

	//test the threeaxes corresponding to the face normals of AABB b(category 1)
	if (max(v0.x, max(v1.x, v2.x)) - limit_zero < -1 * extents.x || min(v0.x, min(v1.x, v2.x)) + limit_zero > extents.x)
	{
		return false;
	}
	if (max(v0.y, max(v1.y, v2.y)) - limit_zero < -1 * extents.y || min(v0.y, min(v1.y, v2.y)) + limit_zero > extents.y)
	{
		return false;
	}
	if (max(v0.z, max(v1.z, v2.z)) - limit_zero < -1 * extents.z || min(v0.z, min(v1.z, v2.z)) + limit_zero > extents.z)
	{
		return false;
	}

	//caculate the plane
	double temp_a = (b.y - a.y) * (c.z - a.z) - (b.z - a.z) * (c.y - a.y);
	double temp_b = (b.z - a.z) * (c.x - a.x) - (b.x - a.x) * (c.z - a.z);
	double temp_c = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	double temp_d = 0 - (temp_a * a.x + temp_b * a.y + temp_c * a.z);
	return plane_aabb_overlap(temp_a, temp_b, temp_c, temp_d, in_min_point, in_max_point);
}

BoundingBox Merge_BoundingBox(const BoundingBox &box1, const BoundingBox &box2)
{
	vector3<double> Min_point;
	vector3<double> Max_point;
	Min_point.x = min(box1.min_point.x, box2.min_point.x);
	Min_point.y = min(box1.min_point.y, box2.min_point.y);
	Min_point.z = min(box1.min_point.z, box2.min_point.z);
	Max_point.x = max(box1.max_point.x, box2.max_point.x);
	Max_point.y = max(box1.max_point.y, box2.max_point.y);
	Max_point.z = max(box1.max_point.z, box2.max_point.z);
	return BoundingBox(Min_point, Max_point);
}