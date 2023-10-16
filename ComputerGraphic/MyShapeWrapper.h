#include <vector>
#include "MyCircle.h"
#include "MyLine.h"
#include "MyPoly.h"
class MyShapeWrapper {
public:
    MyShapeWrapper(MyCircle circle)
        : circle_(circle), isCircle_(true), isLine_(false), isPoly_(false) {}
    MyShapeWrapper(MyLine line)
        : line_(line), isCircle_(false), isLine_(true), isPoly_(false) {}
    MyShapeWrapper(MyPoly poly)
        : poly_(poly), isCircle_(false), isLine_(false), isPoly_(true) {}
    void Drawobj();
    void Move(int x, int y);
    void Rotate(float angle);
    void Set_Color(int color);
    void Zoom(int size);

private:
    MyCircle circle_;
    MyLine line_;
    MyPoly poly_;
    bool isCircle_;
    bool isLine_;
    bool isPoly_;
};
