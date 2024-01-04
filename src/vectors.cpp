#include "vectors.hpp"
#include <iostream>


Vec3 Vec3::operator-(const double a) const {
  return Vec3(x-a, y-a, z-a);
}

Vec3 Vec3::operator-(const Vec3& a) const {
  return Vec3(x-a.x, y-a.y, z-a.z);
}

Vec3 Vec3::operator+(const Vec3& a) const {
  return Vec3(x+a.x, y+a.y, z+a.z);
}

double Vec3::dot(const Vec3& a) const {
  return x*a.x + y*a.y + z*a.z;
}

double Vec3::length_squared() const {
  return x*x + y*y + z*z;
}

Vec3 Vec3::operator/(const double a) const {
  return Vec3(x / a, y / a, z / a);
}

Vec3 Vec3::operator*(const double a) const {
  return Vec3(x * a, y * a, z * a);
}

Vec3 Vec3::operator*(const Vec3& a) const {
  return Vec3(a.x * x, a.y * y, a.z * z);
}

Vec3 operator*(const double b, const Vec3& a) {
  return Vec3(b*a.x, b*a.y, b*a.z);
}

std::ostream &operator<<(std::ostream& out, const Vec3& a) {
    out << "(" << a.x << ", " << a.y << ", " << a.z << ")";
    return out;
}

Vec3 Vec3::normalized() const {
  double len = length_squared();
  if (len == 0) {
    throw std::runtime_error("Attempt to normalize a zero-length vector.");
  }
  return Vec3(x / len, y / len, z / len);
}

// Transform values to vector from linear to gamma scale

void Vec3::linear_color_to_gamma() {
  x = std::sqrt(x/255.0)*255;
  y = std::sqrt(y/255.0)*255;
  z = std::sqrt(z/255.0)*255;
}

double Vec3::dot(const Vec3 &u, const Vec3 &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vec3 Vec3::cross(const Vec3& a, const Vec3& b) {
    return Vec3(a.y * b.z - a.z * b.y, 
                a.z * b.x - a.x * b.z, 
                a.x * b.y - a.y * b.x);
}

void Vec3::normalize(Vec3& v) {
    double length = sqrt(dot(v, v));
    if (length > 0) {
        v.x /= length;
        v.y /= length;
        v.z /= length;
    }
}


double Vec3::length() const {
        return sqrt(length_squared());
    }

Vec3 Vec3::operator-() const { return Vec3(-x, -y, -z); }

// Returns a random real in [0,1).
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

// Returns a random real in [min,max).
inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

// Generate arbitrary random vectors.
Vec3 Vec3::random(double min, double max) {
        return Vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }

// Return unit vector.
Vec3 Vec3:: unit_vector(Vec3 v) {
    return v / v.length();
}

// Generate the random vector inside of the unit sphere, reject point if outside of sphere.
Vec3 Vec3::random_in_unit_sphere() {
    while (true) {
        auto p = Vec3::random(-1,1);
        if (p.length_squared() < 1)
            return p;
    }
}

// Normalize vector to get vector on the unit sphere.
Vec3 Vec3:: random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

// Check if in the same and correct hemisphere as normal, if not, invert the vector.
Vec3 Vec3::random_on_hemisphere(const Vec3& normal) {
    Vec3 on_unit_sphere = random_unit_vector();
    if (Vec3::dot(on_unit_sphere, normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

// Returns reflected vector
Vec3 Vec3::reflect(const Vec3& v, const Vec3& normal) {
  return v - 2 * dot(v,normal) * normal;
}

// linear to gamma inversion.
double linear_to_gamma(double linear_component)
{
    return sqrt(linear_component);
}