#ifndef DRAWER_H
#define DRAWER_H
#include <iostream>
#include "lodepng.h"
using namespace std;
struct Color         //Pixel�����r, g, b, a
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	Color mix_back(Color background_color);          //�뱳��ɫ���
	Color(unsigned char x, unsigned char y, unsigned char z, unsigned char w)
	{
		r = x, g = y, b = z, a = w;
	}
	Color()
	{
		r = 0, g = 0, b = 0, a = 0;
	}
	Color operator*(const double &a)
	{
		Color temp;
		temp.r = (unsigned char)(a * (double)r);
		temp.g = (unsigned char)(a * (double)g);
		temp.b = (unsigned char)(a * (double)b);
		temp.a = 255;
		return temp;
	}
	Color operator+(const Color &a)
	{
		Color temp;
		temp.r = a.r + r;
		temp.g = a.g + g;
		temp.b = a.b + b;
		temp.a = 255;
		return temp;
	}
};
struct Point
{
	int x;
	int y;
};
class drawer
{
public:
	drawer();
	~drawer();
	static drawer* get_instance()            //����
	{
		if (instance == nullptr)
		{
			instance = new drawer();
		}
		return instance;
	}
	void set_size(unsigned width, unsigned height);         //����ͼƬ�Ĵ�С 
	void set_pixel(unsigned x, unsigned y, Color color);     //����������ɫͼƬ�����Ͻ�Ϊ0, 0
	void set_pixel(Point point, Color color);
	Color get_pixel(unsigned x, unsigned y);
	Color get_pixel(Point point);
	bool output_image();                           //��ͼ�����
	bool point_illegal(int x, int y);                          //�жϵ�ǰ���λ���Ƿ�Ϸ�ʱ
	const char* filename = "test.png";             //ͼƬ���ʱ���ļ���
private:
	vector<unsigned char> image;
	unsigned width;
	unsigned height;
	static drawer* instance;
};

#endif