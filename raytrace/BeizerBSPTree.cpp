#define PI 3.1415926535
#include "BeizerBSPTree.h"
#include <assert.h>
#include <cmath>
#include <algorithm>
#include <iostream>

BeizerBSPTree::BeizerBSPTree(vector3<double> point_array[])
{
	extreme_x1 = NOT_LEGAL, extreme_x2 = NOT_LEGAL;
	extreme_z1 = NOT_LEGAL, extreme_z2 = NOT_LEGAL;
	for (int i = 0; i < 4; i++)
	{
		assert(point_array[i].y == 0);
		beizer_line.add_control_point(point_array[i]);
	}
	beizer_xa = 3 * (point_array[3].x - point_array[2].x + point_array[1].x - point_array[0].x);
	beizer_xb = 2 * (point_array[2].x - 2 * point_array[1].x + 3 * point_array[0].x);
	beizer_xc = point_array[1].x - 3 * point_array[0].x;
	beizer_za = 3 * (point_array[3].z - point_array[2].z + point_array[1].z - point_array[0].z);
	beizer_zb = 2 * (point_array[2].z - 2 * point_array[1].z + 3 * point_array[0].z);
	beizer_zc = point_array[1].z - 3 * point_array[0].z;
	double delta_x = beizer_xb * beizer_xb - 4 * beizer_xa * beizer_xc;
	if (delta_x > limit_zero)        //������
	{
		extreme_x1 = (-1 * beizer_xb + sqrt(delta_x)) / (2 * beizer_xa);         //�п��ܼ�ֵ��Ĳ���>1��<0
		extreme_x2 = (-1 * beizer_xb - sqrt(delta_x)) / (2 * beizer_xa);
	}
	else if (fabs(delta_x) < limit_zero)          //һ����
	{
		extreme_x1 = (-1 * beizer_xb) / (2 * beizer_xa);
	}
	//����Ϊ�޽�,do nothing
	double delta_z = beizer_zb * beizer_zb - 4 * beizer_za * beizer_zc;
	if (delta_z > limit_zero)        //������
	{
		extreme_z1 = (-1 * beizer_zb + sqrt(delta_z)) / (2 * beizer_za);
		extreme_z2 = (-1 * beizer_zb - sqrt(delta_z)) / (2 * beizer_za);
	}
	else if (fabs(delta_z) < limit_zero)          //һ����
	{
		extreme_z1 = (-1 * beizer_zb) / (2 * beizer_za);
	}
	//����Ϊ�޽�
	x_sections = new section[divide];
	z_sections = new section[divide];
	for (int i = 0; i < divide; i++)
	{
		x_sections[i] = get_section_x(i);
		z_sections[i] = get_section_z(i);
	}
	//�������ɵ����Ͻ�����
	build_tree();
}


BeizerBSPTree::~BeizerBSPTree()
{
	delete[] x_sections;
	delete[] z_sections;
}

section BeizerBSPTree::get_section_x(int t)
{
	double lower_bound = (double)t * (1 / (double)divide);
	double upper_bound = (double)(t + 1) * (1 / (double)divide);
	double min_x, max_x;           //��[lower_bound,upper_bound)�ϵ������Сֵ
	double upper_value = beizer_line.get_point(upper_bound).x;
	double lower_value = beizer_line.get_point(lower_bound).x;
	min_x = min(upper_value, lower_value);
	max_x = max(upper_value, lower_value);
	if (lower_bound <= extreme_x1 && upper_bound > extreme_x1)
	{
		double extreme_x1_value = beizer_line.get_point(extreme_x1).x;
		min_x = min(min_x, extreme_x1_value);
		max_x = max(max_x, extreme_x1_value);
	}
	if (lower_bound <= extreme_x2 && upper_bound > extreme_x2)
	{
		double extreme_x2_value = beizer_line.get_point(extreme_x2).x;
		min_x = min(min_x, extreme_x2_value);
		max_x = max(max_x, extreme_x2_value);
	}
	return section(min_x, max_x);
}

section BeizerBSPTree::get_section_z(int t)
{
	double lower_bound = (double)t * (1 / (double)divide);
	double upper_bound = (double)(t + 1) * (1 / (double)divide);
	double min_z, max_z;           //��[lower_bound,upper_bound)�ϵ������Сֵ
	double upper_value = beizer_line.get_point(upper_bound).z;
	double lower_value = beizer_line.get_point(lower_bound).z;
	min_z = min(upper_value, lower_value);
	max_z = max(upper_value, lower_value);
	if (lower_bound <= extreme_z1 && upper_bound > extreme_z1)
	{
		double extreme_z1_value = beizer_line.get_point(extreme_z1).z;
		min_z = min(min_z, extreme_z1_value);
		max_z = max(max_z, extreme_z1_value);
	}
	if (lower_bound <= extreme_z2 && upper_bound > extreme_z2)
	{
		double extreme_z2_value = beizer_line.get_point(extreme_z2).z;
		min_z = min(min_z, extreme_z2_value);
		max_z = max(max_z, extreme_z2_value);
	}
	return section(min_z, max_z);
}

