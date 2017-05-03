#pragma once
#include "Object.h"
#include "Point.h"
class BoundingBox : public Object                //与坐标轴平行的boundingbox
{
private:
	void init();
	static bool aabb_overlap_1d(double x_min1, double x_max1, double x_min2, double x_max2);
public:
	vector3<double> min_point, max_point;             //length的三个维度为长宽高，start_point为三个维度上坐标最小的点
	BoundingBox();
	BoundingBox(vector3<double> in_min_point, vector3<double> in_max_point);
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	bool intersect(Ray input_ray, vector3<double> &intersect_point, double &in_t_min, double &in_t_max);
	bool contain(vector3<double> input);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);

	//判断aabb与各种物体是否有重叠
	static bool sphere_aabb_overlap(vector3<double> sphere_center, double radius, vector3<double> in_min_point, vector3<double> in_max_point);
	static bool plane_aabb_overlap(double a, double b, double c, double d, vector3<double> in_min_point, vector3<double> in_max_point);       //a, b, c, d is ax + by + cz + d = 0
	static bool aabb_aabb_overlap(vector3<double> min_point1, vector3<double> max_point1, vector3<double> min_point2, vector3<double> max_point2);
	static bool triangle_aabb_overlap(vector3<double> a, vector3<double> b, vector3<double> c, vector3<double> in_min_point, vector3<double> in_max_point);    //a, b, c is triangle vertex
	~BoundingBox();
};

BoundingBox Merge_BoundingBox(const BoundingBox &box1, const BoundingBox &box2);