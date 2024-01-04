#ifndef PATH_TRACER_MATERIAL_HPP
#define PATH_TRACER_MATERIAL_HPP

#include <string>
#include <memory>
#include "vectors.hpp"

/**
* \brief Class Texture handles loading the texture from provided file
*/
class Texture {
public:
    // Texture constructor
    Texture(const std::string& filepath);

    // Texture destructor
    ~Texture();

    // Function to sample color from a given texture file at specific coordinates.
    Vec3 Sample(double u, double v) const;

private:
    unsigned char* data_;  // Pointer to image data
    int width_, height_;   // Dimensions of the image
    int channels_;         // Number of color channels in the image

    // Function to load texture data from given filepath to a data_ array.
    void LoadTexture(const std::string& filepath); 
};

/**
* \brief Class Material contains information about the objects properties. Object Color is set to baseColor unless a texture file is provided.
* If texture file is provided, Texture class handles loading, saving and freeing texture data.
*/
class Material {
public:
    // Constructor for Material object
    Material(const Vec3& baseColor, double reflectance, double luminosity, double diffusivity,
             const std::string& texturePath);

    // Default constructor
    Material();

    // Copy constructor
    Material(const Material& other);

    // Copy assignment operator
    Material& operator=(const Material& other);

    // Function to get material color data in given coordinates
    Vec3 Sample(double u, double v) const;

    // Getter functions for reflectance, luminosity and diffusivity
    double getReflectance() const { return reflectance_; }
    double getLuminosity() const { return luminosity_; }
    double getDiffusivity() const { return diffusivity_; }

    Vec3 baseColor_;                   // Material base color, used if no texture file is loaded.
    double reflectance_;               // Reflectance of material surface 
    double luminosity_;                // Luminosity of the object
    double diffusivity_;               // Diffusivity of material surface 
    std::string filepath_;             // Filepath to material texture file
    std::shared_ptr<Texture> texture_; // Texture object which holds the image data
};

#endif
