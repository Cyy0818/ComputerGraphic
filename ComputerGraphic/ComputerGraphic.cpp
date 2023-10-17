#define SHOW_CONSOLE
#include"MyArc.h"
#include"ApplicationRoot.h"
#include"MyLine.h"
#include"MyCircle.h"
#include"Mypoly.h"
#include"MyBspline.h"
#include"MyBezier.h"
#include<functional>
#include<map>
#include <graphics.h>
#include <cmath>
#include<conio.h>
#include"MyPhong.h"
#include<iostream>
#include <ege.h>
using namespace std;

int main() {
	ApplicationRoot app(1500, 900);
    app.mainfunction = [](ApplicationRoot* app, std::map<std::string, int>& env, const Frame* const CurrentFrame) {
        mouse_msg msg = getmouse();
        
        int delta_x = msg.x - env["Mouse_x"];
        int delta_y = msg.y - env["Mouse_y"];
        env["Mouse_x"] = msg.x;
        env["Mouse_y"] = msg.y;

        MOUSEMSG msg1 = GetMouseMsg();
        if ((int)msg.is_down() == 1 && (int)msg.is_left() == 1) {
            if (msg.x < 60 && msg.x > 0   && msg.y < 60) env["Mode"] = 1;
            if (msg.x < 120 && msg.x > 60 && msg.y < 60) env["Mode"] = 2;
            if (msg.x < 220 && msg.x > 120 && msg.y < 60) env["Mode"] = 3;
            if (msg.x < 290 && msg.x > 220 && msg.y < 60) env["Mode"] = 4;
            if (msg.x < 360 && msg.x > 290 && msg.y < 60) env["Mode"] = 5;
            if (msg.x < 430 && msg.x > 360 && msg.y < 60) env["Mode"] = 6;
            if (msg.x < 500 && msg.x > 430 && msg.y < 60) env["Mode"] = 7;
            if (msg.x < 570 && msg.x > 500 && msg.y < 60) env["Mode"] = 8;
            if (msg.x < 680 && msg.x > 570 && msg.y < 60) env["Mode"] = 9;
            if (msg.x < 740 && msg.x > 680 && msg.y < 60) env["Mode"] = 10;
            if (msg.x < 860 && msg.x > 740 && msg.y < 60) env["Mode"] = 11;
            if (msg.x < 980 && msg.x > 860 && msg.y < 60) env["Mode"] = 12;
            if (msg.x < 1100 && msg.x > 980 && msg.y < 60) env["Mode"] = 13;
            if (msg.x < 1160 && msg.x > 1100 && msg.y < 60) env["Mode"] = 14;
            
        }

        //拖拽
        if (env["Mode"] == 10) {
            cout << "可以拖拽了" << endl;
            
            if ((int)msg.is_down() == 1 && (int)msg.is_left() == 1) {
                env["Selected_Obj"] = CurrentFrame->indices[msg1.y][msg1.x];
                cout << "selected" << endl;
            }

            MOUSEMSG msg1 = GetMouseMsg();
            if (env["Left_Down"] == 0 && (msg1.uMsg == WM_LBUTTONDOWN)) {
                env["Left_Down"] =1;
            }
            if (env["Left_Down"] == 1 && (msg1.uMsg == WM_LBUTTONUP)) {
                env["Left_Down"] = 0;
            }
            cout << env["Left_Down"];

            if (env["Selected_Obj"] != -1 && env["Left_Down"]==1) {
                cout << "move" << endl;
                app->objList[env["Selected_Obj"]]->move(delta_x, delta_y);
            }
          
        }

        //Rotate around Gravity Center
        if (env["Mode"] == 11) {
            cout << "Rotate around Gravity Center" << endl;
            if ((int)msg.is_down() == 1 && (int)msg.is_left() == 1) {
                env["Selected_Obj"] = CurrentFrame->indices[msg.y][msg.x];
                if (env["Selected_Obj"] != -1) {
                    int c_x = 0, c_y = 0;
                    app->objList[env["Selected_Obj"]]->get_gravity_center(c_x, c_y);
                    env["Selected_Obj_Center_x"] = c_x;
                    env["Selected_Obj_Center_y"] = c_y;
                    cout << "selected" << endl;
                }
                
            }
            MOUSEMSG msg1 = GetMouseMsg();
            if (env["Left_Down"] == 0 && (msg1.uMsg == WM_LBUTTONDOWN)) {
                env["Left_Down"] = 1;
            }
            if (env["Left_Down"] == 1 && (msg1.uMsg == WM_LBUTTONUP)) {
                env["Left_Down"] = 0;
            }
            if (env["Selected_Obj"] != -1 && (env["Left_Down"] == 1)) {
                int cursor_x = msg1.x, cursor_y = msg1.y;
                int pre_cursor_x = cursor_x - (delta_x), pre_cursor_y = cursor_y - (delta_y);
                std::pair<int, int> vec_a(cursor_x - env["Selected_Obj_Center_x"], cursor_y - env["Selected_Obj_Center_y"]);
                std::pair<int, int> vec_b(pre_cursor_x - env["Selected_Obj_Center_x"], pre_cursor_y - env["Selected_Obj_Center_y"]);
                int dot_product = vec_a.first * vec_b.first + vec_a.second * vec_b.second;
                double cos_ = dot_product / (sqrt(vec_a.first * vec_a.first + vec_a.second * vec_a.second)) / (sqrt(vec_b.first * vec_b.first + vec_b.second * vec_b.second));
                double theta = acos(cos_);
                app->objList[env["Selected_Obj"]]->rotate(env["Selected_Obj_Center_x"], env["Selected_Obj_Center_y"], theta);
                std::this_thread::sleep_for(std::chrono::milliseconds(130));
            }
        }

        //Rotate around any point
        if (env["Mode"] == 12) {
            cout << "set a point" << endl;
            if ((int)msg.is_down() == 1 && (int)msg.is_left() == 1) {
                env["Selected_Rotate_Center_x"] = msg.x;
                env["Selected_Rotate_Center_y"] = msg.y;
                cout << "center: (" << msg.x << "," << msg.y << ")" << endl;
            }
        }

        ////Rotate Part
        if (env["Mode"] == 13) {
            cout << "Rotate around any point" << endl;
            if ((int)msg.is_down() == 1 && (int)msg.is_left() == 1) {
                env["Selected_Obj"] = CurrentFrame->indices[msg1.y][msg1.x];
                if (env["Selected_Obj"] != -1) {
                    cout << "selected" << endl;
                }
            }

            MOUSEMSG msg1 = GetMouseMsg();
            if (env["Left_Down"] == 0 && (msg1.uMsg == WM_LBUTTONDOWN)) {
                env["Left_Down"] = 1;
            }
            if (env["Left_Down"] == 1 && (msg1.uMsg == WM_LBUTTONUP)) {
                env["Left_Down"] = 0;
            }

            if (env["Selected_Obj"] != -1 && (env["Left_Down"] == 1)) {
                int cursor_x = msg1.x, cursor_y = msg1.y;
                int pre_cursor_x = cursor_x - (delta_x), pre_cursor_y = cursor_y - (delta_y);
                std::pair<int, int> vec_a(cursor_x - env["Selected_Rotate_Center_x"], cursor_y - env["Selected_Rotate_Center_y"]);
                std::pair<int, int> vec_b(pre_cursor_x - env["Selected_Rotate_Center_x"], pre_cursor_y - env["Selected_Rotate_Center_y"]);
                int dot_product = vec_a.first * vec_b.first + vec_a.second * vec_b.second;
                double cos_ = dot_product / (sqrt(vec_a.first * vec_a.first + vec_a.second * vec_a.second)) / (sqrt(vec_b.first * vec_b.first + vec_b.second * vec_b.second));
                double theta = acos(cos_);
                app->objList[env["Selected_Obj"]]->rotate(env["Selected_Rotate_Center_x"], env["Selected_Rotate_Center_y"], theta);
                std::this_thread::sleep_for(std::chrono::milliseconds(130));
            }
        }

        //zoom
        if (env["Mode"] == 14) {
            cout << "zoom" << endl;
            if ((int)msg.is_down() == 1 && (int)msg.is_left() == 1) {
                env["Selected_Obj"] = CurrentFrame->indices[msg1.y][msg1.x];
                cout << "selected" << endl;
            }
            if ((int)msg.is_wheel() == 1) {
                if (msg.wheel > 0) {
                    app->objList[env["Selected_Obj"]]->zoom(1.2);
                }
                if (msg.wheel < 0) {
                    app->objList[env["Selected_Obj"]]->zoom(0.8);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(330));
            }
        }


        //画线
        if (env["Mode"] == 1) {
            int x1, x2, y1, y2, wide, blank;
            cout << "线宽为：";
            cin >> wide;
            cout << endl;
            cout << "间距为：";
            cin >> blank;
            cout << endl;
            int flag;
            cout << "1.中点算法" << endl << "2.Bersenham算法" << endl;
            cin >> flag;
            bool isDrawing = true;
            if (flag == 1) {
                while (isDrawing) {
                    MOUSEMSG msg1 = GetMouseMsg();
                    if (msg1.uMsg == WM_LBUTTONDOWN) {
                        x1 = msg1.x;
                        y1 = msg1.y;
                    }
                    if (msg1.uMsg == WM_LBUTTONUP) {
                        x2 = msg1.x;
                        y2 = msg1.y;
                        isDrawing = false;
                        cout << x1 << " " << y1 << endl;
                        cout << x2 << " " << y2 << endl;
                        MyLine* line = new MyLine(x1, y1, x2, y2, RED, blank, wide, flag);
                        app->objList.Append(line);
                        break;
                    }
                }
            }
            else if (flag == 2)
            {
                while (isDrawing) {
                    MOUSEMSG msg1 = GetMouseMsg();
                    if (msg1.uMsg == WM_LBUTTONDOWN) {
                        x1 = msg1.x;
                        y1 = msg1.y;
                    }
                    if (msg1.uMsg == WM_LBUTTONUP) {
                        x2 = msg1.x;
                        y2 = msg1.y;
                        isDrawing = false;
                        cout << x1 << " " << y1 << endl;
                        cout << x2 << " " << y2 << endl;
                        MyLine* line = new MyLine(x1, y1, x2, y2, RED, blank, wide, flag);
                        app->objList.Append(line);
                        break;
                    }
                }
            }
            env["Mode"] = 0;
        }

        //绘制圆形
        if (env["Mode"] == 2) {
            int x1, x2, y1, y2;
            double r;
            cout << "绘制圆形" << endl;
            bool isDrawing = true;
            while (isDrawing) {
                MOUSEMSG msg1 = GetMouseMsg();
                if (msg1.uMsg == WM_LBUTTONDOWN) {
                    x1 = msg1.x;
                    y1 = msg1.y;
                }
                if (msg1.uMsg == WM_LBUTTONUP) {
                    x2 = msg1.x;
                    y2 = msg1.y;
                    r = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                    int color = RED;
                    MyCircle* circle = new MyCircle(x1, y1, r, RED);
                    app->objList.Append(circle);
                    isDrawing = false;
                    break;
                }
            }
            env["Mode"] = 0;
        }

        //绘制多边形
        if (env["Mode"] == 3) {
            int flag;
            cout << "绘制多边形" << endl;
            vector<std::pair<double, double>> vertex;
            int numPoints;
            cout << "输入顶点的数量： ";
            cin >> numPoints;
            while (vertex.size() < numPoints) {
                MOUSEMSG msg1 = GetMouseMsg();

                if (msg1.uMsg == WM_LBUTTONUP) {
                    double x = msg1.x;
                    double y = msg1.y;
                    cout << x << " " << y << endl;
                    vertex.push_back(std::make_pair(x, y));
                }
            }
            MyPoly* poly = new MyPoly(vertex, LIGHTGREEN);
            app->objList.Append(poly);
            env["Mode"] = 0;
        }

        //绘制曲线
        if (env["Mode"] == 4) {
            cout << "绘制曲线" << endl << "1.de Casteljau算法" << endl << "2.B样条" << endl;
            int key;
            cin >> key;
            if (key == 1) {
                vector<std::pair<double, double>> controlPoints;
                int numPoints;
                cout << "输入控制点的数量： ";
                cin >> numPoints;
                while (controlPoints.size() < numPoints) {
                    MOUSEMSG msg1 = GetMouseMsg();

                    if (msg1.uMsg == WM_LBUTTONUP) {
                        double x = msg1.x;
                        double y = msg1.y;
                        cout << x << " " << y << endl;
                        controlPoints.push_back(std::make_pair(x, y));
                    }
                }

                MyBezier* bezier = new MyBezier(controlPoints);
                app->objList.Append(bezier);

            }

            else if (key == 2) {
                vector<std::pair<double, double>> controlPoints;
                int numPoints;
                cout << "输入控制点的数量： ";
                cin >> numPoints;
                while (controlPoints.size() < numPoints) {
                    MOUSEMSG msg1 = GetMouseMsg();
                    if (msg1.uMsg == WM_LBUTTONUP) {
                        double x = msg1.x;
                        double y = msg1.y;
                        cout << x << " " << y << endl;
                        controlPoints.push_back(std::make_pair(x, y));
                    }
                }
                std::vector<double> knots = { 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8 };
                int degree = 3;
                MyBspline* bspline = new MyBspline(controlPoints, knots, degree, LIGHTBLUE);
              
                app->objList.Append(bspline);
            }
            env["Mode"] = 0;
        }

        //裁剪
        if (env["Mode"] == 5) {
            cout << "裁切" << endl << "1.cs裁切算法" << endl << "2.中点裁切算法" << endl << "3.凸多边形的窗口裁切" << endl;;
            int key;
            cin >> key;
            if (key == 1) {
                double x1, y1, x2, y2;
                bool isSelecting = true;
                while (isSelecting) {
                    MOUSEMSG msg1 = GetMouseMsg();
                    if (msg1.uMsg == WM_LBUTTONDOWN) {
                        x1 = msg1.x;
                        y1 = msg1.y;
                        cout << "起始点：" << x1 << ", " << y1 << endl;
                    }
                    if (msg1.uMsg == WM_LBUTTONUP) {
                        x2 = msg1.x;
                        y2 = msg1.y;
                        cout << "结束点：" << x2 << ", " << y2 << endl;
                        isSelecting = false;
                    }
                }
                // 遍历objList并裁切对象
                for (int i = 0; i < app->objList.get_count(); ++i) {
                    ObjWrapper* obj = app->objList[i];
                    if (dynamic_cast<MyLine*>(obj) != nullptr) {
                        MyLine* line = dynamic_cast<MyLine*>(obj);
                        line->CS_clip(x1, y1, x2, y2);
                    }
                }
            }

            else if (key == 2) {
                double x1, y1, x2, y2;
                bool isSelecting = true;
                while (isSelecting) {
                    MOUSEMSG msg1 = GetMouseMsg();
                    if (msg1.uMsg == WM_LBUTTONDOWN) {
                        x1 = msg1.x;
                        y1 = msg1.y;
                        cout << "起始点：" << x1 << ", " << y1 << endl;
                    }
                    if (msg1.uMsg == WM_LBUTTONUP) {
                        x2 = msg1.x;
                        y2 = msg1.y;
                        cout << "结束点：" << x2 << ", " << y2 << endl;
                        isSelecting = false;
                    }
                }
                // 遍历objList并裁切对象
                for (int i = 0; i < app->objList.get_count(); ++i) {
                    ObjWrapper* obj = app->objList[i];
                    if (dynamic_cast<MyLine*>(obj) != nullptr) {
                        MyLine* line = dynamic_cast<MyLine*>(obj);
                        line->CS_clip(x1, y1, x2, y2);
                    }
                }
            }
            else if (key == 3)
            {
                vector<std::pair<double, double>> controlPoints;
                int numPoints;
                cout << "输入控制点的数量： ";
                cin >> numPoints;
                while (controlPoints.size() < numPoints) {
                    MOUSEMSG msg1 = GetMouseMsg();
                    if (msg1.uMsg == WM_LBUTTONUP) {
                        double x = msg1.x;
                        double y = msg1.y;
                        cout << x << " " << y << endl;
                        controlPoints.push_back(std::make_pair(x, y));
                    }
                }
                for (int i = 0; i < app->objList.get_count(); ++i) {
                    ObjWrapper* obj = app->objList[i];
                    if (dynamic_cast<MyPoly*>(obj) != nullptr) {
                        MyPoly* poly = dynamic_cast<MyPoly*>(obj);
                        poly->sutherlandHodgmanClip(controlPoints);
                    }
                }
            }
            env["Mode"] = 0;
        }

        if (env["Mode"] == 6) {
            int x1, x2, y1, y2, startangle, endangle;
            double r;
            cout << "绘制弧形" << endl;
            cout << "输入起始角度   结束角度" << endl;
            cin >> startangle >> endangle;
            bool isDrawing = true;
            while (isDrawing) {
                MOUSEMSG msg1 = GetMouseMsg();
                if (msg1.uMsg == WM_LBUTTONDOWN) {
                    x1 = msg1.x;
                    y1 = msg1.y;
                }
                if (msg1.uMsg == WM_LBUTTONUP) {
                    x2 = msg1.x;
                    y2 = msg1.y;
                    r = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                    int color = RED;
                    MyArc* arc = new MyArc(x1, y1, r, RED, startangle, endangle);
                    app->objList.Append(arc);
                    isDrawing = false;

                    break;
                }
            }
            env["Mode"] = 0;
        }

        if (env["Mode"] == 7) {
            cout << "填充" << endl << "1.扫描线填充" << endl << "2.种子填充" << endl;
            int key;
            cin >> key;
            if (key == 1) {
                for (int i = 0; i < app->objList.get_count(); ++i) {
                    ObjWrapper* obj = app->objList[i];
                    if (dynamic_cast<MyPoly*>(obj) != nullptr) {
                        MyPoly* poly = dynamic_cast<MyPoly*>(obj);
                        poly->scanFill();
                    }
                }
            }
            else if (key == 2) {
                bool isFilling = 1;
                while (isFilling) {
                    MOUSEMSG msg1 = GetMouseMsg();
                    if (msg1.uMsg == WM_LBUTTONUP) {
                        double x = msg1.x;
                        double y = msg1.y;
                        for (int i = 0; i < app->objList.get_count(); ++i) {
                            ObjWrapper* obj = app->objList[i];
                            if (dynamic_cast<MyPoly*>(obj) != nullptr) {
                                MyPoly* poly = dynamic_cast<MyPoly*>(obj);
                                poly->SeedFill(x, y, LIGHTBLUE);
                            }
                            isFilling = false;
                        }
                    }

                }
            }
            env["Mode"] = 0;
        }

        if (env["Mode"] == 8) {
            cout << "输入光源位置" << endl;
            float x, y, z;
            cin >> x >> y >> z;
            MyPhong* phong = new MyPhong(100, x, y, z);
            app->objList.Append(phong);
            env["Mode"] = 0;
        }

        if (env["Mode"] == 9) {
            vector<std::pair<double, double>> controlPoints;
            int numPoints;
            int key;
            cin >> key;
            cout << "需要更改的控制点数量" << endl << "1.贝塞尔曲线" << "2.B样条" << endl;
            if (key == 1) {
                cout << "需要更改的控制点数量" << endl;
                int count = 0;
                cin >> numPoints;
                while (count < numPoints) {
                    MOUSEMSG msg1 = GetMouseMsg();
                    if (msg1.uMsg == WM_LBUTTONUP) {
                        double x = msg1.x;
                        double y = msg1.y;
                        for (int i = 0; i < app->objList.get_count(); ++i) {
                            ObjWrapper* obj = app->objList[i];
                            if (dynamic_cast<MyBezier*>(obj) != nullptr) {
                                MyBezier* bezier = dynamic_cast<MyBezier*>(obj);
                                bezier->handleMouseDown(x, y);
                            }
                        }
                        count++;
                    }
                }
            }
            else if (key == 2)
            {
                cout << "需要更改的控制点数量" << endl;
                int count = 0;
                cin >> numPoints;
                while (count < numPoints) {
                    MOUSEMSG msg1 = GetMouseMsg();
                    if (msg1.uMsg == WM_LBUTTONUP) {
                        double x = msg1.x;
                        double y = msg1.y;
                        for (int i = 0; i < app->objList.get_count(); ++i) {
                            ObjWrapper* obj = app->objList[i];
                            if (dynamic_cast<MyBezier*>(obj) != nullptr) {
                                MyBspline* bspline = dynamic_cast<MyBspline*>(obj);
                                bspline->handleMouseDown(x, y);
                            }
                        }
                        count++;
                    }
                }
            }
            env["Mode"] = 0;
        }

        
        return 0;    
    };
	app.Run();
	return 0;
}


