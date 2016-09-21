#ifndef CBOARD_H
#define CBOARD_H

#include "Shape.h"

namespace Raytracer148 {
	class CBoard : public Shape {
	public:
		CBoard(Eigen::Vector3d &origin, Eigen::Vector3d &v1, Eigen::Vector3d &v2, Eigen::Vector3d &color1, Eigen::Vector3d &color2, int blocks, double reflectStrength);
	
		virtual HitRecord intersect(const Ray &ray);
		virtual Eigen::Vector3d getColor(const Eigen::Vector3d &position);
		virtual double getReflectStrength();

	private:
		Eigen::Vector3d o;
		Eigen::Vector3d u;
		Eigen::Vector3d v;
		Eigen::Vector3d o_color1;
		Eigen::Vector3d o_color2;
		Eigen::Matrix3d m_inv;     // this is the inverse matrix of (o|u|v). Keeping it in memory to avoid multiple calculations of this matrix. Must check value of m_isInvertible to verify validty of value.
		bool m_isInvertible;       // true if the matrix (o|u|v) is invertible (and then the value of m_inv is meaningful).
		int b;
		double reflect;
	};
}

#endif

