#pragma once
#include "Object_Collections.h"
#include <vector>
#include "Point.h"
#include "Camera.h"
using namespace std;
class World
{
private:
	vector<Object*> objects;
	Color ray_cast(int i, int j);
	drawer* drawer_instance;
public:
	Light light;
	Camera camera;
	void add_object(Object* input_obj);
	void ray_cast();                //π‚œﬂÕ∂…‰
	World();
	~World();
};