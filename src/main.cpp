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
	Image im(512, 512);

	Scene scene;
	scene.setShadow(0.5);

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
	scene.addShape(new CBoard(o, u, v, color1, color2, 6, 0));
	
	Vector3d center;
	Vector3d normal;
	Vector3d color;
	center[0] = 0;
	center[1] = 0.5;
	center[2] = 1.5;
	normal[0] = 0;
	normal[1] = 0;
	normal[2] = 1.0;
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 0.0;
	scene.addShape(new ThinLens(center, normal, .6, 0.4, color, 1));


	center[0] = 0;
	center[1] = 0.1;
	center[2] = 1.3;
	normal[0] = 0;
	normal[1] = 0;
	normal[2] = 1.0;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 0.0;
//	scene.addShape(new ThinLens(center, normal, .3, 0.4, color, 0.6));

	center[0] = 0;
	center[1] = 0;
	center[2] = 2;
	color[0] = 0;
	color[1] = 1;
	color[2] = 0;
//	scene.addShape(new Sphere(center, color, .5, .6));

	scene.render(im);

	im.writePNG("lens.png");
	return 0;
}
