#pragma once

#include <stdexcept>
#include <vector>

using namespace std;

class Matrix : public vector<vector<double>>
{
public:
    using vector::vector;

    friend Matrix operator*(const Matrix& first, const Matrix& second)
    {
        if (first.empty() || second.empty() || first[0].size() != second.size())
            throw invalid_argument("Размеры матриц не подходят для умножения");

        Matrix result(first.size(), vector<double>(second[0].size(), 0));

        for (size_t i = 0; i < first.size(); ++i)
            for (size_t j = 0; j < second[0].size(); ++j)
                for (size_t k = 0; k < second.size(); ++k)
                    result[i][j] += first[i][k] * second[k][j];

        return result;
    }
};
