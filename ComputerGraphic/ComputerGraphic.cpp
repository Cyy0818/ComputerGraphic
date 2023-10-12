#define SHOW_CONSOLE
#include <graphics.h>
#include <iostream>
#include <ege.h>
#include "Display.h"
#include "MyLine.h"
#include "MyCircle.h"
#include"Drawableobj.h"
using namespace std;


int main() {
  
    Display<MyShapeWrapper> display;
    bool isDrawing = false;
    int x1, y1, x2, y2, stepLength = 0, wide = 0;
    double r;

    for (; is_run(); delay_fps(300)){
        display.init_screen();
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONUP) {
            if (msg.x < 240 && msg.y < 80) {
                outtextxy(100, 500, L"line");
                // Line button clicked
                isDrawing = true;
                while (mousemsg()) {
                    mouse_msg temp = getmouse();
                    // 处理鼠标消息
                }
                while (!kbhit()) {
                    mouse_msg mouseMsg1 = getmouse();
                    if (mouseMsg1.is_left() && mouseMsg1.is_down()) {
                        x1 = mouseMsg1.x;
                        y1 = mouseMsg1.y;
                    }
                    if (mouseMsg1.is_left() && mouseMsg1.is_up()) {
                        isDrawing = false;
                        x2 = mouseMsg1.x;
                        y2 = mouseMsg1.y;
                        int color = BLUE;
                        MyLine line(x1, y1, x2, y2, color, stepLength, wide);
                        MyShapeWrapper drawable(line);
                        display.Push(drawable);
                        display.DrawAll();
                        break;
                    }
                    
                }
            }
            else if (msg.x < 480 && msg.x > 240 && msg.y < 80 && msg.y > 0) {
                // Circle button clicked
                outtextxy(200, 500, L"circle");
                isDrawing = true;
                while (mousemsg()) {
                    mouse_msg temp = getmouse();
                }
                while (!kbhit()) {
                    mouse_msg mouseMsg2 = getmouse();
                    if (mouseMsg2.is_left() && mouseMsg2.is_down()) {
                        x1 = mouseMsg2.x;
                        y1 = mouseMsg2.y;
                    }
                    if (mouseMsg2.is_left() && mouseMsg2.is_up()) {
                        isDrawing = false;
                        x2 = mouseMsg2.x;
                        y2 = mouseMsg2.y;
                        r = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                        int color = RED;
                        MyCircle circle(x1, y1, r, color);
                        MyShapeWrapper drawable(circle);
                        display.Push(drawable);
                        display.DrawAll();
                        break;
                    }
                }
            }
            else if (msg.x < 720 && msg.y < 80) {
                while (!kbhit()) {
                    MyPoly polygon;
                    polygon.inputVertices();
                    MyShapeWrapper drawable(polygon);
                    display.Push(drawable);
                    display.DrawAll();
                    break;
                }
            }
            else if (msg.mkLButton && msg.x < 960 && msg.x > 720 && msg.y < 80 && msg.y > 0) {
                closegraph();
                exit(1);
            }
        }

        if (kbhit()) {
            char key = getch();
            if (key == '+') {
                stepLength++;
                wide--;
            }
            else if (key == '-') {
                if (stepLength > 1) {
                    stepLength--;
                    wide--;
                }
            }
            else if (key == 'd') {
                display.Pop();
                cleardevice();
                display.DrawAll();
            }
        }
    }

    return 0;
}
