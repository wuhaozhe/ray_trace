#pragma once
#include "Point.h"
#include "photon.h"
#include <list>
#include <utility>
#include <assert.h>
#include <limits>
using namespace std;
class kd_node
{
public:
	double position[3];         //��ǰ���λ��
	int axis;              //��ǰ�ڵ㻮�ֵ���
	kd_node* left_child;
	kd_node* right_child;
	photon current_photon;      //��ǰ�ڵ����洢�Ĺ���
	kd_node(photon input_photon): current_photon(input_photon), left_child(nullptr), right_child(nullptr), axis(0)
	{
		position[0] = current_photon.photon_ray.start_point.x;
		position[1] = current_photon.photon_ray.start_point.y;
		position[2] = current_photon.photon_ray.start_point.z;
		//cout << position[0] << " " << position[1] << " " << position[2] << endl;
	}
};
class k_collection            //size Ϊk��һ������ͬʱ�洢һ�����ֵ
{
	int k_size;
public:
	list<pair<kd_node*, double>> kdnode_list;            //��һ��Ϊ��ǰ�ڵ㣬�ڶ���Ϊ��ǰ�ڵ���target�ľ���
	bool add_node(kd_node* input_node, double input_distance)
	{
		if (kdnode_list.size() < k_size)          //��Ȼ�����
		{
			double distance = input_distance;
			auto it = kdnode_list.begin();
			while (it != kdnode_list.end() && it->second < distance)
			{
				++it;
			}
			kdnode_list.insert(it, make_pair(input_node, distance));
			it = kdnode_list.end(); --it;
			max_value = it->second;
			return true;
		}
		else               //�������С��max_value�����
		{
			double distance = input_distance;
			if (distance >= max_value)
			{
				return false;
			}
			else
			{
				kdnode_list.pop_back();
				auto it = kdnode_list.begin();
				while (it != kdnode_list.end() && it->second < distance)
				{
					++it;
				}
				kdnode_list.insert(it, make_pair(input_node, distance));
				it = kdnode_list.end(); --it;
				max_value = it->second;
				return true;
			}
		}
	}
	double max_value;       //k���ڵ��о�������ֵ
	k_collection(int k): k_size(k)
	{
		max_value = numeric_limits<double>::max();
		kdnode_list.clear();
	}
};
double getvalue(photon input, int dimension);
bool compare_x(photon a, photon b);
bool compare_y(photon a, photon b);
bool compare_z(photon a, photon b);
//void quickSelect(vector<photon>& photon_array, int k, int dimension, int low, int high);             //�ҵ�k��ĵ�,low������������������high�����Ҳࣨ���ұգ�
class kdTree
{
private:
	kd_node* root;
	kd_node* build_kdTree(vector<photon>& photon_array, int depth, int left_bound, int right_bound);             //���ұ�����
	kd_node* create_leaf(photon input_photon);
	void nearest(kd_node* current, double* target, k_collection& collection);
	double distance(double* a, double* b);
public:
	const int k_size = 2000;            //KNN�㷨��k��ȡֵ
	kdTree(vector<photon> photon_array);
	k_collection knn(vector3<double> target);         //Ѱ��k������
	~kdTree();
};

