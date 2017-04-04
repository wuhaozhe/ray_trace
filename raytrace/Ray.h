#pragma once
#include "Point.h"
#include "drawer.h"
class Ray                                  //光线类型
{
public:
	vector3<double> start_point;             //起始点
	vector3<double> direction;                //方向
	Ray(vector3<double> input_point, vector3<double> input_direction);
	virtual ~Ray();
};

class Light : public Ray
{
public:
	double intensity;           //光强
	Color color;
	Light(vector3<double> input_point, vector3<double> input_direction, double input_intensity, Color in_color) : Ray(input_point, input_direction)
	{
		intensity = input_intensity;
		color = in_color;
	}
	~Light()
	{

	}
};
struct Material_feature      //物体表面的一些反射系数
{
	double Kdr = 0, Kdg = 0, Kdb = 0;             //漫反射系数
	double Ksr = 0, Ksg = 0, Ksb = 0;             //镜面反射系数
	double Kar = 0, Kag = 0, Kab = 0;             //环境光反射系数
};