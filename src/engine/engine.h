#pragma once

#include <memory>
#include "../camera/camera.h"
#include "../window//window.h"
#include "../input/input.h"
#include "../gui/gui.h"
#include "../world/worldBuilder.h"

class VoxelEngine {
public:
    VoxelEngine() = default;

    void init();

    void run(WorldBuilder& worldBuilder);


private:
    void processInput();

    void update();

    void render(WorldBuilder& worldBuilder);

    bool m_isRunning{false};
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Gui> m_gui;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Input> m_input;

    float m_deltaTime{};
    uint32_t m_millisecsPreviousFrame{0};

};