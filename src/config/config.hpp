#pragma once

#include <string>

#ifndef DEBUG
#define DEBUG
#endif

const std::string SHADER_DIR = "shaders";
const std::string ASSET_DIR = "assets";

// Screen Settings
#define SCR_WIDTH 1600
#define SCR_HEIGHT 900
#define ASPECT (float) SCR_WIDTH / (float) SCR_HEIGHT

// Camera Settings
#define YAW            (-90.0f)
#define PITCH          (-30.0f)
#define SPEED           20.0f
#define SENSITIVITY     0.1f
#define ZOOM            45.0f
#define ZNEAR           0.1f
#define ZFAR            200.0f
