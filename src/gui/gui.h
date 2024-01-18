#pragma once

#include <SDL2/SDL.h>


class Gui {
public:
    Gui(SDL_Window* window, SDL_GLContext gl_context);

    ~Gui();

    void updateFpsCounter(float dt);

    void render() const;

private:
    void renderGraphicsInfo() const;

    double m_previousSeconds{0.0};
    double m_currentSeconds{0.0};
    int m_frameCount{0};
    double m_fps{0.0};

};
