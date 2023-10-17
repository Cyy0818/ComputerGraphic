#ifndef MYCIRCLE_H
#define SHOW_CONSOLE
#define MYCIRCLE_H
#include<vector>
#include<graphics.h>
#include"ApplicationRoot.h"

class MyCircle :public ObjWrapper {
public:
    MyCircle() : x0_(0), y0_(0), r_(0), color_(0) {}
    MyCircle(int x0, int y0, double r, int color)
        : x0_(x0), y0_(y0), r_(r), color_(color) {}
    void CirclePoint(int x0, int y0, int x, int y, int color, std::vector<Pixel>& buffer);
    std::vector<Pixel> MidPointCircle(int x0, int y0, double r, int color);
    void plan();
private:
    int x0_, y0_, color_;
    double r_;
};


#endif // MYCIRCLE_H