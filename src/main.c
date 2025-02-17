#include "exheaders/raylib.h"
#include "player.h"
#include "superheader.h"
#include "terraingen/grid.h"
#include "tools.h"


extern Camera2D camera;



int main(){
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "2ND ATTEMPT TO FORGET THE PAST, WE WILL MAKE IT BROTHERS");
    SysSetup();
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
        PlayerControl();
        //GenerateChunk(3);
        RenderGrid();

        EndMode2D();
        SysDrawFPS(10, 10);
        EndDrawing();
    }
    SysClose();
    CloseWindow();
}