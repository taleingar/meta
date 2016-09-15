#include "Plane.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Plane::intersect(const Ray &ray) {
	HitRecord result;
	result.t = -1;

	// set up intersection system as at^2+bt+c (see lecture 10)
	//double at = ray.direction.squaredNorm();
	//double bt = 2 * ray.direction.dot(ray.origin - c);
	//double ct = (ray.origin - c).squaredNorm() - r * r;

	double t=n.dot(c-ray.origin)/n.dot(ray.direction);
	Vector3d position = ray.origin + t * ray.direction;
	
	if (t < numeric_limits<double>::epsilon()) 
		return result; // no hit!

	if((position - c).squaredNorm() > s){
		return result;
	}

	result.t = t;
    result.position = position;
	result.normal = n.normalized();
	return result;
}
Vector3d Plane::getColor(Eigen::Vector3d &position){
    return o_color;
}

double Plane::getReflectStrength() {
	return reflect;
}