#include "terrain.h"
#include "../tools.h"
#include "../rayguiabs.h"
#include <synchapi.h>
#include <winbase.h>
#include "../player.h"
extern Camera2D camera;

#define CHUNKSIZE 100000
BLOCK blocks[CHUNKSIZE];
uint64_t blockamount = 0;
static bool init = false;
static bool ThreadFinished = false;
static float height = 10;
static float spacing = 0.1;
static bool ThreadCreated = false;

extern Texture2D atlas;
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

static Rectangle BlocktypeToTexture(BLOCKTYPE type){
    switch(type){
        case Dirt:{
            Rectangle rec = {0, 0, 30, 30};
            return rec;
        }
        case Grass:{
            Rectangle rec = {30, 0, 30, 30};
            return rec;
        }    
        case Stone:{
            Rectangle rec = {60, 0, 30, 30};
            return rec;
        }
        case Brick:{
            Rectangle rec = {120, 0, 30, 30};
            return rec;      
        }
        default:{
            Rectangle rec = {90, 0, 30, 30};
            return rec;
        }
    }
}

void CreateBlock(int x, int y, BLOCKTYPE type){
    //Color color;
    struct BRETURN b = GetFreeBlock();
    if(blockamount + 1 >= CHUNKSIZE){
        printf("WORLDSIZE LIMIT REACHED\n");
        return;
    }
    blocks[b.bnum].type = type;
    blocks[b.bnum].x = x;//roundf(x / 50.0f) * 50.0f;
    blocks[b.bnum].y = y;//roundf(y / 50.0f) * 50.0f;
    blocks[b.bnum].texture = BlocktypeToTexture(type);
    blocks[b.bnum].isBroken = false;
    // printf("Made a block! BNUM is %llu\n", b.bnum);
    if(b.shouldincrement == true) blockamount++;
}

DWORD GenerateTerrain(LPVOID args){
    BLOCKTYPE type;
    for(int i = 0; i < 300; i++){
        for(int j = 0; j < 300; j++){
            float wave = height*sin(i*spacing) * 30;
            if(j < 10) type = Grass;
            else if(j < 20) type = Dirt;
            else type = Stone;
            CreateBlock((i) * 30, j * 30 + wave, type);
        }
    }
    ThreadFinished = true;
    return 0;
}

void RenderChunk(int offset) {
    static float prevtime;
    static HANDLE hThread;
    if(init == false){
        if(ThreadCreated == false){
            ThreadFinished = false;
            prevtime = GetTime();
            hThread = CreateThread(NULL, 0, GenerateTerrain, NULL, 0, NULL);
            ThreadCreated = true;
        }
       
        //GenerateTerrain(NULL);
        if(ThreadFinished == false){
            LockControls();
            ClearBackground(DARKBROWN);
            return;
        }
        else {
            UnlockControls();
            init = true;
            CloseHandle(hThread);
        }
    }

    for(int i = 0; i < blockamount; i++){
        if(fabsf(camera.target.x - blocks[i].x) >= GetScreenWidth()) continue;
        if(fabsf(camera.target.y - blocks[i].y) >= GetScreenHeight()) continue;
        if(blocks[i].isBroken == true) continue;
        Vector2 pos = {blocks[i].x, blocks[i].y};
        DrawTextureRec(atlas, blocks[i].texture, pos, WHITE);
        if(fabsf(SysGetMouseX() - blocks[i].x) <= 15 && fabsf(SysGetMouseY() - blocks[i].y) <= 15){
            DrawRectangleLines(blocks[i].x, blocks[i].y, 30, 30, RED);
            if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
                blocks[i].isBroken = true;
                printf("Destroys Block at %d, %d\n",blocks[i].x, blocks[i].y);
            }
            
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if(GetMouseX() <= 400 && GetMouseY() <= 400) continue;
            if(GetTime() - prevtime >= 0.1){
                int x = roundf(SysGetMouseX() / 30.0f) * 30.0f;
                int y = roundf(SysGetMouseY() / 30.0f) * 30.0f;
                CreateBlock(x, y, Brick);
                printf("Creates Block at %d, %d\n",x, y);
                prevtime = GetTime();
            }
            
        }
    }
    
    
}

void UiCustomizeTerrain(){
    
    if(ThreadFinished == false){
        const char* text = "Generating Terrain";
        SysDrawText(text, ((float)GetScreenWidth() - MeasureTextEx(SysGetFont(), text, 30, 2).x) / 2, 
        (float)GetScreenHeight() / 2, 30, WHITE);
        char buffer[512];
        sprintf(buffer, "Placing Block %llu...", blockamount);
        SysDrawText(buffer, ((float)GetScreenWidth() - MeasureTextEx(SysGetFont(), buffer, 30, 2).x) / 2, 
        ((float)GetScreenHeight() + 60) / 2, 30, WHITE);
        return;
    }
    Color bcolor = {100, 0, 0, 100};
    DrawRectangle(0, 0, 400, 400,bcolor);
    SysDrawFPS(10, 10);
    RayGUIDrawSlider(10, 50, 200, 50, "", "", &height, 0, 40);
    SysDrawText("Height", 210, 50, 20, BLACK);
    RayGUIDrawSlider(10, 120, 200, 50, "", "", &spacing, 0, 2);
    SysDrawText("Spacing", 210, 120, 20, BLACK);

    int clicked = RayGUIDrawButton(10, 200, 100, 50, "Regenerate");
    if(clicked == 1){
        blockamount = 0;
        ThreadCreated = false;
        init = false;
    } 
}


