#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(u32 w, u32 h) : width{w}, height{h}
{
	data = new rgb[w * h];
}

Image::Image(const char *a)
{
	data = (rgb*)stbi_load(a, (int*)(&width), (int*)(&height), (int*)(&channels), 0);
}

Image::Image(const Image &source)	//copy constructor
{
	for (u32 y = 0; y < height; y++)
	{
		for (u32 x = 0; x < width; x++)
		{
			this->data[y * width + x] = source.data[y * width + x];
		}
	}
}

Image& Image::operator = (const Image &source)
{
	for (u32 y = 0; y < height; y++)
	{
		for (u32 x = 0; x < width; x++)
		{
			this->data[y * width + x] = source.data[y * width + x];
		}
	}

	return *this;
}

Image::~Image()
{
	delete[] data;
}

void Image::fill(rgb c)
{
	for (u32 y = 0; y < height; y++)
	{
		for (u32 x = 0; x < width; x++)
		{
			this->pixel(x, y, c);
		}
	}
}

void Image::pixel(u32 x, u32 y, rgb c)
{
	if (x >= width || y >= height) return;
	else
	{
		data[y * width + x] = c;
	}
}

rgb Image::get_pixel(int x, int y)
{
	if (x < 0) x = 0;
	if (x >= width) x = width - 1;
	if (y < 0) y = 0;
	if (y >= height) y = height - 1;
	return data[y * width + x];
}

Image Image::convolution(vector<double> *kernel)
{
	Image buffer(width, height);

	u8 size = sqrt(kernel->size());

	for (u32 y = 0; y < height; y++)
	{
		for (u32 x = 0; x < width; x++)
		{
			double r = 0, g = 0, b = 0;
			auto it = kernel->begin();
			for (int ky = (int)y - size / 2; ky <= (int)y + size / 2; ky++)
			{
				for (int kx = (int)x - size / 2; kx <= (int)x + size / 2; kx++)
				{
					r += (double)this->get_pixel(kx, ky).r * (*it);
					g += (double)this->get_pixel(kx, ky).g * (*it);
					b += (double)this->get_pixel(kx, ky).b * (*it);
					it++;
				}
			}
			buffer.pixel(x, y, rgb((u8)r, (u8)g, (u8)b));
		}
	}
	return buffer;
}

Image Image::blur(int size)
{
	Image buffer(width, height);

	for (u32 y = 0; y < height; y++)
	{
		for (u32 x = 0; x < width; x++)
		{
			double r = 0, g = 0, b = 0;
			for (int ky = (int)y - size / 2; ky <= (int)y + size / 2; ky++)
			{
				for (int kx = (int)x - size / 2; kx <= (int)x + size / 2; kx++)
				{
					r += (double)this->get_pixel(kx, ky).r;
					g += (double)this->get_pixel(kx, ky).g;
					b += (double)this->get_pixel(kx, ky).b;
				}
			}
			r /= (double)(size * size);
			g /= (double)(size * size);
			b /= (double)(size * size);
			buffer.pixel(x, y, rgb((u8)r, (u8)g, (u8)b));
		}
	}
	return buffer;
}

void Image::line(u32 x1, u32 y1, u32 x2, u32 y2, rgb c)
{
	u32 xmax = max(x1, x2), xmin = min(x1, x2), ymax = max(y1, y2), ymin = min(y1, y2);
	if (x1 == x2)
	{
		for (ymin; ymin <= ymax; ymin++) this->pixel(x1, ymin, c);
	}
	else if (y1 == y2)
	{
		for (xmin; xmin <= xmax; xmin++) this->pixel(xmin, y1, c);
	}
	else if ((xmax - xmin) == (ymax - ymin))
	{
		if ((x1 > x2 && y1 > y2) || (x2 > x1 && y2 > y1) )
		{
			for (xmin; xmin <= xmax; xmin++, ymin++) this->pixel(xmin, ymin, c);
		}
		else
		{
			for (xmin; xmin <= xmax; xmin++, ymax--) this->pixel(xmin, ymax, c);
		}
	}
	else
	{
		double slope = ((double)y2 - y1) / ((double)x2 - x1);
		double offset = ((double)x2 * y1 - (double)x1 * y2) / ((double)x2 - x1);
		if (xmax - xmin > ymax - ymin)
		{
			for (xmin; xmin <= xmax; xmin++) this->pixel(xmin, slope * xmin + offset, c);
		}
		else
		{
			for (ymin; ymin <= ymax; ymin++) this->pixel((ymin - offset) / slope, ymin, c);
		}
	}
}

void Image::rect(u32 x, u32 y, u32 w, u32 h, rgb c)
{
	for (u32 k = y; k < h + y; k++)
	{
		for (u32 m = x; m < w + x; m++)
		{
			this->pixel(m, k, c);
		}
	}
}

void Image::point(u32 x, u32 y, rgb c)
{
	u8 add = 2;
	for (int k = (int)y - add; k <= (int)y + add; k++)
	{
		for (int m = (int)x - add; m <= (int)x + add; m++)
		{
			if (k >= height || m >= width) continue;
			this->pixel(m, k, c);
		}
	}
}

void Image::save_as(const char *s)
{
	stbi_write_png(s, width, height, channels, data, width * channels);
}
