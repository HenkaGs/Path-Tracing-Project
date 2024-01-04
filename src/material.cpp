#include "material.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

// Texture constructor
Texture::Texture(const std::string& filepath) {
    LoadTexture(filepath);
}

// Texture destructor
Texture::~Texture() {
    stbi_image_free(data_);
}

// Function LoadTexture uses function stbi_load found in stb_image.h to load texture data from a given texture file and saves it in data_.
void Texture::LoadTexture(const std::string& filepath) {
        data_ = stbi_load(filepath.c_str(), &width_, &height_, &channels_, 0);
        if (data_ == nullptr) {
            // Print error message if loading failed.
            std::cout << "Error loading textures" <<std::endl;
        }
}


Vec3 Texture::Sample(double u, double v) const {
    // Convert (u, v) texture coordinates to image space
    int x = static_cast<int>(u * width_);
    int y = static_cast<int>((1.0 - v) * height_); 
    int idx = (y * width_ + x) * channels_;

    // Ensure that we don't go out of bounds
    idx = std::min(idx, width_ * height_ * channels_ - 1);
    
    // Sample the color from the image data
    if (idx >= 0 && idx < width_ * height_ * channels_) {
        unsigned char* pixel = data_ + idx;
        return Vec3(pixel[0], pixel[1], pixel[2]); // Returns Vec3 with color data as parameters.
    } else {
        // Incase of error, return white
        return Vec3(255, 255, 255);
    } 
}

// Default material constructor
Material::Material()
    : baseColor_(Vec3()), reflectance_(0.0), luminosity_(0.0), diffusivity_(0.0), filepath_("") {
}

// Material constructor
Material::Material(const Vec3& baseColor, double reflectance, double luminosity, double diffusivity,
                   const std::string& texturePath)
    : baseColor_(baseColor), reflectance_(reflectance), luminosity_(luminosity), diffusivity_(diffusivity), filepath_(texturePath){
    if (!texturePath.empty() && texturePath != "empty") { 
        // If a filepath for a texture file is given, load texture data.
        texture_ = std::make_shared<Texture>(texturePath);
    }

}

// Function to sample material color from given coordinates. If texture data is available then sample from texture data. Else returns material baseColor_.
Vec3 Material::Sample(double u, double v) const {
    if (texture_) {
        Vec3 value = texture_->Sample(u, v); 
        return value;
    } else {
        return baseColor_;
    }
}

// Material copy constructor
Material::Material(const Material& other)
    : baseColor_(other.baseColor_), reflectance_(other.reflectance_), luminosity_(other.luminosity_), filepath_(other.filepath_), texture_(other.texture_){

}

// Material copy assigment operator
Material& Material::operator=(const Material& other) {
    if (this != &other) {
        baseColor_ = other.baseColor_;
        reflectance_ = other.reflectance_;
        luminosity_ = other.luminosity_;
        diffusivity_ = other.diffusivity_;
	texture_ = other.texture_;
	filepath_ = other.filepath_;
    }
    return *this;
}
