#include"MyBezier.h"
void MyBezier :: Draws()
{
    for (double t = 0; t <= 1; t += 0.01) {
        pair<int, int> point = calculatePoint(t);
        putpixel(point.first, point.second, RED);
    }
}

int MyBezier::binomialCoefficient(int n,int k) {
    if (k == 0 || k == n) {
        return 1;
    }
    int result = 1;
    for (int i = 1; i <= k; ++i) {
        result = result * (n - i + 1) / i;
    }
    return result;
}
pair<double, double> MyBezier :: calculatePoint(double t) {
    double x = 0, y = 0;
    int n = controlPoints_.size() - 1;

    // ¼ÆËãBernstein»ùº¯Êý
    for (int i = 0; i <= n; ++i) {
        double coef = binomialCoefficient(n, i) * pow(1 - t, n - i) * pow(t, i);
        x += coef * controlPoints_[i].first;
        y += coef * controlPoints_[i].second;
    }

    return make_pair(x, y);
}