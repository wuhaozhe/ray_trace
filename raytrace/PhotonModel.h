#pragma once
struct object_feature          //�洢���ڹ�����˵���������
{
	double specular_reflect = 0;             //���淴�䣬�����䣬���䣬������ռ��Ȩ��
	double diffuse_reflect = 0;
	double refract = 0;
	double absorb = 0;
	bool reflect_red = true, reflect_green = true, reflect_blue = true;
	bool refract_red = true, refract_green = true, refract_blue = true;
	double pd = 0, ps = 0;                      //phongģ�����������;��淴���ķ�����
};
class PhotonModel
{
public:
	PhotonModel();
	~PhotonModel();
};

