#pragma once
#include "Point.h"
#include "Ray.h"
#include "drawer.h"
#include "PhotonModel.h"
class Object
{
protected:
	virtual void init() = 0;
public:
	bool has_texture = false;
	enum Object_type
	{
		_Plane = 0, _Triangle = 1, _Polygon = 2, _Sphere = 3, _BoundingBox = 4, _Beizer_Surface = 5, _Beizer_Rotate = 6
	};
	virtual bool intersect(Ray input_ray, vector3<double> &intersect_point) = 0;             //求交点
	virtual Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in) = 0;                  //根据光照模型获取target_pos上的颜色，view_direction是视点方向,同时获得法向量，最后一个参数为法向量的引用
	virtual vector3<double> get_normalvec(vector3<double> target_pos, vector3<double> view_direction) = 0;                    //获取该点的法向量
	virtual object_feature get_feature(vector3<double> target_pos);            //assert target_pos在物体上
	Object_type object_type;
	Object();
	double opacity = 0.5;                      //透明度，【0-1】，为0时认为是不透明的，为1时认为是透明的，透明度使得光穿过该物体时有光强的损耗
	double reflect_coefficient, refract_coefficient;         //反射系数，折射系数
	double n;                  //折射率
	object_feature feature;                     //对于一个光子来说object的feature
	~Object();
};

