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
	double opacity = 0.5;                      //透明度，【0-1】，为0时认为是不透明的，为1时认为是透明的，透明度使得光穿过该物体时有光强的损耗
	bool reflective, refractive;                  //是否可反射，是否可折射
	double reflect_coefficient, refract_coefficient;         //反射系数，折射系数
	~Object();
};

