#pragma once
#include "Point.h"
#include "Ray.h"
#include <cmath>
#include <iostream>
using namespace std;
#define PI 3.14159265
class Camera
{
private:
	vector3<double> horizental;     //��ͼ����Ӧ��ˮƽ����
public:
	vector3<double> position;       //������λ��
	vector3<double> upward;         //��������ϵķ���
	vector3<double> direction;      //�۾������ķ���
	unsigned int size_x, size_y;              //��ͼ�Ĵ�С
	double view_angle_h, view_angle_w;              //�߶��ϵ��ӽǣ�����ϵ��ӽ�
	double distance;                //�۾�����ͶӰ�ľ���
	Camera(vector3<double> eye_place, vector3<double> forward_direction, vector3<double> upward_direction, unsigned int picture_size_x = 640, unsigned int picture_size_y = 480, double input_angle_h = 95)
	{
		position = eye_place;
		upward = upward_direction.normallize();
		direction = forward_direction.normallize();
		size_x = picture_size_x, size_y = picture_size_y;
		view_angle_h = input_angle_h;
		view_angle_w = (view_angle_h / (double)size_y) * (double)size_x;
		distance = (double) size_y / (2 * tan(view_angle_h * PI / 360));                          //viewangle / 2��tan
		horizental = (upward.cross_product(direction)).normallize();
	}
	Camera();
	~Camera();
	Ray generate_ray(int x, int y);
};

