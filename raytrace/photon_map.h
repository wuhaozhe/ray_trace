#pragma once
#include "Point.h"
#include "drawer.h"
#include "Object_Collections.h"
#include "photon.h"
#include "kdTree.h"
#include <cstdlib>
#include <ctime>
#include <stack>
using namespace std;

class photon_map               //光子映射
{
private:
	static photon_map* instance;                 //singleton
	vector<Object*> objects;                  //存储所有物体
	bool single_light;                        //是否只有单个光源
	vector3<double> light_position;            //当是一个点光源时，光源的起始位置
	Color light_color;
	photon init_photon();                     //在光源处产生一个初始的光子
	void generate_photon();                 //光源产生单个光子，随后该光子不断弹射直到被吸收或者到达递归上限
	bool intersect_point(Ray input_ray, int &object_index, vector3<double> &point);            //求取距离input_ray最近的交点 
	void change_color(photon& input_photon, object_feature input_feature, bool reflect_flag);                     //对光子做色光变化, 若reflect_flag为true，做反射的色光变化，否则为折射的色光变化
	kdTree* Tree;
public:
	vector<photon> photon_array;              //存储所有的光子
	const int recursive_depth = 5;             //发射光子时的递归深度
	static photon_map* get_instance()
	{
		if (instance == nullptr)
		{
			instance = new photon_map();
		}
		return instance;
	}
	void init_photon_map(vector<Object*> input_objects, vector3<double> input_light_position, Color input_color)
	{
		objects = input_objects;
		light_position = input_light_position;
		light_color = input_color;
		single_light = true;
	}
	void generate_photon(int photon_num);              //产生光子
	Color get_color(vector3<double> position, vector3<double> input_normal, vector3<double> input_view, double pd, double ps);
	photon_map();
	~photon_map();
};

