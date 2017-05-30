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

class photon_map               //����ӳ��
{
private:
	static photon_map* instance;                 //singleton
	vector<Object*> objects;                  //�洢��������
	bool single_light;                        //�Ƿ�ֻ�е�����Դ
	vector3<double> light_position;            //����һ�����Դʱ����Դ����ʼλ��
	Color light_color;
	photon init_photon();                     //�ڹ�Դ������һ����ʼ�Ĺ���
	void generate_photon();                 //��Դ�����������ӣ����ù��Ӳ��ϵ���ֱ�������ջ��ߵ���ݹ�����
	bool intersect_point(Ray input_ray, int &object_index, vector3<double> &point);            //��ȡ����input_ray����Ľ��� 
	void change_color(photon& input_photon, object_feature input_feature, bool reflect_flag);                     //�Թ�����ɫ��仯, ��reflect_flagΪtrue���������ɫ��仯������Ϊ�����ɫ��仯
	kdTree* Tree;
public:
	vector<photon> photon_array;              //�洢���еĹ���
	const int recursive_depth = 5;             //�������ʱ�ĵݹ����
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
	void generate_photon(int photon_num);              //��������
	Color get_color(vector3<double> position, vector3<double> input_normal, vector3<double> input_view, double pd, double ps);
	photon_map();
	~photon_map();
};

