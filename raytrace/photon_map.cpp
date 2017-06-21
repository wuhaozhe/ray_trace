#define PI 3.1415926
#include "photon_map.h"
#include "PhongModel.h"
#include <cmath>
#include <algorithm>
#include "MyRand.h"
photon_map* photon_map::instance = new photon_map();


photon_map::photon_map()
{
	//srand((unsigned)time(NULL));
}


photon_map::~photon_map()
{
}

photon photon_map::init_photon()
{
	vector3<double> start_point;
	if (single_light)
	{
		start_point = light_position;
	}
	else
	{
		//to do:��������Ĺ�Դ 
	}
	double theta = (MyRand::get_randrom()) * 2 * PI;
	double phi = (MyRand::get_randrom()) * 2 * PI;
	double z = cos(theta);
	double y = sin(theta) * sin(phi);
	double x = sin(theta) * cos(phi);
	return photon(start_point, vector3<double>(x, y, z), light_color);
}

void photon_map::change_color(photon& input_photon, object_feature input_feature, bool reflect_flag)
{
	if (reflect_flag)
	{
		input_photon.color.b = (unsigned char)(input_feature.reflect_blue * (double)input_photon.color.b);
		input_photon.color.g = (unsigned char)(input_feature.reflect_green * (double)input_photon.color.g);
		input_photon.color.r = (unsigned char)(input_feature.reflect_red * (double)input_photon.color.r);
	}
	else
	{
		input_photon.color.b = (unsigned char)(input_feature.refract_blue * (double)input_photon.color.b);
		input_photon.color.g = (unsigned char)(input_feature.refract_green * (double)input_photon.color.g);
		input_photon.color.r = (unsigned char)(input_feature.refract_red * (double)input_photon.color.r);
	}
}

void photon_map::generate_photon()
{
	photon start_photon = init_photon();                   //��һ��ѭ������֮����Ҫ����start_photon��start_pos�ͷ���
	stack<int> refract_stack;
	refract_stack.push(-1);
	double current_n = 1;
	for (int i = 0; i < recursive_depth; i++)             //���Ӳ����ڸ�������֮�䵯��
	{
		int temp_index;          //�洢��������index
		vector3<double> temp_point;          //�洢����Ľ���
		if (intersect_point(start_photon.photon_ray, temp_index, temp_point))
		{   //�������̶ĵ�ԭ����������������䣬�����䣬���淴�仹������
			vector3<double> temp_normalvec = objects[temp_index]->get_normalvec(temp_point, start_photon.photon_ray.direction);
			double roulette = (MyRand::get_randrom());
			object_feature temp_feature = objects[temp_index]->get_feature(temp_point);
			roulette -= temp_feature.absorb;
			if (roulette < 0)            //���ӱ�����
			{
				break;
			}
			roulette -= temp_feature.diffuse_reflect;
			if (roulette < 0)              //������
			{
				//����뷨������ֱ�������������Ե�ǰ����������ת
				vector3<double> base1, base2;
				if (fabs(temp_normalvec.x) < limit_zero)
				{
					base1 = vector3<double>(1, 0, 0);
				}
				else
				{
					base1 = vector3<double>(-1 * ((temp_normalvec.y + temp_normalvec.z) / temp_normalvec.x), 1, 1).normallize();
				}
				base2 = (temp_normalvec.cross_product(base1)).normallize();
				if (temp_normalvec * start_photon.photon_ray.direction > 0)
				{
					temp_normalvec = temp_normalvec * -1;
				}
				double cos_theta = (MyRand::get_randrom());
				double theta = acos(cos_theta);
				double phi = (MyRand::get_randrom()) * 2 * PI;
				double z = cos_theta, x = sin(theta) * cos(phi), y = sin(theta) * sin(phi);
				vector3<double> reflect_direction = (temp_normalvec * z + base1 * x + base2 * y).normallize();
				start_photon.photon_ray.start_point = temp_point;
				change_color(start_photon, temp_feature, true);
				photon_array.push_back(start_photon);                     //��¼�·���������Ĺ���,���ӷ���Ϊ����ǰ�ķ���
				start_photon.photon_ray.direction = reflect_direction;                  //��¼���ٽ����ӵķ���ı�
				continue;
			}
			roulette -= temp_feature.specular_reflect;
			if (roulette < 0)             //���淴��
			{
				vector3<double> reflect_direction = reflect(start_photon.photon_ray.direction, temp_normalvec);        //�Ǿ�����λ��������
				start_photon.photon_ray.direction = reflect_direction;
				start_photon.photon_ray.start_point = temp_point;
				change_color(start_photon, temp_feature, true);
				continue;
			}
			else                          //����
			{
				vector3<double> refract_direction;
				double last_n = current_n;
				if (temp_index == refract_stack.top())      //��Ҫ���������
				{
					int top = refract_stack.top();
					refract_stack.pop();
					if (refract_stack.top() >= 0)
					{
						current_n = objects[refract_stack.top()]->n;
					}
					else
					{
						current_n = 1;
					}
					if (refract(start_photon.photon_ray.direction, temp_normalvec, last_n, current_n, refract_direction))
					{
						//��������
						start_photon.photon_ray.start_point = temp_point;
						start_photon.photon_ray.direction = refract_direction;
						change_color(start_photon, temp_feature, false);
						continue;
					}
					else
					{
						//����ȫ����
						refract_stack.push(top);
						current_n = last_n;
						vector3<double> reflect_direction = reflect(start_photon.photon_ray.direction, temp_normalvec);
						start_photon.photon_ray.direction = reflect_direction;
						start_photon.photon_ray.start_point = temp_point;
						change_color(start_photon, temp_feature, true);
						continue;
					}
				}
				else                        //��Ҫ���������
				{
					refract_stack.push(temp_index);
					current_n = objects[temp_index]->n;
					vector3<double> refract_direction;
					if (refract(start_photon.photon_ray.direction, temp_normalvec, last_n, current_n, refract_direction))                    //�ܹ�����
					{
						start_photon.photon_ray.start_point = temp_point;
						start_photon.photon_ray.direction = refract_direction;
						change_color(start_photon, temp_feature, false);
						continue;
					}
					else                                       //����ȫ����
					{
						refract_stack.pop();
						current_n = last_n;
						vector3<double> reflect_direction = reflect(start_photon.photon_ray.direction, temp_normalvec);
						start_photon.photon_ray.direction = reflect_direction;
						start_photon.photon_ray.start_point = temp_point;
						change_color(start_photon, temp_feature, true);
						continue;
					}
				}
			}
		}
		else
		{
			break;
		}
	}
}

