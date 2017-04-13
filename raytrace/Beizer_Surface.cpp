#include "Beizer_Surface.h"





Beizer_Surface::~Beizer_Surface()
{
	for (int i = 0; i < line; i++)
	{
		delete[] controlled_points[i];
	}
	delete[] controlled_points;
}


Beizer_Surface::Beizer_Surface(int input_line, int input_row): line(input_line), row(input_row)
{
	controlled_points = new vector3<double>*[line];
	for (int i = 0; i < line; i++)
	{
		controlled_points[i] = new vector3<double>[row];
	}
}

void Beizer_Surface::set_control_point(int x, int y, vector3<double> input)
{
	controlled_points[x][y] = input;
}

vector3<double> Beizer_Surface::get_point(double u, double v)
{
	vector3<double>* vec1 = new vector3<double>[line];             //dp时的临时变量
	vector3<double>* vec2 = new vector3<double>[line];           
	vector3<double>* vec3 = new vector3<double>[row];              //存储line级递推后得到的顶点组
	vector3<double>* vec4 = new vector3<double>[row];              //row级dp时的临时变量
	for (int i = 0; i < row; i++)                //通过dp得到p(m, 0, 0, j)
	{
		std::copy(controlled_points[i], controlled_points[i] + line, vec1);
		for (int j = 0; j < line - 1; j++)
		{
			if ((j & 1) == 0)
			{
				for (int k = 0; k < line - j - 1; k++)
				{
					vec2[k] = vec1[k] * (1 - u) + vec1[k + 1] * u;
				}
			}
			else
			{
				for (int k = 0; k < line - j - 1; k++)
				{
					vec1[k] = vec2[k] * (1 - u) + vec2[k + 1] * u;
				}
			}
		}
		if ((line & 1) == 0)
		{
			vec3[i] = vec2[0];
		}
		else
		{
			vec3[i] = vec1[0];
		}
	}
	for (int i = 0; i < row - 1; i++)
	{
		if ((i & 1) == 0)
		{
			for (int j = 0; j < row - i - 1; j++)
			{
				vec4[j] = vec3[j] * (1 - v) + vec3[j + 1] * v;
			}
		}
		else
		{
			for (int j = 0; j < row - i - 1; j++)
			{
				vec3[j] = vec4[j] * (1 - v) + vec4[j + 1] * v;
			}
		}
	}
	if ((row & 1) == 0)
	{
		vector3<double> return_vector = vec4[0];
		delete[] vec1;
		delete[] vec2;
		delete[] vec3;
		delete[] vec4;
		return return_vector;
	}
	else
	{
		vector3<double> return_vector = vec3[0];
		delete[] vec1;
		delete[] vec2;
		delete[] vec3;
		delete[] vec4;
		return return_vector;
	}
}

void Beizer_Surface::generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes)
{
	int num_u = 1 / du + 1, num_v = 1 / dv + 1;        //将要生成的u, v的数量
	int counter = 0;
	for (double u = 0.0f, i = 0; u <= (1.0f + limit_zero); u += du, i++)
	{
		for (double v = 0.0f, j = 0; v <= (1.0f + limit_zero); v += dv, j++)
		{
			points.push_back(get_point(u, v));
			counter++;
			if (i != 0 && j != 0)
			{
				meshes.push_back(vector3<int>(counter - num_v - 1, counter - num_v, counter - 1));
				meshes.push_back(vector3<int>(counter - num_v, counter, counter - 1));
			}
		}
	}
}

void Beizer_Surface::output_obj()
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