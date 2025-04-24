#include "engine.h"
#include <SDL.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"
#include "input.h"
#include "../renderer/renderer.h"
#include "../world/world.h"

CAEngine::CAEngine() = default;

CAEngine::~CAEngine() = default;

void CAEngine::init() {
    mRenderer = std::make_unique<Renderer>();

    mCamera = std::make_unique<Camera>(glm::vec3(0.0f, 20.0f, 20.0f));

    mInput = std::make_unique<Input>();

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
    mInput->process(*mCamera, mRenderer->window()->nativeHandle(), mDeltaTime, mIsRunning);
}

void CAEngine::update(World& world) {
    mDeltaTime = static_cast<float>(SDL_GetTicks() - mMsPreviousFrame) / 1000.0f;
    mMsPreviousFrame = SDL_GetTicks();

    updateFpsCounter();

    mRenderer->gui()->setFPS(mFPS);
    mRenderer->gui()->setWorldStateInfo(world.state().generationCount, world.state().aliveCellCount);

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

    const glm::mat4 view = mCamera->getViewMatrix();
    const glm::mat4 projection = glm::perspective(glm::radians(mCamera->getZoom()), ASPECT, ZNEAR, ZFAR);

    mRenderer->render(view, projection, world.aliveCells());
    mRenderer->gui()->render(mStop, mNext, mReset, mSpeed);
    mRenderer->window()->swapBuffer();
}

void CAEngine::updateFpsCounter() {
    mCurrentFrameCount++;

    mCurrentSeconds += mDeltaTime;
    double elapsedSeconds = mCurrentSeconds - mPreviousSeconds;
    // limit text updates to 4 per second
    if (elapsedSeconds > 0.25) {
        mPreviousSeconds = mCurrentSeconds;
        mFPS = mCurrentFrameCount / elapsedSeconds;
        mCurrentFrameCount = 0;
    }
}
