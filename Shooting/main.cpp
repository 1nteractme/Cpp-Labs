#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>

#include "Shooting.hpp"

using namespace std;

struct BoundaryProblem
{
    SecondOrderODEFunction f;
    string equation;

    double a, A, b, B;
    int N;
};

void header()
{
    constexpr int N = 22;

    cout << setw(10) << "Шаг |"
         << setw(N) << "x |"
         << setw(N) << "y |"
         << setw(N) << "y'' |"
         << "\n";
}

void separator() { cout << setw(22*3 + 7) << setfill('=') << "=" << setfill(' ') << "\n"; }

int main()
{
    const double pi = acos(-1);

    /// Решаемое дифференциальное уравнение
    const BoundaryProblem problem{
        [](double, const double y, double){ return -y; },
        "y'' = -y",
        0, 0,
        pi / 2, 1,
        100
    };

    try
    {
        const auto solution =
            Shooting::shooting(
                problem.f,
                problem.a,
                problem.b,
                problem.A,
                problem.B,
                0.5,    // s0
                1.5,    // s1
                problem.N
            );

        cout << "\nРешаемая функция: " << problem.equation << "\n";
        cout << "Граничные условия: "
             << "y(" << problem.a << ") = " << problem.A
             << ", "
             << "y(" << problem.b << ") = " << problem.B
             << '\n';
        cout << "Количество шагов RK4: " << problem.N << "\n" << endl;

        separator();
        header();
        separator();

        for (size_t i = 0; i < solution.size(); ++i)
        {
            const auto& [x, y, derivative] = solution[i];

            cout << fixed << setprecision(10)
                 << setw(5) << i << " |"
                 << setw(20) << x << " |"
                 << setw(20) << y << " |"
                 << setw(20) << derivative << " |"
                 << '\n';
        }

        separator();
    }
    catch (const exception& e)
    {
        cerr << "ОШИБКА: " << e.what() << '\n';
        return 1;
    }

    return 0;
}