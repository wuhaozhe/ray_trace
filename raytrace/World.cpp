#include "World.h"



World::World(): light(vector3<double>(0, 0, 10), vector3<double>(0, 0, -1), 0.9, Color(255, 255, 255, 255))
{
	camera = Camera(vector3<double>(-20, 0, 5), vector3<double>(1, 0, 0), vector3<double>(0, 0, 1));
	drawer_instance = drawer::get_instance();
	drawer_instance->set_size(camera.size, camera.size);
}


World::~World()
{
}

void World::add_object(Object* obj)
{
	objects.push_back(obj);
}

Color World::ray_cast(int i, int j)
{
	Color return_color;
	double distance = 10000000000;
	Ray current_ray = camera.generate_ray(i, j);             //产生i, j像素上的光线
	//枚举world中每一个物体求交点，选取一个最近的交点
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		vector3<double> intersect_point;
		if (objects[i]->intersect(current_ray, intersect_point))
		{
			double length = (intersect_point - camera.position).length;
			if (length < distance)
			{
				distance = length;
				return_color = objects[i]->get_color(intersect_point, current_ray.direction, light);
			}
		}
	}
	return return_color;
}

void World::ray_cast()
{
	cout << camera.size<<endl;
	for(int i = 0; i < camera.size; i++)
		for (int j = 0; j < camera.size; j++)
		{
			//cout << i << " " << j << endl;
			drawer_instance->set_pixel(i, j, ray_cast(i - (camera.size / 2), j - (camera.size / 2)));
		}
}