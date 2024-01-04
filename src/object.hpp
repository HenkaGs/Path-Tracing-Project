#ifndef PATH_TRACER_OBJECT_CLASS
#define PATH_TRACER_OBJECT_CLASS

#include "vectors.hpp"
#include "ray.hpp"
#include "material.hpp"

/**
 * \brief Class for stroring information about hits
 * 
 */
class HitRecord {
  public:
    Vec3 pos;
    Vec3 normal;
    double dist;
    Vec3 color;  // Add Color to store the texture color
    const Material* materialPtr;
};

/**
 * \brief Virtual base class for objects in scene
 * 
 */
class Object {
  public:
    Object() { }
    virtual ~Object() { }

    //Public virtual functions
    virtual void PrintInfo() const = 0;
    virtual Vec3 getPos() const = 0;
    virtual void setPos(Vec3 pos) = 0;
    virtual double getRad() const = 0;
    virtual void setRad(double radius) = 0;

    // Returns true and fills passed HitRecord if ray hits object, else returns false
    virtual bool hit(const Ray& ray, HitRecord& record, double mindist) const = 0;

    //Set material property of object
    void setMaterial(const Material& material) {
      this->material_ = material;
    }
    Material material_;
    bool visible_ = true;
};

#endif
