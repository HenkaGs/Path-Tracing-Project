#ifndef PATH_TRACER_VECTORS_CLASS
#define PATH_TRACER_VECTORS_CLASS
#include <ostream>
#include <cmath>

/**
 * \brief Class representing a 3D vector of 3 doubles
 */
class Vec3 {
  public:
    Vec3() { }
    Vec3(double x, double y, double z)
      : x(x), y(y), z(z) { }

    // Common operator overloads
    Vec3 operator-(const double a) const;
    Vec3 operator-(const Vec3& a) const;
    Vec3 operator-() const;
    Vec3 operator+(const Vec3& a) const;
    Vec3 operator/(const double a) const;
    Vec3 operator*(const double a) const;
    Vec3 operator*(const Vec3& a) const;
    Vec3 normalized() const;

    // Transform values to vector from linear to gamma scale
    void linear_color_to_gamma();

    // Utility functions operating on Vec3

    // Returns Vec3 filled with random values between min and max 
    static Vec3 random(double min, double max);

    // Returns random Vec3 on unit sphere
    static Vec3 random_in_unit_sphere();

    // Returns v scaled to unit length
    static Vec3 unit_vector(Vec3 v);

    // Returns random unit vector
    static Vec3 random_unit_vector();

    // Returns random Vec3 on unit half-sphere
    static Vec3 random_on_hemisphere(const Vec3& normal);

    // Returns reflected Vec3
    static Vec3 reflect(const Vec3& v, const Vec3& normal);

    // Standard mathematical utility functions defined in R3
    static double dot(const Vec3 &u, const Vec3 &v);
    static Vec3 cross(const Vec3& a, const Vec3& b);
    static void normalize(Vec3& v);
    double dot(const Vec3& a) const;
    double length_squared() const;
    double length() const;

    friend Vec3 operator*(const double b, const Vec3& a);
    friend std::ostream& operator<<(std::ostream& out, const Vec3& a);

  double x;
  double y;
  double z;
};

#endif