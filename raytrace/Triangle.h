#pragma once
#include "Object.h"
class Triangle: public Object
{
private:
	void init();
public:
	vector3<double> vertex[3];           //三角形的三个顶点
	Triangle();
	Triangle(vector3<double> vertex1, vector3<double> vertex2, vector3<double> vertex3);
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	Color get_color(vector3<double> target_pos, vector3<double> view_direction, Light light);
	~Triangle();
};

