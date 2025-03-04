#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED






#include "../superheader.h"

typedef struct _BLOCK {
    int x;
    int y;
    Color color;
    bool isBroken;
} BLOCK;




void CreateBlock(int x, int y, Color color);
void RenderChunk(int offset);
void UiCustomizeTerrain();


#endif