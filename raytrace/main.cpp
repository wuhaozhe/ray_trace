#include "Plane.h"
#include "Sphere.h"
#include "Point.h"
#include "World.h"
#include "Triangle.h"
#include "Beizer_rotate.h"
#include "Beizer_Surface.h"
#include "Beizer_Surface_Object.h"
#include "BeizerBSPTree.h"
#include "BoundingBox.h"
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	/*World world;
	vector3<double> point_array[9];
	point_array[0] = vector3<double>(0, 0, -1);
	point_array[1] = vector3<double>(0, 2, 1);
	point_array[2] = vector3<double>(0, 4, 3);
	point_array[3] = vector3<double>(2, 0, 3.5);
	point_array[4] = vector3<double>(2, 2, 1.5);
	point_array[5] = vector3<double>(2, 4, 0);
	point_array[6] = vector3<double>(4, 0, 0);
	point_array[7] = vector3<double>(4, 2, 2);
	point_array[8] = vector3<double>(4, 4, 4);
	Beizer_Surface_Object* beizer = new Beizer_Surface_Object(3, 3, point_array);
	//cout << "haha" << endl;
	Object* plane = new Plane(vector3<double>(0, 0, -1), vector3<double>(0, 0, 1));
	world.add_object(beizer);
	world.add_object(plane);
	world.ray_trace();
	(drawer::get_instance())->output_image();*/
	/*Ray temp_ray(vector3<double>(1.87248, 2.625, -1), vector3<double>(-0.465974, -0.0281778, 0.88435));
	vector3<double> intercept_point;
	if (beizer->intersect(temp_ray, intercept_point))
	{
		cout << "intercept" << endl;
	}
	else
	{
		cout << "no intercept" << endl;
	}
	for (int i = 0; i < (beizer->Tree).objects.size(); i++)
	{
		if (((beizer->Tree).objects[i])->intersect(temp_ray, intercept_point))
		{
			cout << "intercept" << endl;
			cout << i << endl;
			Triangle* current_triangle = (Triangle*)(beizer->Tree).objects[i];
			cout << current_triangle->vertex[0] << " " << current_triangle->vertex[1] << " " << current_triangle->vertex[2] << endl;
		}
	}*/
	World world;
	vector3<double> point_array2[4];
	point_array2[0] = vector3<double>(4, 0, 0.1);
	point_array2[1] = vector3<double>(1, 0, 1.1);
	point_array2[2] = vector3<double>(2, 0, 2.1);
	point_array2[3] = vector3<double>(0, 0, 3.1);
	Object* beizer_bsp = new BeizerBSPTree(point_array2);
	world.add_object(beizer_bsp);
	Object* plane = new Plane(vector3<double>(0, 0, -1), vector3<double>(0, 0, 1));
	world.add_object(plane);
	world.ray_trace();
	(drawer::get_instance())->output_image();
	Beizer_rotate rotate;
	for (int i = 0; i < 4; i++)
	{
		rotate.add_control_point(point_array2[i]);
	}
	rotate.output_obj();
	return 0;
}