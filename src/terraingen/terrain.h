#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED






#include "../superheader.h"

#define BLOCKTYPEAMOUNT 5

typedef enum _BLOCKTYPE {
    Grass,
    Dirt,
    Stone,
    Brick,
    Unknown
} BLOCKTYPE;

typedef struct _BLOCK {
    int x;
    int y;
    Color color;
    Rectangle texture;
    BLOCKTYPE type;
    bool isBroken;
} BLOCK;




void CreateBlock(int x, int y, BLOCKTYPE type);
void RenderChunk(int offset);
void UiCustomizeTerrain();


#endif