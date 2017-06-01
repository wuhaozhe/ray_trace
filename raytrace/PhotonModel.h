#pragma once
struct object_feature          //存储对于光子来说物体的特性
{
	double specular_reflect = 0;             //镜面反射，漫反射，折射，吸收所占的权重
	double diffuse_reflect = 0;
	double refract = 0;
	double absorb = 0;
	double reflect_red = 1, reflect_green = 1, reflect_blue = 1;
	double refract_red = 1, refract_green = 1, refract_blue = 1;
	double pd = 0, ps = 0;                      //phong模型中漫反射光和镜面反射光的反射率
};
class PhotonModel
{
public:
	PhotonModel();
	~PhotonModel();
};

