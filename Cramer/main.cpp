#include <iomanip>
#include <iostream>

#include "Cramer.hpp"

using namespace std;

void out(const Vector& v, const double epsilon)
{
    cout << "\n" << "РЕШЕНИЕ СЛАУ: " << endl;
    const char* names[] = {"x", "y", "z"};

    for (int i = 0; i < v.size(); ++i)
    {
        const bool isInteger = abs(v[i] - round(v[i])) < epsilon;

        cout << fixed << (isInteger ? setprecision(0) : setprecision(15));
        cout << names[i] << ": " << v[i] << '\n';
    }
}

int main()
{
    /// СЛАУ
    Matrix A = {
        {2, 1, -1},
        {-3, -1, 2},
        {-2, 1, 2}
    };

    const Vector b = {8, -11, -3};

    try
    {
        constexpr double epsilon = 1e-14;
        const Vector vector = Cramer(A, b, epsilon).cramer();
        out(vector, epsilon);
    }
    catch (const exception& e)
    {
        cerr << "ОШИБКА: " << e.what() << '\n';
        return 1;
    }

    return 0;
}