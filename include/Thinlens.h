#ifndef THINLENS_H
#define THINLENS_H

#include "Shape.h"

namespace Raytracer148 {
	class ThinLens : public Shape {
	public:

		ThinLens(Eigen::Vector3d &center, Eigen::Vector3d &normal, double radius, double focalLength, Eigen::Vector3d &color, double reflectStrength) :
			c(center), n(normal), r(radius), fl(focalLength), o_color(color), reflect(reflectStrength) {}

		virtual HitRecord intersect(const Ray &ray);
		virtual Eigen::Vector3d getColor(Eigen::Vector3d &position);
		virtual double getReflectStrength();

	private:
		Eigen::Vector3d c;			// center
		Eigen::Vector3d n;			// normal   
		double r;					// radius
		double fl;					// focal lenght
		Eigen::Vector3d o_color;
		double reflect;
	};
}


#endif
