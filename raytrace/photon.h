#pragma once
#include "Ray.h"
#include "drawer.h"
using namespace std;
struct photon
{
	Ray photon_ray;                   //光子的起始点和方向
	Color color;                     //光子的颜色
	photon() = default;
	photon(vector3<double> input_start, vector3<double> input_direction, Color input_color) : photon_ray(input_start, input_direction), color(input_color)
	{

	}
};