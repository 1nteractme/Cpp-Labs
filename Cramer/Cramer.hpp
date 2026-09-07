#pragma once

#include <stdexcept>
#include <vector>

using namespace std;

using Matrix = vector<vector<double>>;
using Vector = vector<double>;

class Cramer
{
private:
    Matrix& A;
    const Vector& b;
    const double epsilon;

    /// Детерминант
    /// @brief Вычисляет определитель квадратной матрицы.
    /// @details Используется приведение к верхнетреугольному виду с частичным выбором главного элемента (Метод Гаусса).
    /// @param matrix Квадртаная матрица, для которой вычисляется определитель.
    /// @param epsilon Точность, используемая для проверки элемента на близость к нулю.
    /// @return Значение определителя матрицы.
    [[nodiscard]] static double det(Matrix matrix, const double epsilon)
    {
        const int n = static_cast<int>(matrix.size());

        if (n == 0) return 1;

        for (const auto& row : matrix)
        {
            if (static_cast<int>(row.size()) != n)
                throw invalid_argument("Матрица должна быть квадратной.");
        }

        double det = 1;

        for (int col = 0; col < n; ++col)
        {
            // Поиск главного элемента.
            int pivot = col;

            for (int row = col + 1; row < n; ++row)
            {
                if (abs(matrix[row][col]) > abs(matrix[pivot][col]))
                    pivot = row;
            }

            if (abs(matrix[pivot][col]) < epsilon) return 0;

            // Перестановка строк.
            if (pivot != col)
            {
                swap(matrix[pivot], matrix[col]);
                det *= -1;
            }

            const double pivotValue = matrix[col][col];

            det *= pivotValue;

            // Обнуление элементов ниже главной диагонали.
            for (int row = col + 1; row < n; ++row)
            {
                const double factor = matrix[row][col] / pivotValue;

                for (int j = col; j < n; ++j)
                    matrix[row][j] -= factor * matrix[col][j];
            }
        }

        return det;
    }

public:

    /// Конструктор метода Крамера
    /// @details Создаёт объект для решения системы линейных уравнений методом Крамера.
    /// @param A Матрица коэффициентов системы.
    /// @param b Вектор свободных членов.
    /// @param epsilon Точность, используемая при сравнении чисел с нулём.
    Cramer(Matrix& A, const Vector& b, const double epsilon) : A(A), b(b), epsilon(epsilon) {};

    /// Метода Крамера
    /// @details Решает СЛАУ методом Крамера.
    /// @return Vector - вектор найденных значений неизвестных.
    [[nodiscard]] Vector cramer() const
    {
        const int n = static_cast<int>(A.size());

        if (n == 0 || static_cast<int>(b.size()) != n)
            throw invalid_argument("Некорректная система.");

        const double detA = det(A, epsilon);

        if (abs(detA) < epsilon)
            throw runtime_error("det(A) равен нулю или слишком мал.");

        Vector x(n);

        // Для каждого неизвестного строим Ai.
        for (int column = 0; column < n; ++column)
        {
            Matrix Ai = A;

            // Заменяем column-й столбец правой частью.
            for (int row = 0; row < n; ++row)
                Ai[row][column] = b[row];

            const double detAi = det(Ai, epsilon);
            x[column] = detAi / detA;
        }

        return x;
    }
};