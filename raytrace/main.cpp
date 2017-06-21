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
	reader texture_reader;
	texture_reader.read_file("texture.png", 800, 1192);
	World world;
	Object* floor = new Plane(vector3<double>(0, 0, -10), vector3<double>(0, 0, 1));
	floor->feature.absorb = 0.5; floor->feature.diffuse_reflect = 0.5;
	world.add_object(floor);
	Object* ceiling = new Plane(vector3<double>(0, 0, 10), vector3<double>(0, 0, -1));
	ceiling->feature.absorb = 0.5; ceiling->feature.diffuse_reflect = 0.5;
	world.add_object(ceiling);
	Plane* forwardwall = new Plane(vector3<double>(10, 0, 0), vector3<double>(-1, 0, 0));
	forwardwall->feature.absorb = 0.5; forwardwall->feature.diffuse_reflect = 0.5;
	forwardwall->feature.reflect_blue = 0.5;
	forwardwall->set_texture(texture_reader);
	forwardwall->set_texture_range(vector3<double>(10, -10, -10), vector3<double>(0, 1, 0), vector3<double>(0, 0, 1), 20, 20);
	world.add_object(forwardwall);
	Object* backwall = new Plane(vector3<double>(-10, 0, 0), vector3<double>(1, 0, 0));
	backwall->feature.absorb = 0.5; backwall->feature.diffuse_reflect = 0.5;
	backwall->feature.reflect_blue = 0.5;
	world.add_object(backwall);
	Object* leftwall = new Plane(vector3<double>(0, -10, 0), vector3<double>(0, 1, 0));
	leftwall->feature.absorb = 0.2; leftwall->feature.diffuse_reflect = 0.5; leftwall->feature.specular_reflect = 0.3;
	leftwall->feature.reflect_green = 0.5;
	world.add_object(leftwall);
	Object* rightwall = new Plane(vector3<double>(0, 10, 0), vector3<double>(0, -1, 0));
	rightwall->feature.absorb = 0.5; rightwall->feature.diffuse_reflect = 0.5;
	rightwall->feature.reflect_red = 0.5;
	world.add_object(rightwall);
	Object* ball = new Sphere(vector3<double>(0, 4, -9.25), 0.75);
	ball->feature.absorb = 0.05; ball->feature.diffuse_reflect = 0.1; ball->feature.specular_reflect = 0; ball->feature.refract = 0.85;
	world.add_object(ball);
	Object* ball2 = new Sphere(vector3<double>(5, 4, -8), 2);
	ball2->feature.absorb = 0.05; ball2->feature.diffuse_reflect = 0; ball2->feature.specular_reflect = 0.95; ball2->feature.refract = 0;
	ball2->feature.reflect_blue = 1; ball2->feature.reflect_green = 1; ball2->feature.reflect_red = 1;
	world.add_object(ball2);
	//生成一个Beizer线旋转而成的曲面
	vector3<double> control_array[4];
	control_array[0] = vector3<double>(1, 0, -7.5);
	control_array[1] = vector3<double>(0, 0, -8);
	control_array[2] = vector3<double>(2, 0, -8.5);
	control_array[3] = vector3<double>(0, 0, -9);
	Object* beizer_obj = new BeizerBSPTree(control_array);
	beizer_obj->feature.absorb = 0.2; beizer_obj->feature.diffuse_reflect = 0.3; beizer_obj->feature.specular_reflect = 0.5;
	beizer_obj->feature.reflect_blue = 0.8; beizer_obj->feature.reflect_green = 0.2; beizer_obj->feature.reflect_red = 0.8;
	world.add_object(beizer_obj);
	/*(photon_map::get_instance())->init_photon_map(world.objects, vector3<double>(0, 0, 5), Color(255, 255, 255, 255));
	(photon_map::get_instance())->generate_photon(2000000);
	Color temp = (photon_map::get_instance())->get_color(vector3<double>(10, 0, 0), vector3<double>(-1, 0, 0), vector3<double>(1, 0, 0), 1, 1);
	cout << (int)temp.r << " " << (int)temp.g << " " << (int)temp.b << endl;*/
	//生成一个beizer曲面
	/*vector3<double> control_array[6];
	control_array[0] = vector3<double>(1, 0, -5);
	control_array[1] = vector3<double>(3, 0, -6);
	control_array[2] = vector3<double>(0, 0, -7.5);
	control_array[3] = vector3<double>(1.5, 0, -8);
	control_array[4] = vector3<double>(0, 0, -8.5);
	control_array[5] = vector3<double>(1, 0, -9);
	Beizer_rotate current_rotate;
	for (int i = 0; i < 6; i++)
	{
		current_rotate.add_control_point(control_array[i]);
	}
	current_rotate.output_obj();*/
	vector3<double> control_array2[9];
	control_array2[0] = vector3<double>(0, -9, -10); control_array2[1] = vector3<double>(0, -7, -7); control_array2[2] = vector3<double>(0, -5, -9.5);
	control_array2[3] = vector3<double>(2, -9, -9.5); control_array2[4] = vector3<double>(2, -7, -4); control_array2[5] = vector3<double>(2, -5, -10);
	control_array2[6] = vector3<double>(4, -9, -9); control_array2[7] = vector3<double>(4, -7, -9.5); control_array2[8] = vector3<double>(4, -5, -10);
	Beizer_Surface current_beizer_surface(3, 3);
	for(int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			current_beizer_surface.set_control_point(i, j, control_array2[i * 3 + j]);
		}
	current_beizer_surface.output_obj();
	Object* beizer_surface = new Beizer_Surface_Object(3, 3, control_array2);
	//beizer_surface->
	beizer_surface->feature.absorb = 0.5; beizer_surface->feature.diffuse_reflect = 0.5;
	world.add_object(beizer_surface);
	world.photon_cast();
	world.ray_trace();
	(drawer::get_instance())->output_image();
	return 0;
}