#include "MyBezier.h"

std::vector<Pixel> MyBezier::Draws() {
    std::vector<Pixel> buffer;

    // 计算贝塞尔曲线上的所有点，包括控制多边形上的点和曲线上的点
    for (double t = 0; t <= 1; t += 0.0001) {
        std::pair<int, int> point = deCasteljau(t);
        buffer.push_back(Pixel(point.first, point.second, this->color_));
    }

    // 绘制贝塞尔曲线的控制多边形上的所有整数点
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
            buffer.push_back(Pixel(x0, y0, this->color_));
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




void MyBezier::plan() {
    
    ObjWrapper::Points = Draws();
}

std::pair<double, double> MyBezier::deCasteljau(double t) {
    std::vector<std::pair<double, double>> points = controlPoints_;
    while (points.size() > 1) {
        std::vector<std::pair<double, double>> newPoints;
        for (size_t i = 0; i < points.size() - 1; ++i) {
            double x = (1 - t) * points[i].first + t * points[i + 1].first;
            double y = (1 - t) * points[i].second + t * points[i + 1].second;
            newPoints.emplace_back(x, y);
        }
     
        points = newPoints;
    }

    return points.front();
}


int MyBezier::binomialCoefficient(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    }
    int result = 1;
    for (int i = 1; i <= k; ++i) {
        result = result * (n - i + 1) / i;
    }
    return result;
}
