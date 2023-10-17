#include"MyPoly.h"

std::vector<Pixel> MyPoly:: drawPolygon() {
    std::vector<Pixel> buffer;
    for (size_t i = 0; i < vertex_.size(); ++i) {
        int x0 = static_cast<int>(vertex_[i].first);
        int y0 = static_cast<int>(vertex_[i].second);
        int x1 = static_cast<int>(vertex_[(i + 1) % vertex_.size()].first); 
        int y1 = static_cast<int>(vertex_[(i + 1) % vertex_.size()].second);
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

bool MyPoly::isInsidePolygon(int x, int y) {
    int intersectCount = 0;
    for (size_t i = 0; i < vertex_.size(); ++i) {
        int x1 = static_cast<int>(vertex_[i].first);
        int y1 = static_cast<int>(vertex_[i].second);
        int x2 = static_cast<int>(vertex_[(i + 1) % vertex_.size()].first);
        int y2 = static_cast<int>(vertex_[(i + 1) % vertex_.size()].second);

        // 检查边与射线的交点
        if (((y1 <= y && y < y2) || (y2 <= y && y < y1)) &&
            (x < (x2 - x1) * (y - y1) / (y2 - y1) + x1)) {
            intersectCount++;
        }
    }
    // 如果交点数为奇数，则点在多边形内部
    return (intersectCount % 2 == 1);
}

void MyPoly::SeedFill(int startX, int startY, int fillColor) {
    std::vector<Pixel> buffer;
    int minY = INT_MAX;
    int maxY = INT_MIN;
    color_ = LIGHTBLUE;
    for (const auto& vertex : vertex_) {
        int y = static_cast<int>(vertex.second);
        minY = min(minY, y);
        maxY = max(maxY, y);
    }
    //扫描填充算法
    for (int y = minY; y <= maxY; ++y) {
        std::vector<int> intersections;

        // 遍历边
        for (size_t i = 0; i < vertex_.size(); ++i) {
            int x0 = static_cast<int>(vertex_[i].first);
            int y0 = static_cast<int>(vertex_[i].second);
            int x1 = static_cast<int>(vertex_[(i + 1) % vertex_.size()].first);
            int y1 = static_cast<int>(vertex_[(i + 1) % vertex_.size()].second);

            // 检查扫描线和边
            if ((y0 <= y && y1 > y) || (y1 <= y && y0 > y)) {
                int x = static_cast<int>((static_cast<double>(y - y0) / (y1 - y0)) * (x1 - x0) + x0);
                intersections.push_back(x);
            }
        }
        std::sort(intersections.begin(), intersections.end());
        for (size_t i = 0; i < intersections.size(); i += 2) {
            int startX = intersections[i];
            int endX = intersections[i + 1];
            for (int x = startX; x <= endX; ++x) {
                buffer.push_back(Pixel(x, y, this->color_));
            }
        }
    }
    ObjWrapper::Points = buffer;
}

void MyPoly::scanFill() {
    std::vector<Pixel> buffer;
    int minY = INT_MAX;
    int maxY = INT_MIN;
    color_ = LIGHTRED;
    for (const auto& vertex : vertex_) {
        int y = static_cast<int>(vertex.second);
        minY = min(minY, y);
        maxY = max(maxY, y);
    }
    //扫描填充算法
    for (int y = minY; y <= maxY; ++y) {
        std::vector<int> intersections;

        // 遍历边
        for (size_t i = 0; i < vertex_.size(); ++i) {
            int x0 = static_cast<int>(vertex_[i].first);
            int y0 = static_cast<int>(vertex_[i].second);
            int x1 = static_cast<int>(vertex_[(i + 1) % vertex_.size()].first);
            int y1 = static_cast<int>(vertex_[(i + 1) % vertex_.size()].second);

            // 检查扫描线和边
            if ((y0 <= y && y1 > y) || (y1 <= y && y0 > y)) {
                int x = static_cast<int>((static_cast<double>(y - y0) / (y1 - y0)) * (x1 - x0) + x0);
                intersections.push_back(x);
            }
        }
        std::sort(intersections.begin(), intersections.end());
        for (size_t i = 0; i < intersections.size(); i += 2) {
            int startX = intersections[i];
            int endX = intersections[i + 1];
            for (int x = startX; x <= endX; ++x) {
                buffer.push_back(Pixel(x, y, this->color_));
            }
        }
    }
    ObjWrapper::Points = buffer;
}

void MyPoly::plan() {
    ObjWrapper::Points = this->drawPolygon();
}

