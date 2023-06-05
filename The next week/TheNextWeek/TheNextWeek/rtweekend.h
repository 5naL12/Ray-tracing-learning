#ifndef REWEEKEND_H
#define REWEEKEND_H

#include<cmath>
#include<cstdlib>
#include<limits>
#include<memory>
#include<random>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//常量
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932384626433832795;

//函数
inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180;
}

inline double random_double()
{
	static std::uniform_real_distribution<double>distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double random_double(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

inline int random_int(int min, int max)
{
    return static_cast<int>(random_double(min, max));
}

inline double clamp(double x,double min,double max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

inline void UpdateProgress(float progress)
{
    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

//公共头文件
#include"ray.h"
#include"vec3.h"

#endif // !REWEEKEND_H
