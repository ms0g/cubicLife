#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch) :
        m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
        m_movementSpeed(SPEED),
        m_mouseSensitivity(SENSITIVITY),
        m_zoom(ZOOM) {
    this->m_position = position;
    this->m_worldUp = up;
    this->m_yaw = yaw;
    this->m_pitch = pitch;

    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
        m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
        m_movementSpeed(SPEED),
        m_mouseSensitivity(SENSITIVITY),
        m_zoom(ZOOM) {
    this->m_position = glm::vec3(posX, posY, posZ);
    this->m_worldUp = glm::vec3(upX, upY, upZ);
    this->m_yaw = yaw;
    this->m_pitch = pitch;

    updateCameraVectors();

}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

float Camera::getZoom() const {
    return m_zoom;
}

const glm::vec3& Camera::getPosition() const {
    return m_position;
}

const glm::vec3& Camera::getFront() const {
    return m_front;
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = m_movementSpeed * deltaTime;
    if (direction == FORWARD)
        m_position += m_front * velocity;
    if (direction == BACKWARD)
        m_position -= m_front * velocity;
    if (direction == LEFT)
        m_position -= m_right * velocity;
    if (direction == RIGHT)
        m_position += m_right * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}


void Camera::processMouseScroll(float yoffset) {
    m_zoom -= (float) yoffset;
    if (m_zoom < 1.0f)
        m_zoom = 1.0f;
    if (m_zoom > 45.0f)
        m_zoom = 45.0f;
}


void Camera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 _front;
    _front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    _front.y = sin(glm::radians(m_pitch));
    _front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(_front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}



