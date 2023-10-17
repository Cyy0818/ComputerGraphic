#include"MyBspline.h"

double MyBspline:: basisFunction(int i, int k, double t) {
    if (k == 1) {
        return (knots_[i] <= t && t < knots_[i + 1]) ? 1.0 : 0.0;
    }
    else {
        double denom1 = knots_[i + k - 1] - knots_[i];
        double denom2 = knots_[i + k] - knots_[i + 1];
        double result = 0;
        if (denom1 != 0) {
            result += (t - knots_[i]) / denom1 * basisFunction(i, k - 1, t);
        }
        if (denom2 != 0) {
            result += (knots_[i + k] - t) / denom2 * basisFunction(i + 1, k - 1, t);
        }
        return result;
    }
}
std::vector<Pixel> MyBspline::Draws() {
    std::vector<Pixel> buffer;

    int numPoints = 1000;
    for (int i = 0; i < numPoints; ++i) {
        double t = knots_[degree_] + (knots_[controlPoints_.size()] - knots_[degree_]) * i / (numPoints - 1);
        std::pair<double, double> point = this->calculateBsplinePoint(t);
        std::cout << "Point at t=" << t << ": (" << point.first << ", " << point.second << ")\n";
        buffer.push_back(Pixel(int(point.first), int(point.second), color_));
    }
    bool firstPoint = true;  // 用于判断曲线的起点
    for (size_t i = 0; i < controlPoints_.size() - 1; ++i) {
        int x0 = static_cast<int>(controlPoints_[i].first);
        int y0 = static_cast<int>(controlPoints_[i].second);
        int x1 = static_cast<int>(controlPoints_[i + 1].first);
        int y1 = static_cast<int>(controlPoints_[i + 1].second);

        // 使用Bresenham算法生成整数点并加入buffer
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            if (firstPoint) {
                buffer.push_back(Pixel(x0, y0, LIGHTGREEN));
                firstPoint = false;
            }
            else {
                buffer.push_back(Pixel(x0, y0, LIGHTGREEN));
            }

            if (x0 == x1 && y0 == y1) {
                break;
            }

            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y0 += sy;
            }
        }
    }

    return buffer;
}


void MyBspline:: plan() {
    ObjWrapper::Points = Draws();
}
std::pair<double, double> MyBspline::calculateBsplinePoint(double t) {
    double x = 0, y = 0;
    for (size_t i = 0; i < controlPoints_.size(); ++i) {
        double basis = basisFunction(i, degree_, t);
        x += controlPoints_[i].first * basis;
        y += controlPoints_[i].second * basis;
    }
    return std::make_pair(x, y);
}
