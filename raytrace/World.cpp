#include "World.h"
#include <map>


World::World(): light(vector3<double>(-25, 1, 50), vector3<double>(0, 1, 50), vector3<double>(0, 0, -1), 10, 0.9)
{
	//light(vector3<double>(-25, 1, 50), vector3<double>(0.5, 0, 0), vector3<double>(0, 0.5, 0), vector3<double>(0, 0, -1), 5, 5, 0.9)
	//light(vector3<double>(-25, 1, 50), vector3<double>(0, 1, 50), vector3<double>(0, 0, -1), 10, 0.9)
	camera = Camera(vector3<double>(-20, 0, 5), vector3<double>(1, 0, 0), vector3<double>(0, 0, 1));
	drawer_instance = drawer::get_instance();
	drawer_instance->set_size(camera.size_x, camera.size_y);
}


World::~World()
{
}

void World::add_object(Object* obj)
{
	objects.push_back(obj);
}

bool World::intersect_point(Ray current_ray, int &object_index, vector3<double> &point)       //�󽻵�
{
	double distance = 10000000000;
	object_index = -1;
	//ö��world��ÿһ�������󽻵㣬ѡȡһ������Ľ���
	for (unsigned int i = 0; i < objects.size(); i++)       //todo: ��kd������
	{
		vector3<double> intersect_Point;
		if (objects[i]->intersect(current_ray, intersect_Point))
		{
			double length = (intersect_Point - camera.position).length;
			if (length < distance)
			{
				distance = length;
				object_index = i;
				point = intersect_Point;
			}
		}
	}
	if (object_index < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Color World::determine_color_normalvec(int object_index, vector3<double> point, vector3<double> in_direction, vector3<double> &normal_vector)     //����ÿһ���ƣ������һ����ɫ
{																																					//����Щ���
	Color return_color(0, 0, 0, 255);
	for (int k = 0; k < light.each_light.size(); k++)
	{
		Color temp_color = objects[object_index]->get_color_normalvec(point, in_direction, light.each_light[k], normal_vector);          //�ڵ�ǰ���Դ�µõ�����ɫ
		vector3<double> intersect_to_light(light.each_light[k].start_point - point);
		intersect_to_light = intersect_to_light.normallize();
		Ray to_light_ray(point, intersect_to_light);           //���㵽��Դ������		
		for (unsigned int i = 0; i < objects.size(); i++)                //��ÿ�������󽻣�����Ӱ����to_do�ڴ˴���kd������
		{
			if (i == object_index)
				continue;
			vector3<double> intersect_point;
			if (objects[i]->intersect(to_light_ray, intersect_point))
			{
				temp_color.r *= objects[i]->opacity;
				temp_color.g *= objects[i]->opacity;
				temp_color.b *= objects[i]->opacity;
			}
		}
		return_color = return_color + temp_color;
	}
	return return_color;
}

Color World::intersect_color(int n, Ray current_ray, stack<int> &refract_stack)           //��refract_stack�У�-1��ʾû�����κ������ڣ�������Ϊ1
{
	if (n >= recursive_depth)
	{
		return Color();
	}
	vector3<double> _intersect_point;
	int object_index;
	if (intersect_point(current_ray, object_index, _intersect_point))
	{
		Color return_color;
		vector3<double> normal_vector;
		if (objects[object_index]->reflective)
		{
			return_color = determine_color_normalvec(object_index, _intersect_point, current_ray.direction, normal_vector) * 
							(1 - objects[object_index]->reflect_coefficient);
			vector3<double> reflect_direction = reflect(current_ray.direction, normal_vector);
			Ray reflect_ray(_intersect_point, reflect_direction);
			return_color = return_color + intersect_color(n + 1, reflect_ray, refract_stack) * objects[object_index]->reflect_coefficient;
		}
		else if (objects[object_index]->refractive)
		{
			double last_n = current_n;            //�������������
			//return_color = determine_color_normalvec(object_index, _intersect_point, current_ray.direction, normal_vector) *
			//	(1 - objects[object_index]->refract_coefficient);
			return_color = determine_color_normalvec(object_index, _intersect_point, current_ray.direction, normal_vector);
			//cout << (int)return_color.r << " " << (int)return_color.g << " " << (int)return_color.b << endl;
			if (object_index == refract_stack.top())            //��Ҫ���������
			{
				int top = refract_stack.top();
				refract_stack.pop();
				if (refract_stack.top() >= 0)
				{
					current_n = objects[refract_stack.top()]->n;              //�������������
				}
				else
				{
					current_n = 1;                    //�������������Ϊ1
				}
				vector3<double> refract_direction;
				if (refract(current_ray.direction, normal_vector, last_n, current_n, refract_direction))                    //�ܹ�����
				{
					Ray refract_ray(_intersect_point, refract_direction);
					return_color = return_color + intersect_color(n + 1, refract_ray, refract_stack) * objects[object_index]->refract_coefficient;
					//return_color = return_color + intersect_color(n + 1, refract_ray, refract_stack);
					//cout << (int)return_color.r << " " << (int)return_color.g << " " << (int)return_color.b << endl;
				}
				else                                       //����ȫ����
				{
					refract_stack.push(top);
					current_n = last_n;
					vector3<double> reflect_direction = reflect(current_ray.direction, normal_vector);
					Ray reflect_ray(_intersect_point, reflect_direction);
					return_color = return_color + intersect_color(n + 1, reflect_ray, refract_stack) * objects[object_index]->refract_coefficient;
				}
			}
			else                                              //��Ҫ���������
			{
				refract_stack.push(object_index);
				current_n = objects[object_index]->n;         //�������������
				vector3<double> refract_direction;
				if (refract(current_ray.direction, normal_vector, last_n, current_n, refract_direction))                    //�ܹ�����
				{
					Ray refract_ray(_intersect_point, refract_direction);
					return_color = return_color + intersect_color(n + 1, refract_ray, refract_stack) * objects[object_index]->refract_coefficient;
				}
				else                                       //����ȫ����
				{
					refract_stack.pop();
					current_n = last_n;
					vector3<double> reflect_direction = reflect(current_ray.direction, normal_vector);
					Ray reflect_ray(_intersect_point, reflect_direction);
					return_color = return_color + intersect_color(n + 1, reflect_ray, refract_stack) * objects[object_index]->refract_coefficient;
				}
			}
		}
		else
		{
			return_color = determine_color_normalvec(object_index, _intersect_point, current_ray.direction, normal_vector);
		}
		return return_color;
	}
	else
	{
		return Color();
	}
}

Color World::ray_trace(int i, int j)
{
	Ray current_ray = camera.generate_ray(i, j);             //����i, j�����ϵĹ���
	stack<int> refract_stack;
	refract_stack.push(-1);
	current_n = 1;
	return intersect_color(0, current_ray, refract_stack);
}

void World::ray_trace()
{
	cout << camera.size_x << " " << camera.size_y << endl;
	for(int i = 0; i < camera.size_x; i++)
		for (int j = 0; j < camera.size_y; j++)
		{
			//cout << i << " " << j << endl;
			drawer_instance->set_pixel(i, j, ray_trace(i - (camera.size_x / 2), j - (camera.size_y / 2)));
		}
}