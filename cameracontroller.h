#include "raylib.h"
#include "raymath.h"

#ifndef CAMERA_CONTROLLER
#define CAMERA_CONTROLLER

#define MOUSE_SENSIBILITY 0.2f;
#define CAMERA_SPEED 2.0f;

struct CameraController
{
    float totalAngleX;
    float totalAngleY;

    bool movementEnabled;

    Camera3D camera;

    Vector3 currentPos;
    Vector3 target;

};

typedef struct CameraController CameraController;

CameraController cc_init();

void cc_update(CameraController* cc, float dt, Vector2 mouseDelta);



#endif