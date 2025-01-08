#include "window.h"
#include <stdexcept>

Window::~Window() {
    SDL_GL_DeleteContext(mGlContext);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Window::initImpl(const char* title, int width, int height, bool fullscreen) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("Failed to initialize SDL_VIDEO");
    }

    mTitle = title;

    int flags = SDL_WINDOW_OPENGL;
    if (fullscreen)
        flags |= SDL_WINDOW_FULLSCREEN;
    else
        flags |= SDL_WINDOW_RESIZABLE;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    mWindow = SDL_CreateWindow(
            mTitle.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            displayMode.w,
            displayMode.h,
            flags);

    if (!mWindow) {
        throw std::runtime_error("Failed to create SDL Window");
    }

    SDL_SetWindowFullscreen(mWindow, flags);

    mGlContext = SDL_GL_CreateContext(mWindow);
}

void Window::clearImpl(float r, float g, float b, float a) {
}

void Window::swapBuffer() {
    SDL_GL_SwapWindow(mWindow);
}

