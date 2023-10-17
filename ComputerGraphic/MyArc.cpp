#include"MyArc.h"

std::vector <Pixel> MyArc::DrawArc(int x0, int y0, int radius, double startAngle, double endAngle) {
    const double step = 0.01; // 步长，可以根据需要调整
    std::vector<Pixel> arcPoints;
    startAngle = startAngle * (PI/ 180.0);
    endAngle = endAngle * (PI / 180.0);
    for (double t = startAngle; t <= endAngle; t += step * (PI / 180.0)) {
        int x = static_cast<int>(x0 + radius * cos(t));
        int y = static_cast<int>(y0 + radius * sin(t));
        arcPoints.push_back(Pixel(x, y, color_));
    }
    return arcPoints;
}
void MyArc::plan() {
    ObjWrapper::Points = DrawArc(this->x0_, this->y0_, this->r_,this->startAngle_,this->endAngle_);
}
