#pragma once

#include <cmath>
#include <stdexcept>
#include <vector>

#include "SecondOrderODE.hpp"
#include "State.hpp"

using namespace std;

class Shooting
{
public:
    /// Метод стрельбы.
    /// @brief Решает краевую задачу методом стрельбы.
    /// @details Для поиска неизвестного начального значения производной используется метод секущих.
    /// @param f Правая часть дифференциального уравнения.
    /// @param a Левая граница интервала интегрирования.
    /// @param A Значение функции в левой границе: y(a) = A.
    /// @param b Правая граница интервала интегрирования.
    /// @param B Требуемое значение функции в правой границе: y(b) = B.
    /// @param s0 Первое начальное приближение для производной y'(a).
    /// @param s1 Второе начальное приближение для производной y'(a).
    /// @param n Количество шагов метода RK4.
    /// @param maxIterations Максимальное количество итераций метода секущих.
    /// @param epsilon Допустимая абсолютная погрешность невязки.
    /// @return Вектор состояний численного решения краевой задачи.
    static vector<State> shooting(
        const SecondOrderODEFunction& f,
        const double a, const double b,
        const double A, const double B,
        double s0, double s1,
        const int n,
        const int maxIterations = 100,
        const double epsilon = 1e-10)
    {
        if (n <= 0)
            throw invalid_argument("Количество шагов должно быть положительным.");

        if (maxIterations <= 0)
            throw invalid_argument("Максимальное количество итераций должно быть положительным.");

        if (epsilon <= 0)
            throw invalid_argument("Точность должна быть положительной.");

        // Остаток
        auto residual = [&](const double slope)
        {
            const auto solution = SecondOrderODE::integrateRK4(f, a, A, slope, b, n);
            return solution.back().y - B;
        };

        double r0 = residual(s0);
        double r1 = residual(s1);

        if (abs(r0) < epsilon)
            return SecondOrderODE::integrateRK4(f, a, A, s0, b, n);

        if (abs(r1) < epsilon)
            return SecondOrderODE::integrateRK4(f, a, A, s1, b, n);

        for (int iteration = 0; iteration < maxIterations; ++iteration)
        {
            const double denominator = r1 - r0;

            if (abs(denominator) < epsilon)
                throw runtime_error("Знаменатель метода секущих слишком мал.");

            /// Метод секущих
            const double s2 = s1 - r1 * (s1 - s0) / denominator;
            const double r2 = residual(s2);

            if (abs(r2) < epsilon)
                return SecondOrderODE::integrateRK4(f, a, A, s2, b, n);

            s0 = s1;
            r0 = r1;

            s1 = s2;
            r1 = r2;
        }

        throw runtime_error("Метод стрельбы не сошелся за заданное количество итераций.");
    }
};