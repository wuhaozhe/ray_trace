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
#include "photon_map.h"
#include "kdTree.h"
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
	floor->feature.absorb = 0.3; floor->feature.diffuse_reflect = 0.45; floor->feature.specular_reflect = 0.25;
	world.add_object(floor);
	Object* ceiling = new Plane(vector3<double>(0, 0, 10), vector3<double>(0, 0, -1));
	ceiling->reflective = true;
	ceiling->reflect_coefficient = 0.2;
	ceiling->color_feature.Kab = 0.3, ceiling->color_feature.Kdb = 0.4; ceiling->color_feature.Ksb = 0.3;
	ceiling->color_feature.Kar = 0.3, ceiling->color_feature.Kdr = 0.4; ceiling->color_feature.Ksr = 0.3;
	ceiling->feature.absorb = 0.3; ceiling->feature.diffuse_reflect = 0.45; ceiling->feature.specular_reflect = 0.25;
	world.add_object(ceiling);
	Object* forwardwall = new Plane(vector3<double>(10, 0, 0), vector3<double>(-1, 0, 0));
	forwardwall->color_feature.Kar = 0.3, forwardwall->color_feature.Kdr = 0.4; forwardwall->color_feature.Ksr = 0.3;
	forwardwall->feature.absorb = 0.3; forwardwall->feature.diffuse_reflect = 0.3; forwardwall->feature.specular_reflect = 0.4;
	forwardwall->feature.reflect_blue = false;
	world.add_object(forwardwall);
	Object* backwall = new Plane(vector3<double>(-10, 0, 0), vector3<double>(1, 0, 0));
	backwall->feature.absorb = 0.3; backwall->feature.diffuse_reflect = 0.3; backwall->feature.specular_reflect = 0.4;
	backwall->feature.reflect_blue = false;
	world.add_object(backwall);
	Object* leftwall = new Plane(vector3<double>(0, -10, 0), vector3<double>(0, 1, 0));
	leftwall->feature.absorb = 0.3; leftwall->feature.diffuse_reflect = 0.3; leftwall->feature.specular_reflect = 0.4;
	leftwall->feature.reflect_green = false;
	world.add_object(leftwall);
	Object* rightwall = new Plane(vector3<double>(0, 10, 0), vector3<double>(0, -1, 0));
	rightwall->feature.absorb = 0.3; rightwall->feature.diffuse_reflect = 0.3; rightwall->feature.specular_reflect = 0.4;
	rightwall->feature.reflect_red = false;
	world.add_object(rightwall);
	Object* ball = new Sphere(vector3<double>(5, 6.5, -2), 1.5);
	ball->feature.absorb = 0.1; ball->feature.diffuse_reflect = 0.1; ball->feature.specular_reflect = 0.1; ball->feature.refract = 0.7;
	world.add_object(ball);
	//生成一个Beizer曲面
	vector3<double> control_array[4];
	control_array[0] = vector3<double>(2, 0, -1);
	control_array[1] = vector3<double>(1, 0, 0);
	control_array[2] = vector3<double>(0.5, 0, 1);
	control_array[3] = vector3<double>(1, 0, 2);
	Object* beizer_obj = new BeizerBSPTree(control_array);
	beizer_obj->feature.absorb = 0.1; beizer_obj->feature.diffuse_reflect = 0.1; beizer_obj->feature.specular_reflect = 0.8;
	beizer_obj->feature.reflect_blue = false; beizer_obj->feature.reflect_green = false;
	world.add_object(beizer_obj);
	(photon_map::get_instance())->init_photon_map(world.objects, vector3<double>(0, 0, 5), Color(255, 255, 255, 255));
	(photon_map::get_instance())->generate_photon(10000);
	Color temp = (photon_map::get_instance())->get_color(vector3<double>(10, 0, 0), vector3<double>(-1, 0, 0), vector3<double>(1, 0, 0), 1, 1);
	cout << (int)temp.r << " " << (int)temp.g << " " << (int)temp.b << endl;
	//world.ray_trace();
	//(drawer::get_instance())->output_image();
	return 0;
}