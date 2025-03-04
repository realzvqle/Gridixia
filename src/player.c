#include "player.h"
#include "exheaders/raylib.h"



Camera2D camera;
static bool controlock = false;
void SetupCamera(){
    Vector2 offset = {0, 0};
    Vector2 target = {0, 0};

    camera.offset = offset;
    camera.target = target;
    camera.rotation = 0;
    camera.zoom = 1;
}

void PlayerControl(){
    if(controlock == true) return;
    if(IsKeyDown(KEY_D)) camera.target.x += 400 * GetFrameTime();
    if(IsKeyDown(KEY_A)) camera.target.x -= 400 * GetFrameTime();
    if(IsKeyDown(KEY_W)) camera.target.y -= 400 * GetFrameTime();
    if(IsKeyDown(KEY_S)) camera.target.y += 400 * GetFrameTime();
    // if(IsKeyPressed(KEY_DOWN)) camera.zoom-=0.1;
    // if(IsKeyPressed(KEY_UP)) camera.zoom+=0.1;
}

void LockControls(){
    controlock = true;
}

void UnlockControls(){
    controlock = false;
}