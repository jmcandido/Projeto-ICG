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

    void updateLookDirection();

   float get_angle_hor();
   float get_angle_ver();
   float get_posX();
   float get_posY();
   float get_posZ();


   void set_angle_hor(float);
   void set_angle_ver(float);
   void set_posX(float posX);
   void set_posY(float posY);
   void set_posZ(float posZ);
};

#endif // CAMERA_H