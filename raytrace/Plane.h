#pragma once
#include "Object.h"
#include "Point.h"
class Plane : public Object
{
private:
	void init();
	vector3<double> min_point, u_direction, v_direction;              //纹理映射时，纹理开始的x,y,z坐标的最小的点
	double u_length, v_length;                 //u是横轴，v是纵轴
	reader texture;                                //读入的纹理
public:
	Plane();
	~Plane();
	double A, B, C, D;                 //平面方程的四个参数
	vector3<double> normal_vector;             //平面的法向量
	void set_texture_range(vector3<double> input_min, vector3<double> input_u_direction, vector3<double> input_v_direction, double in_u, double in_v)
	{
		has_texture = true;
		min_point = input_min;
		u_direction = input_u_direction;
		v_direction = input_v_direction;
		u_length = in_u;
		v_length = in_v;
	}
	void set_texture(reader input_texture)
	{
		texture = input_texture;
	}
	object_feature get_feature(vector3<double> target_pos);
	vector3<double> passed_point;              //平面经过的点
	Plane(vector3<double> input_point, vector3<double> input_normal_vector);
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	double signed_distance(Ray input_ray);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);
	vector3<double> get_normalvec(vector3<double> target_pos, vector3<double> view_direction);                    //获取该点的法向量
};