#include "camera.hpp"
#include "BitmapPlusPlus.hpp"
#include <cmath>

Camera::Camera(double aspect_ratio, int image_width, Vec3 camera_center)
    : aspect_ratio_(aspect_ratio), image_width_(image_width), focal_length_(1.0), viewport_height_(2.0), camera_center_(camera_center)
{
    calculateImageDimensions();
    calculateViewport();
    calculatePixelDeltas();
    positionCamera();
}

// Get ray for pixel with offsets
Ray Camera::getRayForPixel(int i, int j, float i_offset, float j_offset) const
{
    Vec3 pixel_center = pixel00_loc_ + (i * pixel_delta_u_) + (j * pixel_delta_v_);
    pixel_center = pixel_center + Vec3(i_offset * pixel_delta_u_.x, j_offset * pixel_delta_v_.y, 0);
    Vec3 ray_direction = pixel_center - camera_center_;
    return Ray{camera_center_, ray_direction};
}

// Calculate the image height, and ensure that it's at least 1.
void Camera::calculateImageDimensions()
{
    image_height_ = static_cast<int>(image_width_ / aspect_ratio_);
    image_height_ = (image_height_ < 1) ? 1 : image_height_;
}

// Calculate the vectors across the horizontal and down the vertical viewport edges.
void Camera::calculateViewport()
{
    viewport_width_ = viewport_height_ * static_cast<double>(image_width_) / image_height_;
    viewport_u_ = Vec3(viewport_width_, 0, 0);
    viewport_v_ = Vec3(0, -viewport_height_, 0);
}

// Calculate the horizontal and vertical delta vectors from pixel to pixel.
void Camera::calculatePixelDeltas()
{
    pixel_delta_u_ = viewport_u_ / static_cast<double>(image_width_);
    pixel_delta_v_ = viewport_v_ / static_cast<double>(image_height_);
}

//Positions camera by setting pixel00_loc_
void Camera::positionCamera()
{
    Vec3 camera_direction = forward_;
    Vec3 half_u = viewport_u_ * 0.5;
    Vec3 half_v = viewport_v_ * 0.5;
    pixel00_loc_ = camera_center_ - half_u - half_v + camera_direction * focal_length_;
}

// Renders the image and saves it in a file
void Camera::render(const std::string &filename, const Scene &scene, int samples_per_pixel, int recursion_limit)
{
    //Initialize bitmap object
    imheight = image_height_;
    bmp::Bitmap image(image_width_, image_height_);

    //Loop over each pixel
    for (renderProgress = 0; renderProgress < image_height_; renderProgress++)
    {
        int j = renderProgress;
        for (int i = 0; i < image_width_; i++)
        {

            //Average pixel color from samples
            Vec3 pixel_color = {0, 0, 0};
            for (int sample = 0; sample < samples_per_pixel; sample++)
            {
                float i_offset = rand() / (RAND_MAX + 1.0) - 0.5;
                float j_offset = rand() / (RAND_MAX + 1.0) - 0.5;
                Ray ray = getRayForPixel(i, j, i_offset, j_offset);
                pixel_color = pixel_color + scene.getColorForRay(ray, scene, recursion_limit) / samples_per_pixel;
            }

            //Set pixel color of corresponding bitmap pixel
            pixel_color.linear_color_to_gamma();
            bmp::Pixel pixelcolor = {(uint8_t)pixel_color.x, (uint8_t)pixel_color.y, (uint8_t)pixel_color.z};
            image.set(i, j, pixelcolor);
        }
    }
    // Save image to file
    image.save(filename);
}

//Rotates camera
void Camera::rotate(double yaw, double pitch) {
    // Forward vector (assumes the camera looks towards the negative Z-axis in its default orientation)
    Vec3 forward = Vec3(0, 0, -1);

    // Right vector (assumes the right direction is along the positive X-axis)
    Vec3 right = Vec3(1, 0, 0);

    // Up vector (assumes up direction is along the positive Y-axis)
    Vec3 up = Vec3(0, 1, 0);

    // Rotate the forward vector
    forward = rotateVector(forward, right, pitch); // Pitch rotation around right vector
    forward = rotateVector(forward, up, yaw);      // Yaw rotation around up vector

    // Recalculate the right vector as cross product of forward and up
    right = Vec3::cross(up, forward);
    Vec3::normalize(right);

    // Recalculate the up vector as cross product of forward and right
    up = Vec3::cross(forward, right);
    Vec3::normalize(up);

    // Set the camera's new orientation
    forward_ = forward;
    right_ = right;
    up_ = up;

    // Update camera positioning based on new orientation
    positionCamera();
}

// Utility function to rotate a vector around an axis by a given angle
Vec3 Camera::rotateVector(const Vec3& vec, const Vec3& axis, double angle) const {
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);
    return vec * cosTheta + Vec3::cross(axis, vec) * sinTheta + axis * Vec3::dot(axis, vec) * (1 - cosTheta);
}
