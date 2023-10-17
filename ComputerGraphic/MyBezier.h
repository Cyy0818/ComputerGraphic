#pragma once
#define SHOW_CONSOLE
#include<iostream>
#include<graphics.h>
#include"Display.h"
#include<vector>
using namespace std;
class MyBezier {
public:
   
    MyBezier() :controlPoints_(), color_(0) {};
    MyBezier(vector<pair<double, double>> controlPoints) : controlPoints_(controlPoints) {}

    // 计算贝塞尔曲线上点的坐标
    pair<double, double> calculatePoint(double t);
    void Draws();

private:
    vector<pair<double, double>> controlPoints_; // 贝塞尔曲线的控制点
    // 计算二项式系数
    int binomialCoefficient(int n, int k);
    int color_;
    friend class Display<MyBezier>;
    friend class MyShapeWrapper;
};

