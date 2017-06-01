#define PI 3.1415926535
#include "BeizerBSPTree.h"
#include "PhongModel.h"
#include <assert.h>
#include <cmath>
#include <algorithm>
#include <iostream>

void BeizerBSPTree::init()
{
	object_type = Object_type::_Beizer_Rotate;
}
BeizerBSPTree::BeizerBSPTree(vector3<double> point_array[])
{
	init();
	//reflect_coefficient = 0.2;
	//reflective = true;
	//refractive = true;
	//refract_coefficient = 0.99;
	n = 1.05;
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
	if (delta_x > limit_zero)        //两个解
	{
		extreme_x1 = (-1 * beizer_xb + sqrt(delta_x)) / (2 * beizer_xa);         //有可能极值点的参数>1或<0
		extreme_x2 = (-1 * beizer_xb - sqrt(delta_x)) / (2 * beizer_xa);
	}
	else if (fabs(delta_x) < limit_zero)          //一个解
	{
		extreme_x1 = (-1 * beizer_xb) / (2 * beizer_xa);
	}
	//否则为无解,do nothing
	double delta_z = beizer_zb * beizer_zb - 4 * beizer_za * beizer_zc;
	if (delta_z > limit_zero)        //两个解
	{
		extreme_z1 = (-1 * beizer_zb + sqrt(delta_z)) / (2 * beizer_za);
		extreme_z2 = (-1 * beizer_zb - sqrt(delta_z)) / (2 * beizer_za);
	}
	else if (fabs(delta_z) < limit_zero)          //一个解
	{
		extreme_z1 = (-1 * beizer_zb) / (2 * beizer_za);
	}
	//否则为无解
	x_sections = new section[divide];
	z_sections = new section[divide];
	for (int i = 0; i < divide; i++)
	{
		x_sections[i] = get_section_x(i);
		z_sections[i] = get_section_z(i);
	}
	//接下来由低向上建立树
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
	double min_x, max_x;           //在[lower_bound,upper_bound)上的最大最小值
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
	double min_z, max_z;           //在[lower_bound,upper_bound)上的最大最小值
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

BeizerBSPTree_Node** BeizerBSPTree::merge_child(int t_num, int theta_num, BeizerBSPTree_Node** Childs, bool merge_type)     //若merge_type为true，合并t_num,否则,合并theta_num
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
	if (RayTreeIntersect(input_ray, root, intersect_t, t_surface, theta_surface))
	{
		last_linet = intersect_t;
		last_surfacet = t_surface;
		last_theta = theta_surface;
		input_point = input_ray.start_point + input_ray.direction * intersect_t;
		return true;
	}
	else
	{
		return false;
	}
}

bool BeizerBSPTree::RayTreeIntersect(Ray input_ray, BeizerBSPTree_Node* tree_node, double& t, double& t_surface, double& theta_surface)
{
	if (tree_node->left_child == nullptr && tree_node->right_child == nullptr)           //leaf node,回溯point
	{
		double temp_tmin, temp_tmax;
		vector3<double> intersection_point;

		if ((tree_node->boundingbox).intersect(input_ray, intersection_point, temp_tmin, temp_tmax))
		{
			double temp_t;
			if (temp_tmin > -1 * limit_zero)
			{
				temp_t = temp_tmin;
			}
			else if (temp_tmax > -1 * limit_zero)
			{
				temp_t = temp_tmax;
			}
			else
			{
				return false;            //不相交
			}
			if (NewtonIteration(input_ray, temp_t, tree_node->t, tree_node->theta))
			{
				if (fabs(temp_t) < min_distance)
				{
					return false;
				}
				else
				{
					t = temp_t;
					t_surface = tree_node->t;
					theta_surface = tree_node->theta;
					//cout << "t " << t << " surface_t " << t_surface << " theta " << theta_surface * 180 / PI << endl;
					//cout << input_ray.start_point + input_ray.direction * t << " "<<input_ray.start_point<<" "<<input_ray.direction<< endl;
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	assert(tree_node->left_child != nullptr && tree_node->right_child != nullptr);
	vector3<double> intersect_point;
	double t1, t2, t3, t4;
	bool flag_1, flag_2;
	flag_1 = (tree_node->left_child->boundingbox).intersect(input_ray, intersect_point, t1, t2);
	flag_2 = (tree_node->right_child->boundingbox).intersect(input_ray, intersect_point, t3, t4);
	if (flag_1 && flag_2)      //若和两个包围盒都相交
	{
		assert(t2 > -1 * limit_zero && t4 > -1 * limit_zero);
		if (t1 < -1 * limit_zero)     //点在包围盒内部
		{
			t1 = 0;
		}
		if (t3 < -1 * limit_zero)
		{
			t3 = 0;
		}
		if (t1 <= t3)        //优先访问近的
		{
			if (RayTreeIntersect(input_ray, tree_node->left_child, t, t_surface, theta_surface))
			{
				return true;
			}
			else
			{
				return RayTreeIntersect(input_ray, tree_node->right_child, t, t_surface, theta_surface);
			}
		}
		else
		{
			if (RayTreeIntersect(input_ray, tree_node->right_child, t, t_surface, theta_surface))
			{
				return true;
			}
			else
			{
				return RayTreeIntersect(input_ray, tree_node->left_child, t, t_surface, theta_surface);
			}
		}
	}
	else if (!flag_1 && flag_2)
	{
		return RayTreeIntersect(input_ray, tree_node->right_child, t, t_surface, theta_surface);
	}
	else if (flag_1 && !flag_2)
	{
		return RayTreeIntersect(input_ray, tree_node->left_child, t, t_surface, theta_surface);
	}
	else
	{
		return false;
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
	}
	if (max(fabs(delta_t), max(fabs(delta_surfacet), fabs(delta_theta))) > solve_precision)          //认为迭代时迭飞了，没有交点
	{
		return false;
	}
	else
	{
		if (surface_t < -1 * limit_zero || surface_t > 1 + limit_zero)
		{
			return false;
		}
		return true;
	}
}

Color BeizerBSPTree::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)
{
	light.direction = (target_pos - light.start_point).normallize();
	in = get_normalvec(target_pos, view_direction);
	if (in * light.direction > 0)
	{
		in = in * -1;
	}
	return PhongModel::reflect_color(light, in, view_direction, feature);
}

vector3<double> BeizerBSPTree::get_normalvec(vector3<double> target_pos, vector3<double> view_direction)
{
	vector3<double> p_partial_t = beizer_line.Beizer_Derivative(last_surfacet);
	vector3<double> beizer_point = beizer_line.get_point(last_surfacet);
	double x_partial_t = p_partial_t.x * cos(last_theta);
	double x_partial_theta = beizer_point.x * sin(last_theta) * -1;
	double y_partial_t = p_partial_t.x * sin(last_theta);
	double y_partial_theta = beizer_point.x * cos(last_theta);
	double z_partial_t = p_partial_t.z;
	double z_partial_theta = 0;
	double A = y_partial_t * z_partial_theta - y_partial_theta * z_partial_t;
	double B = z_partial_t * x_partial_theta - z_partial_theta * x_partial_t;
	double C = x_partial_t * y_partial_theta - x_partial_theta * y_partial_t;
	return vector3<double>(A, B, C).normallize();
}