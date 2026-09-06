#pragma once

#include <functional>
#include <stdexcept>
#include <vector>

struct Point
{
    double x;
    double y;
};

using namespace std;
using Function = function<double(double, double)>;

class ODE
{
private:
    const Function& f;
    const double x0;
    const double y0;
    const double xEnd;
    const int n;

    static void checkSteps(const int n)
    {
        if (n <= 0)
            throw invalid_argument("Количество шагов должно быть положительным.");
    }

    [[nodiscard]] auto setGrid() const -> pair<vector<Point>, double>
    {
        checkSteps(n);

        const double h = (xEnd - x0) / n;

        vector<Point> result;
        result.push_back({x0, y0});

        return {result, h};
    }

public:
    ODE(const Function& f, const double x0, const double y0, const double xEnd, const int n) :
        f(f), x0(x0), y0(y0), xEnd(xEnd), n(n) { }

    /// ЯВНЫЙ МЕТОД ЭЙЛЕРА
    // y(n+1) = y(n) + h * f(x(n), y(n))
    [[nodiscard]] vector<Point> euler() const
    {
        auto [result, h] = setGrid();

        for (int i = 0; i < n; ++i)
        {
            auto [x, y] = result.back();

            const double y_n = y + h * f(x, y);
            const double x_m = x + h;

            result.push_back({x_m, y_n});
        }

        return result;
    }

    /// УЛУЧШЕННЫЙ ЭЙЛЕР
    /*
     * k1 = f(xn, yn)
     * predictor = yn + h*k1
     * k2 = f(xn+h, predictor)
     * yn+1 = yn + h/2 * (k1+k2)
     */
    [[nodiscard]] vector<Point> heun() const
    {
        auto [result, h] = setGrid();

        for (int i = 0; i < n; ++i)
        {
            auto [x, y] = result.back();

            const double k1 = f(x, y);
            const double predictor = y + h * k1;
            const double k2 = f(x + h, predictor);
            const double yNext = y + h * (k1 + k2) / 2;

            result.push_back({x + h, yNext});
        }

        return result;
    }


    /// RK2 - МЕТОД СРЕДНЕЙ ТОЧКИ
    /*
     *  k1 = f(xn, yn)
     *  k2 = f(xn+h/2, yn+h*k1/2)
     *  yn+1 = yn+h*k2
     */
    [[nodiscard]] vector<Point> midpoint() const
    {
        auto [result, h] = setGrid();

        for (int i = 0; i < n; ++i)
        {
            auto [x, y] = result.back();

            const double k1 = f(x, y);
            const double k2 = f(x + h / 2, y + h * k1 / 2);
            const double y_n = y + h * k2;

            result.push_back({x + h, y_n});
        }

        return result;
    }


    /// КЛАССИЧЕСКИЙ RK4
    /*
     * k1 = f(xn, yn)
     * k2 = f(xn+h/2, yn+h*k1/2)
     * k3 = f(xn+h/2, yn+h*k2/2)
     * k4 = f(xn+h, yn+h*k3)
     * yn+1 = yn + h/6*(k1+2*k2+2*k3+k4)
     */
    [[nodiscard]] vector<Point> rk4() const
    {
        auto [result, h] = setGrid();

        for (int i = 0; i < n; ++i)
        {
            auto [x, y] = result.back();

            const double k1 = f(x, y);
            const double k2 = f(x + h / 2, y + h * k1 / 2);
            const double k3 = f(x + h / 2, y + h * k2 / 2);
            const double k4 = f(x + h, y + h * k3);

            const double y_n = y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;

            result.push_back({x + h, y_n});
        }

        return result;
    }

    /// НЕЯВНЫЙ ЭЙЛЕР
    /*
     * yn+1 = yn + h*f(xn+1, yn+1)
     * Решаем относительно z:
     * F(z) = z - yn - h*f(xn+1,z) = 0
     * методом Ньютона.
     */
    [[nodiscard]] vector<Point> implicitEuler(
        const Function& dFdY, const int maxIterations = 50, const double epsilon = 1e-12) const
    {
        auto [result, h] = setGrid();

        for (int i = 0; i < n; ++i)
        {
            auto [x, y] = result.back();

            const double x_n = x + h;

            // Начальное приближение.
            double z = y + h * f(x, y);

            bool converged = false;

            for (int iteration = 0; iteration < maxIterations; ++iteration)
            {
                const double F = z - y - h * f(x_n, z);
                const double dF = 1 - h * dFdY(x_n, z);

                if (abs(dF) < 1e-14)
                    throw runtime_error("Производная Ньютона слишком мала.");

                const double delta = -F / dF;

                z += delta;

                if (abs(delta) <= epsilon * (1 + abs(z)))
                {
                    converged = true;
                    break;
                }
            }

            if (!converged)
                throw runtime_error("Метод Ньютона не сошелся.");

            result.push_back({x_n, z});
        }

        return result;
    }
};