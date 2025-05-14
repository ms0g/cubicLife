#ifndef CAE_RENDERER_H
#define CAE_RENDERER_H

#include <unordered_map>
#include "shader.h"
#include "skybox.h"
#include "window.h"
#include "gui.h"
#include "mesh/cellMesh.h"

class Cell;
class Window;
class Gui;
class Renderer {
public:
    Renderer();

    std::unique_ptr<Window>& window() {
        return mWindow;
    }

    std::unique_ptr<Gui>& gui() {
        return mGui;
    }

    void render(const glm::mat4& view,
                const glm::mat4& projection,
                const std::unordered_map<std::string, Cell>& aliveCells) const;

    void clear(float r, float g, float b, float a);

private:
    std::unique_ptr<Window> mWindow;
    std::unique_ptr<Gui> mGui;
    std::unique_ptr<Shader> cellShader;
    std::unique_ptr<CellMesh> cellMesh;
    std::unique_ptr<Skybox> skybox;
};

#endif //CAE_RENDERER_H
