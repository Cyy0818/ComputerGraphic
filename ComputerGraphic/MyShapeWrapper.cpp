#include"MyShapeWrapper.h"

void MyShapeWrapper::Drawobj() {
    if (isCircle_) {
        circle_.Draws();
    }
    else if (isLine_) {
        line_.Draws();
    }
    else if (isPoly_) {
        poly_.Draws();
    }
    else if (isBspline_) {
        bspline_.Draws();
    }
}

void MyShapeWrapper::Move(int x, int y) {
    if (isCircle_) {
        circle_.x0_ = 1 * circle_.x0_ + 1 * x;
        circle_.y0_ = 1 * circle_.y0_ + 1 * y;
    }
    else if (isLine_) {
        line_.x1_ = 1 * line_.x1_ + 1 * x;
        line_.x2_ = 1 * line_.x2_ + 1 * x;
        line_.y1_ = 1 * line_.y1_ + 1 * y;
        line_.y2_ = 1 * line_.y2_ + 1 * y;
    }
    else if (isPoly_) {
        for (int i = 0; i < poly_.num; i++) {
            poly_.ver[i].x = 1 * poly_.ver[i].x + 1 * x;
            poly_.ver[i].y = 1 * poly_.ver[i].y + 1 * y;
        }
    }
}

void MyShapeWrapper::Rotate(float angle) {
   
    if (isLine_) {
        int cx, cy;
        cx = round((line_.x1_ + line_.x2_) / 2);
        cy = round((line_.y1_ + line_.y2_) / 2);
        Move(-cx, -cy);
        line_.x1_ = round(cos(angle)) * line_.x1_ - round(sin(angle)) * line_.y1_;
        line_.y1_ = round(sin(angle)) * line_.x1_ + round(cos(angle)) * line_.y1_;
        line_.x2_ = round(cos(angle)) * line_.x2_ - round(sin(angle)) * line_.y2_;
        line_.y2_ = round(sin(angle)) * line_.x2_ + round(cos(angle)) * line_.y2_;
        Move(cx, cy);
    }
    else if (isPoly_) {
        int cx, cy;
        for (int i = 0; i < poly_.num; i++) {
            cx += poly_.ver[i].x;
            cy += poly_.ver[i].y;
        }
        cx = cx / poly_.num;
        cy = cy / poly_.num;
        Move(-cx, -cy);
        for (int i = 0; i < poly_.num; i++) {
            poly_.ver[i].x = round(cos(angle)) * poly_.ver[i].x - round(sin(angle)) * poly_.ver[i].y;
            poly_.ver[i].y = round(sin(angle)) * poly_.ver[i].x + round(cos(angle)) * poly_.ver[i].y;
        }
        Move(cx, cy);
    }
}

void MyShapeWrapper::Set_Color(int color) {
    if (isCircle_)
        circle_.color_ = color;
    else if (isLine_)
        line_.color_ = color;
    else if (isPoly_)
        poly_.color_ = color;
}


void MyShapeWrapper::Zoom(int sizex, int sizey) {
    if (isCircle_)
        circle_.r_ = sizex * circle_.r_;
    else if (isLine_) {
        line_.x1_ = sizex * line_.x1_;
        line_.x2_ = sizex * line_.x2_;
        line_.y1_ = sizex * line_.y1_;
        line_.y2_ = sizex * line_. y2_;


    }
    else if (isPoly_) {
        for (int i = 0; i < poly_.num; i++) {
            poly_.ver[i].x = round(sizex * poly_.ver[i].x);
            poly_.ver[i].y = round(sizey * poly_.ver[i].y);
        }
    }
        

}