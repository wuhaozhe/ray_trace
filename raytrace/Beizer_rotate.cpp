#include "Beizer_rotate.h"
#include <cstdio>


Beizer_rotate::Beizer_rotate() : rotate_axis(0, 0, 1), rotate_angle(1), rotate(rotate_angle, rotate_axis)
{
	
}

Beizer_rotate::Beizer_rotate(vector3<double> input_axis) : rotate_axis(input_axis), rotate(rotate_angle, rotate_axis)
{

}

Beizer_rotate::~Beizer_rotate()
{
}

void Beizer_rotate::add_control_point(vector3<double> input_point)
{
	beizer_line.add_control_point(input_point);
}

void Beizer_rotate::generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes)
{
	int num = 1 / beizer_step + 1;            //beizer曲线方向上点的数量
	int counter = 0;
	for (double t = 0; t <= (1.0f + limit_zero); t += beizer_step)
	{
		points.push_back(beizer_line.get_point(t));
		counter++;
	}
	int num_rotate = 360 / rotate_angle;       //旋转体截面上每个点的数量
	for (double angle = rotate_angle; angle < 360; angle += rotate_angle)
	{
		for (int i = 0; i < num; i++)
		{
			vector3<double> temp = rotate.rotate_matrix * points[counter - num];
			points.push_back(temp);
			if (i == 0)
			{
				meshes.push_back(vector3<int>(counter - num + 1, counter - num + 2, counter + 1));
			}
			else if (i == num - 1)
			{
				meshes.push_back(vector3<int>(counter - num + 1, counter, counter + 1));
			}
			else
			{
				meshes.push_back(vector3<int>(counter - num + 1, counter - num + 2, counter + 1));
				meshes.push_back(vector3<int>(counter - num + 1, counter, counter + 1));
			}
			counter++;            //counter计算生成了多少个点
		}
	}
	counter -= num;
	for (int i = 0; i < num; i++)
	{
		if (i == 0)
		{
			meshes.push_back(vector3<int>(counter + 1, counter + 2, i + 1));
		}
		else if (i == num - 1)
		{
			meshes.push_back(vector3<int>(counter + 1, i, i + 1));
		}
		else
		{
			meshes.push_back(vector3<int>(counter + 1, counter + 2, i + 1));
			meshes.push_back(vector3<int>(counter + 1, i, i + 1));
		}
		counter++;
	}
}

void Beizer_rotate::output_obj()
{
	FILE* stream = fopen("beizer.obj", "w");
	vector<vector3<double> > points;
	vector<vector3<int> > meshes;
	generate_meshes(points, meshes);
	for (int i = 0; i < points.size(); i++)
	{
		fprintf(stream, "v %lf %lf %lf\n", points[i].x, points[i].y, points[i].z);
	}
	for (int i = 0; i < meshes.size(); i++)
	{
		fprintf(stream, "f %d %d %d\n", meshes[i].x, meshes[i].y, meshes[i].z);
	}
	fclose(stream);
}