BoundingBox BeizerBSPTree::get_boundingbox(int t, int theta)
{
	double min_z = z_sections[t].Min;
	double max_z = z_sections[t].Max;
	double min_x, max_x, min_y, max_y;
	double rotate_min = (theta / (double)divide) * PI * 2;
	double rotate_max = ((theta + 1) / (double)divide) * PI * 2;
	double temp_x1, temp_x2, temp_x3, temp_x4;
	double temp_y1, temp_y2, temp_y3, temp_y4;
	temp_x1 = cos(rotate_min) * x_sections[t].Min;
	temp_x2 = cos(rotate_min) * x_sections[t].Max;
	temp_x3 = cos(rotate_max) * x_sections[t].Min;
	temp_x4 = cos(rotate_max) * x_sections[t].Max;
	temp_y1 = sin(rotate_min) * x_sections[t].Min;
	temp_y2 = sin(rotate_min) * x_sections[t].Max;
	temp_y3 = sin(rotate_max) * x_sections[t].Min;
	temp_y4 = sin(rotate_max) * x_sections[t].Max;
	min_x = min(temp_x1, min(temp_x2, min(temp_x3, temp_x4)));
	max_x = max(temp_x1, max(temp_x2, max(temp_x3, temp_x4)));
	min_y = min(temp_y1, min(temp_y2, min(temp_y3, temp_y4)));
	max_y = max(temp_y1, max(temp_y2, max(temp_y3, temp_y4)));
	return BoundingBox(vector3<double>(min_x, min_y, min_z), vector3<double>(max_x, max_y, max_z));
}

BeizerBSPTree_Node** BeizerBSPTree::merge_child(int t_num, int theta_num, BeizerBSPTree_Node** Childs, bool merge_type)     //��merge_typeΪtrue���ϲ�t_num,����,�ϲ�theta_num
{
	BeizerBSPTree_Node** return_array = new BeizerBSPTree_Node*[(t_num * theta_num) / 2];
	if (merge_type)        //merge by t
	{
		for (int i = 0; i < (t_num / 2) * theta_num; i += 1)
		{
			return_array[i] = new BeizerBSPTree_Node;
			return_array[i]->boundingbox = Merge_BoundingBox((Childs[2 * i])->boundingbox, (Childs[2 * i + 1])->boundingbox);
			return_array[i]->left_child = Childs[2 * i];
			return_array[i]->right_child = Childs[2 * i + 1];
		}
		return return_array;
	}
	else                    //merge by theta
	{
		for (int i = 0; i < theta_num / 2; i += 1)
		{
			for (int j = 0; j < t_num; j++)
			{
				return_array[i * t_num + j] = new BeizerBSPTree_Node;
				return_array[i * t_num + j]->boundingbox = Merge_BoundingBox(Childs[2 * i * t_num + j]->boundingbox, Childs[(2 * i + 1) * t_num + j]->boundingbox);
				return_array[i * t_num + j]->left_child = Childs[2 * i * t_num + j];
				return_array[i * t_num + j]->right_child = Childs[(2 * i + 1) * t_num + j];
			}
		}
		return return_array;
	}
}

void BeizerBSPTree::build_tree()
{
	bool merge_flag = true;
	int t_size = divide, theta_size = divide;
	BeizerBSPTree_Node** current_layer = new BeizerBSPTree_Node*[t_size * theta_size];
	for(int i = 0; i < theta_size; i++)
		for (int j = 0; j < t_size; j++)
		{
			current_layer[i * t_size + j] = new BeizerBSPTree_Node;
			current_layer[i * t_size + j]->boundingbox = get_boundingbox(j, i);
			//cout << "t size " << j << " " << "theta size" << i << endl;
			//cout << get_boundingbox(j, i).min_point << " " << get_boundingbox(j, i).max_point << endl;
			current_layer[i * t_size + j]->t = ((double)j / (double)t_size);
			current_layer[i * t_size + j]->theta = ((double)i / (double)theta_size) * PI * 2;
		}
	while (t_size != 1 || theta_size != 1)
	{
		current_layer = merge_child(t_size, theta_size, current_layer, merge_flag);
		if (merge_flag)
		{
			t_size /= 2;
		}
		else
		{
			theta_size /= 2;
		}
		merge_flag = !merge_flag;
	}
	root = current_layer[0];
}

