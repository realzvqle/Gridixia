#include "grid.h"
#include "../tools.h"
#include "../rayguiabs.h"

extern Camera2D camera;

#define WORLDSIZE 100000
BLOCK blocks[WORLDSIZE];
uint64_t blockamount = 0;
static bool init = false;

static float height = 10;
static float spacing = 0.1;

struct BRETURN{
    uint64_t bnum;
    bool shouldincrement;
};

static struct BRETURN GetFreeBlock(){
    for(int i = 0; i < blockamount; i++){
        if(blocks[i].isBroken == true){
            puts("USING PREVIOUS BLOCK NUM");
            struct BRETURN b = {i, false};
            return b;
        }
    }
    //KiUartPrint("H");
    struct BRETURN b = {blockamount, true};
    return b;
}

void CreateBlock(int x, int y, Color color){
    struct BRETURN b = GetFreeBlock();
    if(blockamount + 1 >= WORLDSIZE){
        printf("WORLDSIZE LIMIT REACHED\n");
        return;
    }
    blocks[b.bnum].x = x;//roundf(x / 50.0f) * 50.0f;
    blocks[b.bnum].y = y;//roundf(y / 50.0f) * 50.0f;
    blocks[b.bnum].color = color;
    blocks[b.bnum].isBroken = false;
    printf("Made a block! BNUM is %llu\n", b.bnum);
    if(b.shouldincrement == true) blockamount++;
}


void RenderChunk(int offset) {
    static float prevtime;
    if(init == false){
        prevtime = GetTime();
        blockamount = 0;
        Color color;
        for(int i = 0; i < 300; i++){
            for(int j = 0; j < 300; j++){
                float wave = height*sin(i*spacing) * 30;
                //Color h = {offset * 10, 0, 0, 255};
                if(j < 10) color = DARKGREEN;
                else if(j < 20) color = BROWN;
                else color = GRAY;
                CreateBlock((i+offset) * 30, j * 30 + wave, color);
            }
        }
        init = true;
    }

    for(int i = 0; i < blockamount; i++){
        if(blocks[i].isBroken == true) continue;
        if(fabsf(camera.target.x - blocks[i].x) >= GetScreenWidth() && fabsf(camera.target.y - blocks[i].y) >= GetScreenHeight()) continue;
        DrawRectangle(blocks[i].x, blocks[i].y, 30, 30, blocks[i].color);
        if(fabsf(SysGetMouseX() - blocks[i].x) <= 15 && fabsf(SysGetMouseY() - blocks[i].y) <= 15){
            DrawRectangleLines(blocks[i].x, blocks[i].y, 30, 30, RED);
            if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
                blocks[i].isBroken = true;
                printf("Destroys Block at %d, %d\n",blocks[i].x, blocks[i].y);

            }
            
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if(GetTime() - prevtime >= 0.1){
                int x = roundf(SysGetMouseX() / 30.0f) * 30.0f;
                int y = roundf(SysGetMouseY() / 30.0f) * 30.0f;
                CreateBlock(x, y, GRAY);
                printf("Creates Block at %d, %d\n",x, y);
                prevtime = GetTime();
            }
            
        }
    }
    
    
}

void UiCustomizeTerrain(){
    RayGUIDrawSlider(10, 50, 200, 50, "", "", &height, 0, 40);
    SysDrawText("Height", 210, 50, 20, BLACK);
    RayGUIDrawSlider(10, 120, 200, 50, "", "", &spacing, 0, 2);
    SysDrawText("Spacing", 210, 120, 20, BLACK);

    int clicked = RayGUIDrawButton(10, 200, 100, 50, "Regenerate");
    if(clicked == 1) init = false;
}


