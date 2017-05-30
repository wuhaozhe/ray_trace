#include "Triangle.h"
#include "PhongModel.h"


Triangle::Triangle()
{
	init();
}


Triangle::~Triangle()
{
}

void Triangle::init()
{
	object_type = Object_type::_Triangle;
}

Triangle::Triangle(vector3<double> vertex1, vector3<double> vertex2, vector3<double> vertex3)
{
	init();
	vertex[0] = vertex1;
	vertex[1] = vertex2;
	vertex[2] = vertex3;
	E1 = vertex[0] - vertex[1];
	E2 = vertex[0] - vertex[2];
	normal_vector = (E1.cross_product(E2)).normallize();
	/*color_feature.Kdb = 0.3;
	color_feature.Ksb = 0.65;
	color_feature.Kab = 0.05;*/
	color_feature.Kdg = 0.3;
	color_feature.Ksg = 0.65;
	color_feature.Kag = 0.05;
	color_feature.Kdr = 0.3;
	color_feature.Ksr = 0.65;
	color_feature.Kar = 0.05;
	reflective = true;
	reflect_coefficient = 0.7;
	n = 0;
}

vector3<double> Triangle::solve_equation(vector3<double> a, vector3<double> b, vector3<double> c, vector3<double> d)
{
	double denominator = det(a, b, c);
	if (fabs(denominator) > limit_zero)         //denominator != 0
	{
		double det_1 = det(d, b, c);
		double det_2 = det(a, d, c);
		double det_3 = det(a, b, d);
		double x1 = det_1 / denominator;
		double x2 = det_2 / denominator;
		double x3 = det_3 / denominator;
		return vector3<double>(x1, x2, x3);
	}
	else
	{
		return vector3<double>(100, 100, 100);
	}
}

bool Triangle::intersect(Ray input_ray, vector3<double> &intersect_point)
{
	vector3<double> S = vertex[0] - input_ray.start_point;
	vector3<double> solution = solve_equation(input_ray.direction, E1, E2, S);
	if (solution.x > -1 * limit_zero && solution.y >= -1 * limit_zero && solution.z >= -1 * limit_zero && (solution.y + solution.z) <= 1 + limit_zero)
	{
		intersect_point = input_ray.direction * solution.x + input_ray.start_point;
		return true;
	}
	else
	{
		return false;
	}
}

Color Triangle::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)
{
	light.direction = (target_pos - light.start_point).normallize();
	if (normal_vector * light.direction > 0)
	{
		normal_vector = normal_vector * -1;
	}
	in = normal_vector;
	return PhongModel::reflect_color(light, normal_vector, view_direction, color_feature);
}

vector3<double> Triangle::get_normalvec(vector3<double> target_pos, vector3<double> view_direction)
{
	return normal_vector;
}