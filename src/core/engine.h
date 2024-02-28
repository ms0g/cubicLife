#pragma once

#include <memory>
#include "camera.h"
#include "window.h"
#include "input.h"
#include "gui.h"

class Terrain;
class Skybox;
class VoxelEngine {
public:
    VoxelEngine() = default;

    void init();

    void run(Terrain& terrain, Skybox& skybox);

private:
    void processInput();

    void update();

    void render(Terrain& terrain, Skybox& skybox);

    bool m_isRunning{false};
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Gui> m_gui;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Input> m_input;

    float m_deltaTime{};
    uint32_t m_millisecsPreviousFrame{0};

};