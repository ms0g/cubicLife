#pragma once

#include <SDL.h>

class Gui {
public:
    Gui(SDL_Window* window, SDL_GLContext gl_context);

    ~Gui();

    void setFPS(const double fps) { mFPS = fps; }

    void setWorldStateInfo(const uint64_t generationCount, const uint32_t aliceCellCount) {
        mGenerationCount = generationCount;
        mAliveCellCount = aliceCellCount;
    }

    void render(bool& stop, bool& next, bool& reset, float& speed);

private:
    void renderWorldState() const;

    void renderControlUI(bool& stop, bool& next, bool& reset, float& speed);

    double mFPS{0.0};
    uint64_t mGenerationCount{0};
    uint32_t mAliveCellCount{0};
};
