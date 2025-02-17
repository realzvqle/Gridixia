#include "grid.h"



uint8_t grid[ROWS * CELLSIZE] ;


void RenderGrid() {
    static bool init = false;
    static int size = sizeof(grid) / sizeof(grid[0]);

    if(!init){
        for(int i = 0; i < size; i++){
            grid[i] = 1;
        }
        init = true;
    }
    int startY = (GetScreenHeight() / 2) - (ROWS * CELLSIZE) / 2;
    int startX = (GetScreenWidth() / 2) - (COLUMNS * CELLSIZE) / 2;  

    for (int i = 1; i < size; i++) {
        int x = (i - 1) % COLUMNS;
        int y = (i - 1) / COLUMNS;
        switch(grid[i]){
            case 1:
                DrawRectangle(startX + x * CELLSIZE, startY + y * CELLSIZE, CELLSIZE, CELLSIZE, WHITE);
                break;
            default:
                break;
        }

        if(abs(GetMouseX() - (startX + x * CELLSIZE)) <= 20 && abs(GetMouseY() - (startY + y * CELLSIZE)) <= 20){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                grid[i] = 0;
            }
            if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
                grid[i] = 1;
            }
        }
    }
}