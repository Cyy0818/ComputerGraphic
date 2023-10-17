#include "MyCircle.h"

void MyCircle::CirclePoint(int x0, int y0, int x, int y, int color, std::vector<Pixel>& buffer) {
    buffer.push_back(Pixel(x0 + x, y0 + y, color));
    buffer.push_back(Pixel(x0 + y, y0 + x, color));
    buffer.push_back(Pixel(x0 - x, y0 + y, color));
    buffer.push_back(Pixel(x0 - y, y0 + x, color));
    buffer.push_back(Pixel(x0 + x, y0 - y, color));
    buffer.push_back(Pixel(x0 + y, y0 - x, color));
    buffer.push_back(Pixel(x0 - x, y0 - y, color));
    buffer.push_back(Pixel(x0 - y, y0 - x, color));
}

std::vector<Pixel> MyCircle::MidPointCircle(int x0, int y0, double r, int color) {
    std::vector<Pixel> buffer;
    int x = 0, y = r, e = 1 - r;
    CirclePoint(x0, y0, x, y, color, buffer);

    while (x <= y) {
        if (e < 0) {
            e += 2 * x + 3;
        }
        else {
            e += 2 * (x - y) + 5;
            y--;
        }
        x++;
        CirclePoint(x0, y0, x, y, color, buffer);
    }

    return buffer;
}

void MyCircle::plan() {
    ObjWrapper::Points = MidPointCircle(this->x0_, y0_, this->r_, this->color_);
}
