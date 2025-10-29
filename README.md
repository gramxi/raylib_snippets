# Some code snippets for raylib
Useful snippets extending the raylib library. 

# How to use

- Include the raylib library into your project (https://github.com/raysan5/raylib/)
- Clone this repository
- Ready to go!

# Some information
- every code file (and its corresponding header file) is independent from the other code files, so you can delete the ones you don't need
- special external dependencies are listed for each file below

# The snippets: 

## Camera controller
Free moving camera controller. Like in every game engine. Move with WASD (forward, backward and sides) and QE (up and down). Look around by clicking the right muse button. 

IMPORTANT: Up-axis is Y

DEPENDENCIES: raylib, raymath

Use it by creating the controller once and updating it every frame. 

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
Works by creating 3 meshes and using the camera raycast built into raylib for detecting collision (Yes, I know, we can be more efficient by not creating meshes...)

DEPENDENCIES: raylib, raymath

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

## MicroUI to raylib (mu2rl)

A simple port of the MicroUI Library (https://github.com/rxi/microui/) to be used in raylib. 

Use it by including the microui (.c/.h) files into your project (and of course the mu2rl files too :). 
Initialize the library as normal and then call mu_handle_input() before and mu_draw_shapes() after draw step. Use the text_width and text_height als delegates for mu_Context.text_width/text_height.

IMPORTANT: Work in progress. Text height is for example always 20.

DEPENDENCIES: raylib, microui

```C
#include "mu2rl.h"

// init mui lib (nothing special here)
mu_Context* ctx = (mu_Context*)malloc(sizeof(mu_Context));

mu_init(ctx);

// assign text measuring methods
ctx->text_width = text_width;
ctx->text_height = text_height;

// in update loop 

mu_handle_input(ctx);

//draw something AWESOME
mu_begin(ctx);

    // [...]

mu_end(ctx);

//draw the gui onto screen (ensure to wrap this into Begin/EndDrawing() functions by raylib ;)

mu_draw_shapes(ctx); 

```