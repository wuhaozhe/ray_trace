#include "Point.h"

vector3<double> reflect(vector3<double> in, vector3<double> normal_vector)          //������normal_vectorΪ������,inΪ����ĵ�λ������
{
	if (normal_vector * in > 0)
	{
		normal_vector = normal_vector * -1;                //��֤�������ķ���
	}
	return in - normal_vector * (2 * (in * normal_vector));
}

bool refract(vector3<double> in, vector3<double> normal_vector, double ni, double nt, vector3<double> &out) //inΪ�����,normal_vectorΪ������,niΪ�����һ�������ʣ�ntΪ�����һ��������,outΪ�����
{                                               //bool�����Ƿ�������⣬����˵������ȫ����
	in = in * -1;
	double cos_i = in * normal_vector;         //ͨ�������cosooi
	if (cos_i < 0)
	{
		cos_i *= -1;
		normal_vector = normal_vector * -1;                 //��֤����������
	}
	double ni_cp_nt = ni / nt;                //ni��nt��ֵ
	double square_cos_t = 1 - ni_cp_nt * ni_cp_nt * (1 - cos_i * cos_i);       //cos_tƽ��
	if (square_cos_t <= 0 || abs(square_cos_t) < limit_zero)
	{
		return false;               //����ȫ����
	}
	double cos_t = sqrt(square_cos_t);
	out = (in * (-1 * (ni_cp_nt)) + normal_vector * (ni_cp_nt * cos_i - cos_t)).normallize();
	return true;
}

std::ostream& operator<<(std::ostream& out, const vector3<double>& s)
{
	out << "[" << s.x << " ," << s.y << " ," << s.z << "]";
	return out;
}

std::ostream& operator<<(std::ostream& out, const vector3<int>& s)
{
	out << "[" << s.x << " ," << s.y << " ," << s.z << "]";
	return out;
}