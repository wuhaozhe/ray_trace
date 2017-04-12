#include "drawer.h"
#include <assert.h>
drawer* drawer::instance = new drawer();      //对静态成员实例化
drawer::drawer()
{
}


drawer::~drawer()
{
}

void drawer::set_pixel(unsigned x, unsigned y, Color color)
{
	assert(x < width && y < height);
	y = height - 1 - y;               //将坐标轴上下颠倒
	image[4 * width * y + 4 * x + 0] = color.r;
	image[4 * width * y + 4 * x + 1] = color.g;
	image[4 * width * y + 4 * x + 2] = color.b;
	image[4 * width * y + 4 * x + 3] = color.a;
}
void drawer::set_pixel(Point point, Color color)
{
	set_pixel(point.x, point.y, color);
}
Color drawer::get_pixel(unsigned x, unsigned y)
{
	assert(x < width && y < height);
	y = width - 1 - y;
	Color target_color;
	target_color.r = image[4 * width * y + 4 * x + 0];
	target_color.g = image[4 * width * y + 4 * x + 1];
	target_color.b = image[4 * width * y + 4 * x + 2];
	target_color.a = image[4 * width * y + 4 * x + 3];
	return target_color;
}
Color drawer::get_pixel(Point point)
{
	return get_pixel(point.x, point.y);
}
void drawer::set_size(unsigned input_width, unsigned input_height)
{
	height = input_height;
	width = input_width;
	image.resize(4 * width * height);
}
bool drawer::output_image()
{
	unsigned error = lodepng::encode(filename, image, width, height);
	if (error)
	{
		cout << "encode error" << error << ": " << lodepng_error_text(error) << endl;
		return false;
	}
	else
		return true;
}
bool drawer::point_illegal(int x, int y)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		return true;                   //当前点不合法
	}
	else
	{
		return false;                  //当前点合法
	}
}

Color Color::mix_back(Color background_color)
{
	Color mixed_color;
	double ratio = (double)a / 255;
	mixed_color.r = (unsigned char)(ratio * (double)r + (1 - ratio) * (double)background_color.r);            //根据灰度来算合成的r
	mixed_color.g = (unsigned char)(ratio * (double)g + (1 - ratio) * (double)background_color.g);            //根据灰度来算合成的g
	mixed_color.b = (unsigned char)(ratio * (double)b + (1 - ratio) * (double)background_color.b);            //根据灰度来算合成的g
	mixed_color.a = 255;
	return mixed_color;
}