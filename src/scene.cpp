#include "scene.hpp"
#include "sphere.hpp"
#include "vectors.hpp"
#include <string>
#include <limits>
#include <fstream>
#include <iostream>

// Destructor freeing all objects
Scene::~Scene() {
  for (auto it : objects_) {
      delete it;
  }
}

// Reads a sigle line from the input stream and stores objects in objects_
bool Scene::ReadLine(std::istream& stream) {

  //First check object type by reading first element of the stream to a string
  std::string object_type;
  stream >> object_type;
  Object* o;

  //If object type matches a implemented object, call the Read function of the object
  if (object_type == "Sphere") {
    o = Sphere::Read(stream);
  } else { return false; }
  if (o == NULL) { return false; }

  //Store object in vector
  objects_.push_back(o);
  return true;
}

int Scene::GetObjectCount()
{
	return objects_.size();
}

// Reads a scene input file, calls ReadLine for each line
int Scene::LoadFile(const std::string& filename) {
  std::ifstream istr(filename);
  int counter = 0;
  if (istr.rdstate() & (istr.failbit | istr.badbit)) {
      return -1;
  } else {
    // repeat until end of file
    while (!istr.eof()) {
      if (this->ReadLine(istr)) {
        counter++;
      }
    }
  }
  return counter;
}

// Prints debugging info about scene
void Scene::DebugPrint() {
  std::cout << "Scene with " << objects_.size() << " objects:\n";
  for (auto it : objects_) {
      it->PrintInfo();
  }
}

// If ray hits an object in scene, return true and fills the passed HitRecord, otherwise returns false
bool Scene::hit(const Ray& ray, HitRecord& record, double mindist, double maxdist) const {
  record.dist = maxdist;
  bool return_value = false;
  for (auto it : objects_) {
    if (it->hit(ray, record, mindist)) {
      return_value = true;
    }
  }
  return return_value;
}

// Gets color for ray depending hit objects' material properties and diffusion.
Vec3 Scene::getColorForRay(const Ray& ray, const Scene& scene, int recursionlimit) const {
    HitRecord record;

    //If recursion limit is not exceeded and ray hits something in scene
    if (recursionlimit > 0 && scene.hit(ray, record, 0.001, std::numeric_limits<double>::max())) {
        
        // If reflectance is zero, return possible luminance
        if (record.materialPtr->getReflectance() < 1e-6) {
          return record.materialPtr->getLuminosity() * record.color;
        }

        //Else reflect ray and call getColorForRay recursively
        Vec3 direction;
        if (record.materialPtr->getDiffusivity() < 0.001) {
           direction = Vec3::reflect(ray.dir, record.normal);
        } else {
          direction = Vec3::random_on_hemisphere(record.normal);
        }
        return record.materialPtr->getReflectance() * getColorForRay(Ray(record.pos, direction), scene, recursionlimit - 1) * record.color/255 + record.materialPtr->getLuminosity() * record.color;
    } else {
        return Vec3(0, 0, 0);
    }
}
// Returns pointer to object by index
Object* Scene::GetObject(size_t index) const {
    if (index < objects_.size()) {
        return objects_[index];
    } else {
        return nullptr; 
    }
}