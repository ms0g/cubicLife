#include "engine.h"
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "image/stb_image.h"
#include "filesystem/filesystem.h"
#include "glad/glad.h"

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

void VoxelEngine::init() {
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

    m_cubeShader = std::make_unique<Shader>(
            fs::path(SHADER_DIR + "cube.vert.glsl"),
            fs::path(SHADER_DIR + "cube.frag.glsl"));

    m_cube = std::make_unique<Cube>(*m_cubeShader);


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


}

void VoxelEngine::render() {
    m_window->clear(0.2f, 0.3f, 0.3f, 1.0f);
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(m_camera->getZoom()), ASPECT, ZNEAR, ZFAR);

    m_cubeShader->activate();
    m_cubeShader->setMat4("view", view);
    m_cubeShader->setMat4("projection", projection);

    for (auto& pos: cubePositions) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);

        m_cubeShader->setMat4("model", model);

        m_cube->draw();
    }
#ifdef DEBUG
    m_gui->render();
#endif
    // SDL swap buffers
    m_window->swapBuffer();
}
