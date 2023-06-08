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
	virtual bool bounding_box(
		double time0, double time1, aabb& output_box) const override;

public:
	point3 center;
	double radius;
	shared_ptr<material> mat_ptr;
	static void get_sphere_uv(const point3& p, double& u, double& v)
	{
		auto theta = acos(-p.y());
		auto phi = atan2(-p.z(), p.x()) + pi;

		u = phi / (2 * pi);
		v = theta / pi;
	}
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
			rec.set_face_normal(r, outward_noraml);
			get_sphere_uv(outward_noraml, rec.u, rec.v);
			rec.mat_ptr = mat_ptr;
			return true;
		}
		t = (-half_b + root) / a;
		if (t > t_min && t < t_max)
		{
			rec.t = t;
			rec.p = r.at(t);
			vec3 outward_noraml = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_noraml);
			get_sphere_uv(outward_noraml, rec.u, rec.v);
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

bool sphere::bounding_box(double time0, double time1, aabb& output_box) const
{
	output_box = aabb(
		center - vec3(radius, radius, radius),
		center + vec3(radius, radius, radius));
	return true;
}

#endif // !SPHERE_H
