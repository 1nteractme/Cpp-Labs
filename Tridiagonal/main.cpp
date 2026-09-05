#include <iostream>
#include "Tridiagonal.hpp"

using namespace std;

int main()
{
    ///  ОСНОВНАЯ СИСТЕМА
    const vector<vector<double>> s = {
        {2, -1, 0},
        {-1, 2, -1},
        {0, -1, 2}
    };

    /// ПРАВАЯ ЧАСТЬ
    const vector<double> d = {1, 0, 1};

    try
    {
        /// ПЕРЕДАЕМ ИСХОДНУЮ СИСТЕМУ (s) И ЕЕ РЕШЕНИЕ (d)
        const Tridiagonal solve(s, d);

        cout << "ВЫДЕЛЕННЫЕ ДИАГОНАЛИ:\n";
        solve.PrintDiagonals();

        cout << "\nРЕШЕНИЕ:\n";
        solve.PrintSolve();
    }
    catch (const exception& e)
    {
        cerr << "ОШИБКА: " << e.what() << '\n';
        return 1;
    }

    return 0;
}