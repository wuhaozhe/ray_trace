#include "PhongModel.h"
#include <cmath>
#include <iostream>

int PhongModel::reflect_parameter = 3;
PhongModel::PhongModel()
{
}


PhongModel::~PhongModel()
{
}

Color PhongModel::reflect_color(Light light, vector3<double> normal_vector, vector3<double> view_direction, Material_feature feature)
{
	double r = 0;
	double g = 0;
	double b = 0;
	vector3<double> reverse_light = light.direction * -1;
	vector3<double> reverse_view = view_direction * -1;
	double L_N_dot = reverse_light * normal_vector;
	//cout << "veiw" << view_direction.x << " " << view_direction.y << view_direction.z << endl;
	//cout << reverse_view.x << " " << reverse_view.y << " " << reverse_view.z << endl;
	//cout << reverse_light.x << " " << reverse_light.y << " " << reverse_light.z << endl;
	vector3<double> angle_bisector = (reverse_light + reverse_view).normallize();             //求角平分线
	double R_V_dot = angle_bisector * normal_vector;
	r += light.intensity * light.color.r * feature.Kdr * L_N_dot;
	g += light.intensity * light.color.g * feature.Kdg * L_N_dot;
	b += light.intensity * light.color.b * feature.Kdb * L_N_dot;
	r += light.intensity * light.color.r * feature.Ksr * pow(R_V_dot, reflect_parameter);
	g += light.intensity * light.color.g * feature.Ksg * pow(R_V_dot, reflect_parameter);
	b += light.intensity * light.color.b * feature.Ksb * pow(R_V_dot, reflect_parameter);
	r += light.intensity * light.color.r * feature.Kar;
	g += light.intensity * light.color.g * feature.Kag;
	b += light.intensity * light.color.b * feature.Kab;
	//cout << r << " " << g << " " << b << endl;
	return Color((unsigned char)r, (unsigned char)g, (unsigned char)b, 255);
}