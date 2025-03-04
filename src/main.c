#include "exheaders/raylib.h"
#include "player.h"
#include "terraingen/terrain.h"
#include "tools.h"


extern Camera2D camera;



int main(){
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "2ND ATTEMPT TO FORGET THE PAST, WE WILL MAKE IT BROTHERS");
    SysSetup();
    
    float value = 0;
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode2D(camera);
        PlayerControl();
        RenderChunk(0);
        EndMode2D();
        UiCustomizeTerrain();
        EndDrawing();
    }
    SysClose();
    CloseWindow();
}