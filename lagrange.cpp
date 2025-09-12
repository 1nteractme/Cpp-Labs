#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

double lagrange(const double xx, const double *x, const double *y, const int n) {
    double result(0);

    for (int i = 0; i < n; i++) {
        double k = 1;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            k *= xx - x[j];
            k /= x[i] - x[j];
        }

        result += y[i] * k;
    }

    return result;
}

double f() {
    return f();
}

int main() {
    const int n = 10;
    const double s = 0;
    const double e = 1;
    const auto step = (e - s) / (n - 1);

    auto *x = new double[4];
    x[0] = 0.1;
    x[1] = 0.5;
    x[2] = 0.9;
    x[3] = 2.3;

    auto *y = new double[4];
    y[0] = -2.30259;
    y[1] = -0.69315;
    y[2] = -0.10536;
    y[3] = 0.26236;

    cout << lagrange(0.1, x, y, 4) << endl;
    cout << log(0.1);

    return 0;
}
