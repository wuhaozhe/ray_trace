#pragma once
#include "Beizer_Line.h"
#include "rotate.h"
#include <vector>
using namespace std;
class Beizer_rotate              //ʵ����Beizer������ת�õ�������
{
public:
	vector3<double> rotate_axis;             //Beizer������������ת����,�ǵ�λ���˵�
	double rotate_angle, beizer_step = 0.01;                 //ÿ����ת��ת�ĽǶ���Beizer������t�Ĳ���������ͼ��ľ�ϸ�̶ȣ� 
	Beizer_rotate();                         //Ĭ���ǰ�0, 0, 1��ת��
	Beizer_rotate(vector3<double> input_axis);
	~Beizer_rotate();
	void add_control_point(vector3<double> input_point);
	void generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes);         //������������Ӧ������
	void output_obj();                 //���obj�ļ�
private:
	Beizer_Line beizer_line;
	Rotate rotate;
};