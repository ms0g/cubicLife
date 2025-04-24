#pragma once

template<typename T>
class IWindow {
public:
    virtual ~IWindow() = default;

    void init(const char* title = "Test Window",
              const int width = 800,
              const int height = 600,
              const bool fullscreen = false) {
        initImpl(title, width, height, fullscreen);
    }

    T* nativeHandle() const {
        return mWindow;
    }

    void clear(const float r = 0.0f, const float g = 0.0f, const float b = 0.0f, const float a = 0.0f) {
        clearImpl(r, g, b, a);
    }

protected:
    virtual void initImpl(const char* title, int width, int height, bool fullscreen) = 0;

    virtual void clearImpl(float r, float g, float b, float a) = 0;

    virtual void swapBuffer() = 0;

    T* mWindow{nullptr};
};
