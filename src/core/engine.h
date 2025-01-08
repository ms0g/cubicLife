#pragma once

#include <memory>

class World;
class Camera;
class Window;
class Input;
class Gui;
class Renderer;
class CAEngine {
public:
    CAEngine();

    ~CAEngine();

    void init();

    void run(World& world);

private:
    void processInput();

    void update(World& world);

    void render(World& world);

    void updateFpsCounter();

    // Engine state
    bool mIsRunning{false};
    bool mStop{true};
    bool mNext{false};
    bool mReset{false};
    float mSpeed{0.99};

    // Frame
    double mPreviousSeconds{0.0};
    double mCurrentSeconds{0.0};
    uint32_t mCurrentFrameCount{0};
    uint32_t mFPS{0};

    std::unique_ptr<Window> mWindow;
    std::unique_ptr<Gui> mGui;
    std::unique_ptr<Camera> mCamera;
    std::unique_ptr<Input> mInput;
    std::unique_ptr<Renderer> mRenderer;

    float mDeltaTime{};
    uint32_t mMsPreviousFrame{0};
};