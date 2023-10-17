#include <vector>
#include "MyCircle.h"
#include "MyLine.h"
#include "MyPoly.h"
#include"MyBezier.h"
class MyShapeWrapper {
public:
    MyShapeWrapper(MyCircle circle)
        : circle_(circle), isCircle_(true), isLine_(false), isPoly_(false),isBezier_(false) {}
    MyShapeWrapper(MyLine line)
        : line_(line), isCircle_(false), isLine_(true), isPoly_(false),isBezier_(false) {}
    MyShapeWrapper(MyPoly poly)
        : poly_(poly), isCircle_(false), isLine_(false), isPoly_(true), isBezier_(false) {}
    MyShapeWrapper(MyBezier bezier)
        : bezier_(bezier), isCircle_(false), isLine_(false), isPoly_(false), isBezier_(true) {}
    void Drawobj();
    void Move(int x, int y);
    void Rotate(float angle);
    void Set_Color(int color);
    void Zoom(int size);

private:
    MyCircle circle_;
    MyLine line_;
    MyPoly poly_;
    MyBezier bezier_;
    bool isCircle_;
    bool isLine_;
    bool isPoly_;
    bool isBezier_;
};
