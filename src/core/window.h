#pragma once

#include <string>
#include <SDL.h>
#include "IWindow.hpp"

class Window : public IWindow<SDL_Window> {
public:
    Window() = default;

    ~Window() override;

    [[nodiscard]] inline SDL_GLContext glContext() const { return mGlContext; };

    void swapBuffer() override;

private:
    void initImpl(const char* title, int width, int height, bool fullscreen) override;

    void clearImpl(float r, float g, float b, float a) override;

    std::string mTitle;
    SDL_GLContext mGlContext{};
};
