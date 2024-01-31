#pragma once

#include <memory>
#include "../camera/camera.h"
#include "../window//window.h"
#include "../shader/shader.h"
#include "../mesh/mesh.h"
#include "../input/input.h"
#include "../gui/gui.h"

class VoxelEngine {
public:
    VoxelEngine() = default;

    void init();

    void run();


private:
    void processInput();

    void update();

    void render();

    bool m_isRunning{false};
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Gui> m_gui;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Input> m_input;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Mesh> m_mesh;

    float m_deltaTime{};
    uint32_t m_millisecsPreviousFrame{0};

};