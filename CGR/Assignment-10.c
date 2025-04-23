#include <graphics.h>
#include <math.h>
#include <dos.h>

// Constants
#define PI 3.14159265

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    float ballX = getmaxx() / 2;  // Center X
    float baseY = 400;            // Ground level
    float amplitude = 100;        // Height of the bounce
    float angle = 0;              // Angle for sine function
    float radius = 30;

    while (!kbhit()) {
        cleardevice();

        // Draw ground
        setcolor(DARKGRAY);
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar(0, baseY + radius, getmaxx(), baseY + radius + 10);

        // Calculate vertical position using sine wave
        float ballY = baseY - fabs(sin(angle * PI / 180) * amplitude);

        // Draw yellow ball
        setfillstyle(SOLID_FILL, YELLOW);
        fillellipse((int)ballX, (int)ballY, (int)radius, (int)radius);

        angle += 5;  // Speed of bouncing
        if (angle >= 360) angle = 0;

        delay(30);  // ~30 FPS
    }

    closegraph();
    return 0;
}
