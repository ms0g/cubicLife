#pragma once

#include <memory>

class World;
class Skybox;
class Camera;
class Window;
class Input;
class Gui;
class CellularAutomatonEngine {
public:
    CellularAutomatonEngine();

    ~CellularAutomatonEngine();

    void init();

    void run(World& world, Skybox& skybox);

private:
    void processInput();

    void update(World& world);

    void render(World& world, Skybox& skybox);

    bool mIsRunning{false};
    std::unique_ptr<Window> mWindow;
    std::unique_ptr<Gui> mGui;
    std::unique_ptr<Camera> mCamera;
    std::unique_ptr<Input> mInput;

    float mDeltaTime{};
    uint32_t mMillisecsPreviousFrame{0};
};