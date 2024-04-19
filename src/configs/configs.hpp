#pragma once

#include <string>

#ifndef DEBUG
#define DEBUG
#endif

const std::string SHADER_DIR = "shaders";
const std::string ASSET_DIR = "assets";

constexpr unsigned int SCR_WIDTH = 1600;
constexpr unsigned int SCR_HEIGHT = 900;
constexpr float ASPECT = (float) SCR_WIDTH / (float) SCR_HEIGHT;

// Camera Settings
constexpr float YAW{-90.0f};
constexpr float PITCH{-30.0f};
constexpr float SPEED{20.0f};
constexpr float SENSITIVITY{0.1f};
constexpr float ZOOM{45.0f};
constexpr float ZNEAR{0.1f};
constexpr float ZFAR{200.0f};
