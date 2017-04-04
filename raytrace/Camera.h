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
	vector3<double> horizental;     //视图所对应的水平方向
public:
	vector3<double> position;       //所处的位置
	vector3<double> upward;         //摄像机向上的方向
	vector3<double> direction;      //眼镜所看的方向
	unsigned int size;              //视图的大小
	double view_angle;              //视角
	double distance;                //眼睛距离投影的距离
	Camera(vector3<double> eye_place, vector3<double> forward_direction, vector3<double> upward_direction, unsigned int picture_size = 500, double input_angle = 95)
	{
		position = eye_place;
		upward = upward_direction.normallize();
		direction = forward_direction.normallize();
		size = picture_size;
		view_angle = input_angle;
		distance = (double) size / (2 * tan(view_angle * PI / 360));                          //viewangle / 2的tan
		horizental = (upward.cross_product(direction)).normallize();
		//cout <<"horizental"<< horizental.x << " " << horizental.y << " " << horizental.z<<endl;
		//cout << "upward" << upward.x << " " << upward.y << " " << upward.z << endl;
		//cout << direction.x << " " << direction.y << " " << direction.z << endl;
		//cout << distance << endl;
	}
	Camera();
	~Camera();
	Ray generate_ray(int x, int y);
};

