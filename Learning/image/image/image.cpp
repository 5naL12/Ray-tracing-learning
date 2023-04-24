#include"color.h"
#include"vec3.h"
#include"ray.h"

#include <iostream>

using std::cin;
using std::cout;

//判断光线是否与某个球相交
double hit_sphere(const point3& center,double radius,const ray &r)
{
    vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double half_b = dot(r.direction(), oc);
    double c = dot(oc, oc) - radius * radius;
    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        double t1 = (-half_b - sqrt(discriminant)) / a;
        if (t1 > 0)
            return t1;
        double t2 = (-half_b + sqrt(discriminant)) / a;
        if (t2 > 0)
            return t2;
        return -1.0;
    }
}

//实现渐变色
color ray_color(const ray& r)
{
    double t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0)
    {
        vec3 N = unit_vector(r.at(t) - point3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    //线性插值
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    //图像
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);

    //摄像机
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_long = 1.0;

    point3 origin = point3(0, 0, 0);
    vec3 horizontal = vec3(viewport_width, 0, 0);
    vec3 vertical = vec3(0, viewport_height, 0);
    //视口左下角坐标
    point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_long);

    //渲染

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        for (int i = 0; i < image_width; ++i)
        {
            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);
            write_color(cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}