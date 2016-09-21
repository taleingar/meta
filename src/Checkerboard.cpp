#include "Checkerboard.h"

// for debug
#include <iostream>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

CBoard::CBoard(Eigen::Vector3d &origin, Eigen::Vector3d &v1, Eigen::Vector3d &v2, Eigen::Vector3d &color1, Eigen::Vector3d &color2, int blocks, double reflectStrength) :
	o(origin), u(v1), v(v2), o_color1(color1), o_color2(color2), b(blocks), reflect(reflectStrength)  {
	Eigen::Matrix3d m;
	m.col(0) = o;
	m.col(1) = u;
	m.col(2) = v;
	m_isInvertible = (m.determinant() != 0);
	m_inv = m.inverse();
}

HitRecord CBoard::intersect(const Ray &ray) {
	HitRecord result;
	result.t = -1;
		
	// set up intersection at 
	
	Eigen::Matrix3d m;
	m.col(0) = -ray.direction;
	m.col(1) = u;
	m.col(2) = v;
	if (m.determinant() == 0)    // no inversion for matrix, ray is parallel to plane.
		return result;
	Eigen::Vector3d vec = ray.origin - o;
	Eigen::Vector3d res = m.inverse() * vec;  // res(0) = t, res(1) = ucoeff, res(2) = v(coeff)

	// need to check what happens if cannot inverse...
	if (res[1] > 0 && res[1] < 1 &&
		res[2] > 0 && res[2] < 1)            // hit
	{
		result.t = res(0);
		result.position = o + u*res(1) + v*res(2);
//		result.normal = v.cross(u).normalized();
		Eigen::Vector3d normal = v.cross(u).normalized();
		result.direction = ray.direction - 2.0*normal.dot(ray.direction)*normal;
		return result;
	}
	
	return result;
}


Vector3d CBoard::getColor(const Eigen::Vector3d &position) {
	if (!m_isInvertible)			 // should not reach this point. If m_isInvertible there should be no hit, and therefore no position...)
		return o_color1;    
	Eigen::Vector3d res = m_inv * position;
	if ( ((int)(res[1]*b) + (int)(res[2]*b))%2 )
		return o_color1;
	return o_color2;
}

double CBoard::getReflectStrength() {
	return reflect;
}