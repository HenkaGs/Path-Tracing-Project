#include "sphere.hpp"
#include "vectors.hpp"
#include <string>
#include <limits>
#include <memory>
#include <math.h>
#include <iostream>

// This function reads properties of a Sphere object from an input stream and creates a new Sphere object with these properties. 
// If the reading process encounters an error or if the data is invalid, it returns NULL.
Sphere* Sphere::Read(std::istream &stream) {
    std::string temp;
    Vec3 center;
    double radius = -1;                                             // Set to -1 incase no proper value is read so the function returns NULL
    double r = 0, g = 0, b = 0;
    double reflectance = -1, luminosity = -1, diffusivity = -1;     // Set to -1 incase no proper value is read so the function returns NULL
    std::string filepath;

     while (stream >> temp) {
        if (temp == "---") {
            break; 
        }
        if (temp == "center") {
            if (!(stream >> center.x >> center.y >> center.z)) {
                return NULL; 
            }
        } else if (temp == "radius") {
            if (!(stream >> radius) || radius < 0) {
                return NULL; 
            }
        } else if (temp == "color") {
            int rTemp, gTemp, bTemp; 
            if (!(stream >> rTemp >> gTemp >> bTemp)) {
                return NULL; 
            }
            r = static_cast<unsigned char>(rTemp);
            g = static_cast<unsigned char>(gTemp);
            b = static_cast<unsigned char>(bTemp);
        } else if (temp == "reflectance") {
            if (!(stream >> reflectance) || reflectance < 0 || reflectance > 1) {  // Check for proper input value betweeen [0,1]
                return NULL; 
            }
        } else if (temp == "luminosity") {
            if (!(stream >> luminosity) || luminosity < 0 || luminosity > 1) {     // Check for proper input value betweeen [0,1]
                return NULL; 
            }
        } else if (temp == "diffusivity") {
            if (!(stream >> diffusivity) || diffusivity < 0 || diffusivity > 1) {  // Check for proper input value betweeen [0,1]
                return NULL; 
            }
        } else if (temp == "filepath") {
            stream >> temp;
            if (temp == "---") {
            break; 
            } filepath = temp;
        } else {
            break;
        }
        if (stream.fail()) {
            stream.clear(); 
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return NULL;
        }
    }

    if (radius < 0 || reflectance < 0 || luminosity < 0) {  // If inproper values return NULL
        return NULL; 
    }
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    // Construct new material and sphere objects.
    Material material(Vec3(r, g, b), reflectance, luminosity, diffusivity, filepath);
    return new Sphere(center, radius, material);
}

// Prints debugging info
void Sphere::PrintInfo() const {
  std::cout << "Sphere with center [" << center_.x 
            << "," << center_.y << "," << center_.z << "] and radius "
            << radius_ << std::endl;
}

// Determines if the passed ray hits the sphere, returning true if yes, otherwise false
// If ray hits the sphere, fills passed hitrecord with info about hit
bool Sphere::hit(const Ray& ray, HitRecord& record, double mindist) const {
  if (visible_ == false)
 {return false;}
  Vec3 co = ray.pos - center_;
  //Solve coefficients of second order equation and discriminant
  double a = ray.dir.length_squared();
  double b = co.dot(2.0*ray.dir);
  double c = co.length_squared() - radius_*radius_;
  double discriminant = b*b - 4.0*a*c;

  if (discriminant < 0) {
    return false;
  }
  
  //First try if smaller root satisfies mindist and maxdist. If not, try larger root
  double root = (-b - sqrt(discriminant))/(2*a);
  if (root < mindist || root > record.dist) {
    root = (-b + sqrt(discriminant))/(2*a);
    if (root < mindist || root > record.dist) {
      return false;
    }
  }

  //Write stuff to HitRecord
  record.dist = root;
  record.pos = ray.pos + root*ray.dir;
  record.normal = (1.0/radius_) * (record.pos - center_);
  if (record.normal.dot(ray.dir) > 0) {
    record.normal = -1.0*record.normal;
  }
  //Get UV coords for color sampling
  double u, v;
  GetUv(record.pos, u, v); 
  //Sample the color from the material
  record.color = material_.Sample(u, v);
  record.materialPtr = &this->material_;
  return true;

}


// This function calculates the UV coordinates of a given point p on the surface of the sphere.
void Sphere::GetUv(const Vec3& p, double& u, double& v) const {
    Vec3 p_origin = (p - center_) / radius_; 

    double phi = atan2(p_origin.z, p_origin.x) + M_PI; 
    double theta = acos(-p_origin.y); 

    u = phi / (2 * M_PI);
    v = theta / M_PI;
}



