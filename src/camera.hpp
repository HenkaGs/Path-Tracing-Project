#ifndef PATH_TRACER_CAMERA_CLASS
#define PATH_TRACER_CAMERA_CLASS

#include <cmath>
#include <string>
#include "vectors.hpp"
#include "ray.hpp"
#include "scene.hpp"

/**
 * \brief Camera class representing camera in 3D space and implementing render functionality
 */
class Camera
{
public:
    //Contructor
    Camera(double aspect_ratio, int image_width, Vec3 camera_center);

    //Returns ray for pixel in pixel grid, with offsets
    Ray getRayForPixel(int i, int j, float i_offset = 0, float j_offset = 0) const;

    //Rotates camera 
    void rotate(double yaw, double pitch);

    // Utility function to rotate a vector around an axis by a given angle
    Vec3 rotateVector(const Vec3& vec, const Vec3& axis, double angle) const;

    // Renders the image by calling a ray color function and saves it in a file specified by filepath
    void render(const std::string &filename, const Scene &scene, int samples_per_pixel = 1, int recursion_limit = 1);

    //Public variables to monitor camera state
    int renderProgress;
    int imheight;

    Vec3 forward_;
    Vec3 right_;
    Vec3 up_;

private:
    //Camera specification variables
    double aspect_ratio_;
    int image_width_;
    int image_height_;
    double focal_length_;
    double viewport_height_;
    double viewport_width_;
    Vec3 camera_center_;
    Vec3 viewport_u_;
    Vec3 viewport_v_;
    Vec3 pixel_delta_u_;
    Vec3 pixel_delta_v_;
    Vec3 pixel00_loc_;

    //Camera initialization functions
    void calculateImageDimensions();
    void calculateViewport();
    void calculatePixelDeltas();
    void positionCamera();
};

#endif