#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

namespace Raytracer148 {
class Plane : public Shape {
public:
    Plane(Eigen::Vector3d &center, Eigen::Vector3d &normal, Eigen::Vector3d &color, double size, double reflectStrength) :
		c(center), n(normal), o_color(color), s(size), reflect(reflectStrength) {}

    virtual HitRecord intersect(const Ray &ray);
    virtual Eigen::Vector3d getColor(const Eigen::Vector3d &position);
	virtual double getReflectStrength();

private:
    Eigen::Vector3d c;
    Eigen::Vector3d n;
    Eigen::Vector3d o_color;
    double s;
	double reflect;
};
}

#endif
