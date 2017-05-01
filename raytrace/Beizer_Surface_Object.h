#pragma once
#include "BSPTree.h"
#include "Object.h"
#include "Beizer_Surface.h"
#include "BoundingBox.h"
#include <map>
using namespace std;

class Beizer_Surface_Object :public Object
{
private:
	void init();
	BSPTree Tree;
	Beizer_Surface beizer_surface;
	BoundingBox* box;           //��ǰBeizer����İ�Χ��
	map<vector3<double>, int> point_index_map;             //�洢���Ӧ��������Ƭ������
public:
	Beizer_Surface_Object(int line, int row, vector3<double> point_array[]);    //a * line + b Ϊindex
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);   //inΪ������������
	~Beizer_Surface_Object();
};

