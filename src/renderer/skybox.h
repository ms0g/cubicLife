#pragma once

#include <memory>
#include "glm/glm.hpp"

class Shader;
class SkyboxMesh;
class Skybox {
public:
    Skybox();

    ~Skybox();

    void render(const glm::mat4& view, const glm::mat4& projection);

private:
    std::unique_ptr<SkyboxMesh> mMesh;
    std::unique_ptr<Shader> mShader;
};

