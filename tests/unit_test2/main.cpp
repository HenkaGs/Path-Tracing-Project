#include "scene.hpp"
#include "ray.hpp"
#include "object.hpp"
#include <iostream>

int main() {
  Scene scene;
  scene.LoadFile("input_scene.txt");
  scene.DebugPrint();

  Ray ray;
  HitRecord record;

  ray.pos = Vec3(0,0,0);
  ray.dir = Vec3(1,0,0);
  bool hit = scene.hit(ray, record, 0, 100);
  if (hit) { std::cout << "Ray " << ray.pos << " " << ray.dir << " hits " << record.pos <<  " " << record.normal << std::endl; }

  ray.pos = Vec3(5,0,0);
  ray.dir = Vec3(1,0.1,-0.1);
  hit = scene.hit(ray, record, 0, 100);
  if (hit) { std::cout << "Ray " << ray.pos << " " << ray.dir << " hits " << record.pos <<  " " << record.normal << std::endl; }

  ray.pos = Vec3(-5,0,0);
  ray.dir = Vec3(1,0,0);
  hit = scene.hit(ray, record, 0, 100);
  if (hit) { std::cout << "Ray " << ray.pos << " " << ray.dir << " hits " << record.pos <<  " " << record.normal << std::endl; }

  return 0;
}