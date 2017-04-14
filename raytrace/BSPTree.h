#ifndef BSPTREE_H
#define BSPTREE_H
#include "Point.h"
#include "Object.h"
#include "Ray.h"
#include "BoundingBox.h"
#include <vector>
#include <limits>
using namespace std;
class BSPTree_Node
{
private:

public:
	BSPTree_Node* left_child;      //����
	BSPTree_Node* right_child;       //�Һ���
	BoundingBox box;                 //��ǰ�ڵ��������box
	vector<int> object_list;           //�洢��ǰ�ڵ����洢��object������
	int cut;                          //��cutΪ0�� ������x�᷽����,cutΪ1��������y�᷽����,cutΪ2��������z�᷽����
	BSPTree_Node(): left_child(nullptr), right_child(nullptr), cut(0)
	{
	}
};
class BSPTree                  //������
{
private:
	vector<Object*> objects;
	BSPTree_Node* root;                  //BSPTree_Node�ĸ��ڵ�
	void resursive_build(BSPTree_Node* parent, int current_depth);               //���ø��ڵ�ݹ�Ĺ�������
public:
	int leaf_object_num = 2;        //Ҷ�ӽ�����������
	int depth_limit = 100;            //bsp_tree���������
	BSPTree();
	~BSPTree();
	bool intersect_point(Ray input_ray, int &object_index, vector3<double> &point);                   //��ȡ����input_ray����Ľ���
	void build_tree();                   //������
};

#endif