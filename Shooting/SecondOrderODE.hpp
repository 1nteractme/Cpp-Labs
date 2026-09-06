#pragma once

#include <functional>
#include <stdexcept>
#include <vector>

#include "State.hpp"

using namespace std;
using SecondOrderODEFunction = function<double(double, double, double)>;

class SecondOrderODE
{
public:
    /// Метод интегрирования Рунге-Кутты четвёртого порядка.
    /// @brief Численный метод решения дифференциальных уравнений.
    /// @details Позволяет найти приближённое значение функции, когда аналитически решить уравнение сложно или невозможно.
    /// @param f Правая часть дифференциального уравнения.
    /// @param x Начальная координата x = a.
    /// @param y Начальное значение y(a).
    /// @param dF Начальная производная y'(a).
    /// @param b Конечная координата x = b.
    /// @param n Колличество шагов интегрирования.
    /// @return Массив всех найденных точек численного решения [x, y, dF].
    static vector<State> integrateRK4(
        const SecondOrderODEFunction& f,
        const double x,
        const double y,
        const double dF,
        const double b,
        const int n)
    {
        if (n <= 0)
            throw invalid_argument("Количество шагов должно быть положительным.");

        const double h = (b - x) / static_cast<double>(n);

        vector<State> result;
        result.reserve(n + 1);
        result.push_back({x, y, dF});

        for (int i = 0; i < n; ++i)
        {
            const auto& [x, y, dFdY] = result.back();

            const double xCurrent = x;
            const double yCurrent = y;
            const double vCurrent = dFdY;

            // k1
            const double k1y = vCurrent;
            const double k1v = f(xCurrent, yCurrent, vCurrent);

            // k2
            const double y2 = yCurrent + h * k1y / 2;
            const double v2 = vCurrent + h * k1v / 2;

            const double k2y = v2;
            const double k2v = f(xCurrent + h / 2, y2, v2);

            // k3
            const double y3 = yCurrent + h * k2y / 2;
            const double v3 = vCurrent + h * k2v / 2;

            const double k3y = v3;
            const double k3v = f(xCurrent + h / 2, y3, v3);

            // k4
            const double y4 = yCurrent + h * k3y;
            const double v4 = vCurrent + h * k3v;

            const double k4y = v4;
            const double k4v = f(xCurrent + h, y4, v4);

            // Следующая точка
            const double yNext = yCurrent + h * (k1y + 2 * k2y + 2 * k3y + k4y) / 6;
            const double vNext = vCurrent + h * (k1v + 2 * k2v + 2 * k3v + k4v) / 6;

            result.push_back({xCurrent + h, yNext, vNext});
        }

        return result;
    }
};