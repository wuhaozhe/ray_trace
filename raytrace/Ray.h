#pragma once
#include "Point.h"
#include "drawer.h"
#include <vector>
#include <iostream>
using namespace std;
class Ray                                  //��������
{
public:
	vector3<double> start_point;             //��ʼ��
	vector3<double> direction;                //����
	Ray(vector3<double> input_point, vector3<double> input_direction);
	virtual ~Ray();
};

class Single_Light : public Ray          //�����ĵ��Դ
{
public:
	double intensity;           //��ǿ
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

class Light                                 //��Դ��Ϊ���֣����Դ���߹�Դ�����Դ
{
public:
	vector<Single_Light> each_light;                    //���Դ����ɢ�ĵ��Դ���
	double intensity;                //��ǿ
	Light()             //Ĭ��Ϊ���Դ
	{
		intensity = 0.9;
		Single_Light single_light(vector3<double>(-25, 1, 50), vector3<double>(0, 0, -1), 0.9, Color(255, 255, 255, 255));
		each_light.push_back(single_light);
	}
	Light(vector3<double> light_point, vector3<double> direction, double input_intensity)           //��Դʵ����Ϊ���Դ
	{
		intensity = input_intensity;
		Single_Light single_light(light_point, direction, input_intensity, Color(255, 255, 255, 255));
		each_light.push_back(single_light);
	}
	Light(vector3<double> start_point, vector3<double> end_point, vector3<double> direction, int light_num, double input_intensity)             //��Դʵ����Ϊ�߹�Դ, light_numΪ�������ϵĵ��Դ����
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
	Light(vector3<double> start_point, vector3<double> u_direction, vector3<double> v_direction, vector3<double> direction, int line_num, int row_num, double input_intensity)          //��Դʵ����Ϊ���Դ,u_direction, v_direction�������Դ����������
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
struct Material_feature      //��������һЩ����ϵ��
{
	double Kdr = 0, Kdg = 0, Kdb = 0;             //������ϵ��
	double Ksr = 0, Ksg = 0, Ksb = 0;             //���淴��ϵ��
	double Kar = 0, Kag = 0, Kab = 0;             //�����ⷴ��ϵ��
};