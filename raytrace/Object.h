#pragma once
#include "Point.h"
#include "Ray.h"
#include "drawer.h"
class Object
{
protected:
	enum Object_type
	{
		Plane, Triangle, Polygon, Sphere, Box
	};
	virtual void init() = 0;
public:
	virtual bool intersect(Ray input_ray, vector3<double> &intersect_point) = 0;             //求交点
	virtual Color get_color(vector3<double> target_pos, vector3<double> view_direction, Light light) = 0;                  //根据光照模型获取target_pos上的颜色，view_direction是视点方向
	Object_type object_type;
	Object();
	Material_feature color_feature;
	~Object();
};

