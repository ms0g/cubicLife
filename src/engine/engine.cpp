#include "engine.h"
#include <iostream>
#include "glm/glm.hpp"
#include "image/stb_image.h"
#include "filesystem/filesystem.h"
#include "../mesh/texture.h"
#include "glad/glad.h"


void VoxelEngine::init(const char* modelName) {
    m_window = std::make_unique<Window>();
    m_window->init("Voxel Engine");

    m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

    m_input = std::make_unique<Input>();
#ifdef DEBUG
    m_gui = std::make_unique<Gui>(m_window->nativeHandle(),
                                  m_window->glContext());
#endif
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // Configure global opengl state
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);

    m_shader = std::make_unique<Shader>(
            fs::path(SHADER_DIR + "toon.vert.glsl"),
            fs::path(SHADER_DIR + "toon.frag.glsl"));

    std::vector<float> vertices = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


    std::vector<Texture> textures;
    Texture texture;
    texture.id = texture::load(fs::path(ASSET_DIR + "grass.png").c_str());
    texture.name = "texture1";
    texture.path = "container.jpg";

    textures.push_back(texture);

    m_shader->activate();
    m_shader->setInt(texture.name, 0);

    m_mesh = std::make_unique<Mesh>(vertices, textures);

    m_isRunning = true;
}

void VoxelEngine::run() {
    while (m_isRunning) {
        processInput();
        update();
        render();
    }
}

void VoxelEngine::processInput() {
    m_input->process(*m_camera, m_window->nativeHandle(), m_deltaTime, m_isRunning);
}

void VoxelEngine::update() {
    m_deltaTime = (SDL_GetTicks() - m_millisecsPreviousFrame) / 1000.0f;
    m_millisecsPreviousFrame = SDL_GetTicks();
#ifdef DEBUG
    m_gui->updateFpsCounter(m_deltaTime);
#endif

    m_camera->update();

    m_shader->update(m_camera->getViewMatrix(),
                     glm::perspective(glm::radians(m_camera->getZoom()),
                                      ASPECT, ZNEAR, ZFAR),
                     glm::mat4(1.0f));
}

void VoxelEngine::render() {
    m_window->clear(0.2f, 0.3f, 0.3f, 1.0f);

    m_mesh->render();
#ifdef DEBUG
    m_gui->render();
#endif
    // SDL swap buffers
    m_window->swapBuffer();
}
