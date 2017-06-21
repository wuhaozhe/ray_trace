#pragma once
#include "Object_Collections.h"
#include <vector>
#include "Point.h"
#include "Camera.h"
#include "photon_map.h"
#include <stack>
using namespace std;
class World
{
private:
	drawer* drawer_instance;
	bool intersect_point(Ray input_ray, int &object_index, vector3<double> &point);            //��ȡ����input_ray����Ľ���
	//Color determine_color_normalvec(int object_index, vector3<double> point, vector3<double> in_direction, vector3<double> &normal_vector);        //�����ɫ���Ѿ��������Ӱ���ͷ�����������ĵ���������Ϊ���뷽��
	Color intersect_color(int n, Ray current_ray, stack<int> &refract_stack);                 //n����ݹ���ȣ�current_ray�������׷�ٵĹ���
	double current_n;                     //��ǰ��������
	bool intersect_other_objects(vector3<double> point);           //�жϵ�ǰ�㵽��Դ���߶��Ƿ������������ཻ
public:
	vector<Object*> objects;
	Color ray_trace(int i, int j);
	Color ray_trace_withDOF(int i, int j);
	const int recursive_depth = 5;                          //����׷�ٵĵݹ����
	const double photon_weight = 0.99;                       //Ϊ�˽��͸�Ƶ����������Դ����ֱ�����䵽һ����ʱ������ͼ����ɫ��phongģ�͵���ɫ�ı�ֵ
	Light light;
	Camera camera;
	void add_object(Object* input_obj);
	void photon_cast();
	void ray_trace();                //����׷��
	World();
	~World();
};