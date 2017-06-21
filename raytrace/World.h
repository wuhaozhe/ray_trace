#pragma once
#include "Object_Collections.h"
#include <vector>
#include "Point.h"
#include "Camera.h"
#include "photon_map.h"
#include <stack>
using namespace std;
class World
{
private:
	drawer* drawer_instance;
	bool intersect_point(Ray input_ray, int &object_index, vector3<double> &point);            //求取距离input_ray最近的交点
	//Color determine_color_normalvec(int object_index, vector3<double> point, vector3<double> in_direction, vector3<double> &normal_vector);        //获得颜色（已经添加了阴影）和法向量，传入的第三个参数为射入方向
	Color intersect_color(int n, Ray current_ray, stack<int> &refract_stack);                 //n代表递归深度，current_ray代表对其追踪的光线
	double current_n;                     //当前的折射率
	bool intersect_other_objects(vector3<double> point);           //判断当前点到光源的线段是否与其他物体相交
public:
	vector<Object*> objects;
	Color ray_trace(int i, int j);
	Color ray_trace_withDOF(int i, int j);
	const int recursive_depth = 5;                          //光线追踪的递归深度
	const double photon_weight = 0.99;                       //为了降低高频噪声，当光源可以直接照射到一个点时，光子图的颜色与phong模型的颜色的比值
	Light light;
	Camera camera;
	void add_object(Object* input_obj);
	void photon_cast();
	void ray_trace();                //光线追踪
	World();
	~World();
};