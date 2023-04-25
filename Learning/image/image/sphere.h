#ifndef SPHERE_H
#define SPHERE_H

#include"hittable.h"
#include"vec3.h"

class sphere : public hittable
{
public:
	sphere() {}
	sphere(point3 cen, double r, shared_ptr<material> m)
		: center(cen), radius(r), mat_ptr(m)
	{
	};

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	point3 center;
	double radius;
	shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec)const
{
	vec3 oc = r.origin() - center;
	double a = r.direction().length_squared();
	double half_b = dot(r.direction(), oc);
	double c = oc.length_squared() - radius * radius;
	double discriminant = half_b * half_b - a * c;
	if (discriminant > 0)
	{
		double root = sqrt(discriminant);
		double t = (-half_b - root) / a;
		if (t > t_min && t < t_max)
		{
			rec.t = t;
			rec.p = r.at(t);
			vec3 outward_noraml = (rec.p - center) / radius;
			rec.set_face_noraml(r, outward_noraml);
			rec.mat_ptr = mat_ptr;
			return true;
		}
		t = (-half_b + root) / a;
		if (t > t_min && t < t_max)
		{
			rec.t = t;
			rec.p = r.at(t);
			vec3 outward_noraml = (rec.p - center) / radius;
			rec.set_face_noraml(r, outward_noraml);
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

#endif // !SPHERE_H
