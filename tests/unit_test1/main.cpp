#include "scene.hpp"

int main() {
  Scene scene;
  scene.LoadFile("input_scene.txt");
  scene.DebugPrint();
  return 0;
}