bool BeizerBSPTree::intersect(Ray input_ray, vector3<double>& input_point)
{
	double intersect_t = std::numeric_limits<double>::max();
	double t_surface = NOT_LEGAL, theta_surface = NOT_LEGAL;
	RayTreeIntersect(input_ray, root, intersect_t, t_surface, theta_surface);
	//cout << input_ray.start_point + input_ray.direction * intersect_t;
	if (intersect_t < std::numeric_limits<double>::max() && t_surface != NOT_LEGAL && theta_surface != NOT_LEGAL)         //��bounding_box�ཻ
	{
		if (NewtonIteration(input_ray, intersect_t, t_surface, theta_surface))
		{
			input_point = input_ray.start_point + input_ray.direction * intersect_t;
			last_linet = intersect_t;
			last_surfacet = t_surface;
			last_theta = theta_surface;
			return true;
		}
		else
		{
			return false;
		}
	}
	else              //��bounding_box���ཻ
	{
		return false;
	}
}

void BeizerBSPTree::RayTreeIntersect(Ray input_ray, BeizerBSPTree_Node* tree_node, double& t, double& t_surface, double& theta_surface)
{
	if (tree_node->left_child == nullptr && tree_node->right_child == nullptr)           //leaf node,����point
	{
		double temp_tmin, temp_tmax;
		vector3<double> intersection_point;
		(tree_node->boundingbox).intersect(input_ray, intersection_point, temp_tmin, temp_tmax);
		if (temp_tmin > -1 * limit_zero)
		{
			if (temp_tmin < t)
			{
				cout << t << endl;
				t = temp_tmin;
				t_surface = tree_node->t;
				theta_surface = tree_node->theta;
			}
		}
		else if (temp_tmax > -1 * limit_zero)
		{
			if (temp_tmax < t)
			{
				t = temp_tmax;
				t_surface = tree_node->t;
				theta_surface = tree_node->theta;
			}
		}
		return;
	}
	assert(tree_node->left_child != nullptr && tree_node->right_child != nullptr);
	vector3<double> intersect_point;
	if ((tree_node->left_child->boundingbox).intersect(input_ray, intersect_point))
	{
		RayTreeIntersect(input_ray, tree_node->left_child, t, t_surface, theta_surface);
	}
	if ((tree_node->right_child->boundingbox).intersect(input_ray, intersect_point))
	{
		RayTreeIntersect(input_ray, tree_node->right_child, t, t_surface, theta_surface);
	}
}

bool BeizerBSPTree::NewtonIteration(Ray input_ray, double& line_t, double& surface_t, double& theta)
{
	double delta_t, delta_surfacet, delta_theta;
	for (int i = 0; i < 5; i++)
	{
		vector3<double> beizer_point = beizer_line.get_point(surface_t);
		vector3<double> beizer_partial_surfacet = beizer_line.Beizer_Derivative(surface_t);
		vector3<double> surface_partial_surfacet = vector3<double>(cos(theta) * beizer_partial_surfacet.x, sin(theta) * beizer_partial_surfacet.x, beizer_partial_surfacet.z);
		vector3<double> surface_partial_theta = vector3<double>(-1 * sin(theta) * beizer_point.x, cos(theta) * beizer_point.x, 0);
		vector3<double> f_value = input_ray.start_point + input_ray.direction * line_t - vector3<double>(beizer_point.x * cos(theta), beizer_point.x * sin(theta), beizer_point.z);
		double D = input_ray.direction * surface_partial_surfacet.cross_product(surface_partial_theta);
		if (fabs(D) < limit_zero)
			return false;
		delta_t = surface_partial_surfacet * (surface_partial_theta.cross_product(f_value)) / D;
		delta_surfacet = input_ray.direction * (surface_partial_theta.cross_product(f_value)) / D;
		delta_theta = input_ray.direction * (surface_partial_surfacet.cross_product(f_value)) / D;
		line_t -= delta_t;
		surface_t -= delta_surfacet;
		theta += delta_theta;
		//cout << delta_t << " " << delta_surfacet << " " << delta_theta << endl;
		//cout << surface_partial_surfacet<< endl;
	}
	if (max(fabs(delta_t), max(fabs(delta_surfacet), fabs(delta_theta))) > solve_precision)          //��Ϊ����ʱ�����ˣ�û�н���
	{
		return false;
	}
	else
	{
		return true;
	}
}