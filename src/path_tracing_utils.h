#include <cstring>

#include <cmath>
#include "path_tracing_vars.h"
#include "vectors.hpp"
#include "object.hpp"
#include "material.hpp"
#include <iostream>
#include <thread>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function to load an image into an OpenGL texture
GLuint LoadTexture(char *filename)
{
    std::cout << "Loading rendered image..." << std::endl;
    unsigned char *data = stbi_load(filename, &imwidth, &imheight, NULL, 4);
    if (data == NULL)
    {
        std::cout << "Error: Image Data Null" << std::endl;
        return false;
    }
    if (data)
    {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imwidth, imheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
        std::cout << "Image loaded successfully" << std::endl;
        return textureID;
    }
    std::cout << "Image load failed" << std::endl;
    return 0; // Failed to load image
}

// Loads the generated image
void LoadRenderResult()
{
    // Modify to take the resulting filepath from rendering backend
    myTexture = LoadTexture(imagePath);
    displayImage = true;
}

// Control panel to change the position of the selected object
void objectPosMan(int idx)
{
    ImGui::Text("Pos X:");
    ImGui::SameLine();
    if (ImGui::ArrowButton("##leftX", ImGuiDir_Left))
    {
        positions[idx].x -= 0.1;
        renderingNow = 1;
        renderMode_current_idx = 0;
    }
    ImGui::SameLine();
    if (ImGui::ArrowButton("##rightX", ImGuiDir_Right))
    {
        positions[idx].x += 0.1;
        renderingNow = 1;
        renderMode_current_idx = 0;
    }
    ImGui::Text("Pos Y:");
    ImGui::SameLine();
    if (ImGui::ArrowButton("##leftY", ImGuiDir_Down))
    {
        positions[idx].y -= 0.1;
        renderingNow = 1;
        renderMode_current_idx = 0;
    }
    ImGui::SameLine();
    if (ImGui::ArrowButton("##rightY", ImGuiDir_Up))
    {
        positions[idx].y += 0.1;
        renderingNow = 1;
        renderMode_current_idx = 0;
    }

    ImGui::Text("Pos Z:");
    ImGui::SameLine();
    if (ImGui::ArrowButton("##leftZ", ImGuiDir_Down))
    {
        positions[idx].z += 0.1;
        renderingNow = 1;
        renderMode_current_idx = 0;
    }
    ImGui::SameLine();
    if (ImGui::ArrowButton("##rightZ", ImGuiDir_Up))
    {
        positions[idx].z -= 0.1;
        renderingNow = 1;
        renderMode_current_idx = 0;
    }
}

// Backend to call Scene to load the file
void loadFile()
{
    fileLoaded = false;

    scene = Scene();

    if (scene.LoadFile(filePath) != -1)
    { // Create materials

        sceneObjects.clear();
        colors.clear();
        reflectances.clear();
        luminosities.clear();
        diffusivities.clear();
        filepaths.clear();
        positions.clear();
        radiuses.clear();
        sceneObjects_current_idx = 0;

        for (int i = 0; i < scene.GetObjectCount(); i++)
        {
            // Populate list
            std::string obj = "Object " + std::to_string(i + 1);
            sceneObjects.push_back(obj);

            colors.push_back(scene.GetObject(i)->material_.baseColor_);
            reflectances.push_back(scene.GetObject(i)->material_.reflectance_);
            luminosities.push_back(scene.GetObject(i)->material_.luminosity_);
            diffusivities.push_back(scene.GetObject(i)->material_.diffusivity_);
            filepaths.push_back(scene.GetObject(i)->material_.filepath_);

            positions.push_back(scene.GetObject(i)->getPos());
            radiuses.push_back(scene.GetObject(i)->getRad());

            // scene.GetObject(i)->center_;
            // scene.GetObject(i)->radius_;
        }

        //scene.DebugPrint();

        fileLoaded = true;
        fileNotFoundFlag = false;
    }
    else
    {
        fileNotFoundFlag = true;
    }
}

// Pass relevant data to Camera object and call render. This starts the backend rendering.
void renderBackend()
{

    int spp = samplesPerPixel;
    int rd = recursionDepth;

    if (renderMode_current_idx == 0)
    {
        spp = 1;
        rd = 1;
    }

    //scene.DebugPrint();

    cam = Camera(1, 1000, Vec3(cameraVectorX, cameraVectorY, cameraVectorZ));
    cam.rotate(yaw, pitch);
    cam.render("test.bmp", scene, spp, rd);
}

