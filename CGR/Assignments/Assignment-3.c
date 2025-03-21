#include <stdio.h>
#include <graphics.h>

void boundaryFill(int x, int y, int boundaryColor, int fillColor) {
    int current = getpixel(x, y);
    if (current != boundaryColor && current != fillColor) {
        putpixel(x, y, fillColor);
        boundaryFill(x + 1, y, boundaryColor, fillColor);
        boundaryFill(x - 1, y, boundaryColor, fillColor);
        boundaryFill(x, y + 1, boundaryColor, fillColor);
        boundaryFill(x, y - 1, boundaryColor, fillColor);
    }
}

void floodFill(int x, int y, int oldColor, int fillColor) {
    int current = getpixel(x, y);
    if (current == oldColor) {
        putpixel(x, y, fillColor);
        floodFill(x + 1, y, oldColor, fillColor);
        floodFill(x - 1, y, oldColor, fillColor);
        floodFill(x, y + 1, oldColor, fillColor);
        floodFill(x, y - 1, oldColor, fillColor);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    
    int poly[] = {100, 100, 200, 100, 200, 200, 100, 200, 100, 100};
    drawpoly(5, poly);
    
    printf("Filling using Boundary Fill Algorithm\n");
    boundaryFill(150, 150, WHITE, RED);
    delay(2000);
    cleardevice();
    
    drawpoly(5, poly);
    printf("Filling using Flood Fill Algorithm\n");
    floodFill(150, 150, BLACK, GREEN);
    
    delay(5000);
    closegraph();
    return 0;
}