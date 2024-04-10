#pragma once

#include <SDL2/SDL.h>

class Gui {
public:
    Gui(SDL_Window* window, SDL_GLContext gl_context);

    ~Gui();

    void setFPS(double fps) { mFPS = fps; }

    void render(bool& stop, bool& next, float& speed);

private:
    void renderGraphicsInfo() const;

    void renderControlUI(bool& stop, bool& next, float& speed);

    double mFPS{0.0};
};
