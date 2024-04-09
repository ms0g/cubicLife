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

    double mPreviousSeconds{0.0};
    double mCurrentSeconds{0.0};
    int mFrameCount{0};
    double mFps{0.0};
};
