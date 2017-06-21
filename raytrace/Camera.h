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
#define LENS_DISTANCE 0.25               //图像距离透镜的距离
#define LENS_WIDTH 5                   //假定透镜的长度与宽度为5（一共25个像素模拟）
#define LENS_DELTA_PIXEL 0.1           //透镜中每个点的距离
#define FOCAL_PLANE_DISTANCE 13         //与焦平面的距离
#define EYE_WIDTH 0.5                  //模拟的视网膜长度
#define EYE_HEIGHT 0.5                 //模拟的视网膜宽度
class Camera
{
private:
	vector3<double> horizental;     //视图所对应的水平方向
	vector3<double>* lens_array;    //存储lens中所有点
	vector3<double> lens_center;    //存储lens的中心
public:
	vector3<double> position;       //所处的位置
	vector3<double> upward;         //摄像机向上的方向
	vector3<double> direction;      //眼镜所看的方向
	unsigned int size_x, size_y;              //视图的大小
	double view_angle_h, view_angle_w;              //高度上的视角，宽度上的视角
	double distance;                //眼睛距离投影的距离
	Camera(vector3<double> eye_place, vector3<double> forward_direction, vector3<double> upward_direction, unsigned int picture_size_x = DEFAULT_WIDTH, unsigned int picture_size_y = DEFAULT_HEIGHT, double input_angle_h = DEFUALT_ANGLE)
	{
		position = eye_place;
		upward = upward_direction.normallize();
		direction = forward_direction.normallize();
		size_x = picture_size_x, size_y = picture_size_y;
		view_angle_h = input_angle_h;
		view_angle_w = (view_angle_h / (double)size_y) * (double)size_x;
		distance = (double) size_y / (2 * tan(view_angle_h * PI / 360));                          //viewangle / 2的tan
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

