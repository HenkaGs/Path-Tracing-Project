#include "scene.hpp"
#include "ray.hpp"
#include "object.hpp"
#include "camera.hpp"
#include "vectors.hpp"
#include <iostream>

int main() {
  Scene scene;
  scene.LoadFile("input_scene.txt");
  scene.DebugPrint();

  Camera cam(2, 500, Vec3(0, 0, 0));
  cam.render("test.bmp");

  return 0;
}