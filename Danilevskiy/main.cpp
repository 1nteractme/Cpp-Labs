#include <iostream>
#include "Danilevskiy.hpp"

using namespace std;

int main(){
    const Matrix A = {
            {1, 2, 3, 4},
            {2, 1, 2, 3},
            {3, 2, 1, 2},
            {4, 3, 2, 1}
    };

    try{
        constexpr double EPS = 1e-12;
        const Danilevskiy METHOD(A, EPS);
        METHOD.solve();
    }
    catch(const exception& error){
        cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }

    return 0;
}