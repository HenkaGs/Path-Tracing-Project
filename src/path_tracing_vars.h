#ifndef PATH_TRACING_VARS
#define PATH_TRACING_VARS
#include "scene.hpp"
#include "ray.hpp"
#include "object.hpp"
#include "camera.hpp"
#include "vectors.hpp"
#include "material.hpp"
#include <chrono>
#include <vector>
#include <string>

bool fileLoaded = false;
bool fileNotFoundFlag = false;

std::vector<std::string> sceneObjects = {"None"};
std::vector<Vec3> colors;
std::vector<double> reflectances;
std::vector<double> luminosities;
std::vector<double> diffusivities;
std::vector<std::string> filepaths;
std::vector<Vec3> positions;
std::vector<double> radiuses;

static int sceneObjects_current_idx = 0;

const char *renderModes[] = {"Preview", "Final"};
static int renderMode_current_idx = 0;

int samplesPerPixel = 5;
int recursionDepth = 5;

float luminosity = 0.2;
float reflectance = 0.2;
float diffusivity = 0.2;

double yaw = 0;
double pitch = 0;

int renderProgress;
int renderMax;

float cameraVectorX = 0.0;
float cameraVectorY = 0.0;
float cameraVectorZ = 2.0;

float col1[3] = {0, 0.7, 0};

char filePath[256] = "../../scenes/input_scene_stars.txt"; // Default scene path here
char imagePath[256] = "test.bmp";

bool noRender = true;
std::chrono::duration<double> elapsed;

GLuint myTexture;
bool displayImage = false;
int renderingNow = 0;
int imwidth, imheight, imchannels;

Scene scene;
Camera cam(1, 1000, Vec3(cameraVectorX, cameraVectorY, cameraVectorZ));

#endif