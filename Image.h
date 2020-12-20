#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>
#include "rgb.h"

using namespace std;

typedef uint32_t u32;
typedef uint8_t u8;
typedef uint16_t u16;

typedef int32_t s32;
typedef int8_t s8;
typedef int16_t s16;

class Image : rgb
{
	public:
		u32 width;
		u32 height;
		u8 channels;
		rgb *data;
	public:
		Image(u32 w, u32 h);
		Image(const char *a);
		Image(const Image &source);	//copy constructor
		Image& operator = (const Image &source);
		~Image();
		void fill(rgb c);
		void pixel(u32 x, u32 y, rgb c);
		rgb get_pixel(int x, int y);
		Image convolution(vector<double> *kernel);
		Image blur(int size);
		void line(u32 x1, u32 y1, u32 x2, u32 y2, rgb c);
		void rect(u32 x, u32 y, u32 w, u32 h, rgb c);
		void point(u32 x, u32 y, rgb c);
		void save_as(const char *s);
};

#endif
