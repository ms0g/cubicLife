#pragma once

#include <string>

const std::string SHADER_DIR = "shaders";
const std::string ASSET_DIR = "assets";

// Screen Settings
constexpr float SCR_WIDTH{1600.0f};
constexpr float SCR_HEIGHT{900.0f};
constexpr float ASPECT{SCR_WIDTH / SCR_HEIGHT};

// Camera Settings
constexpr float YAW{-90.0f};
constexpr float PITCH{-30.0f};
constexpr float SPEED{20.0f};
constexpr float SENSITIVITY{0.1f};
constexpr float ZOOM{45.0f};
constexpr float ZNEAR{0.1f};
constexpr float ZFAR{200.0f};
