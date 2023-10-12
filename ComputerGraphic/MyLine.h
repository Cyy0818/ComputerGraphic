#ifndef MYLINE_H
#define MYLINE_H
#define SHOW_CONSOLE 
#include<iostream>
#include <vector>
#include"Display.h"
#include<ege.h>
#include<graphics.h>
using namespace std;
class MyLine {
public:
    MyLine() : x1_(0), y1_(0), x2_(0), y2_(0), color_(0),skipLength_(0),wide_(0) {}
    MyLine(int x1, int y1, int x2, int y2, int color,int skipLength,int wide)
        : x1_(x1), y1_(y1), x2_(x2), y2_(y2), color_(color), skipLength_(skipLength),wide_(wide) {}
    void BresenhamLine(int x1, int y1, int x2, int y2, int color, int skipLength, int wide);
    void Draws();

private:
    int x1_, y1_, x2_, y2_, color_, skipLength_, wide_;

    friend class Display<MyLine>; 
    friend class MyShapeWrapper;
};

#endif 



