#pragma once
#include "Point.h"
#include "Ray.h"
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
#define PI 3.14159265
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480
#define DEFUALT_ANGLE 95
#define LENS_DISTANCE 0.25               //ͼ�����͸���ľ���
#define LENS_WIDTH 5                   //�ٶ�͸���ĳ�������Ϊ5��һ��25������ģ�⣩
#define LENS_DELTA_PIXEL 0.1           //͸����ÿ����ľ���
#define FOCAL_PLANE_DISTANCE 13         //�뽹ƽ��ľ���
#define EYE_WIDTH 0.5                  //ģ�������Ĥ����
#define EYE_HEIGHT 0.5                 //ģ�������Ĥ���
class Camera
{
private:
	vector3<double> horizental;     //��ͼ����Ӧ��ˮƽ����
	vector3<double>* lens_array;    //�洢lens�����е�
	vector3<double> lens_center;    //�洢lens������
public:
	vector3<double> position;       //������λ��
	vector3<double> upward;         //��������ϵķ���
	vector3<double> direction;      //�۾������ķ���
	unsigned int size_x, size_y;              //��ͼ�Ĵ�С
	double view_angle_h, view_angle_w;              //�߶��ϵ��ӽǣ�����ϵ��ӽ�
	double distance;                //�۾�����ͶӰ�ľ���
	Camera(vector3<double> eye_place, vector3<double> forward_direction, vector3<double> upward_direction, unsigned int picture_size_x = DEFAULT_WIDTH, unsigned int picture_size_y = DEFAULT_HEIGHT, double input_angle_h = DEFUALT_ANGLE)
	{
		position = eye_place;
		upward = upward_direction.normallize();
		direction = forward_direction.normallize();
		size_x = picture_size_x, size_y = picture_size_y;
		view_angle_h = input_angle_h;
		view_angle_w = (view_angle_h / (double)size_y) * (double)size_x;
		distance = (double) size_y / (2 * tan(view_angle_h * PI / 360));                          //viewangle / 2��tan
		horizental = (upward.cross_product(direction)).normallize();
		lens_array = new vector3<double>[LENS_WIDTH * LENS_WIDTH];
		for (int i = 0; i < LENS_WIDTH; i++)
		{
			for (int j = 0; j < LENS_WIDTH; j++)
			{
				vector3<double> delta_i = horizental * (i - LENS_WIDTH / 2) * LENS_DELTA_PIXEL;
				vector3<double> delta_j = upward * (j - LENS_WIDTH / 2) * LENS_DELTA_PIXEL;
				lens_array[i * LENS_WIDTH + j] = position + direction * LENS_DISTANCE + delta_i + delta_j;
			}
		}
		lens_center = position + direction * LENS_DISTANCE;
	}
	Camera();
	~Camera();
	Ray generate_ray(int x, int y);
	vector<Ray> generate_DOF_ray(int x, int y);
};

