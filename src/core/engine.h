#pragma once

#include <memory>

class Terrain;
class Skybox;
class Camera;
class Window;
class Input;
class Gui;
class VoxelEngine {
public:
    VoxelEngine();

    ~VoxelEngine();

    void init();

    void run(Terrain& terrain, Skybox& skybox);

private:
    void processInput();

    void update();

    void render(Terrain& terrain, Skybox& skybox);

    bool mIsRunning{false};
    std::unique_ptr<Window> mWindow;
    std::unique_ptr<Gui> mGui;
    std::unique_ptr<Camera> mCamera;
    std::unique_ptr<Input> mInput;

    float mDeltaTime{};
    uint32_t mMillisecsPreviousFrame{0};

};