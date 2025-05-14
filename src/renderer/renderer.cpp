#include "renderer.h"
#include <stdexcept>
#include <iostream>
#include <format>
#include <SDL.h>
#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "image/stb_image.h"
#include "../world/cell.h"
#include "../core/io.hpp"
#include "../config/config.hpp"

Renderer::Renderer() {
    mWindow = std::make_unique<Window>();
    mWindow->init("CAEngine");

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    mGui = std::make_unique<Gui>(mWindow->nativeHandle(),
                                 mWindow->glContext());
    // Tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // Configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    std::vector<float> cellVertices = {
             // Back face
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, // Bottom-left
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, // top-right
             0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f, // bottom-right
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, // top-right
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, // bottom-left
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f, // top-left
             // Front face
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f, // bottom-left
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 0.0f, // bottom-right
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 1.0f, // top-right
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 1.0f, // top-right
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 1.0f, // top-left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f, // bottom-left
             // Left face
            -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f, // top-right
            -0.5f,  0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, // top-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, // bottom-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, // bottom-left
            -0.5f, -0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, // bottom-right
            -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f, // top-right
             // Right face
             0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // top-left
             0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-right
             0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // top-right
             0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-right
             0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // top-left
             0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // bottom-left
             // Bottom face
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // top-right
             0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // top-left
             0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // bottom-left
             0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // bottom-left
            -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // bottom-right
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // top-right
             // Top face
            -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // top-left
             0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // bottom-right
             0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // top-right
             0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // bottom-right
            -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // top-left
            -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // bottom-left
    };

    std::vector<Texture> cellTextures = {
        {
            texture::load(fs::path(ASSET_DIR + "/glowing-rocks.jpg").c_str()),
            "texture1",
            "glowing-rocks.jpg"
        }
    };

    cellMesh = std::make_unique<CellMesh>(cellVertices, cellTextures);
    cellMesh->setup();

    cellShader = std::make_unique<Shader>(fs::path(SHADER_DIR + "/cell.vert"),
                                          fs::path(SHADER_DIR + "/cell.frag"));

    cellShader->activate();
    cellShader->setInt(cellTextures[0].name, 0);

    skybox = std::make_unique<Skybox>();

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GLSL Version:: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    std::cout << "OpenGL Driver Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << "\n";
}

void Renderer::render(const glm::mat4& view, const glm::mat4& projection,
                      const std::unordered_map<std::string, Cell>& aliveCells) const {
    // Setup model matrices
    std::vector<glm::mat4> modelMatrices;
    for (const auto& [_, cell]: aliveCells) {
        auto model = glm::mat4(1.0f);
        model = glm::translate(model, cell.pos());

        modelMatrices.push_back(model);
    }

    cellMesh->setupInstancing(modelMatrices);

    cellShader->activate();
    cellShader->setMat4("view", view);
    cellShader->setMat4("projection", projection);
    cellMesh->draw();

    auto skyview = glm::mat4(glm::mat3(view));
    skybox->render(skyview, projection);
}

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
