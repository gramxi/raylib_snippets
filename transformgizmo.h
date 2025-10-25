#include "raylib.h"
#include "raymath.h"

#ifndef TRANSFORM_GIZMO
#define TRANSFORM_GIZMO

#define GIZMO_THICKNESS 0.1f


#define TG_MOUSE_SENSITIVITY 0.001f


typedef struct GizmoArrow {
    Mesh arrow_x;
    Mesh arrow_y;
    Mesh arrow_z;
    Material mat;
    bool selected_axis[3];
} GizmoArrow;


GizmoArrow tg_create_arrow();

void tg_draw(Camera3D camera, Vector3* pos, GizmoArrow* arrow);

void tg_draw_arrows(Vector3* pos, GizmoArrow* arrow, bool x, bool y, bool z);

#endif