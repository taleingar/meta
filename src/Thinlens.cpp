#include "Thinlens.h"

// for debug
#include <iostream>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

// must be somewhere in Eigen. But couldn't find...
inline double PointToPlaneDist(const Eigen::Vector3d &point, const Eigen::Vector3d &pl_normal, const Eigen::Vector3d &pl_point) {
	return pl_normal.normalized().dot(point - pl_point);
}

HitRecord ThinLens::intersect(const Ray &ray) {
	HitRecord result;
	result.t = -1;

	if (ray.direction.dot(n) < numeric_limits<double>::epsilon())   // ray parallel to lens (either meeting lens or not)
		return result;                                            

	double t = (c - ray.origin).dot(n) / ray.direction.dot(n);      // calculate ray and plane intersection
	Eigen::Vector3d position = ray.origin + t*ray.direction;		// calculate point of intersection on plane

	if ((position - c).norm() < r)   // hit
	{
		double o = PointToPlaneDist(ray.origin, n, c);
		Eigen::Vector3d lens_to_obj = ray.origin - c;
		Eigen::Vector3d lens_to_objn = lens_to_obj.normalized();

		Eigen::Vector3d new_direction;
		if (abs(o - fl) < numeric_limits<double>::epsilon())
		{
			new_direction = -lens_to_objn;
		}
		else 
		{
			double i = 1.0 / (1.0 / fl - 1.0 / o);
			Eigen::Vector3d image;
			if (lensType == concave)
			{
				image = (i / o)*lens_to_obj + c;
				if (o < fl) 
					new_direction = (image - position).normalized();
				else 
					new_direction = (position - image).normalized();
			}
			else
			{
				image = (-i / o)*lens_to_obj + c;
				if (o > fl) 
					new_direction = (image - position).normalized();
				else 
					new_direction = (position - image).normalized();
			}

		}

//		result.normal = (new_direction - ray.direction.normalized()).normalized();
		result.direction = new_direction;
		result.position = position;
		result.t = t;
		return result;
	}

	return result;
}


Vector3d ThinLens::getColor(const Eigen::Vector3d &position) {
	return o_color;
}

double ThinLens::getReflectStrength() {
	return reflect;
}