#include "scene.hpp"
#include "ray.hpp"
#include "object.hpp"
#include "camera.hpp"
#include "vectors.hpp"
#include "material.hpp"
#include <iostream>

int main() {
    Scene scene;

    // Create materials
    Material texturedMaterial(Color(255, 0, 0), 0.5, 0.0, "8k_jupiter.jpg"); // textured, half reflective
    Material greenMaterial(Color(0, 112, 0), 0.3, 0.0, ""); // Green, less reflective
    Material blueMaterial(Color(0, 0, 128), 0.1, 0.0, ""); // Blue, minimally reflective


    // Load scene from file or create objects programmatically
    scene.LoadFile("input_scene.txt");

    scene.GetObject(0)->setMaterial(texturedMaterial);
    scene.GetObject(1)->setMaterial(texturedMaterial);
    scene.GetObject(2)->setMaterial(texturedMaterial);

    scene.DebugPrint();

    // Test rays
    Ray testRay1(Vec3(0, 0, 0), Vec3(0, 0, -1)); // Should hit redSphere
    Ray testRay2(Vec3(3, 0, 0), Vec3(-1, 0, -1)); // Should hit greenSphere
    Ray testRay3(Vec3(-3, 0, 0), Vec3(1, 0, -1)); // Should hit blueSphere

    HitRecord record;
    if (scene.hit(testRay1, record, 0, 100)) {
        std::cout << "Ray hits object at " << record.pos << " with color " << record.color << std::endl;
    }

    if (scene.hit(testRay2, record, 0, 100)) {
        std::cout << "Ray hits object at " << record.pos << " with color " << record.color << std::endl;
    }

    if (scene.hit(testRay3, record, 0, 100)) {
        std::cout << "Ray hits object at " << record.pos << " with color " << record.color << std::endl;
    }


    return 0;
}
