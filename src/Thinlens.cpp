#include "Thinlens.h"

// for debug
#include <iostream>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

// must be somewhere in Eigen. But couldn't find...
double PointToPlaneDist(Eigen::Vector3d &point, Eigen::Vector3d &pl_normal, Eigen::Vector3d &pl_point) {
//	double sb, sn, sd;
//	sn = -pl_normal.dot(point - pl_point);
//	sd = pl_normal.dot(pl_normal);
//	sb = sn / sd;

//	Eigen::Vector3d b = point + sb*pl_normal;
//	return (point - b).norm();
	return pl_normal.normalized().dot(point - pl_point);
}

HitRecord ThinLens::intersect(const Ray &ray) {
	HitRecord result;
	result.t = -1;

	double t = (c - ray.origin).dot(n) / ray.direction.dot(n);
	Eigen::Vector3d position = ray.origin + t*ray.direction;

	if ((position - c).norm() < r)   // hit
	{
		Eigen::Vector3d origin = ray.origin;
		double o = PointToPlaneDist(origin, n, c);
		Eigen::Vector3d lens_to_obj = origin - c;
		Eigen::Vector3d lens_to_objn = lens_to_obj.normalized();

		Eigen::Vector3d new_direction;
		if (abs(o - fl) <0.1)
		{
			new_direction = -lens_to_objn;

			}
		else {

			double i = 1.0 / (1.0 / fl - 1.0 / o);
			if (o > fl) {
				Eigen::Vector3d image = (-i / o)*lens_to_obj + c;
				new_direction = (image - position).normalized();
			}
			else {
				Eigen::Vector3d image = (-i / o)*lens_to_obj + c;
				new_direction = (position - image).normalized();
			}
		}

//		result.normal = (new_direction - ray.direction.normalized()).normalized();
		result.normal = new_direction;
		result.position = position;
		result.t = t;
		return result;
	}

	return result;
}


Vector3d ThinLens::getColor(Eigen::Vector3d &position) {
	return o_color;
}

double ThinLens::getReflectStrength() {
	return reflect;
}