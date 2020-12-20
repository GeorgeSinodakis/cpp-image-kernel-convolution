#include "rgb.h"

rgb::rgb(u8 r, u8 g, u8 b) : r{r}, g{g}, b{b} 
{
	
}

rgb::rgb()
{
	r = 0;
	g = 0;
	b = 0;
}

rgb& rgb::operator + (const rgb &color)
{
	if (r + color.r > 255) r = 255;
	else r += color.r;
	if (g + color.g > 255) g = 255;
	else g += color.g;
	if (b + color.b > 255) b = 255;
	else b += color.b;

	return *this;
}

rgb& rgb::operator = (const rgb &source)
{
	r = source.r;
	g = source.g;
	b = source.b;

	return *this;
}

rgb& rgb::operator * (const float &f)
{
	r *= f;
	g *= f;
	b *= f;

	return *this;
}

void rgb::add(rgb color)
{
	if (r + color.r > 255) r = 255;
	else r += color.r;
	if (g + color.g > 255) g = 255;
	else g += color.g;
	if (b + color.b > 255) b = 255;
	else b += color.b;
}

void rgb::scale(double f)
{
	r *= f;
	g *= f;
	b *= f;
}
