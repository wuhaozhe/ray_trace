#include "Point.h"

vector3<double> reflect(vector3<double> in, vector3<double> normal_vector)          //返回以normal_vector为法向量,in为射入的单位化向量
{
	if (normal_vector * in > 0)
	{
		normal_vector = normal_vector * -1;                //保证法向量的方向
	}
	return in - normal_vector * (2 * (in * normal_vector));
}

bool refract(vector3<double> in, vector3<double> normal_vector, double ni, double nt, vector3<double> &out) //in为入射光,normal_vector为法向量,ni为入射光一侧折射率，nt为反射光一侧折射率,out为折射光
{                                               //bool返回是否有折射光，若否，说明发生全反射
	in = in * -1;
	double cos_i = in * normal_vector;         //通过叉积求cosooi
	if (cos_i < 0)
	{
		cos_i *= -1;
		normal_vector = normal_vector * -1;                 //保证法向量方向
	}
	double ni_cp_nt = ni / nt;                //ni与nt比值
	double square_cos_t = 1 - ni_cp_nt * ni_cp_nt * (1 - cos_i * cos_i);       //cos_t平方
	if (square_cos_t <= 0 || abs(square_cos_t) < limit_zero)
	{
		return false;               //发生全反射
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