// This is a wrapper around the renderBackend function to clean the timing setup.
void Render()
{
    std::cout << "Rendering scene at " << filePath << std::endl;
    auto start = std::chrono::steady_clock::now();
    //   Call Backend Here
    //   We want backend to take arguments, e.g. scene location, and return the file path to the resulting image

    renderBackend();

    auto end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "Rendering took " << elapsed.count() << " s" << std::endl;
    noRender = false;
    renderingNow = -1;
}

// SceneControls control panel. Change camera position and start preview rendering.
void ShowSceneControls()
{
    ImGui::Begin("Scene Controls");
    if (fileLoaded)
    {
        ImGui::Text("Camera X:");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##leftX", ImGuiDir_Left))
        {
            cameraVectorX -= 0.1;
            renderingNow = 1;
            renderMode_current_idx = 0;
        }
        ImGui::SameLine();
        if (ImGui::ArrowButton("##rightX", ImGuiDir_Right))
        {
            cameraVectorX += 0.1;
            renderingNow = 1;
            renderMode_current_idx = 0;
        }
        ImGui::Text("Camera Y:");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##leftY", ImGuiDir_Down))
        {
            cameraVectorY -= 0.1;
            renderingNow = 1;
            renderMode_current_idx = 0;
        }
        ImGui::SameLine();
        if (ImGui::ArrowButton("##rightY", ImGuiDir_Up))
        {
            cameraVectorY += 0.1;
            renderingNow = 1;
            renderMode_current_idx = 0;
        }

        ImGui::Text("Camera Z:");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##leftZ", ImGuiDir_Down))
        {
            cameraVectorZ += 0.1;
            renderingNow = 1;
            renderMode_current_idx = 0;
        }
        ImGui::SameLine();
        if (ImGui::ArrowButton("##rightZ", ImGuiDir_Up))
        {
            cameraVectorZ -= 0.1;
            renderingNow = 1;
            renderMode_current_idx = 0;
        }
        ImGui::Text("Camera Pitch & Yaw");
        if (ImGui::ArrowButton("##leftP", ImGuiDir_Down))
        {
            pitch -= 0.1;
            renderingNow = 1;
            renderMode_current_idx = 0;
        }
        ImGui::SameLine();
        if (ImGui::ArrowButton("##rightP", ImGuiDir_Up))
        {
            pitch += 0.1;
            renderingNow = 1;
            renderMode_current_idx = 0;
        }
        if (ImGui::ArrowButton("##leftYaw", ImGuiDir_Left))
        {
            yaw += 0.1;
            renderingNow = 1;
            renderMode_current_idx = 0;
        }
        ImGui::SameLine();
        if (ImGui::ArrowButton("##rightYaw", ImGuiDir_Right))
        {
            yaw -= 0.1;
            renderingNow = 1;
            renderMode_current_idx = 0;
        }
    }
    else
    {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "LOAD FILE TO ENABLE RENDERING");
    }
    ImGui::End();
}

// Change attributes of the selected object - the functional part
void AlterObject(int idx)
{
    if (fileLoaded)
    {

        const double zero = 0.;
        const double one = 1.;
        // ImGui::SliderFloat("Reflectance", &reflectances[idx], 0, 1);
        // ImGui::DragScalar("drag double", ImGuiDataType_Double, &reflectances[idx], 0.0005f, &zero, &one, "%.10f grams");

        ImGui::SliderScalar("Reflectance", ImGuiDataType_Double, &reflectances[idx], &zero, &one, "%.10f");
        ImGui::SliderScalar("Luminosity", ImGuiDataType_Double, &luminosities[idx], &zero, &one, "%.10f");
        ImGui::SliderScalar("Diffusivity", ImGuiDataType_Double, &diffusivities[idx], &zero, &one, "%.10f");
        ImGui::SliderScalar("Radius", ImGuiDataType_Double, &radiuses[idx], &zero, &one, "%.10f");
        ImGui::Checkbox("Visible", &scene.GetObject(idx)->visible_);
        objectPosMan(idx);
        ImGui::Text(filepaths[idx].c_str());
        // ImGui::ColorEdit3("Color", &colors[idx]);
    }
}

