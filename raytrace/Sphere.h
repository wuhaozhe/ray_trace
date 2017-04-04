#pragma once
#include "Object.h"
#include "Point.h"
class Sphere:public Object
{
private:
	void init();
public:
	vector3<double> sphere_center;         //ÇòÐÄ
	double radius;                        //°ë¾¶
	Sphere();
	Sphere(vector3<double> input_center, double input_radius);
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	Color get_color(vector3<double> target_pos, vector3<double> view_direction, Light light);
	~Sphere();
};