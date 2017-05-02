#pragma once
#include "Object.h"
class Beizer_Rotate_Object :public Object      //��Ӧ�����߱�����X-Zƽ����
{
private:
	void init();
public:
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);   //inΪ������������
	Beizer_Rotate_Object(vector3<double> point_array[]);       //Ĭ��Ϊ3��Beizer����
	~Beizer_Rotate_Object();
};

