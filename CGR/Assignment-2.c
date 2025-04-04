#include <stdio.h>
#include <math.h>

void DDACircle(int xc, int yc, int r) {
    float x = 0, y = r;
    float dtheta = 1.0 / r; // Step size for theta
    printf("DDA Circle:\n");
    while (x <= y) {
        printf("%d | %d\n", (int)(xc + x), (int)(yc + y));
        printf("%d | %d\n", (int)(xc - x), (int)(yc + y));
        printf("%d | %d\n", (int)(xc + x), (int)(yc - y));
        printf("%d | %d\n", (int)(xc - x), (int)(yc - y));
        printf("%d | %d\n", (int)(xc + y), (int)(yc + x));
        printf("%d | %d\n", (int)(xc - y), (int)(yc + x));
        printf("%d | %d\n", (int)(xc + y), (int)(yc - x));
        printf("%d | %d\n", (int)(xc - y), (int)(yc - x));
        x += dtheta * r;
        y = sqrt(r * r - x * x);
    }
}

void bresenhamsCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    printf("Bresenham's Circle:\n");
    while (x <= y) {
        printf("%d | %d\n", xc + x, yc + y);
        printf("%d | %d\n", xc - x, yc + y);
        printf("%d | %d\n", xc + x, yc - y);
        printf("%d | %d\n", xc - x, yc - y);
        printf("%d | %d\n", xc + y, yc + x);
        printf("%d | %d\n", xc - y, yc + x);
        printf("%d | %d\n", xc + y, yc - x);
        printf("%d | %d\n", xc - y, yc - x);
        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

int main() {
    printf("DDA Circle:\n");
    DDACircle(10, 10, 5);
    printf("--------------------------------------\n");
    printf("Bresenham's Circle:\n");
    bresenhamsCircle(10, 10, 5);
    return 0;
}
