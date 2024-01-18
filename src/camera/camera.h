#pragma once

#include "glm/glm.hpp"

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

class Camera {
public:
    explicit Camera(const glm::vec3& position = glm::vec3{0.0f, 0.0f, 0.0f},
                    const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    glm::mat4 getViewMatrix();

    [[nodiscard]] float getZoom() const;

    [[nodiscard]] const glm::vec3& getPosition() const;

    [[nodiscard]] const glm::vec3& getFront() const;

    void processKeyboard(CameraMovement direction, float deltaTime);

    void processMouseMovement(float xoffset, float yoffset);

    void processMouseScroll(float yoffset);

private:
    void updateCameraVectors();

    // camera Attributes
    glm::vec3 m_position{};
    glm::vec3 m_front;
    glm::vec3 m_up{};
    glm::vec3 m_right{};
    glm::vec3 m_worldUp{};
    // euler Angles
    float m_yaw;
    float m_pitch;
    // camera options
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;

    static constexpr float YAW{-90.0f};
    static constexpr float PITCH{0.0f};
    static constexpr float SPEED{2.5f};
    static constexpr float SENSITIVITY{0.1f};
    static constexpr float ZOOM{45.0f};


};
