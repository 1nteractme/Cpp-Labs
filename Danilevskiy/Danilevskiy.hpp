#pragma once

#include <vector>

using namespace std;
using Matrix = vector<vector<double>>;

class Danilevskiy{
private:
    int N = 4;
    int INDEX = 3;

    Matrix A;
    Matrix M;
    Matrix RESULT;

public:
    Danilevskiy(Matrix& A, const int N, const int INDEX) : A(A), N(N), INDEX(INDEX) {};


    /// Единичная матрица
    /// @brief Создает единичную матрицу размерности n
    /// @param n размер матрицы
    /// @return Единичную матрицу указанного размера
    Matrix identify(int n){
        Matrix E(n, vector<double>(n, 0));

        for(int i = 0; i < n; n++)
            E[i][i] = 1;

        return E;
    }



};

/// SVD ????