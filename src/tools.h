#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED



#include "superheader.h"

#define MAXMAPHEIGHT 5000
#define MAXMAPWIDTH 5000
#define MINMAPHEIGHT -5000
#define MINMAPWIDTH -5000


void SysSetup();
void SysDrawText(const char* text, float posX, float posY, float size, Color color);
void SysDrawFPS(float posX, float posY);
void SysFollow(float targetx, float targety, float* curx, float* cury, float speed);
void SysRunAway(float targetx, float targety, float* curx, float* cury, float speed);
void SysClose();
float SysGetDistance(float first, float second);
bool SysFollowStatus(float targetx, float targety, float* curx, float* cury, float speed);
float SysGetMouseX();
float SysGetMouseY();
void SysDrawVersion(float posx, float posy, float size);
float SysGetVersion();
Font SysGetFont();
bool SysNPCIsInScreen(float npcx, float npcy);
float SysGetDistanceAll(float x1, float y1, float x2, float y2);
void SysDrawXandY(float posX, float posY, float x, float y);
#endif