#include "engine.h"
#include <iostream>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "image/stb_image.h"
#include "../world/terrain.h"

void VoxelEngine::init() {
    m_window = std::make_unique<Window>();
    m_window->init("Voxel Engine");

    m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 50.0f, 20.0f));

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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //glEnable(GL_BLEND);

    m_isRunning = true;
}

void VoxelEngine::run(Terrain& terrain) {
    while (m_isRunning) {
        processInput();
        update();
        render(terrain);
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

void VoxelEngine::render(Terrain& terrain) {
    m_window->clear(0.2f, 0.3f, 0.3f, 1.0f);

    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(m_camera->getZoom()), ASPECT, ZNEAR, ZFAR);

    terrain.build(view, projection);
#ifdef DEBUG
    m_gui->render();
#endif
    // SDL swap buffers
    m_window->swapBuffer();
}
