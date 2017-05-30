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
	photon current_photon;      //当前节点所存储的光子
	double position[3];         //当前点的位置
	int axis;              //当前节点划分的轴
	kd_node* left_child;
	kd_node* right_child;
	bool is_leaf()
	{
		return left_child == nullptr && right_child == nullptr;
	}
	kd_node(photon input_photon): current_photon(input_photon), left_child(nullptr), right_child(nullptr), axis(0)
	{
		position[0] = current_photon.photon_ray.start_point.x;
		position[1] = current_photon.photon_ray.start_point.y;
		position[2] = current_photon.photon_ray.start_point.z;
		//cout << position[0] << " " << position[1] << " " << position[2] << endl;
	}
};
class k_collection            //size 为k的一个链表，同时存储一个最大值
{
	int k_size;
public:
	list<pair<kd_node*, double>> kdnode_list;            //第一项为当前节点，第二项为当前节点与target的距离
	bool add_node(kd_node* input_node, double input_distance)
	{
		if (kdnode_list.size() < k_size)          //必然会插入
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
		else               //如果距离小于max_value则插入
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
	double max_value;       //k个节点中距离的最大值
	k_collection(int k): k_size(k)
	{
		max_value = numeric_limits<double>::max();
		kdnode_list.clear();
	}
};
double getvalue(photon input, int dimension);
void quickSelect(vector<photon>& photon_array, int k, int dimension);             //找第k大的点
class kdTree
{
private:
	kd_node* root;
	kd_node* build_kdTree(vector<photon> photon_array, int depth);
	kd_node* create_leaf(photon input_photon);
	void nearest(kd_node* current, double* target, k_collection& collection);
	double distance(double* a, double* b);
public:
	const int k_size = 15;            //KNN算法中k的取值
	kdTree(vector<photon>& photon_array);
	k_collection knn(vector3<double> target);         //寻找k个近邻
	~kdTree();
};

