#pragma once
#define SHOW_CONSOLE
#include<graphics.h>
#include"ApplicationRoot.h"
#include<vector>
#include <iostream>

class MyBspline : public ObjWrapper {
public:
    MyBspline(const std::vector<std::pair<double, double>>& controlPoints, const std::vector<double>& knots, int degree, int color)
        : controlPoints_(controlPoints), knots_(knots), degree_(degree), color_(color) {}

    std::pair<double, double> calculateBsplinePoint(double t);
    // 遍历所有控制点，判断鼠标点击的点是否在控制点附近
    bool isMouseNearControlPoint(int mouseX, int mouseY) {
        for (const auto& point : controlPoints_) {
            double distance = std::sqrt(std::pow(point.first - mouseX, 2) + std::pow(point.second - mouseY, 2));
            if (distance < 10) {
                std::cout << "鼠标点击的点在控制点附近" << std::endl;
                return true; // 鼠标点击点在控制点附近
            }
        }
        std::cout << "鼠标点击的点不在控制点附近" << std::endl;
        return false; // 鼠标点击点不在控制点附近
    }

    // 在处理鼠标按下事件时调用该函数，判断鼠标点击的点是否在控制点附近
    void handleMouseDown(int mouseX, int mouseY) {
        if (isMouseNearControlPoint(mouseX, mouseY)) {
            bool isSelected = true;
            while (isSelected) {
                MOUSEMSG msgtemp = GetMouseMsg();
                std::cout << "点击控制点" << std::endl;
                if (msgtemp.uMsg == WM_LBUTTONUP) {

                    double x = msgtemp.x;
                    double y = msgtemp.y;
                    // 遍历所有控制点，找到最近的控制点并将其更新为鼠标新按下的点
                    for (auto& point : controlPoints_) {
                        double distance = std::sqrt(std::pow(point.first - mouseX, 2) + std::pow(point.second - mouseY, 2));
                        if (distance < 10) {
                            // 更新控制点的位置
                            point.first = x;
                            point.second = y;
                            std::cout << point.first << " " << point.second << std::endl;
                            break;
                        }
                    }
                    ObjWrapper::Points.clear();
                    plan();
                    isSelected = false; // 退出循环
                }
            }
        }
    }
    std::vector<Pixel> Draws();
    void plan();
private:
    std::vector<std::pair<double, double>> controlPoints_;
    std::vector<double> knots_;
    int degree_;
    int color_;
    double basisFunction(int i, int k, double t);
};

