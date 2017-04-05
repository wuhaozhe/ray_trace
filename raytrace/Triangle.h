#pragma once
#include "Object.h"
#include "Point.h"
class Triangle: public Object
{
private:
	void init();
	double det(vector3<double> a, vector3<double> b, vector3<double> c)        //返回a, b, c为列的三阶行列式
	{
		double a1 = a.x * b.y * c.z;
		double a2 = b.x * c.y * a.z;
		double a3 = c.x * a.y * b.z;
		double b1 = c.x * b.y * a.z;
		double b2 = b.x * a.y * c.z;
		double b3 = a.x * c.y * b.z;
		return a1 + a2 + a3 - b1 - b2 - b3;
	}
	vector3<double> solve_equation(vector3<double> a, vector3<double> b, vector3<double> c, vector3<double> d);              //求解非齐次三元一次方程组
	vector3<double> normal_vector, E1, E2;
public:
	vector3<double> vertex[3];           //三角形的三个顶点
	Triangle();
	Triangle(vector3<double> vertex1, vector3<double> vertex2, vector3<double> vertex3);
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Light light, vector3<double> &in);
	~Triangle();
};

