#include "Sphere.h"
#include "PhongModel.h"
#include <cmath>

void Sphere::init()
{
	object_type = Object_type::_Sphere;
}
Sphere::Sphere()
{
	init();
	refractive = true;
	refract_coefficient = 0.8;
}
Sphere::Sphere(vector3<double> input_center, double input_radius): sphere_center(input_center), radius(input_radius)
{
	init();
	square_radius = radius * radius;
	refractive = true;
	color_feature.Kab = 0.4;
	color_feature.Kdb = 0.3;
	color_feature.Ksb = 0.3;
	refract_coefficient = 0.7;
	reflect_coefficient = 0.99;
	n = 1.5;
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(Ray input_ray, vector3<double> &intersect_point)          //默认球体是空心的，如果在球面内那么相交后的效果也可以被显示
{
	vector3<double> l = sphere_center - input_ray.start_point;
	double direction_radius_dot = l * input_ray.direction;
	if (l.length > radius && fabs(l.length - radius) >= limit_zero)           //光源位于球体外部
	{
		if (direction_radius_dot > 0)
		{
			double square_distance = l.length * l.length - direction_radius_dot * direction_radius_dot;
			if (square_distance > square_radius || fabs(square_distance - square_radius) < limit_zero)                //相切或相离均认为不相交
			{
				return false;
			}
			else
			{
				double square_t1 = square_radius - square_distance;
				double t1 = sqrt(square_t1);
				double t = direction_radius_dot - t1;
				intersect_point = input_ray.start_point + input_ray.direction * t;
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else if(fabs(l.length - radius) < limit_zero)               //光源在球面上（需要进行判断，如果光线的前进方向与圆心距离变近，那么求交，如果前进方向与圆心距离变远，那么不想交）
	{                                                           //可以根据光线的方向与到圆心的点积判断(锐角，则靠近，钝角，则远离)
		if(direction_radius_dot > 0)          //光线与球心的距离变近
		{
			double square_distance = l.length * l.length - direction_radius_dot * direction_radius_dot;
			double square_t1 = square_radius - square_distance;
			double t1 = sqrt(square_t1);
			double t = direction_radius_dot + t1;
			intersect_point = input_ray.start_point + input_ray.direction * t;
			return true;
		}
		else                                 //变远
		{
			return false;
		}
	}
	else                                               //光源在球面内
	{
		double square_distance = l.length * l.length - direction_radius_dot * direction_radius_dot;
		double square_t1 = square_radius - square_distance;
		double t1 = sqrt(square_t1);
		double t = direction_radius_dot + t1;
		intersect_point = input_ray.start_point + input_ray.direction * t;
		return true;
	}
}

Color Sphere::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)
{
	light.direction = (target_pos - light.start_point).normallize();
	vector3<double> normal_vector = (target_pos - sphere_center).normallize();
	//cout<<"intersect" << target_pos.x << " "<< target_pos.y << " " << target_pos.z << endl;
	//cout <<"normal "<< normal_vector.x << " " << normal_vector.y << " " << normal_vector.z << endl;
	//cout << "light " << light.direction.x << " " << light.direction.y << " " << light.direction.z << endl;
	//cout << "view " << view_direction.x << " " << view_direction.y << " " << view_direction.z << endl;
	in = normal_vector;
	return PhongModel::reflect_color(light, normal_vector, view_direction, color_feature);
}