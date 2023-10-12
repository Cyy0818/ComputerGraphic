#ifndef DISPLAY_H
#define DISPLAY_H
#define SHOW_CONSOLE 
#include <stack>
#include<graphics.h>
template <typename T>
class Display {
public:
    void Push(const T& obj) {
        Objstack.push(obj);
    }

    void Pop() {
        if (!Objstack.empty()) {
            Objstack.pop();
        }
    }

    void init_screen()
    {
        initgraph(1920, 1080);
        line(1, 1, 1, 80); line(1, 1, 960, 1); line(1, 80, 960, 80); line(240, 1, 240, 80); line(480, 1, 480, 80); line(720, 1, 720, 80); line(960, 1, 960, 80);
        setbkcolor(WHITE);
        setcolor(BLACK);                //设置字体颜色为白色
        setfont(40, 20, L"宋体");       //EASYX:多字节字符集下不带L，UNICODE字符集下带L  EGE：未知
        outtextxy(80, 20, L"line"); outtextxy(300, 20, L"circle"); outtextxy(510, 20, L"fillcolor"); outtextxy(800, 20, L"exit");
        //EGE：xyprintf(80, 20, L"line");xyprintf(300, 20, L"circle");xyprintf(510, 20, L"fillcolor");xyprintf(800, 20, L"exit");

    }

    void DrawAll() {
        init_screen();
        std::stack<T> tempStack;
        while (!Objstack.empty()) {
            T obj = Objstack.top();
            obj.Drawobj(); 
            tempStack.push(obj);
            Objstack.pop();
        }
        while (!tempStack.empty()) {
            T obj = tempStack.top();
            Objstack.push(obj);
            tempStack.pop();
        }

        delay(100);
    }

private:
    std::stack<T> Objstack;
};

#endif // DISPLAY_H
