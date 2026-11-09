#pragma once

#include "Matrix.hpp"
#include "Polynomial.hpp"

#include <fmt/format.h>
#include <tabulate/table.hpp>
#include <utility>

using namespace tabulate;

class Danilevskiy
{
public:
    explicit Danilevskiy(Matrix matrix, const double eps) : A_(std::move(matrix)), eps_(eps)
    {
        if (A_.empty())
            throw invalid_argument("Матрица не должна быть пустой");

        for (const auto& row : A_)
            if (row.size() != A_.size())
                throw invalid_argument("Матрица должна быть квадратной");

        frobenius_ = computeFrobenius();
    }

    /// Матрица Фробениуса
    [[nodiscard]] const Matrix& frobenius() const { return frobenius_; }

    /// Характеристический полином по первой строке матрицы Фробениуса
    [[nodiscard]] Polynomial characteristicPolynomial() const
    {
        const size_t n = frobenius_.size();
        Polynomial p;
        p.reserve(n + 1);
        p.push_back(1.0);

        for (const double c : frobenius_[0])
            p.push_back(-c);

        return p;
    }

    void printMatrix() const
    {
        cout << "\nМатрица Фробениуса:\n";

        Table table;

        for (const auto& row : frobenius_)
        {
            Table::Row_t r;

            for (const double value : row)
                r.emplace_back(fmt::format("{:10.2f}", value));

            table.add_row(r);
        }

        table.format().font_align(FontAlign::right);
        cout << table << '\n';
    }

private:
    Matrix A_;
    double eps_;
    Matrix frobenius_;

    static Matrix identity(const size_t n)
    {
        Matrix E(n, vector<double>(n, 0.0));

        for (size_t i = 0; i < n; ++i)
            E[i][i] = 1.0;

        return E;
    }

    static double pivot(const size_t index, const Matrix& m)
    {
        return m[index][index - 1];
    }

    [[nodiscard]] Matrix buildTransform(const size_t index, const Matrix& m) const
    {
        Matrix result = identity(m.size());
        const double p = pivot(index, m);

        if (abs(p) < eps_)
            throw runtime_error("Опорный элемент близок к нулю");

        for (size_t i = 0; i < m.size(); ++i)
        {
            const bool isDiag = (i == index - 1);
            result[index - 1][i] = isDiag ? 1.0 / p : -m[index][i] / p;
        }

        return result;
    }

    [[nodiscard]] Matrix invertMatrix(Matrix m) const
    {
        const size_t n = m.size();
        Matrix result = identity(n);

        for (size_t i = 0; i < n; ++i)
        {
            size_t pivotRow = i;

            for (size_t j = i + 1; j < n; ++j)
                if (abs(m[j][i]) > abs(m[pivotRow][i]))
                    pivotRow = j;

            if (abs(m[pivotRow][i]) < eps_)
                throw runtime_error("Матрица необратима");

            swap(m[i], m[pivotRow]);
            swap(result[i], result[pivotRow]);

            const double divisor = m[i][i];

            for (size_t j = 0; j < n; ++j)
            {
                m[i][j]      /= divisor;
                result[i][j] /= divisor;
            }

            for (size_t j = 0; j < n; ++j)
            {
                if (j == i) continue;

                const double factor = m[j][i];

                for (size_t k = 0; k < n; ++k)
                {
                    m[j][k]      -= factor * m[i][k];
                    result[j][k] -= factor * result[i][k];
                }
            }
        }

        return result;
    }

    [[nodiscard]] Matrix computeFrobenius() const
    {
        Matrix cur = A_;

        if (cur.size() == 1)
            return cur;

        for (size_t index = cur.size(); (index--) > 1;)
        {
            if (abs(pivot(index, cur)) < eps_)
            {
                size_t swapRow = cur.size();

                for (size_t i = 0; i < cur.size(); ++i)
                {
                    if (i != index && abs(cur[i][index - 1]) >= eps_)
                    {
                        swapRow = i;
                        break;
                    }
                }

                if (swapRow == cur.size())
                    throw runtime_error("Невозможно выбрать опорный элемент");

                swap(cur[index], cur[swapRow]);

                for (auto& row : cur)
                    swap(row[index], row[swapRow]);

                if (abs(pivot(index, cur)) < eps_)
                    throw runtime_error("После перестановки опорный элемент близок к нулю");
            }

            const Matrix T    = buildTransform(index, cur);
            const Matrix Tinv = invertMatrix(T);

            cur = Tinv * cur * T;
        }

        return cur;
    }
};