#include "../include/camera.h"

Camera::Camera() {}
Camera::~Camera() {}

Camera::Camera(float x, float y, float z, float lookX, float lookY, float lookZ, float angH, float angV, float moveSpeed, float rotSpeed)
    : posX(x), posY(y), posZ(z), lookX(lookX), lookY(lookY), lookZ(lookZ), angleH(angH), angleV(angV), movementSpeed(moveSpeed), rotationSpeed(rotSpeed) {}

void Camera::applyView() {
    gluLookAt(this->posX, this->posY, this->posZ,
              this->posX + this->lookX, this->posY + this->lookY, this->posZ + this->lookZ,
              0.0, 1.0, 0.0);
}
