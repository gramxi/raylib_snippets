
#include "cameracontroller.h"



CameraController cc_init() {

    CameraController cc = {0};

    cc.camera = (Camera3D) {0};

    cc.camera.position = (Vector3) {0.0f, 1.0f, 0.0f};
    cc.camera.target = (Vector3) {1.0f, 1.0f, 0.0f};
    cc.camera.up = (Vector3) {0.0f, 1.0f, 0.0f};
    cc.camera.fovy = 60.0f;
    cc.camera.projection = CAMERA_PERSPECTIVE;


    cc.totalAngleX = 0.0f;
    cc.totalAngleY = 0.0f;

    cc.movementEnabled = true;

    cc.currentPos = (Vector3) {0.0f, 1.0f, 0.0f};
    cc.target = (Vector3) {1.0f, 0.0f, 0.0f};

    return cc;

}

void cc_update(CameraController* cc, float dt, Vector2 mouseDelta)
{

    float camspeed = CAMERA_SPEED;


    float deltaTime = dt;


    if (cc->movementEnabled)
    {
        cc->totalAngleX += mouseDelta.x * MOUSE_SENSIBILITY;
        cc->totalAngleY += mouseDelta.y * MOUSE_SENSIBILITY;
    }



    cc->totalAngleY = Clamp(cc->totalAngleY, 60, 130);

    if (cc->movementEnabled)
    {
        cc->target =  (Vector3){
            cosf(cc->totalAngleX * DEG2RAD) * sinf(cc->totalAngleY * DEG2RAD),
            cosf(cc->totalAngleY * DEG2RAD),
            sinf(cc->totalAngleX * DEG2RAD) * sinf(cc->totalAngleY * DEG2RAD),
        };

    }


    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        camspeed += 4.0f;
    }



    if (IsKeyDown(KEY_W))
    {

        cc->currentPos = Vector3Add(cc->currentPos, Vector3Scale(cc->target , deltaTime * camspeed));
        


    }
    if (IsKeyDown(KEY_S))
    {

        cc->currentPos = Vector3Add(cc->currentPos, Vector3Scale(cc->target , -deltaTime * camspeed));
        

    }
    if (IsKeyDown(KEY_D))
    {

        Vector3 offset = Vector3Scale(Vector3CrossProduct(cc->target, (Vector3) {0.0f, 1.0f, 0.0f}), deltaTime * camspeed);

        cc->currentPos = Vector3Add(cc->currentPos, offset);

    }
    if (IsKeyDown(KEY_A))
    {

        Vector3 offset = Vector3Scale(Vector3CrossProduct(cc->target, (Vector3) {0.0f, 1.0f, 0.0f}), deltaTime * camspeed);

        cc->currentPos = Vector3Subtract(cc->currentPos, offset);

    }

    if (IsKeyDown(KEY_Q))
    {
        Vector3 offset = Vector3Scale((Vector3) {0.0f, 1.0f, 0.0f}, deltaTime * camspeed);


        cc->currentPos = Vector3Subtract(cc->currentPos , offset);

    }
    if (IsKeyDown(KEY_E))
    {
        Vector3 offset = Vector3Scale((Vector3) {0.0f, 1.0f, 0.0f}, deltaTime * camspeed);


        cc->currentPos = Vector3Add(cc->currentPos , offset);
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        cc->movementEnabled = true;
    }
    else
    {
        cc->movementEnabled = false;
    }

    cc->camera.position = cc->currentPos;
    cc->camera.target = Vector3Add(cc->currentPos, cc->target);
}
