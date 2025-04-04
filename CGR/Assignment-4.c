#include <graphics.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159
#endif

// Structure for a 2D point
typedef struct {
    int x, y;
} Point;

// Function to apply translation
void applyTranslation(Point* p, int tx, int ty) {
    p->x += tx;
    p->y += ty;
}

// Function to apply scaling
void applyScaling(Point* p, float sx, float sy, Point center) {
    p->x = center.x + (int)((p->x - center.x) * sx);
    p->y = center.y + (int)((p->y - center.y) * sy);
}

// Function to apply rotation
void applyRotation(Point* p, float angle, Point center) {
    float rad = angle * (M_PI / 180.0);
    int x_new = center.x + (int)((p->x - center.x) * cos(rad) - (p->y - center.y) * sin(rad));
    int y_new = center.y + (int)((p->x - center.x) * sin(rad) + (p->y - center.y) * cos(rad));
    p->x = x_new;
    p->y = y_new;
}

// Function to draw a quadrilateral
void drawQuadrilateral(Point p1, Point p2, Point p3, Point p4) {
    line(p1.x, p1.y, p2.x, p2.y);
    line(p2.x, p2.y, p3.x, p3.y);
    line(p3.x, p3.y, p4.x, p4.y);
    line(p4.x, p4.y, p1.x, p1.y);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Define initial points (slightly different than before)
    Point p1 = {260, 200}, p2 = {340, 200}, p3 = {340, 280}, p4 = {260, 280};
    Point center = {(p1.x + p2.x + p3.x + p4.x) / 4, (p1.y + p2.y + p3.y + p4.y) / 4};

    // Draw original shape
    cleardevice();
    drawQuadrilateral(p1, p2, p3, p4);
    outtextxy(10, 10, "Initial Shape");
    getch();

    // Apply Translation
    applyTranslation(&p1, 40, 60);
    applyTranslation(&p2, 40, 60);
    applyTranslation(&p3, 40, 60);
    applyTranslation(&p4, 40, 60);
    cleardevice();
    drawQuadrilateral(p1, p2, p3, p4);
    outtextxy(10, 10, "Translated Shape");
    getch();

    // Apply Scaling
    applyScaling(&p1, 1.3, 1.3, center);
    applyScaling(&p2, 1.3, 1.3, center);
    applyScaling(&p3, 1.3, 1.3, center);
    applyScaling(&p4, 1.3, 1.3, center);
    cleardevice();
    drawQuadrilateral(p1, p2, p3, p4);
    outtextxy(10, 10, "Scaled Shape");
    getch();

    // Apply Rotation
    applyRotation(&p1, 30, center);
    applyRotation(&p2, 30, center);
    applyRotation(&p3, 30, center);
    applyRotation(&p4, 30, center);
    cleardevice();
    drawQuadrilateral(p1, p2, p3, p4);
    outtextxy(10, 10, "Rotated Shape (30 degrees)");
    getch();

    closegraph();
    return 0;
}
