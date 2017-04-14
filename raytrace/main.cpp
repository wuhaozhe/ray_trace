#include "Plane.h"
#include "Sphere.h"
#include "Point.h"
#include "World.h"
#include "Triangle.h"
#include "Beizer_rotate.h"
#include "Beizer_Surface.h"
#include "BoundingBox.h"
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	/*vector3<double> temp1(1, 1, -1);
	vector3<double> temp2(0, 0, 1);
	Object *a = new Plane(temp1, temp2);
	Plane *b = dynamic_cast<Plane*>(a);
	World e;
	e.add_object(a);
	vector3<double> center(-5, 0, 4.01);
	double raidus = 5;
	vector3<double> center2(2, 10, 5);
	double radius2 = 5;
	Object *sphere2 = new Sphere(center2, radius2);
	//sphere2->refractive = false;
	vector3<double> center3(-10, 0, 4.01);
	double radius3 = 1;
	Object *sphere3 = new Sphere(center3, radius3);
	sphere3->n = 1.5;
	Object *sphere4 = new Sphere(vector3<double>(15, 10, 5), 5);
	(sphere4->color_feature).Kar = 0.05;
	(sphere4->color_feature).Kdr = 0.3;
	(sphere4->color_feature).Ksr = 0.6;
	sphere4->refractive = false;
	Object *sphere = new Sphere(center, raidus);
	sphere->n = 2;
	/*e.add_object(sphere);
	e.add_object(sphere2);
	e.add_object(sphere3);
	e.add_object(sphere4);*/
	/*vector3<double> v1(1, -10, 0);
	vector3<double> v2(5, -4, 0);
	vector3<double> v3(3, -15, 10);
	Object *triangle = new Triangle(v1, v2, v3);
	//e.add_object(triangle);
	Object *box = new BoundingBox(vector3<double>(6, 4, 2), vector3<double>(-1, 2, 1));
	e.add_object(box);
	e.ray_trace();
	drawer *p = drawer::get_instance();
	p->output_image();
	/*vector3<double> temp1(1.5, 1.5, 1.5);
	vector3<double> temp2(1.5, 1.5, 1.5);
	vector3<double> temp3 = temp1 + temp2;*/
	/*vector3<double> normal_vector(0, 0, 1);
	vector3<double> point(0, 0, 0);
	vector3<double> direction(0, 1, 1);
	vector3<double> point2(0, 0, -1);
	vector3<double> point3;*/
	/*Plane *c = new Plane(point, normal_vector);
	Ray d(point2, direction);
	if (c->intersect(d, point3))
	{
		
		cout << point3.x << " " << point3.y << " " << point3.z;
	}
	else
	{
		cout << "not intersect";
	}*/
	/*vector3<double> temp1(0, 0, 0);
	double raidus = 1;
	vector3<double> temp2(0, 0, 0);
	vector3<double> direction(0, 0, 1);
	Ray temp4(temp2, direction);
	vector3<double> temp3;
	Sphere* sphere = new Sphere(temp1, raidus);
	if (sphere->intersect(temp4, temp3))
	{
		cout << temp3.x << " " << temp3.y << " " << temp3.z << endl;
	}
	else
	{
		cout << "failed" << endl;
	}*/
	/*vector3<double> temp1(sqrt(3), 1, 0);
	temp1 = temp1.normallize();
	vector3<double> temp2(0, -1, 0);
	vector3<double> temp3;
	if (refract(temp1, temp2, 1, sqrt(3), temp3))
	{
		cout << temp3.x << " " << temp3.y << " " << temp3.z << endl;
	}
	else
	{
		cout << "reflect!" << endl;
	}*/
	/*Beizer_Surface a(3, 3);
	a.set_control_point(0, 0, vector3<double>(0, 0, 0));
	a.set_control_point(0, 1, vector3<double>(0, 1.5, 1));
	a.set_control_point(0, 2, vector3<double>(0, 2, 0.5));
	a.set_control_point(1, 0, vector3<double>(1, 0, 0.3));
	a.set_control_point(1, 1, vector3<double>(1, 1, 10));
	a.set_control_point(1, 2, vector3<double>(1, 2, 0.9));
	a.set_control_point(2, 0, vector3<double>(2, 0, -0.2));
	a.set_control_point(2, 1, vector3<double>(2, 1.3, 0.05));
	a.set_control_point(2, 2, vector3<double>(1, 2.2, 0.8));
	a.output_obj();*/
	/*Beizer_rotate b;
	b.add_control_point(vector3<double>(0, 1, 0));
	b.add_control_point(vector3<double>(0, 2, 1.6));
	b.add_control_point(vector3<double>(0, 3, 1.3));
	b.output_obj();*/
	return 0;
}