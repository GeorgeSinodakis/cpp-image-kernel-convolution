#ifndef RGB_H
#define RGB_H

#include <iostream>

using namespace std;

typedef uint32_t u32;
typedef uint8_t u8;
typedef uint16_t u16;

typedef int32_t s32;
typedef int8_t s8;
typedef int16_t s16;

class rgb
{
public:
	u8 r;
	u8 g;
	u8 b;
	rgb(u8 r, u8 g, u8 b);
	rgb();
	rgb& operator + (const rgb &color);
	rgb& operator = (const rgb &source);
	rgb& operator * (const float &f);
	void add(rgb color);
	void scale(double f);
};

#endif
