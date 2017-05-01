#include "Plane.h"
#include "Sphere.h"
#include "Point.h"
#include "World.h"
#include "Triangle.h"
#include "Beizer_rotate.h"
#include "Beizer_Surface.h"
#include "Beizer_Surface_Object.h"
#include "BoundingBox.h"
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	World world;
	vector3<double> point_array[9];
	point_array[0] = vector3<double>(0, 0, -1);
	point_array[1] = vector3<double>(0, 2, 1);
	point_array[2] = vector3<double>(0, 4, 3);
	point_array[3] = vector3<double>(2, 0, -1);
	point_array[4] = vector3<double>(2, 2, 1);
	point_array[5] = vector3<double>(2, 4, 3);
	point_array[6] = vector3<double>(4, 0, -1);
	point_array[7] = vector3<double>(4, 2, 1);
	point_array[8] = vector3<double>(4, 4, 3);
	Object* beizer = new Beizer_Surface_Object(3, 3, point_array);
	cout << "haha" << endl;
	Object* plane = new Plane(vector3<double>(0, 0, -1), vector3<double>(0, 0, 1));
	world.add_object(beizer);
	world.add_object(plane);
	world.ray_trace();
	(drawer::get_instance())->output_image();
	return 0;
}