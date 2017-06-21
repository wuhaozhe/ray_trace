#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

Ray Camera::generate_ray(int x, int y)
{
	vector3<double> target_direction = (horizental * x + upward * y + direction * distance).normallize();          //朝向x, y的方向
	//cout << x << " " << y<<endl;
	//cout <<"generate "<< target_direction.x << " " << target_direction.y << " " << target_direction.z << endl;
	return Ray(position, target_direction);
}

vector<Ray> Camera::generate_DOF_ray(int x, int y)
{
	vector3<double> focal_position = position + direction * ((double)LENS_DISTANCE + (double)FOCAL_PLANE_DISTANCE) + horizental * (((double)x * EYE_WIDTH * (double)FOCAL_PLANE_DISTANCE) / ((double)size_x * (double)LENS_DISTANCE))
		 + upward * (((double)y * EYE_HEIGHT * (double)FOCAL_PLANE_DISTANCE) / ((double)size_y * (double)LENS_DISTANCE));       //焦平面上的点
	vector<Ray> return_array;
	for (int i = 0; i < LENS_WIDTH * LENS_WIDTH; i++)
	{
		return_array.push_back(Ray(lens_array[i] ,(focal_position - lens_array[i]).normallize()));
	}
	return return_array;
}