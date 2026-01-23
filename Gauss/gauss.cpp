#include <iomanip>
#include <iostream>

///
/// @return FUNCTION
double f(const double x) {
    return x * sin(1 / x);
}

///
/// @fun FACTORIAL_FUNCTION
double factorial(const long num) {
    auto res = 1;

    for (int n = 1; n <= num; n++)
        res *= n;

    return res;
}

///
/// @fun SOCHETANIYE BEZ POVTORENIY (KONECHNIYE RAZNOSTI)
double C(const int k, const int n) {
    auto res = 1;

    for (int p = k + 1; p <= n; p++)
        res *= p;

    for (int p = 1; p <= n - k; p++)
        res /= p;

    return res;
}

///
/// @return INTERPOLATED_GAUSSIAN_METHOD_WITH_C_(IMPROVED_FIRST_NEWTON)
double gaussian_method(const double x, const double start, const double end, const int n) {
    const double step = (end - start) / (n - 1.0);
    double res = f(start + step * 0);

    for (int i = 1; i <= n; i++) {
        double k = 1;

        for (int j = 0; j < i; j++)
            k *= x - (start + step * j);

        const int kf = i;
        double resf = 0;

        for (int jf = 0; jf <= kf; jf++) {
            constexpr int iF = 0;
            resf += pow((-1), jf) * C(jf, kf) * f(start + step * (kf + iF - jf));
        }

        res += (resf * k) / (factorial(i) * pow(step, i));
    }

    return res;
}

using namespace std;

template<typename Names, typename Values>
void print_table(const Names &names,
                 const Values &values,
                 const size_t rows,
                 const size_t cols) {
    constexpr int s = 20;
    constexpr int ns = 3;

    // Заголовки
    cout << right;
    for (size_t j = 0; j < cols; ++j)
        cout << setw(s) << names[j] << " " << setfill(' ') << "|";
    cout << '\n';

    // Разделительная линия
    cout << setfill('-') << setw((s * cols) + (cols * 2)) << "-" << setfill(' ') << '\n';

    // Значения
    cout << right << fixed << setprecision(ns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            cout << setw(s) << values[i][j] << " " << setfill(' ') << "|";

        cout << endl;
    }
    cout << '\n';
}

int main() {
    constexpr size_t N = 10;
    constexpr double START = 0.05;
    constexpr double END = 2.0;

    const char* names[3] = {
        "GAUSSIAN METHOD", "F(X)", "E"
    };

    double values[N][3];

    for (auto x = 0; x < N; ++x) {
        const double gx = gaussian_method(x, START, END, N);
        const double fx = f(gx);

        values[x][0] = gx;
        values[x][1] = fx;
        values[x][2] = fabs(gx - fx);
    }

    print_table(names, values, N, 3);

    return 0;
}