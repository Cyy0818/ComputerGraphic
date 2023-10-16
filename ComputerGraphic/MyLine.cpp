#include"MyLine.h"

void MyLine::BresenhamLine(int x1, int y1, int x2, int y2, int color, int skipLength,int wide) {
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int erro = (dx > dy ? dx : -dy) / 2;
    int blankCount = 0;

    while (x1 != x2 || y1 != y2) {
        if (blankCount <skipLength) {
            blankCount++;
        }
        else {
            putpixel(x1, y1, color);
            blankCount = 0; 
        }

        int e2 = erro;
        if (e2 > -dx) { erro -= dy; x1 += sx; }
        if (e2 < dy) { erro += dx; y1 += sy; }
    }
    putpixel(x2, y2, color);
}

void MyLine::Draws() {
    BresenhamLine(x1_, y1_, x2_, y2_, color_,skipLength_,wide_);
}
