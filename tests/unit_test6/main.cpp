#include "scene.hpp"
#include "ray.hpp"
#include "object.hpp"
#include "camera.hpp"
#include "vectors.hpp"
#include <iostream>

int main() {
  Scene scene;
  scene.LoadFile("input_scene_stars.txt");

  scene.DebugPrint();

  Camera cam(1, 1000, Vec3(0, 0, 2));
  cam.render("test.bmp", scene);

  return 0;
}