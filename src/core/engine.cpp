#include "engine.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"
#include "window.h"
#include "input.h"
#include "gui.h"
#include "../renderer/renderer.h"
#include "../world/world.h"

CAEngine::CAEngine() = default;

CAEngine::~CAEngine() = default;

void CAEngine::init() {
    mWindow = std::make_unique<Window>();
    mWindow->init("CAEngine");

    mRenderer = std::make_unique<Renderer>();

    mCamera = std::make_unique<Camera>(glm::vec3(0.0f, 20.0f, 20.0f));

    mInput = std::make_unique<Input>();
#ifdef DEBUG
    mGui = std::make_unique<Gui>(mWindow->nativeHandle(),
                                 mWindow->glContext());
#endif

    mIsRunning = true;
}

void CAEngine::run(World& world) {
    while (mIsRunning) {
        processInput();
        update(world);
        render(world);
    }
}

void CAEngine::processInput() {
    mInput->process(*mCamera, mWindow->nativeHandle(), mDeltaTime, mIsRunning);
}

void CAEngine::update(World& world) {
    mDeltaTime = (float) (SDL_GetTicks() - mMsPreviousFrame) / 1000.0f;
    mMsPreviousFrame = SDL_GetTicks();

    updateFpsCounter();
#ifdef DEBUG
    mGui->setFPS(mFPS);
    mGui->setWorldStateInfo(world.state().generationCount, world.state().aliveCellCount);
#endif

    if (mNext) {
        world.update();
        mNext = false;
    }

    if (mReset) {
        world.reset();
        mReset = false;
    }

    if (!mStop) {
        int updateFrameCount = static_cast<int>(mFPS * mSpeed);
        if (mCurrentFrameCount % (updateFrameCount < 1 ? 1 : updateFrameCount) == 0)
            world.update();
    }

    mCamera->update();
}

void CAEngine::render(World& world) {
    mRenderer->clear(0.2f, 0.3f, 0.3f, 1.0f);

    glm::mat4 view = mCamera->getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(mCamera->getZoom()), ASPECT, ZNEAR, ZFAR);

    mRenderer->render(view, projection, world.aliveCells());

#ifdef DEBUG
    mGui->render(mStop, mNext, mReset, mSpeed);
#endif
    // SDL swap buffers
    mWindow->swapBuffer();
}

void CAEngine::updateFpsCounter() {
    double elapsedSeconds;

    mCurrentFrameCount++;

    mCurrentSeconds += mDeltaTime;
    elapsedSeconds = mCurrentSeconds - mPreviousSeconds;
    // limit text updates to 4 per second
    if (elapsedSeconds > 0.25) {
        mPreviousSeconds = mCurrentSeconds;
        mFPS = mCurrentFrameCount / elapsedSeconds;
        mCurrentFrameCount = 0;
    }
}
