#ifndef HITTABLE_H
#define HITTABLE_H

#include"ray.h"
#include"rtweekend.h"

class material;

struct hit_record
{
	point3 p;//交点
	vec3 normal;//法向量
	shared_ptr<material> mat_ptr;
	double t;//距离
	bool front_face;

	inline void set_face_noraml(const ray& r, const vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal);
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif