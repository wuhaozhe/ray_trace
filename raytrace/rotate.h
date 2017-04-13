#ifndef ROTATE_H
#define ROTATE_H
#include "Point.h"
#include <cmath>
const double pi = 3.1415926;
class Rotate
{
private:
	double angle;           //��ת�Ƕ�
	vector3<double> axis;           //��ת��
public:
	Matrix3<double> rotate_matrix;         //��ת����
	Rotate(double input_angle, vector3<double> input_axis)
	{
		axis = input_axis.normallize();
		angle = input_angle;
		double cos_a = cos((angle / 180) * pi);
		double sin_a = sin((angle / 180) * pi);
		rotate_matrix.Array[0][0] = cos_a + (1 - cos_a) * axis.x * axis.x;               //������ת����
		rotate_matrix.Array[0][1] = (1 - cos_a) * axis.x * axis.y - axis.z * sin_a;
		rotate_matrix.Array[0][2] = (1 - cos_a) * axis.x * axis.z + axis.y * sin_a;
		rotate_matrix.Array[1][0] = (1 - cos_a) * axis.y * axis.x + axis.z * sin_a;
		rotate_matrix.Array[1][1] = cos_a + (1 - cos_a) * axis.y * axis.y;
		rotate_matrix.Array[1][2] = (1 - cos_a) * axis.y * axis.z - axis.x * sin_a;
		rotate_matrix.Array[2][0] = (1 - cos_a) * axis.z * axis.x - axis.y * sin_a;
		rotate_matrix.Array[2][1] = (1 - cos_a) * axis.z * axis.y + axis.x * sin_a;
		rotate_matrix.Array[2][2] = cos_a + (1 - cos_a) * axis.z * axis.z;
	}
};

#endif // ROTATE
