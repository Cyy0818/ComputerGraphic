#ifndef MYCIRCLE_H
#define SHOW_CONSOLE
#define MYARC_H
#include<vector>
#include<graphics.h>
#include"ApplicationRoot.h"

class MyArc :public ObjWrapper {
public:
    MyArc() : x0_(0), y0_(0), r_(0), color_(0), startAngle_(0), endAngle_(0) {}
    MyArc(int x0, int y0, double r, int color, double startAngle, double endAngle)
        : x0_(x0), y0_(y0), r_(r), color_(color), startAngle_(startAngle), endAngle_(endAngle) {}
    std::vector < Pixel> DrawArc(int x0, int y0, int radius, double startAngle, double endAngle);
    void plan();
private:

    int x0_, y0_, color_;
    double r_;
    double startAngle_, endAngle_;
};


#endif //MYARC_H