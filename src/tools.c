#include "tools.h"
#include "exheaders/raylib.h"
#include "player.h"
#include "rayguiabs.h"

static Font font;
Texture2D atlas;
extern Camera2D camera;


void SysSetup(){
    SetupCamera();
    font = LoadFontEx("resources/fonts/PixelifySans/PixelifySans-Regular.ttf", 200, NULL, 0);
    atlas = LoadTexture("resources/textures/atlas.png");
    RayGUIInitialize();
}

Font SysGetFont(){
    return font;
}



void SysClose(){
    UnloadFont(font);
    UnloadTexture(atlas);
}

void SysDrawText(const char* text, float posX, float posY, float size, Color color){
    Vector2 vec = {posX, posY};
    DrawTextEx(font, text, vec, size, 2, color);
}

void SysDrawFPS(float posX, float posY){
    char buffer[512];
    sprintf(buffer, "%d FPS", GetFPS());
    SysDrawText(buffer, posX, posY, 25,  BLACK);
}

void SysDrawXandY(float posX, float posY, float x, float y){
    char buffer[512];
    sprintf(buffer, "X: %0.2f\nY:%0.2f\n",x, y);;
    SysDrawText(buffer, posX, posY, 25,  PURPLE);
}

void SysFollow(float targetx, float targety, float* curx, float* cury, float speed){
    if(*curx <= MINMAPWIDTH) *curx = MINMAPWIDTH;
    if(*cury <= MINMAPHEIGHT) *cury = MINMAPHEIGHT;
    if(*curx >= MAXMAPWIDTH) *curx = MAXMAPWIDTH;
    if(*cury >= MAXMAPHEIGHT) *cury = MAXMAPHEIGHT;
    if (targetx < *curx) {
        *curx -= speed * GetFrameTime();
    } else if (targetx > *curx) {
        *curx += speed * GetFrameTime();
    }
    if (targety < *cury) {
        *cury -= speed * GetFrameTime();
    } else if (targety > *cury) {
        *cury += speed * GetFrameTime();
    }
}

bool SysFollowStatus(float targetx, float targety, float* curx, float* cury, float speed){
    static bool finished = false;

    if(*curx <= MINMAPWIDTH) *curx = MINMAPWIDTH;
    if(*cury <= MINMAPHEIGHT) *cury = MINMAPHEIGHT;
    if(*curx >= MAXMAPWIDTH) *curx = MAXMAPWIDTH;
    if(*cury >= MAXMAPHEIGHT) *cury = MAXMAPHEIGHT;
    
    if (targetx < *curx) {
        *curx -= speed * GetFrameTime();
    } else if (targetx > *curx) {
        *curx += speed * GetFrameTime();
    }
    if (targety < *cury) {
        *cury -= speed * GetFrameTime();
    } else if (targety > *cury) {
        *cury += speed * GetFrameTime();
    }
    if(SysGetDistance(targetx, *curx) <= 30 && SysGetDistance(targety, *cury) <= 30) return true;
    else return false;
}
void SysRunAway(float targetx, float targety, float* curx, float* cury, float speed){
    if(*curx <= MINMAPWIDTH) *curx = MINMAPWIDTH;
    if(*cury <= MINMAPHEIGHT) *cury = MINMAPHEIGHT;
    if(*curx >= MAXMAPWIDTH) *curx = MAXMAPWIDTH;
    if(*cury >= MAXMAPHEIGHT) *cury = MAXMAPHEIGHT;
    if (targetx > *curx) {
        *curx -= speed * GetFrameTime();
    } else if (targetx < *curx) {
        *curx += speed * GetFrameTime();
    }
    if (targety > *cury) {
        *cury -= speed * GetFrameTime();
    } else if (targety < *cury) {
        *cury += speed * GetFrameTime();
    }
}

float SysGetDistance(float first, float second){
    return fabsf(first - second);
}



float SysGetMouseX(){
    Vector2 mouse = {GetMouseX(), GetMouseY()};
    Vector2 mousepos = GetScreenToWorld2D(mouse, camera);
    return mousepos.x;
}

float SysGetMouseY(){
    Vector2 mouse = {GetMouseX(), GetMouseY()};
    Vector2 mousepos = GetScreenToWorld2D(mouse, camera);
    return mousepos.y;
}
float SysGetVersion(){
    return 0.0f;
}

void SysDrawVersion(float posx, float posy, float size){
    char buffer[512];
    sprintf(buffer, "Version %0.1f\nBuilt On %s at %s", SysGetVersion(), __DATE__, __TIME__);
    SysDrawText(buffer, posx, posy, size, GOLD);
}

float SysGetDistanceAll(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}