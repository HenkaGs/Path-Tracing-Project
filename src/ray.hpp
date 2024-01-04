#ifndef PATH_TRACER_RAY_CLASS
#define PATH_TRACER_RAY_CLASS

#include "vectors.hpp"

// Class represeting a ray with origin and direction

class Ray {
public:
    // Default constructor
    Ray() : pos(Vec3(0, 0, 0)), dir(Vec3(0, 0, 1)) {}

    // Constructor with position and direction
    Ray(const Vec3& pos, const Vec3& dir) : pos(pos), dir(dir) {}

    Vec3 pos;
    Vec3 dir;
};

#endif