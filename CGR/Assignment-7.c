#include <graphics.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_CENTER_X 320
#define SCREEN_CENTER_Y 240
#define DEPTH_FACTOR 200   // for perspective

typedef struct {
    float x, y, z;
} Point3D;

Point3D cube[8] = {
    {100, 100, 100}, {200, 100, 100},
    {200, 200, 100}, {100, 200, 100},
    {100, 100, 200}, {200, 100, 200},
    {200, 200, 200}, {100, 200, 200}
};

// Perspective projection
void project(Point3D p, int *x, int *y) {
    float factor = DEPTH_FACTOR / (DEPTH_FACTOR + p.z);
    *x = SCREEN_CENTER_X + p.x * factor;
    *y = SCREEN_CENTER_Y - p.y * factor;
}

void drawCube(Point3D c[8], int color) {
    setcolor(color);
    int i, x1, y1, x2, y2;
    for (i = 0; i < 4; i++) {
        project(c[i], &x1, &y1);
        project(c[(i + 1) % 4], &x2, &y2);
        line(x1, y1, x2, y2);  // front face

        project(c[i + 4], &x1, &y1);
        project(c[((i + 1) % 4) + 4], &x2, &y2);
        line(x1, y1, x2, y2);  // back face

        project(c[i], &x1, &y1);
        project(c[i + 4], &x2, &y2);
        line(x1, y1, x2, y2);  // vertical edges
    }
}

// Transformation functions
void translate(Point3D c[], float tx, float ty, float tz) {
    for (int i = 0; i < 8; i++) {
        c[i].x += tx;
        c[i].y += ty;
        c[i].z += tz;
    }
}

void scale(Point3D c[], float sx, float sy, float sz) {
    for (int i = 0; i < 8; i++) {
        c[i].x *= sx;
        c[i].y *= sy;
        c[i].z *= sz;
    }
}

void rotateX(Point3D c[], float angle) {
    float rad = angle * M_PI / 180;
    for (int i = 0; i < 8; i++) {
        float y = c[i].y;
        float z = c[i].z;
        c[i].y = y * cos(rad) - z * sin(rad);
        c[i].z = y * sin(rad) + z * cos(rad);
    }
}

void rotateY(Point3D c[], float angle) {
    float rad = angle * M_PI / 180;
    for (int i = 0; i < 8; i++) {
        float x = c[i].x;
        float z = c[i].z;
        c[i].x = x * cos(rad) + z * sin(rad);
        c[i].z = -x * sin(rad) + z * cos(rad);
    }
}

void rotateZ(Point3D c[], float angle) {
    float rad = angle * M_PI / 180;
    for (int i = 0; i < 8; i++) {
        float x = c[i].x;
        float y = c[i].y;
        c[i].x = x * cos(rad) - y * sin(rad);
        c[i].y = x * sin(rad) + y * cos(rad);
    }
}

void reflect(Point3D c[], char axis) {
    for (int i = 0; i < 8; i++) {
        if (axis == 'x') c[i].x = -c[i].x;
        if (axis == 'y') c[i].y = -c[i].y;
        if (axis == 'z') c[i].z = -c[i].z;
    }
}

void shear(Point3D c[], float shx, float shy) {
    for (int i = 0; i < 8; i++) {
        c[i].x += shx * c[i].y;
        c[i].y += shy * c[i].x;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    Point3D shape[8];
    for (int i = 0; i < 8; i++) shape[i] = cube[i];

    int ch;
    float a, b, c;
    char axis;

    do {
        cleardevice();
        drawCube(shape, GREEN);

        printf("\n\n-- 3D TRANSFORMATIONS --\n");
        printf("0. Exit\n1. Translate\n2. Scale\n3. RotateX\n4. RotateY\n5. RotateZ\n6. Reflect\n7. Shear\nChoice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 0:
                break;
            case 1:
                printf("Enter tx ty tz: ");
                scanf("%f%f%f", &a, &b, &c);
                translate(shape, a, b, c);
                break;
            case 2:
                printf("Enter sx sy sz: ");
                scanf("%f%f%f", &a, &b, &c);
                scale(shape, a, b, c);
                break;
            case 3:
                printf("Enter angle for rotation about X: ");
                scanf("%f", &a);
                rotateX(shape, a);
                break;
            case 4:
                printf("Enter angle for rotation about Y: ");
                scanf("%f", &a);
                rotateY(shape, a);
                break;
            case 5:
                printf("Enter angle for rotation about Z: ");
                scanf("%f", &a);
                rotateZ(shape, a);
                break;
            case 6:
                printf("Reflect about (x/y/z): ");
                scanf(" %c", &axis);
                reflect(shape, axis);
                break;
            case 7:
                printf("Enter shear values shx, shy: ");
                scanf("%f%f", &a, &b);
                shear(shape, a, b);
                break;
            default:
                printf("Invalid choice\n");
        }

        getch(); // Wait to view the result before next operation

    } while (ch != 0);

    closegraph();
    return 0;
}
