#include <algorithm>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <iterator>

#include "ODE.hpp"

using namespace std;
using ExactFunction = function<double(double)>;

namespace
{
    constexpr auto GREEN = "\033[32m";
    constexpr auto YELLOW = "\033[93m";
    constexpr auto RESET = "\033[0m";

    constexpr int TABLE_WIDTH = 98;
}


void sep() { cout << setfill('=') << setw(TABLE_WIDTH) << "" << setfill(' ') << '\n'; }

void header()
{
    cout << '\n';

    cout << "|     x     " << "|    Euler    " << "|    Heun    " << "|  Midpoint  " << "|     RK4     " <<
        "|  Implicit Euler  " << "|     e     |" << "\n";

    sep();
}

template <typename T>
void out_line(const int width, const T value, const bool highlight = false, const bool isEps = false)
{
    cout << "| ";

    if (highlight) cout << GREEN;
    if (isEps) cout << YELLOW;

    cout << fixed << setprecision(6) << setw(width) << value;

    if (highlight) cout << RESET;

    cout << ' ';
}

void out(const ODE& methods, const Function& dFdY, const ExactFunction& exact)
{
    constexpr double epsilon = 1e-12;
    constexpr int maxIterations = 50;

    const auto euler = methods.euler();
    const auto heun = methods.heun();
    const auto midpoint = methods.midpoint();
    const auto rk4 = methods.rk4();
    const auto implicitEuler = methods.implicitEuler(dFdY, maxIterations, epsilon);

    header();

    for (size_t i = 0; i < euler.size(); ++i)
    {
        /// Точное значение в текущей точке
        const double x = euler[i].x;
        const double exactValue = exact(x);

        /// Абсолютные ошибки всех методов
        const double errors[] =
        {
            abs(euler[i].y - exactValue),
            abs(heun[i].y - exactValue),
            abs(midpoint[i].y - exactValue),
            abs(rk4[i].y - exactValue),
            abs(implicitEuler[i].y - exactValue)
        };

        const size_t best = distance(begin(errors), ranges::min_element(errors));

        out_line(9,  x);
        out_line(11, euler[i].y, best == 0);
        out_line(10, heun[i].y, best == 1);
        out_line(10, midpoint[i].y, best == 2);
        out_line(11, rk4[i].y, best == 3);
        out_line(16, implicitEuler[i].y, best == 4);
        out_line(9,  exactValue, true, true);

        cout << "|\n";
    }

    sep();
}


int main()
{
    const Function f = [](double, const double y) { return y; };
    const Function dFdY = [](double, double) { return 1; }; /// Производная f по y
    const ExactFunction exact = [](const double x) { return exp(x); }; /// Точное решение

    try
    {
        constexpr double x0(0), y0(1), xEnd(1);
        constexpr int n = 10;
        const ODE methods(f, x0, y0, xEnd, n);

        out(methods, dFdY, exact);
    }
    catch (const exception& e)
    {
        cerr << "ОШИБКА: " << e.what() << '\n';
        return 1;
    }

    return 0;
}