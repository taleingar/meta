#ifndef THINLENS_H
#define THINLENS_H

#include "Shape.h"

namespace Raytracer148 {
	enum LensType {convex, concave};
	class ThinLens : public Shape {
	public:
		// reflect strength acts as transparancy strength. 1 is full transparent
		ThinLens(Eigen::Vector3d &center, Eigen::Vector3d &normal, double radius, double focalLength, Eigen::Vector3d &color, double reflectStrength, LensType type) :
			c(center), n(normal), r(radius), fl(focalLength), o_color(color), reflect(reflectStrength), lensType(type) {}

		virtual HitRecord intersect(const Ray &ray);
		virtual Eigen::Vector3d getColor(const Eigen::Vector3d &position);
		virtual double getReflectStrength();

	private:
		Eigen::Vector3d c;			// center
		Eigen::Vector3d n;			// normal   
		double r;					// radius
		double fl;					// focal lenght
		Eigen::Vector3d o_color;
		double reflect;
		LensType lensType;
	};
}


#endif
