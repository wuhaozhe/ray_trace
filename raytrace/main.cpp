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
	floor->feature.absorb = 0.5; floor->feature.diffuse_reflect = 0.5;
	world.add_object(floor);
	Object* ceiling = new Plane(vector3<double>(0, 0, 10), vector3<double>(0, 0, -1));
	ceiling->feature.absorb = 0.5; ceiling->feature.diffuse_reflect = 0.5;
	world.add_object(ceiling);
	Object* forwardwall = new Plane(vector3<double>(10, 0, 0), vector3<double>(-1, 0, 0));
	forwardwall->feature.absorb = 0.5; forwardwall->feature.diffuse_reflect = 0.5;
	forwardwall->feature.reflect_blue = 0.5;
	world.add_object(forwardwall);
	Object* backwall = new Plane(vector3<double>(-10, 0, 0), vector3<double>(1, 0, 0));
	backwall->feature.absorb = 0.5; backwall->feature.diffuse_reflect = 0.5;
	backwall->feature.reflect_blue = 0.5;
	world.add_object(backwall);
	Object* leftwall = new Plane(vector3<double>(0, -10, 0), vector3<double>(0, 1, 0));
	leftwall->feature.absorb = 0.5; leftwall->feature.diffuse_reflect = 0.5;
	leftwall->feature.reflect_green = 0.5;
	world.add_object(leftwall);
	Object* rightwall = new Plane(vector3<double>(0, 10, 0), vector3<double>(0, -1, 0));
	rightwall->feature.absorb = 0.5; rightwall->feature.diffuse_reflect = 0.5;
	rightwall->feature.reflect_red = 0.5;
	world.add_object(rightwall);
	Object* ball = new Sphere(vector3<double>(5, 7, -8.5), 1.5);
	ball->feature.absorb = 0.05; ball->feature.diffuse_reflect = 0; ball->feature.specular_reflect = 0; ball->feature.refract = 0.95;
	world.add_object(ball);
	//生成一个Beizer曲面
	vector3<double> control_array[4];
	control_array[0] = vector3<double>(2, 0, -1);
	control_array[1] = vector3<double>(1, 0, 0);
	control_array[2] = vector3<double>(0.5, 0, 1);
	control_array[3] = vector3<double>(1, 0, 2);
	Object* beizer_obj = new BeizerBSPTree(control_array);
	beizer_obj->feature.absorb = 0.3; beizer_obj->feature.diffuse_reflect = 0.2; beizer_obj->feature.specular_reflect = 0.5;
	beizer_obj->feature.reflect_blue = 0.5; beizer_obj->feature.reflect_green = 0.5;
	world.add_object(beizer_obj);
	/*(photon_map::get_instance())->init_photon_map(world.objects, vector3<double>(0, 0, 5), Color(255, 255, 255, 255));
	(photon_map::get_instance())->generate_photon(2000000);
	Color temp = (photon_map::get_instance())->get_color(vector3<double>(10, 0, 0), vector3<double>(-1, 0, 0), vector3<double>(1, 0, 0), 1, 1);
	cout << (int)temp.r << " " << (int)temp.g << " " << (int)temp.b << endl;*/
	world.photon_cast();
	world.ray_trace();
	(drawer::get_instance())->output_image();
	return 0;
}