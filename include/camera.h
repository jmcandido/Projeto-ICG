#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <GL/glu.h>

class Camera {
private:
    float posX, posY, posZ;  
    float lookX, lookY, lookZ; 
    float angleH, angleV;  
    float movementSpeed, rotationSpeed; 

public:
    Camera();
    ~Camera();

    Camera(float x, float y, float z, float lookX, float lookY, float lookZ, float angH, float angV, float moveSpeed, float rotSpeed);

    void applyView();
};

#endif // CAMERA_H