#pragma once
#define NOT_LEGAL -1
#include "Beizer_Line.h"
#include "BoundingBox.h"
struct section       //���䣨����ҿ����䣩
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
	double t, theta;
	BoundingBox boundingbox;
	BeizerBSPTree_Node() :left_child(nullptr), right_child(nullptr), t(NOT_LEGAL), theta(NOT_LEGAL)
	{

	}
};
class BeizerBSPTree
{
private:
	double beizer_xa, beizer_xb, beizer_xc;         //Beizer���߶�Ӧ��x�����ϵĵ������Ĳ�����ax^2 + bx + c��
	double beizer_za, beizer_zb, beizer_zc;         //Beizer���߶�Ӧ��z�����ϵĵ������Ĳ�����az^2 + bz + c��
	double extreme_x1, extreme_x2;                  //Beizer���߶�Ӧ��x�����ϼ�ֵ��Ĳ��������η����������⣩
	double extreme_z1, extreme_z2;                  //Beizer���߶�Ӧ��z�����ϼ�ֵ��Ĳ���
	section get_section_x(int t);            //��ȡ[t,t + 1)�����ֵ����Сֵ
	section get_section_z(int t);          
	
	Beizer_Line beizer_line;
	BeizerBSPTree_Node** merge_child(int t_num, int theta_num, BeizerBSPTree_Node** Childs, bool merge_type);            //����Childs�������ӽڵ���t���з�����theta���з����õ�����Ľڵ�
	void build_tree();
	BeizerBSPTree_Node* root;
	void RayTreeIntersect(Ray input_ray, BeizerBSPTree_Node* tree_node, double& t, double& t_surface, double& theta_surface);          //���յ�t���������Ĳ���,t_surfaceΪ�������ϵĲ���,thetaΪ����ǶȵĲ���
	bool NewtonIteration(Ray input_ray, double& t, double& u, double& v);             //t��ֱ�ߵĲ�����u,v������Ĳ���
	double last_linet, last_surfacet, last_theta;
public:
	BoundingBox get_boundingbox(int t, int theta);           //��ȡ[t, t + 1), [theta, theta + 1)��Χ�ڵ�boundingbox
	section* x_sections;            //������Beizer����x����ͬ���������ֵ����Сֵ
	section* z_sections;            //������Beizer����z����ͬ���������ֵ����Сֵ
	const double solve_precision = 0.05;       //beizer������ʱ�ľ���
	const int divide = 32;           //���ݲ�����beizer���ߣ��Լ���ת������Ϊ���ٿ�
	const int iteration_times = 5;   //ţ�ٵ����ĵ�������
	BeizerBSPTree(vector3<double> point_array[]);        //Ҫ��BeizerBSPTree�г�ʼ��һ��Beizer_Line��Ĭ��Ϊ3��Beizer���ߣ�
	bool intersect(Ray input_ray, vector3<double>& input_point);
	~BeizerBSPTree();
};

