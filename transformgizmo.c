#include "transformgizmo.h"

GizmoArrow tg_create_arrow() {
    GizmoArrow arrow = {0};
    
    Mesh arrowX = GenMeshCube(1.0f, GIZMO_THICKNESS, GIZMO_THICKNESS);
    Mesh arrowY = GenMeshCube(GIZMO_THICKNESS, 1.0f, GIZMO_THICKNESS);
    Mesh arrowZ = GenMeshCube(GIZMO_THICKNESS, GIZMO_THICKNESS, 1.0f);
    
    Material material = LoadMaterialDefault();

    arrow.arrow_x = arrowX;
    arrow.arrow_y = arrowY;
    arrow.arrow_z = arrowZ;

    arrow.mat = material;


    return arrow;
}

float sign(float num) {
    return num > 0 ? 1.0f : -1.0f;
}



void tg_draw(Camera3D camera, Vector3* pos, GizmoArrow* arrow)
{

    tg_draw_arrows(pos,arrow, arrow->selected_axis[0], arrow->selected_axis[1], arrow->selected_axis[2]);
    

    if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        return;
    }


    float camPosDist = Vector3Distance(camera.position, *pos);


    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {

        Ray mouseRay = GetScreenToWorldRay(GetMousePosition(), camera);


        RayCollision hits[3];

        //bounds 
        hits[0] = GetRayCollisionMesh(mouseRay, arrow->arrow_x, MatrixTranslate(pos->x, pos->y, pos->z));
        hits[1] = GetRayCollisionMesh(mouseRay, arrow->arrow_y, MatrixTranslate(pos->x, pos->y, pos->z));
        hits[2] = GetRayCollisionMesh(mouseRay, arrow->arrow_z, MatrixTranslate(pos->x, pos->y, pos->z));


        int axis = -1;
        float dist = 1000;


        for (int i = 0; i < 3; i++)
        {
            arrow->selected_axis[i] = false;

            if(hits[i].hit)
            {
                if(hits[i].distance < dist)
                {
                    dist = hits[i].distance;
                    axis = i;
                }
            }


        }

        if (axis != -1) arrow->selected_axis[axis] = true;

        



    }




    if (arrow->selected_axis[0]) pos->x = pos->x + GetMouseDelta().x * TG_MOUSE_SENSITIVITY * Vector3Distance(camera.position, *pos) * sign(camera.position.z - pos->z);
    if (arrow->selected_axis[1]) pos->y = pos->y - GetMouseDelta().y * TG_MOUSE_SENSITIVITY * Vector3Distance(camera.position, *pos);
    if (arrow->selected_axis[2]) pos->z = pos->z + GetMouseDelta().x * TG_MOUSE_SENSITIVITY * Vector3Distance(camera.position, *pos) * sign(pos->x - camera.position.x);





}


void tg_draw_arrows(Vector3* pos, GizmoArrow* arrow, bool x, bool y, bool z)
{
    
    

    arrow->mat.maps[(int) MATERIAL_MAP_DIFFUSE].color = RED;

    DrawMesh(arrow->arrow_x, arrow->mat, MatrixTranslate(pos->x,pos->y,pos->z));

    arrow->mat.maps[(int) MATERIAL_MAP_DIFFUSE].color = GREEN;

    
    DrawMesh(arrow->arrow_y, arrow->mat, MatrixTranslate(pos->x,pos->y,pos->z));


    arrow->mat.maps[(int) MATERIAL_MAP_DIFFUSE].color = BLUE;

    DrawMesh(arrow->arrow_z, arrow->mat, MatrixTranslate(pos->x,pos->y,pos->z));



}


