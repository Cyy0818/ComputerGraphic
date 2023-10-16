#define SHOW_CONSOLE
#include<iostream>
#include<graphics.h>
#include"Display.h"
class MyPoly {
public:
    MyPoly(): num(0), color_(0), ver(nullptr) {}
    void inputVertices();
    void drawPolygon();
    void scanlineFill();//…®√ËÃÓ≥‰
    void Draws();
private:
    int num;
    int color_;
    struct vertex {
        int x;
        int y;
    } *ver;
    friend class Display<MyPoly>;
    friend class MyShapeWrapper;
};