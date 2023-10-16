#include"MyPoly.h"


void MyPoly::inputVertices() {
    std::cout << "输入多边形的顶点数 ";
    std::cin >> this->num;
    this->ver = new vertex[num];
    std::cout << "输入多边形的顶点位置（x,y)" << std::endl;
    for (int i = 0; i < num; i++) {
        std::cout << "顶点 " << i + 1 << ": ";
        std::cin >> this->ver[i].x >> this->ver[i].y;
    }
}

void MyPoly:: drawPolygon() {
    for (int i = 0; i < num; i++) {
        line(ver[i].x, ver[i].y, ver[(i + 1) % num].x, ver[(i + 1) % num].y);
    }
}

void MyPoly:: scanlineFill() {
    int maxY = 0;
    for (int i = 0; i < num; i++) {
        if (ver[i].y > maxY) {
            maxY = ver[i].y;
        }
    }

    for (int y = 0; y < maxY; y++) {
        int nodes = 0;
        int xNodes[1000];
        for (int i = 0; i < num; i++) {
            int y1 = ver[i].y;
            int y2 = ver[(i + 1) % num].y;
            int x1 = ver[i].x;
            int x2 = ver[(i + 1) % num].x;

            if ((y1 < y2 && y <= y2 && y > y1) || (y1 > y2 && y <= y1 && y > y2)) {
                xNodes[nodes++] = static_cast<int>(x1 + (x2 - x1) * (y - y1) / (y2 - y1));
            }
        }

        // Sort xNodes to get pairs of intersections
        for (int i = 0; i < nodes - 1; i += 2) {
            for (int j = 0; j < nodes - i - 2; j += 2) {
                if (xNodes[j] > xNodes[j + 2]) {
                    std::swap(xNodes[j], xNodes[j + 2]);
                    std::swap(xNodes[j + 1], xNodes[j + 3]);
                }
            }
        }

        // Fill the pixels between pairs of intersections
        for (int i = 0; i < nodes; i += 2) {
            for (int j = xNodes[i]; j < xNodes[i + 1]; j++) {
                putpixel(j, y, color_);
            }
        }
    }
}

void MyPoly::Draws() {
    this->drawPolygon();
    this->scanlineFill();
}