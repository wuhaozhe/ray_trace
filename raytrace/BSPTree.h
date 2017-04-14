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
	BSPTree_Node* left_child;      //左孩子
	BSPTree_Node* right_child;       //右孩子
	BoundingBox box;                 //当前节点所代表的box
	vector<int> object_list;           //存储当前节点所存储的object的索引
	int cut;                          //若cut为0， 代表沿x轴方向切,cut为1，代表沿y轴方向切,cut为2，代表沿z轴方向切
	BSPTree_Node(): left_child(nullptr), right_child(nullptr), cut(0)
	{
	}
};
class BSPTree                  //二分树
{
private:
	vector<Object*> objects;
	BSPTree_Node* root;                  //BSPTree_Node的根节点
	void resursive_build(BSPTree_Node* parent, int current_depth);               //利用父节点递归的构造子树
public:
	int leaf_object_num = 2;        //叶子结点的物体数量
	int depth_limit = 100;            //bsp_tree的深度限制
	BSPTree();
	~BSPTree();
	bool intersect_point(Ray input_ray, int &object_index, vector3<double> &point);                   //获取距离input_ray最近的交点
	void build_tree();                   //建立树
};

#endif