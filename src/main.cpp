#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Checkerboard.h"
#include "ThinLens.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
	Image im(128, 128);

	Scene scene;

	Vector3d center;
	Vector3d normal;
	Vector3d color;


	scene.setShadow(1);
/*
	center[0] = 2;
	center[1] = 3;
	center[2] = 2;
	color[0] = 1.0;
	color[1] = 0.0;
	color[2] = 0.0;
//	scene3.addShape(new Sphere(center, color, 2, 0.9));
*/


	Vector3d o;
	Vector3d u;
	Vector3d v;
	Vector3d color1, color2;
	o[0] = -1.5;
	o[1] = -1.5;
	o[2] = 2;
	u[0] = 3;
	u[1] = 0;
	u[2] = 0;
	v[0] = 0;
	v[1] = 3;
	v[2] = 0;
	color1[0] = 1.0;
	color1[1] = 0.0;
	color1[2] = 0.0;
	color2[0] = 0.2;
	color2[1] = 0.2;
	color2[2] = 0.2;
	// create checker board
	scene.addShape(new CBoard(o, u, v, color1, color2, 8, 0));

	o[0] = 0;
	o[1] = 0;
	o[2] = 5;
	normal[0] = 0;
	normal[1] = 0;
	normal[2] = 1;
	color1[0] = 1.0;
	color1[1] = 1.0;
	color1[2] = 1.0;
	scene.addShape(new Plane(o, normal, color1, 100, 0));


	center[0] = 1;
	center[1] = 0;
	center[2] = 1.5;
	normal[0] = 0.0;
	normal[1] = 0.0;
	normal[2] = 1.0;
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 0.0;
	scene.addShape(new ThinLens(center, normal, .6, 1.5, color, 0.8));

	scene.render(im);

	//im1.writePNG("four_planes.png");
	//im2.writePNG("shadow_reflect.png");

	im.writePNG("lens.png");
	return 0;
}
