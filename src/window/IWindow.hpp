#pragma once

template<typename T>
class IWindow {
public:
    virtual ~IWindow() = default;

    void init(const char* title = "Test Window", int width = 800, int height = 600, bool fullscreen = false) {
        initImpl(title, width, height, fullscreen);
    }

    inline T* nativeHandle() const {
        return m_window;
    }

    void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f) {
        clearImpl(r, g, b, a);
    }


protected:
    virtual void initImpl(const char* title, int width, int height, bool fullscreen) = 0;

    virtual void clearImpl(float r, float g, float b, float a) = 0;

    virtual void swapBuffer() = 0;

    T* m_window;
};