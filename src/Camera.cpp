#include "../include/Camera.h"

Vec2 Camera::pos(0, 0);
Vec2 Camera::speed(0, 0);
GameObject *Camera::focus;
void Camera::Follow(GameObject *newFocus) {
    Camera::focus = newFocus;
}

void Camera::Unfollow() {
    Camera::focus = nullptr;
}

void Camera::Update(float dt) {
    if (Camera::focus) {

    }
}
