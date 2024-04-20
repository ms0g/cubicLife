#include "input.h"
#include <SDL.h>
#include "camera.h"
#include "../../libs/imgui/imgui_impl_sdl.h"

void Input::process(Camera& camera, SDL_Window* window, float dt, bool& isRunning) {
    SDL_Event event;

    SDL_PollEvent(&event);
#ifdef DEBUG
    ImGui_ImplSDL2_ProcessEvent(&event);
#endif

    if (event.type == SDL_QUIT)
        isRunning = false;
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
        event.window.windowID == SDL_GetWindowID(window))
        isRunning = false;

    processKeyboard(camera, dt, isRunning);
    processMouse(camera);

}

void Input::processKeyboard(Camera& camera, float dt, bool& isRunning) {
    auto* keystate = SDL_GetKeyboardState(nullptr);

    if (keystate[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    } else if (keystate[SDL_SCANCODE_W]) {
        camera.processKeyboard(FORWARD, dt);
    } else if (keystate[SDL_SCANCODE_S]) {
        camera.processKeyboard(BACKWARD, dt);
    } else if (keystate[SDL_SCANCODE_A]) {
        camera.processKeyboard(LEFT, dt);
    } else if (keystate[SDL_SCANCODE_D]) {
        camera.processKeyboard(RIGHT, dt);
    }
}

void Input::processMouse(Camera& camera) {
    int x, y;
    bool isClickedRight, isClickedLeft;

    const int buttons = SDL_GetMouseState(&x, &y);
    isClickedLeft = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    isClickedRight = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
#ifdef DEBUG
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(x, y);
    io.MouseDown[0] = isClickedLeft;
    io.MouseDown[1] = isClickedRight;
#endif

    auto xpos = static_cast<float>(x);
    auto ypos = static_cast<float>(y);

    if (mFirstMouse) {
        mLastX = xpos;
        mLastY = ypos;
        mFirstMouse = false;
    }

    float xoffset = xpos - mLastX;
    float yoffset = mLastY - ypos; // reversed since y-coordinates go from bottom to top

    mLastX = xpos;
    mLastY = ypos;

    if (isClickedRight)
        camera.processMouseMovement(xoffset, yoffset);

}
