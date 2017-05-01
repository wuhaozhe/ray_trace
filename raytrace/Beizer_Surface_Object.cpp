#include "Beizer_Surface_Object.h"
#include "Triangle.h"
#include <vector>
#include <iostream>
#include <assert.h>

void Beizer_Surface_Object::init()
{
	object_type = Object_type::_Beizer_Surface;
}

Beizer_Surface_Object::Beizer_Surface_Object(int line, int row, vector3<double> point_array[]): beizer_surface(line, row)
{
	init();
	color_feature.Kdr = 0.3;
	color_feature.Ksr = 0.65;
	color_feature.Kar = 0.05;
	double min_x = 100000, min_y = 100000, min_z = 100000;
	double max_x = -100000, max_y = -100000, max_z = -100000;
	for(int i = 0; i < line; i++)
		for (int j = 0; j < row; j++)
		{
			if (point_array[i * row + j].x < min_x)
			{
				min_x = point_array[i * row + j].x;
			}
			if (point_array[i * row + j].y < min_y)
			{
				min_y = point_array[i * row + j].y;
			}
			if (point_array[i * row + j].z < min_z)
			{
				min_z = point_array[i * row + j].z;
			}
			if (point_array[i * row + j].x > max_x)
			{
				max_x = point_array[i * row + j].x;
			}
			if (point_array[i * row + j].y > max_y)
			{
				max_y = point_array[i * row + j].y;
			}
			if (point_array[i * row + j].z > max_z)
			{
				max_z = point_array[i * row + j].z;
			}
			beizer_surface.set_control_point(i, j, point_array[i * row + j]);
		}
	vector3<double> min_point(min_x, min_y, min_z);
	vector3<double> max_ponit(max_x, max_y, max_z);
	Tree = BSPTree(min_point, max_ponit);
	box = new BoundingBox(min_point, max_ponit);
	vector< vector3<double> > points;
	vector< vector3<int> > meshes;
	beizer_surface.generate_meshes(points, meshes);
	for (int i = 0; i < meshes.size(); i++)       //产生三角面片
	{
		Object* temp = new Triangle(points[meshes[i].x - 1], points[meshes[i].y - 1], points[meshes[i].z - 1]);
		Tree.objects.push_back(temp);
	}
	//建立BSPTree
	Tree.build_tree();
	beizer_surface.output_obj();
}


Beizer_Surface_Object::~Beizer_Surface_Object()
{
	delete box;
}

bool Beizer_Surface_Object::intersect(Ray input_ray, vector3<double> &intersect_point)        //用map存储点对应的物体的index
{
	int intersect_index;
	if (box->intersect(input_ray, intersect_point))
	{
		//cout << input_ray.start_point << " " << input_ray.direction << " box " << box->min_point << " " << box->max_point << endl;
		if (Tree.intersect_point(input_ray, intersect_index, intersect_point))
		{
			//cout << "here" << endl;
			point_index_map[intersect_point] = intersect_index;
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
		//cout << input_ray.start_point << " " << input_ray.direction << " box " << box->min_point << " " << box->max_point << endl;
	}
}

Color Beizer_Surface_Object::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)
{
	assert(point_index_map.find(target_pos) != point_index_map.end());
	return Tree.objects[point_index_map[target_pos]]->get_color_normalvec(target_pos, view_direction, light, in);
}