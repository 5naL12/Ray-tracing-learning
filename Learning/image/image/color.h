#ifndef COLOR_H
#define COLOR_H

#include"vec3.h"
#include<iostream>

void write_color(std::ostream& out,color pixel_color,int sample_per_pixel)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();
	//根据样本数对颜色取平均值
	auto scale = 1.0 / sample_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << " "
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << " "
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << "\n";
}
#endif // DEBUG