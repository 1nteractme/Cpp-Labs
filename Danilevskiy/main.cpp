#include "Danilevskiy.hpp"
#include "PolynomialMethods.hpp"

#include <iostream>

int main()
{
    const Matrix A = {
        {1, 2, 3, 4},
        {2, 1, 2, 3},
        {3, 2, 1, 2},
        {4, 3, 2, 1}
    };

    constexpr double EPS      = 1e-12;
    constexpr double START    = -10.0;
    constexpr double END      =  10.0;
    constexpr size_t COUNT    = 1001;
    constexpr size_t MAX_ITER = 100;

    try
    {
        const Danilevskiy method(A, EPS);
        method.printMatrix();

        const PolynomialMethods pm(
            method.characteristicPolynomial(),
            START, END, COUNT, EPS, MAX_ITER);

        pm.printPolynomial();
        pm.printRoots();
    }
    catch (const exception& e)
    {
        cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }

    return 0;
}