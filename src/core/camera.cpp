#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch) :
        mFront(glm::vec3(0.0f, 0.0f, -1.0f)),
        mMovementSpeed(SPEED),
        mMouseSensitivity(SENSITIVITY),
        mZoom(ZOOM) {
    mPosition = position;
    mWorldUp = up;
    mYaw = yaw;
    mPitch = pitch;

    update();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
        mFront(glm::vec3(0.0f, 0.0f, -1.0f)),
        mMovementSpeed(SPEED),
        mMouseSensitivity(SENSITIVITY),
        mZoom(ZOOM) {
    mPosition = glm::vec3(posX, posY, posZ);
    mWorldUp = glm::vec3(upX, upY, upZ);
    mYaw = yaw;
    mPitch = pitch;

    update();
}

void Camera::update() {
    // calculate the new Front vector
    glm::vec3 _front;
    _front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    _front.y = sin(glm::radians(mPitch));
    _front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(_front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp = glm::normalize(glm::cross(mRight, mFront));
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

float Camera::getZoom() const {
    return mZoom;
}

glm::vec3 Camera::getPosition() const {
    return mPosition;
}

glm::vec3 Camera::getFront() const {
    return mFront;
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = mMovementSpeed * deltaTime;
    if (direction == FORWARD)
        mPosition += mFront * velocity;
    if (direction == BACKWARD)
        mPosition -= mFront * velocity;
    if (direction == LEFT)
        mPosition -= mRight * velocity;
    if (direction == RIGHT)
        mPosition += mRight * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= mMouseSensitivity;
    yoffset *= mMouseSensitivity;

    mYaw += xoffset;
    mPitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (mPitch > 89.0f)
        mPitch = 89.0f;
    if (mPitch < -89.0f)
        mPitch = -89.0f;
}

void Camera::processMouseScroll(float yoffset) {
    mZoom -= (float) yoffset;
    if (mZoom < 1.0f)
        mZoom = 1.0f;
    if (mZoom > 45.0f)
        mZoom = 45.0f;
}





