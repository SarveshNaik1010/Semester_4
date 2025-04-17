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

    Point p1, p2, p3, p4;

    // --- Input initial coordinates ---
    printf("Enter coordinates for p1 (x y): ");
    scanf("%d %d", &p1.x, &p1.y);

    printf("Enter coordinates for p2 (x y): ");
    scanf("%d %d", &p2.x, &p2.y);

    printf("Enter coordinates for p3 (x y): ");
    scanf("%d %d", &p3.x, &p3.y);

    printf("Enter coordinates for p4 (x y): ");
    scanf("%d %d", &p4.x, &p4.y);

    // Calculate center
    Point center = {
        (p1.x + p2.x + p3.x + p4.x) / 4,
        (p1.y + p2.y + p3.y + p4.y) / 4
    };

    // Draw original shape
    cleardevice();
    drawQuadrilateral(p1, p2, p3, p4);
    outtextxy(10, 10, "Initial Shape");
    getch();

    // --- Input transformation parameters ---
    int tx, ty;
    float sx, sy, angle;

    printf("Enter translation values (tx ty): ");
    scanf("%d %d", &tx, &ty);

    printf("Enter scaling factors (sx sy): ");
    scanf("%f %f", &sx, &sy);

    printf("Enter rotation angle (in degrees): ");
    scanf("%f", &angle);

    // Apply Translation
    applyTranslation(&p1, tx, ty);
    applyTranslation(&p2, tx, ty);
    applyTranslation(&p3, tx, ty);
    applyTranslation(&p4, tx, ty);
    cleardevice();
    drawQuadrilateral(p1, p2, p3, p4);
    outtextxy(10, 10, "Translated Shape");
    getch();

    // Recalculate center after translation
    center = (Point){
        (p1.x + p2.x + p3.x + p4.x) / 4,
        (p1.y + p2.y + p3.y + p4.y) / 4
    };

    // Apply Scaling
    applyScaling(&p1, sx, sy, center);
    applyScaling(&p2, sx, sy, center);
    applyScaling(&p3, sx, sy, center);
    applyScaling(&p4, sx, sy, center);
    cleardevice();
    drawQuadrilateral(p1, p2, p3, p4);
    outtextxy(10, 10, "Scaled Shape");
    getch();

    // Apply Rotation
    applyRotation(&p1, angle, center);
    applyRotation(&p2, angle, center);
    applyRotation(&p3, angle, center);
    applyRotation(&p4, angle, center);
    cleardevice();
    drawQuadrilateral(p1, p2, p3, p4);
    outtextxy(10, 10, "Rotated Shape");
    getch();

    closegraph();
    return 0;
}
