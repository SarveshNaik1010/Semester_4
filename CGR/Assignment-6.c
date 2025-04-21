#include <graphics.h>
#include <stdio.h>

#define MAX 20

// Clipping window boundaries
int x_min = 150, y_min = 100, x_max = 450, y_max = 350;

typedef struct {
    int x, y;
} Point;

Point clipEdge(Point p1, Point p2, int edge, char boundary, int* newCount) {
    Point newPoints[2];
    float m;
    *newCount = 0;

    if (p1.x != p2.x)
        m = (float)(p2.y - p1.y) / (p2.x - p1.x);

    switch (boundary) {
        case 'l':
            if (p1.x >= edge && p2.x >= edge)
                newPoints[(*newCount)++] = p2;
            else if (p1.x >= edge && p2.x < edge) {
                newPoints[(*newCount)++] = (Point){edge, p1.y + m * (edge - p1.x)};
            } else if (p1.x < edge && p2.x >= edge) {
                newPoints[(*newCount)++] = (Point){edge, p1.y + m * (edge - p1.x)};
                newPoints[(*newCount)++] = p2;
            }
            break;

        case 'r':
            if (p1.x <= edge && p2.x <= edge)
                newPoints[(*newCount)++] = p2;
            else if (p1.x <= edge && p2.x > edge) {
                newPoints[(*newCount)++] = (Point){edge, p1.y + m * (edge - p1.x)};
            } else if (p1.x > edge && p2.x <= edge) {
                newPoints[(*newCount)++] = (Point){edge, p1.y + m * (edge - p1.x)};
                newPoints[(*newCount)++] = p2;
            }
            break;

        case 'b':
            if (p1.y >= edge && p2.y >= edge)
                newPoints[(*newCount)++] = p2;
            else if (p1.y >= edge && p2.y < edge) {
                newPoints[(*newCount)++] = (Point){p1.x + (edge - p1.y) / m, edge};
            } else if (p1.y < edge && p2.y >= edge) {
                newPoints[(*newCount)++] = (Point){p1.x + (edge - p1.y) / m, edge};
                newPoints[(*newCount)++] = p2;
            }
            break;

        case 't':
            if (p1.y <= edge && p2.y <= edge)
                newPoints[(*newCount)++] = p2;
            else if (p1.y <= edge && p2.y > edge) {
                newPoints[(*newCount)++] = (Point){p1.x + (edge - p1.y) / m, edge};
            } else if (p1.y > edge && p2.y <= edge) {
                newPoints[(*newCount)++] = (Point){p1.x + (edge - p1.y) / m, edge};
                newPoints[(*newCount)++] = p2;
            }
            break;
    }

    return newPoints[0]; // The calling function handles how many points are returned
}

// Apply clipping for one boundary
void clipPolygon(Point in[], int inSize, Point out[], int *outSize, int edge, char boundary) {
    Point temp[MAX];
    int i, k = 0;
    for (i = 0; i < inSize; i++) {
        Point p1 = in[i];
        Point p2 = in[(i + 1) % inSize];
        int newCount;
        Point newPoint = clipEdge(p1, p2, edge, boundary, &newCount);
        if (newCount == 1) temp[k++] = newPoint;
        else if (newCount == 2) {
            temp[k++] = newPoint;
            temp[k++] = p2;
        }
    }

    for (i = 0; i < k; i++) out[i] = temp[i];
    *outSize = k;
}

// Draw polygon
void drawPolygon(Point poly[], int size, int color) {
    setcolor(color);
    for (int i = 0; i < size; i++) {
        line(poly[i].x, poly[i].y, poly[(i + 1) % size].x, poly[(i + 1) % size].y);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Original polygon
    Point poly[5] = {{100, 150}, {200, 50}, {300, 100}, {250, 300}, {150, 250}};
    int n = 5;

    // Draw original polygon
    drawPolygon(poly, n, YELLOW);

    // Draw clipping rectangle
    rectangle(x_min, y_min, x_max, y_max);

    getch();
    cleardevice();

    // Draw clipping window again
    rectangle(x_min, y_min, x_max, y_max);

    // Clip polygon
    Point p1[MAX], p2[MAX];
    int size1 = n, size2;
    for (int i = 0; i < n; i++) p1[i] = poly[i];

    clipPolygon(p1, size1, p2, &size2, x_min, 'l');
    clipPolygon(p2, size2, p1, &size1, x_max, 'r');
    clipPolygon(p1, size1, p2, &size2, y_min, 'b');
    clipPolygon(p2, size2, p1, &size1, y_max, 't');

    drawPolygon(p1, size1, GREEN); // Final clipped polygon

    getch();
    closegraph();
    return 0;
}
