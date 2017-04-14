#pragma once
#include "Object.h"
#include "Point.h"
class BoundingBox : public Object                //��������ƽ�е�boundingbox
{
private:
	void init();
public:
	vector3<double> length, start_point;             //length������ά��Ϊ����ߣ�start_pointΪ����ά����������С�ĵ�
	BoundingBox();
	BoundingBox(vector3<double> input_length, vector3<double> input_point);
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);
	~BoundingBox();
};

