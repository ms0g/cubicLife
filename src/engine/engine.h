#pragma once

#include <memory>
#include "../camera/camera.h"
#include "../window//window.h"
#include "../shader/shader.h"
#include "../model/model.h"
#include "../input/input.h"
#include "../gui/gui.h"


class Engine {
public:
    Engine() = default;

    [[nodiscard]] inline bool isRunning() const { return m_isRunning; }

    void init(const char* modelName);

    void processInput();

    void update();

    void render();

private:
    bool m_isRunning{false};
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Gui> m_gui;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Input> m_input;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Model> m_model;

    float m_deltaTime{};
    uint32_t m_millisecsPreviousFrame{0};

};