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
	Image im1(256, 256);
	Image im2(256, 256);
	Image im3(128, 128);

	Scene scene1;
	Scene scene2;
	Scene scene3;

	Vector3d center;
	Vector3d normal;
	Vector3d color;

	/* shadow demo with 4 planes */
	//set the reflect and shadow parameters
//	scene1.setReflect(0.0);
	scene1.setShadow(0.5);

	center[0] = 0;
	center[1] = 0;
	center[2] = 5;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;

	scene1.addShape(new Sphere(center, color, 1.0, 0.0));

	center[0] = -10;
	center[1] = 0;
	center[2] = 20;
	normal[0] = 1.0;
	normal[1] = 0.0;
	normal[2] = 0.0;
	color[0] = 1.0;
	color[1] = 0.0;
	color[2] = 0.0;
	scene1.addShape(new Plane(center, normal, color, 100, 0.0));

	center[0] = 10;
	center[1] = 0;
	center[2] = 20;
	normal[0] = -1.0;
	normal[1] = 0.0;
	normal[2] = 0.0;
	color[0] = 0.0;
	color[1] = 1.0;
	color[2] = 0.0;
	scene1.addShape(new Plane(center, normal, color, 100, 0.0));

	center[0] = 0;
	center[1] = 0;
	center[2] = 30;
	normal[0] = 0.0;
	normal[1] = 0.0;
	normal[2] = -1.0;
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 1.0;
	scene1.addShape(new Plane(center, normal, color, 100, 0.0));

	center[0] = 0;
	center[1] = 10;
	center[2] = 20;
	normal[0] = 0.0;
	normal[1] = -1.0;
	normal[2] = 0.0;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
	scene1.addShape(new Plane(center, normal, color, 100, 0.0));

	center[0] = 0;
	center[1] = -10;
	center[2] = 20;
	normal[0] = 0.0;
	normal[1] = 1.0;
	normal[2] = 0.0;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
	scene1.addShape(new Plane(center, normal, color, 100, 0.0));

	/*reflectant scene example # 1 green plane*/
//	scene2.setReflect(1.0);
	scene2.setShadow(0.5);

	center[0] = 0;
	center[1] = 0;
	center[2] = 5;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;

	scene2.addShape(new Sphere(center, color, 1.0, 1.0));

	center[0] = 0.0;
	center[1] = -5.0;
	center[2] = 0.0;
	normal[0] = 0.0;
	normal[1] = 1.0;
	normal[2] = 0.0;
	color[0] = 0.0;
	color[1] = 1.0;
	color[2] = 0.0;
	scene2.addShape(new Plane(center, normal, color, 1000, 1.0));


	/*Messy scene*/
//	scene3.setReflect(0);
	scene3.setShadow(0.5);

	center[0] = 0;
	center[1] = 1;
	center[2] = 4;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
//	scene3.addShape(new Sphere(center, color, 0.5));


	center[0] = 0;
	center[1] = -1;
	center[2] = 3;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
//	scene3.addShape(new Sphere(center, color, 1.0));

	center[0] = -4;
	center[1] = 0;
	center[2] = 5;
	normal[0] = 2.0;
	normal[1] = 0.0;
	normal[2] = -1.0;
	color[0] = 1.0;
	color[1] = 0.0;
	color[2] = 0.0;
//	scene3.addShape(new Plane(center, normal, color, 100));

	center[0] = 4;
	center[1] = 0;
	center[2] = 5;
	normal[0] = -2.0;
	normal[1] = 0.0;
	normal[2] = -1.0;
	color[0] = 0.0;
	color[1] = 1.0;
	color[2] = 0.0;
//	scene3.addShape(new Plane(center, normal, color, 100));

	center[0] = 0;
	center[1] = 4;
	center[2] = 5;
	normal[0] = 0.0;
	normal[1] = 2.0;
	normal[2] = -1.0;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
//	scene3.addShape(new Plane(center, normal, color, 100));

	center[0] = 0;
	center[1] = -4;
	center[2] = 5;
	normal[0] = 0.0;
	normal[1] = -2.0;
	normal[2] = -1.0;
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 1.0;
//	scene3.addShape(new Plane(center, normal, color, 100));

	Vector3d o;
	Vector3d u;
	Vector3d v;
	Vector3d color1, color2;
	o[0] = 0;
	o[1] = 0;
	o[2] = 3;
	u[0] = 2;
	u[1] = 0;
	u[2] = 0;
	v[0] = 0;
	v[1] = 2;
	v[2] = 0;
	color1[0] = 1.0;
	color1[1] = 1.0;
	color1[2] = 1.0;
	color2[0] = 0.2;
	color2[1] = 0.2;
	color2[2] = 0.2;
	// create checker board
	scene3.addShape(new CBoard(o, u, v, color1, color2, 5, 0.0));

	center[0] = 1;
	center[1] = 1;
	center[2] = 2.9;
	normal[0] = 0.0;
	normal[1] = 0.0;
	normal[2] = 1.0;
	color[0] = 1.0;
	color[1] = 0.0;
	color[2] = 0.0;
	scene3.addShape(new ThinLens(center, normal, 0.5, 0.5, color, 0.0));
	//scene1.render(im1);
	//scene2.render(im2);
	scene3.render(im3);

	//im1.writePNG("four_planes.png");
	//im2.writePNG("shadow_reflect.png");
	im3.writePNG("messy.png");


	return 0;
}
