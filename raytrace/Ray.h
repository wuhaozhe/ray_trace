#pragma once
#include "Point.h"
#include "drawer.h"
#include <vector>
#include <iostream>
using namespace std;
class Ray                                  //光线类型
{
public:
	vector3<double> start_point;             //起始点
	vector3<double> direction;                //方向
	Ray(vector3<double> input_point, vector3<double> input_direction);
	virtual ~Ray();
};

class Single_Light : public Ray          //单个的点光源
{
public:
	double intensity;           //光强
	Color color;
	Single_Light(vector3<double> input_point, vector3<double> input_direction, double input_intensity, Color in_color) : Ray(input_point, input_direction)
	{
		intensity = input_intensity;
		color = in_color;
	}
	~Single_Light()
	{

	}
};

class Light                                 //光源分为三种，点光源、线光源、面光源
{
public:
	vector<Single_Light> each_light;                    //面光源由离散的点光源组成
	double intensity;                //光强
	Light()             //默认为点光源
	{
		intensity = 0.9;
		Single_Light single_light(vector3<double>(-25, 1, 50), vector3<double>(0, 0, -1), 0.9, Color(255, 255, 255, 255));
		each_light.push_back(single_light);
	}
	Light(vector3<double> light_point, vector3<double> direction, double input_intensity)           //光源实例化为点光源
	{
		intensity = input_intensity;
		Single_Light single_light(light_point, direction, input_intensity, Color(255, 255, 255, 255));
		each_light.push_back(single_light);
	}
	Light(vector3<double> start_point, vector3<double> end_point, vector3<double> direction, int light_num, double input_intensity)             //光源实例化为线光源, light_num为这条线上的点光源数量
	{
		intensity = input_intensity;
		double each_intensity = intensity / light_num;
		vector3<double> diff((end_point.x - start_point.x) / light_num, (end_point.y - start_point.y) / light_num, (end_point.z - start_point.z) / light_num);
		for (int i = 0; i < light_num; i++)
		{
			//cout << start_point << endl;
			Single_Light single_light(start_point, direction, each_intensity, Color(255, 255, 255, 255));
			each_light.push_back(single_light);
			start_point = start_point + diff;
		}
	}
	Light(vector3<double> start_point, vector3<double> u_direction, vector3<double> v_direction, vector3<double> direction, int line_num, int row_num, double input_intensity)          //光源实例化为面光源,u_direction, v_direction代表面光源的两个方向
	{
		intensity = input_intensity;
		double each_intensity = intensity / (line_num * row_num);
		for (int i = 0; i < line_num; i++)
		{
			for (int j = 0; j < row_num; j++)
			{
				cout << start_point << endl;
				Single_Light single_light(start_point, direction, each_intensity, Color(255, 255, 255, 255));
				each_light.push_back(single_light);
				start_point = start_point + v_direction;
			}
			start_point = start_point + u_direction;
			start_point = start_point - v_direction * row_num;
		}
	}
};
struct Material_feature      //物体表面的一些反射系数
{
	double Kdr = 0, Kdg = 0, Kdb = 0;             //漫反射系数
	double Ksr = 0, Ksg = 0, Ksb = 0;             //镜面反射系数
	double Kar = 0, Kag = 0, Kab = 0;             //环境光反射系数
};