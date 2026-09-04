#include "SimpleIteration.hpp"
#include "Data.hpp"

int main()
{
    const Data data;

    constexpr double eps = 0.001;
    const auto matrix_A = data.Matrix;
    const auto vector_B = data.Vector;

    SimpleIteration methode(matrix_A, vector_B);

    methode.printData();
    methode.MSI(eps);

    return 0;
}