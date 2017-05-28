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
	World world;
	Object* floor = new Plane(vector3<double>(0, 0, -10), vector3<double>(0, 0, 1));
	floor->reflective = true;
	floor->reflect_coefficient = 0.2;
	floor->color_feature.Kab = 0.3, floor->color_feature.Kdb = 0.4; floor->color_feature.Ksb = 0.3;
	floor->color_feature.Kar = 0.3, floor->color_feature.Kdr = 0.4; floor->color_feature.Ksr = 0.3;
	world.add_object(floor);
	Object* ceiling = new Plane(vector3<double>(0, 0, 10), vector3<double>(0, 0, -1));
	ceiling->reflective = true;
	ceiling->reflect_coefficient = 0.2;
	ceiling->color_feature.Kab = 0.3, ceiling->color_feature.Kdb = 0.4; ceiling->color_feature.Ksb = 0.3;
	ceiling->color_feature.Kar = 0.3, ceiling->color_feature.Kdr = 0.4; ceiling->color_feature.Ksr = 0.3;
	world.add_object(ceiling);
	Object* forwardwall = new Plane(vector3<double>(10, 0, 0), vector3<double>(-1, 0, 0));
	forwardwall->color_feature.Kar = 0.3, forwardwall->color_feature.Kdr = 0.4; forwardwall->color_feature.Ksr = 0.3;
	world.add_object(forwardwall);
	Object* backwall = new Plane(vector3<double>(-10, 0, 0), vector3<double>(1, 0, 0));
	world.add_object(backwall);
	Object* leftwall = new Plane(vector3<double>(0, -10, 0), vector3<double>(0, 1, 0));
	world.add_object(leftwall);
	Object* rightwall = new Plane(vector3<double>(0, 10, 0), vector3<double>(0, -1, 0));
	world.add_object(rightwall);
	Object* ball = new Sphere(vector3<double>(5, 6.5, -2), 1.5);
	world.add_object(ball);
	//生成一个Beizer曲面
	vector3<double> control_array[4];
	control_array[0] = vector3<double>(2, 0, -1);
	control_array[1] = vector3<double>(1, 0, 0);
	control_array[2] = vector3<double>(0.5, 0, 1);
	control_array[3] = vector3<double>(1, 0, 2);
	Object* beizer_obj = new BeizerBSPTree(control_array);
	world.add_object(beizer_obj);
	world.ray_trace();
	(drawer::get_instance())->output_image();
	return 0;
}