void photon_map::generate_photon(int photon_num)
{
	/*while (photon_array.size() < photon_num)
	{
		generate_photon();
		if (photon_array.size() % 100000 == 0 && photon_array.size() != 0)
		{
			cout << photon_array.size() << endl;
		}
	}*/
	for (int i = 0; i < photon_num; i++)
	{
		generate_photon();
		if (i % 10000 == 0 && i != 0)
		{
			cout << i << endl;
		}
	}
	Tree = new kdTree(photon_array);
}

bool photon_map::intersect_point(Ray current_ray, int &object_index, vector3<double> &point)       //�󽻵�
{
	double distance = 10000000000;
	object_index = -1;
	//ö��world��ÿһ�������󽻵㣬ѡȡһ������Ľ���
	for (unsigned int i = 0; i < objects.size(); i++)       //todo: ��kd������
	{
		vector3<double> intersect_Point;
		if (objects[i]->intersect(current_ray, intersect_Point))
		{
			double length = (intersect_Point - current_ray.start_point).length;
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

Color photon_map::get_color(vector3<double> position, vector3<double> input_normal, vector3<double> input_view, double pd, double ps)
{
	k_collection collection = Tree->knn(position);
	double r = 0, g = 0, b = 0;
	for (auto it = collection.kdnode_list.begin(); it != collection.kdnode_list.end(); it++)
	{
		vector3<double> photon_direction = it->first->current_photon.photon_ray.direction;         //���ӳ���ķ���
		Color photon_color = it->first->current_photon.color;
		if (photon_direction * input_normal > 0)       //input_normal������
		{
			input_normal = input_normal * -1;
		}
		//double BRDF_ratio = PhongModel::PhongBRDF(input_normal, photon_direction, input_view, pd, ps);        //ͨ��phongģ�͵�brdf���ص�
		if (input_normal * input_view < 0)
		{
			r += (double)photon_color.r;
			g += (double)photon_color.g;
			b += (double)photon_color.b;
		}
	}
	double area = PI * collection.max_value * collection.max_value;
	//cout <<"max_value"<< collection.max_value << endl;
	r /= area;
	g /= area;
	b /= area;
	r *= BRDF_ratio;
	g *= BRDF_ratio;
	b *= BRDF_ratio;
	r = min(r, 255.0);
	g = min(g, 255.0);
	b = min(b, 255.0);
	return Color(r, g, b, 255);
}