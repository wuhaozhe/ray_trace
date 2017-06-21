#pragma once
#include "BSPTree.h"
#include "Object.h"
#include "Beizer_Surface.h"
#include "BoundingBox.h"
#include <map>
using namespace std;

class ReadObj
{

};

class Beizer_Surface_Object :public Object
{
private:
	void init();
	Beizer_Surface beizer_surface;
	BoundingBox* box;           //当前Beizer曲面的包围盒
	int last_index;
	map<vector3<double>, int> point_index_map;             //存储点对应的三角面片的索引
public:
	BSPTree Tree;
	Beizer_Surface_Object(int line, int row, vector3<double> point_array[]);    //a * line + b 为index
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);   //in为法向量的引用
	vector3<double> get_normalvec(vector3<double> target_pos, vector3<double> view_direction);                    //获取该点的法向量
	~Beizer_Surface_Object();
};

