#ifndef __APPLICATIONROOT__
#define __APPLICATIONROOT__
#define SHOW_CONSOLE 
#include <iostream>
#include <functional>
#include <vector>
#include <thread>
#include <algorithm>
#include <utility>
#include <graphics.h>
#include "ResourcePool.h"
#include <cmath>
#include <chrono>
#include <map>



class Pixel {
public:
    Pixel(int x, int y, int color) :x(x), y(y), color(color) {}
    int x, y, color;
};

class Frame {
public:
    int Width, Height;
    std::vector<std::vector<int>> indices;
    std::vector<std::vector<int>> pixels;
    Frame(int width, int height) : Width(width), Height(height) {
        pixels.resize(height, std::vector<int>(width, WHITE));
        indices.resize(height, std::vector<int>(width, -1));
    }
};

//所有可绘制的对象都继承ObjWrapper
class ObjWrapper {
public:
    bool Rigid;
    int z_depth;
    ObjWrapper() : z_depth(0), index(-1), Rigid(FALSE) {}
    virtual void plan() {};
    std::vector<Pixel> Points;
    int index;

    void move(int x, int y) {
        for (auto& p : Points) {
            p.x += x;
            p.y += y;
        }
    }

    void rotate(int c_x, int c_y, double angle) {
        this->move(-c_x, -c_y);
        auto _cos = cos(angle);
        auto _sin = sin(angle);
        for (auto& p : this->Points) {
            auto x = p.x;
            auto y = p.y;
            p.x = (int)(_cos * x - _sin * y);
            p.y = (int)(_sin * x + _cos * y);
        }
        this->move(c_x, c_y);
    }

    void zoom(double scaleFactor) {
        std::vector<std::vector<int>> inputImage;
        inputImage.resize(1080, std::vector<int>(1920, -1));
        int min_x = 99999, max_x = 0, min_y = 99999, max_y = 0;
        for (auto p : this->Points) {
            inputImage[p.y][p.x] = p.color;
            min_x = (p.x > min_x) ? min_x : p.x;
            min_y = (p.y > min_y) ? min_y : p.y;
            max_x = (p.x > max_x) ? p.x : max_x;
            max_y = (p.y > max_y) ? p.y : max_y;
        }
        int srcWidth = max_x - min_x + 1;
        int srcHeight = max_y - min_y + 1;
        std::vector<std::vector<int>> srcImage;
        srcImage.resize(srcHeight, std::vector<int>(srcWidth, -1));
        for (int y = 0; y < srcHeight; ++y) {
            for (int x = 0; x < srcWidth; ++x) {
                srcImage[y][x] = inputImage[y + min_y][x + min_x];
            }
        }
        int destWidth = static_cast<int>(srcWidth * scaleFactor);
        int destHeight = static_cast<int>(srcHeight * scaleFactor);
        std::vector<std::vector<int>> destImage;
        destImage.resize(destHeight, std::vector<int>(destWidth, -1));

        for (int y = 0; y < destHeight; ++y) {
            for (int x = 0; x < destWidth; ++x) {
                float srcX = x / scaleFactor;
                float srcY = y / scaleFactor;

                int x0 = static_cast<int>(srcX);
                int y0 = static_cast<int>(srcY);
                int x1 = (x0 + 1);
                int y1 = (y0 + 1);

                float alpha = srcX - x0;
                float beta = srcY - y0;

                // 使用双线性插值计算颜色值
                int color00 = srcImage[y0][x0];
                int color01 = srcImage[y0][x1];
                int color10 = srcImage[y1][x0];
                int color11 = srcImage[y1][x1];

                int color = (1 - alpha) * (1 - beta) * color00 + alpha * (1 - beta) * color01 +
                    (1 - alpha) * beta * color10 + alpha * beta * color11;

                destImage[y][x] = color;
            }
        }

        this->Points.clear();
        for (int y = 0; y < destHeight; ++y) {
            for (int x = 0; x < destWidth; ++x) {
                if (destImage[y][x] != -1)
                    this->Points.push_back(Pixel(x + min_x, y + min_y, destImage[y][x]));
            }
        }
    }


    void get_gravity_center(int& x, int& y) {
        int sumx = 0, sumy = 0, count = 0;
        for (auto p : this->Points) {
            sumx += p.x;
            sumy += p.y;
            count++;
        }
        x = sumx / count;
        y = sumy / count;
    }
};

// 用一个资源池来为入队的obj分配index
class ObjList {
public:
    int get_count() {
        return this->count;
    }

    ObjList() :count(0), size(1000) {
        p_pool = new ResourcePool<ObjWrapper*>(size);
    }

    ObjWrapper* operator[](int index) {
        return p_pool->operator[](index);
    }

    void Append(ObjWrapper* obj) {
        obj->plan();
        int index = p_pool->allocate();
        p_pool->set(index, obj);
        obj->index = index;
        count++;
    }

    void Pop(int index) {
        delete p_pool->operator[](index);
        p_pool->deallocate(index);
        count--;
    }

private:
    int count;
    int size;
    ResourcePool<ObjWrapper*>* p_pool;

};

class Force
{
public:
    int x, y, N;
    Force(int x, int y, int N) :x(x), y(y), N(N) {}
    // 重载+运算符来合成两个力
    Force operator+(const Force& other) const
    {
        double k1 = y / x;
        double k2 = other.y / other.x;
        double _tan = abs((k1 - k2) / (1 + k1 * k2));;
        double _cos = 1 / (1 + _tan * _tan);
        int Fn = N * N + other.N * other.N + 2 * N * other.N * _cos;
        return Force(x + other.x, y + other.y, Fn);
    }

};

