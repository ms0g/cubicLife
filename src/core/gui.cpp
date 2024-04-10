#include "gui.h"
#include <string>
#include "glad/glad.h"
#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/imgui_impl_sdl.h"
#include "../../libs/imgui/imgui_impl_opengl3.h"
#include "../../libs/imgui/imgui_internal.h"

Gui::Gui(SDL_Window* window, SDL_GLContext gl_context) {
    // Initialize the ImGui context
    const char* glsl_version = "#version 410";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

Gui::~Gui() {
    // Clean up ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Gui::render(bool& stop, bool& next, float& speed) {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

//    bool show_demo_window = true;
//    ImGui::ShowDemoWindow(&show_demo_window);

    renderGraphicsInfo();
    renderWorldInfo();
    renderControlUI(stop, next, speed);

    //Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::renderGraphicsInfo() const {
    if (ImGui::Begin("Graphics")) {
        ImGui::Text("%s FPS", std::to_string(mFPS).c_str());
        ImGui::Text("OpenGL version: %s", glGetString(GL_VERSION));
        ImGui::Text("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
        ImGui::Text("OpenGL Driver Vendor: %s", glGetString(GL_VENDOR));
        ImGui::Text("OpenGL Renderer: %s", glGetString(GL_RENDERER));
    }
    ImGui::End();
}

void Gui::renderWorldInfo() const {
    if (ImGui::Begin("Info")) {
        ImGui::Text("%sth Generation", std::to_string(mGenerationCount).c_str());
        ImGui::Text("%s Alive Cell", std::to_string(mAliveCellCount).c_str());
    }
    ImGui::End();
}

void Gui::renderControlUI(bool& stop, bool& next, float& speed) {
    static float _speed = 0.98f;

    if (ImGui::Begin("Controls")) {
        if (ImGui::Button("Start")) {
            stop = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop")) {
            stop = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Next")) {
            next = true;
        }
        if (ImGui::SliderFloat("Speed", &_speed, 0.01, 0.98)) {
            speed = (float)0.99 - _speed;
        }
    }
    ImGui::End();
}
