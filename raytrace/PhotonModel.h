#pragma once
struct object_feature          //�洢���ڹ�����˵���������
{
	double specular_reflect = 0;             //���淴�䣬�����䣬���䣬������ռ��Ȩ��
	double diffuse_reflect = 0;
	double refract = 0;
	double absorb = 0;
	double reflect_red = 1, reflect_green = 1, reflect_blue = 1;
	double refract_red = 1, refract_green = 1, refract_blue = 1;
	double pd = 0, ps = 0;                      //phongģ�����������;��淴���ķ�����
};
class PhotonModel
{
public:
	PhotonModel();
	~PhotonModel();
};

