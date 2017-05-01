#ifndef POINT_H
#define POINT_H
#include <cmath>
#include <assert.h>
#include <iostream>
#define limit_zero 0.000000001                   //double < limit_zeor , it's 0

template<typename T>
class vector2
{
public:
	T x;
	T y;
	T length;           //vector2的长度
	vector2()
	{
		x = 0;
		y = 0;
		length = 0;
	}
	vector2(T input_x, T input_y)
	{
		x = input_x;
		y = input_y;
		length = sqrt(x * x + y * y);
	}
	vector2 normallize()
	{
		assert(length > limit_zero);
		vector2<T> normallized;
		normallized.length = 1;
		normallized.x = x / length;
		normallized.y = y / length;
		return normallized;
	}
	T operator*(vector2<T> &a)
	{
		T dot_x = a.x * x;
		T doy_y = a.y * y;
		return dot_x + dot_y;
	}
	vector2<T> operator*(const double &a)
	{
		T temp_x = x * a;
		T temp_y = y * a;
		return vector2<T>(temp_x, temp_y);
	}
	vector2<T> operator+(const vector2<T> &a)
	{
		T plus_x = a.x + x;
		T plus_y = a.y + y;
		return vector2<T>(plus_x, plus_y);
	}
	vector2<T> operator-(const vector2<T> &a)
	{
		T minus_x = x - a.x;
		T minus_y = y - a.y;
		return vector2<T>(minus_x, minus_y);
	}
	T produce_length()
	{
		length = sqrt(x * x + y * y);
		return length;
	}
};

template<typename T>
class vector3
{
public:
	T x;
	T y;
	T z;
	T length;
	vector3()
	{
		x = 0;
		y = 0;
		z = 0;
		length = 0;
	}
	vector3(T input_x, T input_y, T input_z)
	{
		x = input_x;
		y = input_y;
		z = input_z;
		length = sqrt(x * x + y * y + z * z);
	}
	vector3 normallize()
	{
		assert(length > limit_zero);
		vector3<T> normallized;
		normallized.length = 1;
		normallized.x = x / length;
		normallized.y = y / length;
		normallized.z = z / length;
		return normallized;
	}
	T operator*(vector3<T> &a)
	{
		T dot_x = x * a.x;
		T dot_y = y * a.y;
		T dot_z = z * a.z;
		return dot_x + dot_y + dot_z;
	}
	vector3<T> operator*(const double &a)
	{
		T temp_x = x * a;
		T temp_y = y * a;
		T temp_z = z * a;
		return vector3<T>(temp_x, temp_y, temp_z);
	}
	vector3<T> operator/(const double &a)
	{
		T temp_x = x / a;
		T temp_y = y / a;
		T temp_z = z / a;
		return vector3<T>(temp_x, temp_y, temp_z);
	}
	vector3<T> operator+(const vector3<T> &a)
	{
		T plus_x = a.x + x;
		T plus_y = a.y + y;
		T plus_z = a.z + z;
		return vector3<T>(plus_x, plus_y, plus_z);
	}
	vector3<T> operator-(const vector3<T> &a)
	{
		T minus_x = x - a.x;
		T minus_y = y - a.y;
		T minus_z = z - a.z;
		return vector3<T>(minus_x, minus_y, minus_z);
	}
	T produce_length()
	{
		length = sqrt(x * x + y * y + z * z);
		return length;
	}
	vector3<T> cross_product(vector3<T> a)
	{
		T cross_x = y * a.z - z * a.y;
		T cross_y = z * a.x - x * a.z;
		T cross_z = x * a.y - y * a.x;
		return vector3<T>(cross_x, cross_y, cross_z);
	}
};
inline bool operator<(const vector3<double> a, const vector3<double> b)
{
	return a.length < b.length;
}

template<typename T>
class Matrix3               //矩阵
{
public:
	T Array[3][3];
	vector3<T> operator*(const vector3<T> &a)
	{
		T temp_x = Array[0][0] * a.x + Array[0][1] * a.y + Array[0][2] * a.z;
		T temp_y = Array[1][0] * a.x + Array[1][1] * a.y + Array[1][2] * a.z;
		T temp_z = Array[2][0] * a.x + Array[2][1] * a.y + Array[2][2] * a.z;
		return vector3<T>(temp_x, temp_y, temp_z);
	}
};


std::ostream& operator<<(std::ostream& out, const vector3<double>& s);
std::ostream& operator<<(std::ostream& out, const vector3<int>& s);
vector3<double> reflect(vector3<double> in, vector3<double> normal_vector);         //返回以normal_vector为法向量,in为射入的单位化向量


bool refract(vector3<double> in, vector3<double> normal_vector, double ni, double nt, vector3<double> &out); //in为入射光,normal_vector为法向量,ni为入射光一侧折射率，nt为反射光一侧折射率,out为折射光

#endif