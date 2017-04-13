#pragma once
#include <vector>
#include "Point.h"
#include <assert.h>
using namespace std;

class Beizer_Line               //ʵ����Beizer����
{
private:
	vector<vector3<double> > controlled_point;               //beizer���ߵĿ��Ƶ�
public:
	vector3<double> get_point(double t);                    //ʹ��de Casteljau�㷨�������t����Ӧ�ĵ�
	void add_control_point(vector3 <double> input_point);               //���һ�����Ƶ�
	Beizer_Line();
	~Beizer_Line();
};

