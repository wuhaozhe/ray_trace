#pragma once
#include "Object.h"
#include "Point.h"
class BoundingBox : public Object                //与坐标轴平行的boundingbox
{
private:
	void init();
public:
	vector3<double> length, start_point;             //length的三个维度为长宽高，start_point为三个维度上坐标最小的点
	BoundingBox();
	BoundingBox(vector3<double> input_length, vector3<double> input_point);
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);
	~BoundingBox();
};

