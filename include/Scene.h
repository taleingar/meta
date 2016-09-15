#ifndef SCENE_H
#define SCENE_H

#include "Shape.h"
#include "Image.h"
#include <vector>
#include <limits>

namespace Raytracer148 {
class Scene {
public:
  Scene() {
      //default light position
//      lightPos[0] = 5.0;
 //     lightPos[1] = 5.0;
      lightPos[0] = 0.0;
      lightPos[1] = 0.0;
      lightPos[2] = -2.0;
      shadowRatio = 0.0;
      reflectRatio = 0.0;
  }

  virtual ~Scene() {
    for (unsigned int i = 0; i < shapes.size(); i++)
      delete shapes[i];
    shapes.resize(0);
  }

  void addShape(Shape *s) { shapes.push_back(s); }
  HitRecord closestHit(const Ray &ray, int shapeId);
  bool ShadowclosestHit(const Ray &ray, int shapeId);
 // void setReflect(double ratio);
  void setShadow(double ratio);

  //Eigen::Vector3d trace(const Ray &ray);
  Eigen::Vector3d trace(const Ray &ray, int recurse_level, const int max_recurse_level, int shapeId);
  void render(Image &image);

private:
  std::vector<Shape*> shapes;
  Eigen::Vector3d lightPos;
  double shadowRatio;
  double reflectRatio;
};
}

#endif
