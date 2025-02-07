#include <stdio.h>
#include <stdlib.h>


void DDALine(int x1, int y1, int x2, int y2) {
    float x = x1;
    float y = y1;
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) >= abs(dy) ? abs(dx) : abs(dy);

    if (steps == 0) {
        printf("Single Point: (%d, %d)\n", x1, y1);
        return;
    }

    float xinc = (float)dx / steps;
    float yinc = (float)dy / steps;
    
    for(int i = 0; i <= steps; i++) { 
        printf("%.2f | %.2f\n", x, y);
        x += xinc;
        y += yinc;
    }
}

void bresenhamsLine(int x1, int y1, int x2, int y2) {
    int x = x1;
    int y = y1;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int dx2 = dx * 2;
    int dy2 = dy * 2;

    int g = dy2 - dx;
    while(x <= x2) {
        printf("%d | %d\n", x, y);
        x++;
        if(g >= 0) {
            g += dy2 - dx2;
            y++;
        } else {
            g += dy2;
        }
    }

}

int main() {
    DDALine(2, 5, 12, 7);
    bresenhamsLine(2, 5, 12, 7);
    return 0;
}
