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
    void Drawobj() {
        if (isCircle_) {
            circle_.Draws();
        }
        else if (isLine_) {
            line_.Draws();
        }
        else if (isPoly_) {
            poly_.Draws();
        }
      
    }

private:
    MyCircle circle_;
    MyLine line_;
    MyPoly poly_;
    bool isCircle_;
    bool isLine_;
    bool isPoly_;
};
