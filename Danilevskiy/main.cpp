#include <iomanip>
#include <iostream>
#include "Danilevskiy.hpp"

using namespace std;
using Matrix = vector<vector<double>>;

int main(){
    int N = 4;
    int INDEX = 3;

    Matrix A = {
            {1, 2, 3, 4},
            {2, 1, 2, 3},
            {3, 2, 1, 2},
            {4, 3, 2, 1}
    };

    auto METHOD = Danilevskiy(A, N, INDEX);

    return 0;
}