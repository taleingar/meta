#ifndef CBOARD_H
#define CBOARD_H

#include "Shape.h"

namespace Raytracer148 {
	class CBoard : public Shape {
	public:
		CBoard(Eigen::Vector3d &origin, Eigen::Vector3d &v1, Eigen::Vector3d &v2, Eigen::Vector3d &color1, Eigen::Vector3d &color2, int blocks, double reflectStrength) : 
			o(origin), u(v1), v(v2), o_color1(color1), o_color2(color2), b(blocks), reflect(reflectStrength) {}

		virtual HitRecord intersect(const Ray &ray);
		virtual Eigen::Vector3d getColor(const Eigen::Vector3d &position);
		virtual double getReflectStrength();

	private:
		Eigen::Vector3d o;
		Eigen::Vector3d u;
		Eigen::Vector3d v;
		Eigen::Vector3d o_color1;
		Eigen::Vector3d o_color2;
		int b;
		double reflect;
	};
}

#endif

