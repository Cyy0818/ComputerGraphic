#include "MyCircle.h"

void MyCircle::CirclePoint(int x0, int y0, int x, int y, int color) {
    putpixel(x0 + x, y0 + y, color);
    putpixel(x0 + y, y0 + x, color);
    putpixel(x0 - x, y0 + y, color);
    putpixel(x0 - y, y0 + x, color);
    putpixel(x0 + x, y0 - y, color);
    putpixel(x0 + y, y0 - x, color);
    putpixel(x0 - x, y0 - y, color);
    putpixel(x0 - y, y0 - x, color);
}

void MyCircle::MidPointCircle(int x0, int y0, double r, int color) {
    int x = 0, y = r, e = 1 - r;
    CirclePoint(x0, y0, x, y, color);

    while (x <= y) {
        if (e < 0) {
            e += 2 * x + 3;
        }
        else {
            e += 2 * (x - y) + 5;
            y--;
        }
        x++;
        CirclePoint(x0, y0, x, y, color);
    }
}
void MyCircle::Draws() {
    MidPointCircle(x0_, y0_, r_, color_);
}
