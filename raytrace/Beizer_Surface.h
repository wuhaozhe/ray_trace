#pragma once
#include "Point.h"
#include <vector>
using namespace std;

class Beizer_Surface
{
	vector3<double> **controlled_points;
	int line, row;
public:
	double du = 0.011f, dv = 0.011f;
	Beizer_Surface(int input_line, int input_row);           //ָ��biezer_surface���м���
	void set_control_point(int x, int y, vector3<double> input);        //���õ�x�е�y��
	vector3<double> get_point(double u, double v);                   //��ò���Ϊu, v�������ϵĵ�
	void generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes);         //������������Ӧ������
	void output_obj();                 //���obj�ļ�
	~Beizer_Surface();
};