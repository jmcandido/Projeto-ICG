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


// void Camera::updateLookDirection() {
//     float ch = std::cos(angleH);
//     float sh = std::sin(angleH);
//     float cv = std::cos(angleV);
//     float sv = std::sin(angleV);

//     lookX = cv * ch;
//     lookY = sv;
//     lookZ = cv * sh;
// }


void Camera::updateLookDirection()
{
    this->lookX = sin(this->angleH) * cos(this->angleV);
    this->lookY = sin(this->angleV);
    this->lookZ = -cos(this->angleH) * cos(this->angleV);
}

void Camera::moveForward() {
    posX += lookX * movementSpeed;
    posY += lookY * movementSpeed;
    posZ += lookZ * movementSpeed;
}

void Camera::moveBackward() {
    posX -= lookX * movementSpeed;
    posY -= lookY * movementSpeed;
    posZ -= lookZ * movementSpeed;
}
void Camera::moveLeft()
{
    this->posX += this->lookZ * this->movementSpeed;
    this->posZ -= this->lookX * this->movementSpeed;
}

void Camera::moveRight()
{
    this->posX -= this->lookZ * this->movementSpeed;
    this->posZ += this->lookX * this->movementSpeed;
}

void Camera::moveUp()
{
    this->posY += this->movementSpeed;
}

void Camera::moveDown()
{
    this->posY -= this->movementSpeed;
}


float Camera::get_angle_hor(){
    return this->angleH;
}

float Camera::get_angle_ver(){
    return this->angleV;
}

float Camera::get_posX(){
    return this->posX;
}

float Camera::get_posY(){
    return this->posY;
}

float Camera::get_posZ(){
    return this->posZ;
}

float Camera::get_movementSpeed()
{
    return this->movementSpeed;
}

float Camera::get_rotationSpeed()
{
    return this->rotationSpeed;
}

void Camera::set_angle_hor(float angleH)
{
    this->angleH = angleH;
}

void Camera::set_posX(float posX)
{
    this->posX = posX;
}

void Camera::set_posY(float posY)
{
    this->posY = posY;
}

void Camera::set_posZ(float posZ)
{
    this->posZ = posZ;
}

void Camera::set_angle_ver(float angleV)
{   
    if (angleV < -1.5) 
     this->angleV = -1.5;     //garantir os limites de ângulação vertical
    else if (angleV > 1.5)
    this->angleV = 1.5;
    else this->angleV = angleV;
}

void Camera::set_movementSpeed(float movementSpeed)
{
    this->movementSpeed = movementSpeed;
}
