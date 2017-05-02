#pragma once
#include "Object.h"
class Beizer_Rotate_Object :public Object      //对应的曲线必须在X-Z平面上
{
private:
	void init();
public:
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);   //in为法向量的引用
	Beizer_Rotate_Object(vector3<double> point_array[]);       //默认为3次Beizer曲线
	~Beizer_Rotate_Object();
};

