#include "Checkerboard.h"

// for debug
#include <iostream>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord CBoard::intersect(const Ray &ray) {
	HitRecord result;
	result.t = -1;
		
	// set up intersection at 
	
	Eigen::MatrixXd m(3, 3);
	m.col(0) = -ray.direction;
	m.col(1) = u;
	m.col(2) = v;
	Eigen::Vector3d v = ray.origin - o;
	Eigen::Vector3d res = m.inverse() * v;  // res(0) = t, res(1) = ucoeff, res(2) = v(coeff)

	// need to check what happens if cannot inverse...
	if (res[1] > 0 && res[1] < 1 &&
		res[2] > 0 && res[2] < 1)            // hit
	{
		result.t = res(0);
		result.position = o + u*res(1) + v*res(2);
		result.normal = v.cross(u).normalized();
		return result;
	}
	
	return result;
}


Vector3d CBoard::getColor(Eigen::Vector3d &position) {
	Eigen::MatrixXd m(3, 3);
	m.col(0) = o;
	m.col(1) = u;
	m.col(2) = v;
	Eigen::Vector3d res = m.inverse() * position;
	if ( ((int)(res[0]*b) + (int)(res[1]*b))%2 )
		return o_color1;
	return o_color2;
}

double CBoard::getReflectStrength() {
	return reflect;
}