#include "World.h"
#include <map>


World::World(): light(vector3<double>(0, 0, 15), vector3<double>(0, 0, -1), 0.9, Color(255, 255, 255, 255))
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
	unsigned int index = -1;                     //最近的一个点与物体
	vector3<double> closest_point;
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
				index = i;
				closest_point = intersect_point;
			}
		}
	}
	if (index >= 0)
	{
		vector3<double> intersect_to_light(light.start_point - closest_point);
		intersect_to_light = intersect_to_light.normallize();
		Ray to_light_ray(closest_point, intersect_to_light);           //交点到光源的射线		
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (i == index)
				continue;
			vector3<double> intersect_point;
			if (objects[i]->intersect(to_light_ray, intersect_point))
			{
				return_color.r *= objects[i]->opacity;  
				return_color.g *= objects[i]->opacity;
				return_color.b *= objects[i]->opacity;
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
			drawer_instance->set_pixel(i, j, ray_cast(i - (camera.size / 2), j - (camera.size / 2)));
		}
}