class ApplicationRoot {
public:
    int Width, Height;
    Frame* CurrentFrame;
    Frame* BackFrame;
    ObjList objList;
    ApplicationRoot(const int width, const int height) : Width(width), Height(height) {
        CurrentFrame = new Frame(width, height);
        BackFrame = new Frame(width, height);
    }

    std::function<int(ApplicationRoot*, std::map<std::string, int>& env, const Frame* const CurrentFrame)> mainfunction;

    void Run() {
        // 初始化绘图环境
        initgraph(Width, Height);
        setbkcolor(WHITE);
        setcolor(BLACK);
        line(1, 1, 1160, 1); line(1, 60, 1160, 60);
        setcolor(BLACK);
        setfont(12, 15, L"黑体");

        line(1, 1, 1, 60); outtextrect(10, 20, 50, 50, L"直线"); line(60, 1, 60, 60);
        outtextrect(70, 20, 50, 50, L"圆形"); line(120, 1, 120, 60);
        outtextrect(130, 25, 90, 50, L"多边形"); line(220, 1, 220, 60);
        outtextrect(230, 20, 50, 50, L"曲线"); line(290, 1, 290, 60);
        outtextrect(300, 20, 50, 50, L"裁剪"); line(360, 1, 360, 60);
        outtextrect(370, 20, 50, 50, L"圆弧"); line(430, 1, 430, 60);
        outtextrect(440, 20, 50, 50, L"填充"); line(500, 1, 500, 60);
        outtextrect(510, 20, 50, 50, L"光照"); line(570, 1, 570, 60);
        outtextrect(580, 25, 90, 50, L"控制点"); line(680, 1, 680, 60);

        outtextrect(690, 20, 50, 50, L"拖拽"); line(740, 1, 740, 60);
        outtextrect(750, 20, 100, 50, L"重心旋转"); line(860, 1, 860, 60);
        outtextrect(870, 20, 100, 50, L"选择中心"); line(980, 1, 980, 60);
        outtextrect(990, 20, 100, 50, L"定点旋转"); line(1100, 1, 1100, 60);
        outtextrect(1110, 20, 50, 50, L"缩放"); line(1160, 1, 1160, 60);

        std::map<std::string, int> env;
        long long frame_count = 0;

        Frame** p = &CurrentFrame;

        // 绘制当前 CurrentFrame
        std::thread mythread(&ApplicationRoot::DisplayFrame, this, p);
        mythread.detach();

        while (TRUE) {
            //std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
            // 运行主函数，生成需要绘制的图形元素并添加到objList中
            mainfunction(this, env, CurrentFrame);
            Update_Physics();
            RenderFrame(BackFrame);

            std::swap(CurrentFrame, BackFrame);
            p = &CurrentFrame;
            //std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
            // 计算时间间隔，精确到毫秒
            //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            //if (duration < std::chrono:: milliseconds(33) && duration>std::chrono::milliseconds(5)) {
            //    std::this_thread::sleep_for(std::chrono::milliseconds(std::chrono::milliseconds(33)-duration));
            //}


        }
    }


private:
    long long render_count = 0;

    void DisplayFrame(Frame** frame) {
        while (TRUE) {
            std::this_thread::sleep_for(std::chrono::milliseconds(33));
            // 遍历 objList，绘制每个图形元素
            for (int y = 61; y < (*frame)->Height; y++) {
                for (int x = 0; x < (*frame)->Width; x++) {
                    //DRAW PIXEL
                    putpixel(x, y, (*frame)->pixels[y][x]);
                }
            }
        }
    }

    void RenderFrame(Frame* frame) {
        // 清空像素
        for (int y = 61; y < frame->Height; y++) {
            for (int x = 0; x < frame->Width; x++) {
                frame->pixels[y][x] = WHITE;
                frame->indices[y][x] = -1;
            }
        }

        for (int i = 0; i < objList.get_count(); i++) {
            ObjWrapper* obj = objList[i];
            for (auto p : obj->Points) {
                if (p.x < 0 || p.x >= Width || p.y < 0 || p.y >= Height) {
                    continue;
                }
                auto pixel_on_canvas_depth = 0x7fffffff;
                if (frame->indices[p.y][p.x] >= 0) {
                    auto pixel_on_canvas_depth = objList[frame->indices[p.y][p.x]]->z_depth;
                }
                auto current_depth = obj->z_depth;
                if (current_depth <= pixel_on_canvas_depth) {
                    frame->pixels[p.y][p.x] = p.color;
                    frame->indices[p.y][p.x] = obj->index;
                }
            }
        }
    }

    std::vector<std::pair<int, Force>> Indices_of_Rigid_Body;

    void Update_Physics() {
        //根据力更新位置
        for (auto body : Indices_of_Rigid_Body) {
            auto index = body.first;
            auto f = body.second;
            double portion = sqrt((f.N * f.N) / (f.x * f.x + f.y * f.y));
            this->objList[index]->move(int(portion * f.x), int(portion * f.y));
        }
    }

};

/*
有一个N*N的二维数组，
有一个元素列表：
{
    index ：[点集[pixels（x,y,color),...] ， z值] ,
    ...,
    ...,
    ...
}
顺序输入列表所有元素，要求z小的覆盖z大的，求最终的color平面
*/

#endif // !__APPLICATIONROOT__