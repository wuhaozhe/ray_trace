#pragma once
#include "Point.h"
#include "drawer.h"
class Ray                                  //��������
{
public:
	vector3<double> start_point;             //��ʼ��
	vector3<double> direction;                //����
	Ray(vector3<double> input_point, vector3<double> input_direction);
	virtual ~Ray();
};

class Light : public Ray
{
public:
	double intensity;           //��ǿ
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
struct Material_feature      //��������һЩ����ϵ��
{
	double Kdr = 0, Kdg = 0, Kdb = 0;             //������ϵ��
	double Ksr = 0, Ksg = 0, Ksb = 0;             //���淴��ϵ��
	double Kar = 0, Kag = 0, Kab = 0;             //�����ⷴ��ϵ��
};