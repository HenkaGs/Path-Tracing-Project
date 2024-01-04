#ifndef PATH_TRACER_SPHERE_CLASS
#define PATH_TRACER_SPHERE_CLASS

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "object.hpp"
#include "vectors.hpp"
#include <iostream>
#include "material.hpp"

/**
 * \brief Sphere object inheriting from virtual Object class
 */
class Sphere : public Object {
  public:
    /**
   * \brief Construct a sphere from center and radius data
   */
    Sphere(Vec3 center, double radius, const Material& material)
    : Object(), center_(center), radius_(radius) {
    setMaterial(material); 
    }


    /**
   * \brief Return a new sphere constructed from an input stream
   */
    static Sphere *Read(std::istream &stream);
    void PrintInfo() const override;

    /**
    * \brief Returns true and fills passed HitRecord if ray hits sphere, else returns false
    */
    bool hit(const Ray& ray, HitRecord& record, double mindist) const override;

    /**
    * \brief Getter and setter functions for sphere position
    */
    Vec3 getPos() const override {return center_;}
    void setPos(Vec3 center) override {center_ = center;}

    /**
    * \brief Getter and setter functions for sphere radius
    */
    double getRad() const override {return radius_;}
    void setRad(double radius) override {radius_ = radius;}

    Vec3 center_;
    double radius_;

    // Method to compute UV coordinates from a point on the sphere
    void GetUv(const Vec3& p, double& u, double& v) const;
};

#endif