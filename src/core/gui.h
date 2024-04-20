#pragma once

#include <SDL.h>

class Gui {
public:
    Gui(SDL_Window* window, SDL_GLContext gl_context);

    ~Gui();

    void setFPS(double fps) { mFPS = fps; }

    void setWorldStateInfo(uint64_t generationCount, uint32_t aliceCellCount) {
        mGenerationCount = generationCount;
        mAliveCellCount = aliceCellCount;
    }

    void render(bool& stop, bool& next, float& speed);

private:
    void renderGraphicsInfo() const;

    void renderWorldState() const;

    void renderControlUI(bool& stop, bool& next, float& speed);

    double mFPS{0.0};
    uint64_t mGenerationCount{0};
    uint32_t mAliveCellCount{0};
};
