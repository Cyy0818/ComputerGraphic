#ifndef MYCIRCLE_H
#define MYCIRCLE_H
#define SHOW_CONSOLE 
#include<vector>
#include<graphics.h>
#include"Display.h"
#include<iostream>
using namespace std;

class MyCircle {
public:
    MyCircle() : x0_(0), y0_(0), r_(0), color_(0) {}
    MyCircle(int x0, int y0, double r, int color)
        : x0_(x0), y0_(y0), r_(r), color_(color) {}
    void CirclePoint(int x0, int y0, int x, int y, int color);
    void MidPointCircle(int x0, int y0, double r, int color);
    void Draws();
private:
    int x0_, y0_, color_;
    double r_;
    friend class Display<MyCircle>;
    friend class MyShapeWrapper;
};


#endif // MYCIRCLE_H