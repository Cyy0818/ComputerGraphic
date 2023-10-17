#define SHOW_CONSOLE
#include<iostream>
#include <algorithm>
#include"ApplicationRoot.h"
#include<vector>
#include<stack>
#include <bitset>
#include<queue>
using namespace std;
class MyPoly: public ObjWrapper
{
public:
    MyPoly() :vertex_(), color_(0) {};
    MyPoly(std::vector<std::pair<double, double>> vertex, int color) : vertex_(vertex), color_(color) {};
    std::vector<Pixel> drawPolygon();
    void scanFill();//扫描填充
    void SeedFill(int x, int y, int fillColor);
    void plan();
    bool isInsidePolygon(int x, int y);
    void sutherlandHodgmanClip(const std::vector<std::pair<double, double>>& clipPolygon) {
        std::vector<std::pair<double, double>> resultVertices = vertex_;

        for (size_t i = 0; i < clipPolygon.size(); ++i) {
            size_t clipEdgeStart = i;
            size_t clipEdgeEnd = (i + 1) % clipPolygon.size();

            std::vector<std::pair<double, double>> inputVertices = resultVertices;
            resultVertices.clear();

            std::pair<double, double> clipEdgeStartPoint = clipPolygon[clipEdgeStart];
            std::pair<double, double> clipEdgeEndPoint = clipPolygon[clipEdgeEnd];

            for (size_t j = 0; j < inputVertices.size(); ++j) {
                std::pair<double, double> currentVertex = inputVertices[j];
                std::pair<double, double> nextVertex = inputVertices[(j + 1) % inputVertices.size()];

                if (isInside(clipEdgeStartPoint, clipEdgeEndPoint, nextVertex)) {
                    if (!isInside(clipEdgeStartPoint, clipEdgeEndPoint, currentVertex)) {
                        // 计算交点并添加到结果中
                        std::pair<double, double> intersectionPoint = computeIntersection(clipEdgeStartPoint, clipEdgeEndPoint, currentVertex, nextVertex);
                        resultVertices.push_back(intersectionPoint);
                    }
                    resultVertices.push_back(nextVertex);
                }
                else if (isInside(clipEdgeStartPoint, clipEdgeEndPoint, currentVertex)) {
                    // 计算交点并添加到结果中
                    std::pair<double, double> intersectionPoint = computeIntersection(clipEdgeStartPoint, clipEdgeEndPoint, currentVertex, nextVertex);
                    resultVertices.push_back(intersectionPoint);
                }
            }
        }

        vertex_ = resultVertices;
        ObjWrapper::Points.clear();
        ObjWrapper::Points=drawPolygon();
        SeedFill(1,1,1);

    }

private:
    int color_;
    std::vector<std::pair<double, double>> vertex_;
    bool isInside(const std::pair<double, double>& clipEdgeStart, const std::pair<double, double>& clipEdgeEnd, const std::pair<double, double>& vertex) {
        
        double crossProduct = (clipEdgeEnd.first - clipEdgeStart.first) * (vertex.second - clipEdgeStart.second) -
            (clipEdgeEnd.second - clipEdgeStart.second) * (vertex.first - clipEdgeStart.first);
        return crossProduct >= 0;
    }

    std::pair<double, double> computeIntersection(const std::pair<double, double>& clipEdgeStart, const std::pair<double, double>& clipEdgeEnd,
        const std::pair<double, double>& vertex1, const std::pair<double, double>& vertex2) {
        // 计算交点
        double x1 = vertex1.first, y1 = vertex1.second;
        double x2 = vertex2.first, y2 = vertex2.second;
        double x3 = clipEdgeStart.first, y3 = clipEdgeStart.second;
        double x4 = clipEdgeEnd.first, y4 = clipEdgeEnd.second;
        cout << x1 << " " << x2 << " " << x3 << " " << x4 << endl;
        double intersectionX = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) /
            ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
        double intersectionY = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) /
            ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

        return std::make_pair(intersectionX, intersectionY);
    }
};