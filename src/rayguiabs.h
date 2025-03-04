#ifndef RAYGUIABS_H_INCLUDED
#define RAYGUIABS_H_INCLUDED








#include "superheader.h"


void RayGUIInitialize();
int RayGUIDrawButton(int x, int y, int sizeX, int sizeY, const char* text);
int RayGUIDrawSlider(int x, int y, int sizeX, int sizeY, char* textleft, char* textright, float* value, float min, float max);





#endif