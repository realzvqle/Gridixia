#include "tools.h"
#define RAYGUI_IMPLEMENTATION
#include "exheaders/raygui.h"
#include "rayguiabs.h"



void RayGUIInitialize(){
    GuiSetFont(SysGetFont());
    GuiSetStyle(DEFAULT, TEXT_SIZE, 15); 
}

int RayGUIDrawButton(int x, int y, int sizeX, int sizeY, const char* text){
    Rectangle rec = {x, y, sizeX, sizeY};
    return GuiButton(rec, text);
}

int RayGUIDrawTextBox(int x, int y, int sizeX, int sizeY, char* text, int textSize, bool editMode){
    Rectangle rec = {x, y, sizeX, sizeY};
    return GuiTextBox(rec, text, textSize, editMode);
}

int RayGUIDrawSlider(int x, int y, int sizeX, int sizeY, char* textleft, char* textright, float* value, float min, float max){
    Rectangle rec = {x, y, sizeX, sizeY};
    return GuiSlider(rec, textleft, textright, value, min, max);
}

