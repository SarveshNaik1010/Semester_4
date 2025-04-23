#include <graphics.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14

// -------- Koch Snowflake --------
void koch(int x1, int y1, int x2, int y2, int depth) {
    if (depth == 0) {
        line(x1, y1, x2, y2);
        return;
    }
    int x3 = (2 * x1 + x2) / 3;
    int y3 = (2 * y1 + y2) / 3;
    int x4 = (x1 + 2 * x2) / 3;
    int y4 = (y1 + 2 * y2) / 3;
    float angle = M_PI / 3;
    int x = x4 - x3;
    int y = y4 - y3;
    int x5 = x3 + (int)((x * cos(angle)) - (y * sin(angle)));
    int y5 = y3 + (int)((x * sin(angle)) + (y * cos(angle)));

    koch(x1, y1, x3, y3, depth - 1);
    koch(x3, y3, x5, y5, depth - 1);
    koch(x5, y5, x4, y4, depth - 1);
    koch(x4, y4, x2, y2, depth - 1);
}

// -------- Sierpinski Triangle --------
void drawTriangle(int x, int y, int size) {
    line(x, y, x + size, y);
    line(x, y, x + size / 2, y - size);
    line(x + size, y, x + size / 2, y - size);
}

void sierpinski(int x, int y, int size, int depth) {
    if (depth == 0) {
        drawTriangle(x, y, size);
        return;
    }
    sierpinski(x, y, size / 2, depth - 1);
    sierpinski(x + size / 2, y, size / 2, depth - 1);
    sierpinski(x + size / 4, y - size / 2, size / 2, depth - 1);
}

// -------- Fractal Tree --------
void drawTree(int x1, int y1, int angle, int depth) {
    if (depth == 0) return;
    int x2 = x1 + cos(angle * M_PI / 180.0) * depth * 10;
    int y2 = y1 - sin(angle * M_PI / 180.0) * depth * 10;
    line(x1, y1, x2, y2);
    drawTree(x2, y2, angle - 20, depth - 1);
    drawTree(x2, y2, angle + 20, depth - 1);
}

// -------- Bezier Curve --------
void drawBezier() {
    int x0 = 100, y0 = 400;
    int x1 = 250, y1 = 100;
    int x2 = 400, y2 = 400;
    float t;

    setcolor(GREEN);
    for (t = 0.0; t <= 1.0; t += 0.001) {
        float xt = pow(1 - t, 2) * x0 + 2 * (1 - t) * t * x1 + pow(t, 2) * x2;
        float yt = pow(1 - t, 2) * y0 + 2 * (1 - t) * t * y1 + pow(t, 2) * y2;
        putpixel((int)xt, (int)yt, GREEN);
    }
    outtextxy(200, 420, "Bezier Curve");
}

// -------- B-Spline Curve --------
void drawBSpline(int numPoints, int x[], int y[]) {
    float t;
    int i;

    setcolor(CYAN);
    for (i = 0; i <= numPoints - 4; i++) {
        for (t = 0; t <= 1; t += 0.001) {
            float b0 = ((1 - t) * (1 - t) * (1 - t)) / 6;
            float b1 = (3 * t * t * t - 6 * t * t + 4) / 6;
            float b2 = (-3 * t * t * t + 3 * t * t + 3 * t + 1) / 6;
            float b3 = (t * t * t) / 6;
            float xt = b0 * x[i] + b1 * x[i + 1] + b2 * x[i + 2] + b3 * x[i + 3];
            float yt = b0 * y[i] + b1 * y[i + 1] + b2 * y[i + 2] + b3 * y[i + 3];
            putpixel((int)xt, (int)yt, CYAN);
        }
    }
    outtextxy(380, 420, "B-Spline Curve");
}

// -------- Hilbert Curve --------
void hilbert(float x, float y, float xi, float xj, float yi, float yj, int n) {
    if (n <= 0) return;

    hilbert(x, y, yi / 2, yj / 2, xi / 2, xj / 2, n - 1);
    line((int)(x + (xi + yi) / 2), (int)(y + (xj + yj) / 2),
         (int)(x + (xi - yi) / 2), (int)(y + (xj - yj) / 2));

    hilbert(x + xi / 2, y + xj / 2, xi / 2, xj / 2, yi / 2, yj / 2, n - 1);
    line((int)(x + xi + yi / 2), (int)(y + xj + yj / 2),
         (int)(x + (xi + yi) / 2), (int)(y + (xj + yj) / 2));

    hilbert(x + xi / 2 + yi, y + xj / 2 + yj,
            xi / 2, xj / 2, yi / 2, yj / 2, n - 1);
    line((int)(x + (xi + yi) / 2), (int)(y + (xj + yj) / 2),
         (int)(x + xi / 2 + yi / 2), (int)(y + xj / 2 + yj / 2));

    hilbert(x + xi + yi / 2, y + xj + yj / 2,
            -yi / 2, -yj / 2, -xi / 2, -xj / 2, n - 1);
}

// -------- Main Menu --------
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int choice = 1, depth, i;
    int x[10], y[10], numPoints;

    while(choice != 0) {
        
    printf("Choose:\n");
    printf("1. Koch Snowflake\n");
    printf("2. Sierpinski Triangle\n");
    printf("3. Fractal Tree\n");
    printf("4. Bezier Curve\n");
    printf("5. B-Spline Curve\n");
    printf("6. Hilbert Curve\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    cleardevice();
    setbkcolor(BLACK);

    switch (choice) {
        case 1:
            printf("Enter depth (e.g., 3): ");
            scanf("%d", &depth);
            koch(150, 300, 450, 300, depth);
            koch(450, 300, 300, 100, depth);
            koch(300, 100, 150, 300, depth);
            break;

        case 2:
            printf("Enter depth (e.g., 4): ");
            scanf("%d", &depth);
            sierpinski(150, 400, 300, depth);
            break;

        case 3:
            printf("Enter depth (e.g., 6): ");
            scanf("%d", &depth);
            drawTree(320, 400, 90, depth);
            break;

        case 4:
            drawBezier();
            break;

        case 5:
            printf("Enter number of control points (minimum 4, max 7): ");
            scanf("%d", &numPoints);
            if (numPoints < 4 || numPoints > 7) {
                printf("Invalid number of control points.\n");
                break;
            }
            for (i = 0; i < numPoints; i++) {
                printf("Enter x[%d] y[%d]: ", i, i);
                scanf("%d %d", &x[i], &y[i]);
            }
            drawBSpline(numPoints, x, y);
            break;

        case 6:
            printf("Enter order (depth) of Hilbert curve (1–6 recommended): ");
            scanf("%d", &depth);
            setcolor(WHITE);
            hilbert(200.0, 100.0, 40.0, 0.0, 0.0, 40.0, depth);
            outtextxy(230, 190, "Hilbert Curve");
            break;

        default:
            printf("Invalid choice!\n");
            break;
    }

    }

    getch();
    closegraph();
    return 0;
}
