#pragma once
#include "Object.h"
#include "Point.h"
class Plane : public Object
{
private:
	void init();
	vector3<double> min_point, u_direction, v_direction;              //����ӳ��ʱ������ʼ��x,y,z�������С�ĵ�
	double u_length, v_length;                 //u�Ǻ��ᣬv������
	reader texture;                                //���������
public:
	Plane();
	~Plane();
	double A, B, C, D;                 //ƽ�淽�̵��ĸ�����
	vector3<double> normal_vector;             //ƽ��ķ�����
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
	vector3<double> passed_point;              //ƽ�澭���ĵ�
	Plane(vector3<double> input_point, vector3<double> input_normal_vector);
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	double signed_distance(Ray input_ray);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);
	vector3<double> get_normalvec(vector3<double> target_pos, vector3<double> view_direction);                    //��ȡ�õ�ķ�����
};