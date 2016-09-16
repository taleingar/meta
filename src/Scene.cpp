#include "Scene.h"
#include <cmath>
#include <omp.h>
#include <iostream>

using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray, int shapeId = -1) {
	HitRecord result;
	result.t = -1;
	bool foundSomething = false;

	for (unsigned int i = 0; i < shapes.size(); i++) {
		if(shapeId == i) //skip castign for itself
			continue;

		HitRecord r = shapes[i]->intersect(ray);
		if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
			result = r;
			result.shapeId = i;
			foundSomething = true;
			result.color = shapes[i]->getColor(result.position);
		}
	}
	return result;
}

bool Scene::ShadowclosestHit(const Ray &ray, int shapeId = -1) {
	for (unsigned int i = 0; i < shapes.size(); i++) {
		if(shapeId == i) //skip casting shadows for itself
			continue;
		HitRecord r = shapes[i]->intersect(ray);
		if (r.t > numeric_limits<double>::epsilon()) {
			return true;
		}
	}
	return false;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray, int recurse_level, const int max_recurse_level, int shapeId=-1) {
	// For now we'll have diffuse shading with no shadows, so it's easy!
	HitRecord r = closestHit(ray, shapeId);


	Vector3d result(0,0,0);
	Vector3d center(0,0,0);
	Vector3d lightColor(1.0, 1.0, 1.0);

	//we need to make this coming from the HitRecord, and knowing which object is which
	Vector3d objectColor;

	if (r.t < numeric_limits<double>::epsilon())
		return result;


	//if we have a hit, now cast a shadow
	Ray shadowRay;
	double shadowStrength = 1.0;
	shadowRay.origin= r.position;
	shadowRay.direction = (lightPos-r.position);
	bool got_shadow = ShadowclosestHit(shadowRay, r.shapeId);
	if(got_shadow){
		//this is black
		//return Vector3d(0,0,0);
		shadowStrength = shadowRatio;
	}

	//if we have a hit, now cast a reflection
	Ray reflectRay;
	reflectRay.origin= r.position;
	reflectRay.direction = ray.direction - 2.0*r.normal.dot(ray.direction)*r.normal;
	Vector3d reflect_color(0,0,0);
	if(recurse_level < max_recurse_level){
		reflect_color = trace(reflectRay, ++recurse_level, max_recurse_level, r.shapeId);
	}

	Vector3d lightDir = (lightPos - r.position).normalized();
	objectColor = r.color;

	// Ambient
	double ambientStrength = 0.2;
	Vector3d ambient = ambientStrength * lightColor;

	// Diffuse
	double diffuseStrength = 1.0;
	Vector3d norm = r.normal.normalized();
	double diff = norm.dot(lightDir);
	Vector3d diffuse = diffuseStrength * max(diff, 0.0) * lightColor;

	// Specular
	double specularStrength = 0.5;
	Vector3d viewDir = (center - r.position).normalized();
	Vector3d reflectDir;
	//I - 2.0 * dot(N, I) * N
	reflectDir = -lightDir - 2.0*norm.dot(-lightDir)*norm;
	double spec = pow(max(viewDir.dot(reflectDir), 0.0), 32);
	Vector3d specular = specularStrength * spec * lightColor;

	// double reflectStrength = reflectRatio;
	double reflectStrength = shapes[r.shapeId]->getReflectStrength();

	result = shadowStrength*(ambient+diffuse+specular).cwiseProduct(objectColor)+reflectStrength*reflect_color;

	return result;
}

void Scene::render(Image &image) {
	// We make the assumption that the camera is located at (0,0,0)
	// and that the image plane happens in the square from (-1,-1,1)
	// to (1,1,1).

	assert(image.getWidth() == image.getHeight());
	const int MAX_RECURSVE_STEP = 20;

	int size = image.getWidth();
	double pixelSize = 2. / size;
	int progress = 0;
	int last_printed = progress;
	std::cout << progress << "%" << endl;
	for (int x = 0; x < size; x++)
#pragma omp parallel for
		for (int y = 0; y < size; y++) {
			progress = 100 * (x*size + y) / (size*size); 
			if (last_printed != progress) {
				last_printed = progress;
				std::cout << progress << "%" << endl;
			}
			Vector3d color(0, 0, 0);
			double total = 0;
			//multi-sample 2x2
			for(double sub_x = -0.25; sub_x <=0.25; sub_x+=0.5){
				for(double sub_y = -0.25; sub_y <=0.25; sub_y+=0.5){
					Ray curRay;
					curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

					curRay.direction[0] = (x + 0.5 + sub_x) * pixelSize - 1 ;
					curRay.direction[1] = 1 - (y + 0.5 + sub_y) * pixelSize ;
					curRay.direction[2] = 1;

					color += trace(curRay, 0, MAX_RECURSVE_STEP);
					total++;
				}
			}
			color = color / total;
			image.setColor(x, y, color[0], color[1], color[2]);
		}
}

void Scene::setShadow(double ratio){
	shadowRatio = ratio;
}

/*
void Scene::setReflect(double ratio){
	reflectRatio = ratio;
}
*/