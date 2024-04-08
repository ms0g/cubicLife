#include "engine.h"
#include <iostream>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "image/stb_image.h"
#include "camera.h"
#include "window.h"
#include "input.h"
#include "gui.h"
#include "../world/world.h"
#include "../world/skybox.h"

CAEngine::CAEngine() = default;
CAEngine::~CAEngine() = default;

void CAEngine::init() {
    mWindow = std::make_unique<Window>();
    mWindow->init("CAEngine");

    mCamera = std::make_unique<Camera>(glm::vec3(0.0f, 20.0f, 20.0f));

    mInput = std::make_unique<Input>();
#ifdef DEBUG
    mGui = std::make_unique<Gui>(mWindow->nativeHandle(),
                                 mWindow->glContext());
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

    mIsRunning = true;
}

void CAEngine::run(World& world, Skybox& skybox) {
    while (mIsRunning) {
        processInput();
        update(world);
        render(world, skybox);
    }
}

void CAEngine::processInput() {
    mInput->process(*mCamera, mWindow->nativeHandle(), mDeltaTime, mIsRunning);
}

void CAEngine::update(World& world) {
    mDeltaTime = (SDL_GetTicks() - mMillisecsPreviousFrame) / 1000.0f;
    mMillisecsPreviousFrame = SDL_GetTicks();
#ifdef DEBUG
    mGui->updateFpsCounter(mDeltaTime);
#endif

    world.update();

    mCamera->update();
}

void CAEngine::render(World& world, Skybox& skybox) {
    mWindow->clear(0.2f, 0.3f, 0.3f, 1.0f);

    glm::mat4 view = mCamera->getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(mCamera->getZoom()), ASPECT, ZNEAR, ZFAR);

    world.draw(view, projection);

    glm::mat4 skyview = glm::mat4(glm::mat3(mCamera->getViewMatrix()));
    skybox.update(skyview, projection);

    skybox.draw();
#ifdef DEBUG
    mGui->render();
#endif
    // SDL swap buffers
    mWindow->swapBuffer();
}
