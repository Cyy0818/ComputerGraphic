#ifndef MYLINE_H
#define MYLINE_H
#include <vector>
#include<algorithm>
#include"ApplicationRoot.h"

class MyLine :public ObjWrapper
{
public:
    //起点，终点，颜色，间隙，宽度
    MyLine() : x1_(0), y1_(0), x2_(0), y2_(0), color_(0), skipLength_(0), wide_(0),flag_(0) {}
    MyLine(int x1, int y1, int x2, int y2, int color, int skipLength, int wide,int flag)
        : x1_(x1), y1_(y1), x2_(x2), y2_(y2), color_(color), skipLength_(skipLength), wide_(wide),flag_(flag) {}
    std::vector<Pixel> BresenhamLine(int x1, int y1, int x2, int y2, int color, int skipLength, int wide);
    std::vector<Pixel> MidpointLine(int x0, int y0, int x1, int y1, int color, int skipLength, int lineWidth);
    void plan();
    void CS_clip(int xMin, int yMin, int xMax, int yMax);
    void Mid_clip(int x1, int y1, int x2, int y2, int xmin, int ymin, int xmax, int ymax);
    int x1_, y1_, x2_, y2_, color_, skipLength_, wide_;
    int flag_;
private:
    
    const int INSIDE = 0; // 0000
    const int LEFT = 1;   // 0001
    const int RIGHT = 2;  // 0010
    const int BOTTOM = 4; // 0100
    const int TOP = 8;    // 1000
    int computeCode(int x, int y, int xMin, int yMin, int xMax, int yMax);
};

#endif 



