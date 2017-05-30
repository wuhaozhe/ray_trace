#pragma once
struct object_feature          //存储对于光子来说物体的特性
{
	double specular_reflect = 0;             //镜面反射，漫反射，折射，吸收所占的权重
	double diffuse_reflect = 0;
	double refract = 0;
	double absorb = 0;
	bool reflect_red = true, reflect_green = true, reflect_blue = true;
	bool refract_red = true, refract_green = true, refract_blue = true;
	double pd = 0, ps = 0;                      //phong模型中漫反射光和镜面反射光的反射率
};
class PhotonModel
{
public:
	PhotonModel();
	~PhotonModel();
};

