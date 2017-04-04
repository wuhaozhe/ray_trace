#include "Plane.h"
#include "Point.h"
#include "World.h"
#include <iostream>
using namespace std;

int main()
{
	vector3<double> temp1(1, 1, -1);
	vector3<double> temp2(0, 0, 1);
	Object *a = new Plane(temp1, temp2);
	Plane *b = dynamic_cast<Plane*>(a);
	World e;
	e.add_object(a);
	e.ray_cast();
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
	return 0;
}