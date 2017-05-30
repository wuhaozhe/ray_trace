#pragma once
#include "Ray.h"
#include "drawer.h"
using namespace std;
struct photon
{
	Ray photon_ray;                   //���ӵ���ʼ��ͷ���
	Color color;                     //���ӵ���ɫ
	photon() = default;
	photon(vector3<double> input_start, vector3<double> input_direction, Color input_color) : photon_ray(input_start, input_direction), color(input_color)
	{

	}
};