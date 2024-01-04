#ifndef PATH_TRACER_SCENE_CLASS
#define PATH_TRACER_SCENE_CLASS

#include "object.hpp"
#include <iostream>
#include <string>
#include <vector>

/**
 * \brief Scene class containing physical objects
 */
class Scene {
  public:

    ~Scene();
    /**
   * \brief Reads a sigle line from the input stream and stores objects in objects_
   */
    bool ReadLine(std::istream& stream);

    /**
   * \brief Reads a scene input file, calls ReadLine for each line
   */
    int LoadFile(const std::string& filename);

    /**
   * \brief Prints debugging info about scene
   */
    void DebugPrint();

     /**
   * \brief Returns number of objects in scene
   */
    int GetObjectCount();

    /**
   * \brief If ray hits an object in scene, return true and fills the passed HitRecord, otherwise returns false
   */
    bool hit(const Ray& ray, HitRecord& record, double mindist, double maxdist) const;

    /**
   * \brief Gets color for ray depending hit objects' material properties and diffusion.
   */
    Vec3 getColorForRay(const Ray& ray, const Scene& scene, int recursionlimit = 1) const;

    /**
   * \brief Returns pointer to object by index
   */
    Object* GetObject(size_t index) const;
    
  private:
    std::vector<Object*> objects_;
};

#endif