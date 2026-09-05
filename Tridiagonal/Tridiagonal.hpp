#pragma once

#include <iomanip>
#include <stdexcept>
#include <vector>

using namespace std;

class Tridiagonal
{
private:
    vector<double> a; /// НИЖНЯЯ ДИАГОНИЛЬ
    vector<double> b; /// ГЛАВНАЯ ДИАГОНИЛЬ
    vector<double> c; /// ВЕРХНЯЯ ДИАГОНИЛЬ
    vector<double> d; /// РЕШЕНИЕ СИСТЕМЫ

    /// ВЫДЕЛЯЕТ ДИАГОНАЛИ
    void SubdivideDiagonals(const vector<vector<double>>& matrix, const vector<double>& rhs, const auto& n)
    {
        a.resize(n);
        b.resize(n);
        c.resize(n);
        d = rhs;

        for (int i = 0; i < n; ++i)
        {
            b[i] = matrix[i][i];

            if (i > 0) a[i] = matrix[i][i - 1];
            else a[i] = 0;

            if (i < n - 1) c[i] = matrix[i][i + 1];
            else c[i] = 0;
        }
    }

    static void out_diag(const auto& x, auto name)
    {
        cout << name << ": ";

        for (const double value : x)
            cout << value << " ";

        cout << '\n';
    }

public:
    /// КОНСТРУКТОР
    Tridiagonal(const vector<vector<double>>& matrix, const vector<double>& rhs)
    {
        const int n = matrix.size();

#pragma region ПРОВЕРКА ПРОБЛЕМ СИСТЕМЫ

        if (n == 0)
            throw invalid_argument("Пустая система");

        if (rhs.size() != n)
            throw invalid_argument("Размер системы не совпадает с размером ее решений");

        for (const auto& row : matrix)
            if (row.size() != n)
                throw invalid_argument("Матрица должна быть квадратной");

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (abs(i - j) > 1 && matrix[i][j] != 0)
                    throw invalid_argument("Матрица не является трёхдиагональной");

#pragma endregion

        SubdivideDiagonals(matrix, rhs, n);
    }

    /// МЕТОД ПРОГОНКИ\n
    /// возвращает решение системы линейных уравнений
    [[nodiscard]] vector<double> solve() const
    {
        const int n = b.size();
        constexpr double epsilon = 1e-12;
        vector<double> alpha(n), beta(n), x(n);

        /// ПРЯМОЙ ХОД
        if (abs(b[0]) < epsilon)
            throw runtime_error("Нулевой элемент на главной диагонали");

        alpha[0] = -c[0] / b[0];
        beta[0] = d[0] / b[0];

        for (int i = 1; i < n; ++i)
        {
            const double denominator = b[i] + a[i] * alpha[i - 1]; /// ЗНАМЕНАТЕЛЬ

            if (abs(denominator) < epsilon)
                throw runtime_error("Нулевой знаменатель в методе прогонки");

            alpha[i] = -c[i] / denominator;
            beta[i] = (d[i] - a[i] * beta[i - 1]) / denominator;
        }

        /// ОБРАТНЫЙ ХОД
        x[n - 1] = beta[n - 1];

        for (int i = n - 2; i >= 0; --i)
            x[i] = alpha[i] * x[i + 1] + beta[i];

        return x;
    }

#pragma region МЕТОДЫ ВЫВОДА

    /// ВЫВОД ВЫДЕЛЕННЫХ ДИАГОНАЛЕЙ
    void PrintDiagonals() const
    {
        out_diag(a, "A (нижняя диагональ)");
        out_diag(b, "B (главная диагональ)");
        out_diag(c, "C (верхняя диагональ)");
        out_diag(d, "D (правая часть)");
    }

    /// ВЫВОД РЕШЕНИЙ
    void PrintSolve() const
    {
        const vector<double> x = solve();

        cout << fixed << setprecision(6);

        for (int i = 0; i < x.size(); ++i)
            cout << "x(" << i + 1 << ") = " << x[i] << '\n';
    }

#pragma endregion
};