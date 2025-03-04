#include "exheaders/raylib.h"
#include "player.h"
#include "rayguiabs.h"
#include "superheader.h"
#include "terraingen/grid.h"
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
        //GenerateChunk(3);
        RenderChunk(0);
        RenderChunk(90);
        EndMode2D();
        SysDrawFPS(10, 10);
        UiCustomizeTerrain();
        EndDrawing();
    }
    SysClose();
    CloseWindow();
}