#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <tabulate/table.hpp>
#include <fmt/format.h>

using namespace std;
using namespace tabulate;

class Matrix : public vector<vector<double>>
{
public:
    using vector::vector;

    /// Умножение матриц
    /// @brief Перемножает две матрицы
    /// @param first первая матрица
    /// @param second вторая матрица
    /// @return результат умножения
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

class Danilevskiy
{
private:
    Matrix A;
    const long double eps_;

    /// Единичная матрица
    /// @brief Создает единичную матрицу размерности n
    /// @param n размер матрицы
    /// @return Единичную матрицу указанного размера
    static Matrix identify(const size_t n)
    {
        Matrix E(n, vector<double>(n, 0));

        for (size_t i = 0; i < n; ++i)
            E[i][i] = 1;

        return E;
    }

    /// Знаменатель
    /// @brief Возвращает опорный элемент матрицы
    /// @param index индекс строки опорного элемента
    /// @param M текущая матрица
    /// @return опорный элемент
    static double Denominator(const size_t index, const Matrix& M)
    {
        return M[index][index - 1];
    }

    /// Матрица преобразования
    /// @brief Формирует матрицу M для текущего шага
    /// @param index номер текущего шага
    /// @param M текущая матрица
    /// @return матрица преобразования
    [[nodiscard]] Matrix M(const size_t index, const Matrix& M) const
    {
        Matrix result = identify(M.size());
        const double denominator = Denominator(index, M);

        if (abs(denominator) < eps_)
            throw runtime_error("Опорный элемент близок к нулю");

        for (size_t i = 0; i < M.size(); ++i)
        {
            const bool isValid = i == index - 1;
            result[index - 1][i] = isValid ? 1 / denominator : -M[index][i] / denominator;
        }

        return result;
    }

    /// Обратная матрица
    /// @brief Вычисляет обратную матрицу методом Гаусса
    /// @param M исходная матрица
    /// @return обратная матрица
    [[nodiscard]] Matrix M_Inversed(Matrix M) const
    {
        const size_t n = M.size();
        Matrix result = identify(n);

        for (int i = 0; i < n; ++i)
        {
            int pivot = i;

            for (int j = i + 1; j < n; ++j)
                if (abs(M[j][i]) > abs(M[pivot][i]))
                    pivot = j;

            if (abs(M[pivot][i]) < eps_)
                throw runtime_error("Матрица необратима");

            swap(M[i], M[pivot]);
            swap(result[i], result[pivot]);

            const double divisor = M[i][i];

            for (int j = 0; j < n; ++j)
            {
                M[i][j] /= divisor;
                result[i][j] /= divisor;
            }

            for (int j = 0; j < n; ++j)
            {
                if (j == i)
                    continue;

                const double factor = M[j][i];

                for (int k = 0; k < n; ++k)
                {
                    M[j][k] -= factor * M[i][k];
                    result[j][k] -= factor * result[i][k];
                }
            }
        }

        return result;
    }

    /// Печать матрицы
    /// @brief Выводит матрицу в консоль
    /// @param M матрица для вывода
    /// @param index
    static void printMatrix(const Matrix& M, const size_t index)
    {
        cout << '\n'
            << (index != 0 ? "Итерация k = " + to_string(index) + "\n" : "");
        // << "Матрица преобразования M_k:\n";

        Table table;

        for (const auto& row : M)
        {
            Table::Row_t _row;

            for (const auto value : row)
                _row.emplace_back(fmt::format("{:10.2f}", value));

            table.add_row(_row);
        }

        table.format().font_align(FontAlign::right);
        // table.use_unicode_borders(true, BorderStyle::Light);
        cout << table << endl;
    }

    /// Печать характеристического полинома
    /// @brief Выводит полином в консоль с помощью UNICODE-символов
    /// @param current матрица для вывода
    void printPolynomial(const Matrix& current) const
    {
        const size_t n = current.size();

        cout << "\n"
            << "Характеристический многочлен:\n"
            << "P(λ) = λ" << toSuperscript(n);

        for (size_t i = 0; i < n; ++i)
        {
            const double coefficient = current[0][i];
            const size_t power = n - i - 1;

            if (abs(coefficient) < eps_)
                continue;

            const double absCoefficient = abs(coefficient);

            cout << (coefficient < 0 ? " - " : " + ");

            if (absCoefficient != 1.0 || power == 0)
                cout << absCoefficient;

            if (power > 0)
            {
                cout << "λ";

                if (power > 1)
                    cout << toSuperscript(power);
            }
        }

        cout << '\n';
    }

    /// Степень
    /// @brief Преобразует число в вид UNICODE-символа
    /// @param number текущая степень полинома
    static string toSuperscript(size_t number)
    {
        constexpr const char* digits[] = {"⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹"};

        if (number == 0)
            return digits[0];

        string result;

        while (number > 0)
        {
            result += digits[number % 10];
            number /= 10;
        }

        return result;
    }

public:
    /// Конструктор класса
    /// @brief Сохраняет и проверяет исходную матрицу
    /// @param matrix исходная матрица
    /// @param eps
    explicit Danilevskiy(Matrix matrix, const long double eps) : A(std::move(matrix)), eps_(eps)
    {
        if (A.empty())
            throw invalid_argument("Матрица не должна быть пустой");

        for (const auto& row : A)
            if (row.size() != A.size())
                throw invalid_argument("Матрица должна быть квадратной");
    }

    /// Метод Данилевского
    /// @brief Приводит матрицу к форме Фробениуса
    /// @return матрица Фробениуса
    void solve() const
    {
        Matrix A_ = A;
        Matrix S = A_;

        if (A_.size() == 1)
        {
            cout << "\nМатрица Фробениуса:";
            printMatrix(S, 0);
            printPolynomial(S);
            return;
        }

        for (size_t index = A_.size(); (index--) > 1;)
        {
            if (abs(Denominator(index, A_)) < eps_)
            {
                size_t row = A_.size();

                for (size_t i = 0; i < A_.size(); ++i)
                {
                    if (i != index && abs(A_[i][index - 1]) >= eps_)
                    {
                        row = i;
                        break;
                    }
                }

                if (row == A_.size())
                    throw runtime_error("Невозможно выбрать опорный элемент");

                swap(A_[index], A_[row]);

                for (auto& line : A_)
                    swap(line[index], line[row]);

                if (abs(Denominator(index, A_)) < eps_)
                    throw runtime_error("После перестановки опорный элемент близок к нулю");
            }

            const Matrix M_ = M(index, A_);
            const Matrix M_Inversed_ = M_Inversed(M_);

            S = M_Inversed_ * A_ * M_;
            A_ = S;

            printMatrix(M_, index);
        }

        cout << "\nМатрица Фробениуса:";
        printMatrix(S, 0);

        printPolynomial(S);
    }
};