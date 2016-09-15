#include "Thinlens.h"

// for debug
#include <iostream>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord ThinLens::intersect(const Ray &ray) {
	HitRecord result;
	result.t = -1;

	Eigen::MatrixXd m(3, 3);
	double t = (c - ray.origin).dot(n) / ray.direction.dot(n);

	Eigen::Vector3d position = ray.origin + t*ray.direction;
	if ((position - c).norm() < r)   // hit
	{
		result.normal = n;
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