// Control panel for AlterObject.
void ShowObjectControls()
{
    ImGui::Begin("Scene Properties");

    const char *combo_sceneObjects_prev = sceneObjects[sceneObjects_current_idx].c_str();
    if (ImGui::BeginCombo("Objects", combo_sceneObjects_prev))
    {
        for (int n = 0; n < sceneObjects.size(); n++)
        {
            const bool is_selected = (sceneObjects_current_idx == n);
            if (ImGui::Selectable(sceneObjects[n].c_str(), is_selected))
                sceneObjects_current_idx = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    AlterObject(sceneObjects_current_idx);
    ImGui::End();
}

// Backend to update the materials for objects
void setMaterials()
{
    std::cout << "Setting materials..." << std::endl;
    for (int i = 0; i < colors.size(); i++)
    {
        double luminosity = 0.5;
        if (renderMode_current_idx == 1)
        {
            luminosity = luminosities[i];
        }
        Material newMat(colors[i], reflectances[i], luminosity, diffusivities[i], filepaths[i]);
        scene.GetObject(i)->setMaterial(newMat);
        scene.GetObject(i)->setPos(positions[i]);
        scene.GetObject(i)->setRad(radiuses[i]);
    }
}

// This is a status window that is unused. Preserve for legacy
void ShowStatusWindow()
{
    ImGui::Begin("Status Window");
    ImGui::Text("This is a status window.");
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "File not loaded.");
    ImGui::Text("Current File:");
    ImGui::End();
}

// File Manager control panel. Calls loadFile to handle the backend.
void ShowFileManager()
{
    ImGui::Begin("File Manager");

    ImGui::Text("File Status:");

    ImGui::SameLine();
    if (fileLoaded)
    {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "SCENE LOADED");
    }
    else
    {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "SCENE NOT LOADED");
    }

    ImGui::Text("File Path:");
    ImGui::InputText("##file", filePath, IM_ARRAYSIZE(filePath));

    if (ImGui::Button("Load File"))
    {
        // Code to handle the file opening, e.g., loading the file using 'filePath'
        loadFile();
    }
    if (fileNotFoundFlag)
    {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "FILE NOT FOUND");
    }

    ImGui::End();
}

// Render control panel
void ShowGenerationManager()
{
    ImGui::Begin("Rendering");

    ImGui::Text("Render Status:");

    if (fileLoaded)
    {
        if (renderingNow == -1)
        {
            LoadRenderResult();
            renderingNow++;
        }
        // RenderingNow is an int we increment because ImGui collects all info about widgets during one pass
        // and then renders them at the end. Since calling Render(); function essentially freezes ImGui,
        // we can only display the yellow "RENDERING..." text if we do 2 full ImGui passes before calling Render();
        // Note, this isn't strictly true anymore since we multithreaded, but preserve the setup for now
        if (renderingNow == 0)
        {
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "READY");
        }
        else if (renderingNow == 1)
        {
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "RENDERING...");
            renderingNow++;
            setMaterials(); // We don't set materials inside a thread to avoid race conditions
        }
        else if (renderingNow == 2)
        {
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "RENDERING...");
            std::thread myThread(Render); // Create a thread running myFunction
            myThread.detach();
            //  myThread.join();
            renderingNow = 3;
        }
        else if (renderingNow == 3)
        {
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "RENDERING...");
            renderProgress = cam.renderProgress;
            renderMax = cam.imheight;
            float progress = static_cast<float>(renderProgress) / static_cast<float>(renderMax);
            ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
        }

        const char *combo_preview_value = renderModes[renderMode_current_idx];
        if (ImGui::BeginCombo("Render Mode", combo_preview_value))
        {
            for (int n = 0; n < IM_ARRAYSIZE(renderModes); n++)
            {
                const bool is_selected = (renderMode_current_idx == n);
                if (ImGui::Selectable(renderModes[n], is_selected))
                    renderMode_current_idx = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        ImGui::SliderInt("Samples per pixel", &samplesPerPixel, 1, 200);
        ImGui::SliderInt("Recursion Depth", &recursionDepth, 1, 200);

        if (ImGui::Button("Render Scene"))
        {
            renderingNow = 1;
        }
    }
    else
    {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "LOAD FILE TO ENABLE RENDERING");
    }

    if (noRender == false)
    {
        ImGui::SameLine();
        ImGui::Text("Rendering took %f s", elapsed.count());
    }

    ImGui::End();
}

// Loads the image as a texture
void ShowImage()
{
    ImGui::Begin("Render Window");
    // ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, tint_col, border_col);
    if (displayImage)
    {
        ImGui::Image((void *)(intptr_t)myTexture, ImVec2(imwidth, imheight));
    }
    ImGui::End();
}

// Loads the placeholder image
void LoadWelcomeImage()
{
    myTexture = LoadTexture("../test_images/blackhole.jpg");
    displayImage = true;
}