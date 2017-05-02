#pragma once
#define NOT_LEGAL -1
#include "Beizer_Line.h"
#include "BoundingBox.h"
struct section       //区间（左闭右开区间）
{
	double Min;
	double Max;
	section(double in_min, double in_max): Min(in_min), Max(in_max)
	{

	}
	section() :Min(0), Max(0)
	{

	}
};
class BeizerBSPTree_Node
{
public:
	BeizerBSPTree_Node* left_child;
	BeizerBSPTree_Node* right_child;
	BoundingBox boundingbox;
	BeizerBSPTree_Node() :left_child(nullptr), right_child(nullptr)
	{

	}
};
class BeizerBSPTree
{
private:
	double beizer_xa, beizer_xb, beizer_xc;         //Beizer曲线对应的x方向上的导函数的参数（ax^2 + bx + c）
	double beizer_za, beizer_zb, beizer_zc;         //Beizer曲线对应的z方向上的导函数的参数（az^2 + bz + c）
	double extreme_x1, extreme_x2;                  //Beizer曲线对应的x方向上极值点的参数（二次方程有两个解）
	double extreme_z1, extreme_z2;                  //Beizer曲线对应的z方向上极值点的参数
	section get_section_x(int t);            //获取[t,t + 1)的最大值与最小值
	section get_section_z(int t);          
	BoundingBox get_boundingbox(int t, int theta);           //获取[t, t + 1), [theta, theta + 1)范围内的boundingbox
	Beizer_Line beizer_line;
	BeizerBSPTree_Node** merge_child(int t_num, int theta_num, BeizerBSPTree_Node** Childs, bool merge_type);            //传入Childs，根据子节点层的t的切分数和theta的切分数得到父层的节点
	void build_tree();
	BeizerBSPTree_Node* root;
	bool RayTreeIntersect(Ray input_ray, BeizerBSPTree_Node* tree_node, vector3<double>& point);
public:
	section* x_sections;            //缓存沿Beizer曲线x方向不同参数的最大值与最小值
	section* z_sections;            //缓存沿Beizer曲线z方向不同参数的最大值与最小值
	const double solve_precision = 0.01;       //beizer曲线求交时的精度
	const int divide = 32;           //根据参数将beizer曲线（以及旋转）划分为多少块
	BeizerBSPTree(vector3<double> point_array[]);        //要在BeizerBSPTree中初始化一个Beizer_Line（默认为3次Beizer曲线）
	bool intersect(Ray input_ray, vector3<double>& input_point);
	~BeizerBSPTree();
};

