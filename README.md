# Some code snippets for raylib
Useful snippets extending the raylib library. 

# How to use

- Include the raylib library into your project (https://github.com/raysan5/raylib/)
- Clone this repository
- Ready to go!

# Some information
- every code file (and its corresponding header file) is independent from the other code files, so you can delete the ones you don't need
- no other external dependencies other than raylib and raymath

# The snippets: 

## Camera controller
Free moving camera controller. Like in every game engine. 
Use it by creating the controller once and updating it every frame: 

```C
#include "cameracontroller.h"

CameraController cc = cc_init();

//in update loop

cc_update(&cc, GetFrameTime(), GetMouseDelta());

// use the camera
BeginMode3D(cc.camera);
```

## Transform Gizmo
An arrow gizmo you can move around in 3d view. Useful if you have some objects you want to... well, *move*.
Works by creating 3 meshes and using the camera raycast built into raylib for detecting colission (Yes, I know, we can be more efficient by not creating meshes...)
```C
#include "transformgizmo.h"

// create transform gizmo
GizmoArrow arrow = tg_create_arrow();

// creating position and pointer
Vector3 pos = VEC3_ZERO;

Vector3* pos_ptr = &pos;

//in update loop

//draw the gizmo. You'll need a camera (For example by using the camera controller).  
tg_draw(camera, pos_ptr, &arrow);
```


