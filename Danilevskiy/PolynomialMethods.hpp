#pragma once

#include "Polynomial.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

using namespace std;

class PolynomialMethods
{
public:
    PolynomialMethods(Polynomial polynomial, const double start, const double end, const size_t count, const double eps, const size_t maxIterations) :
                      polynomial_(std::move(polynomial)), start_(start), end_(end), count_(count), eps_(eps), maxIterations_(maxIterations)
    {
        if (polynomial_.size() < 2)
            throw invalid_argument("Степень полинома должна быть положительной");

        if (count_ < 2)
            throw invalid_argument("Количество точек должно быть не меньше двух");

        if (eps_ <= 0 || maxIterations_ == 0)
            throw invalid_argument("Некорректные параметры метода");
    }

    void printPolynomial() const
    {
        const size_t n = polynomial_.size() - 1;

        cout << "\nХарактеристический многочлен:\n"
             << "P(λ) = λ" << toSuperscript(n);

        for (size_t i = 1; i < polynomial_.size(); ++i)
        {
            const double coefficient = polynomial_[i];
            const size_t power = n - i;

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

    void printRoots() const
    {
        const vector<double> roots = findRoots();

        cout << "\nСобственные значения:\n";

        if (roots.empty())
        {
            cout << "Вещественных корней в диапазоне ["
                 << start_ << "; " << end_ << "] не найдено\n";
            return;
        }

        for (const double root : roots)
            cout << "  λ = " << root << '\n';
    }

private:
    const Polynomial polynomial_;
    const double     start_;
    const double     end_;
    const size_t     count_;
    const double     eps_;
    const size_t     maxIterations_;

    static string toSuperscript(size_t number)
    {
        constexpr const char* digits[] =
            {"⁰","¹","²","³","⁴","⁵","⁶","⁷","⁸","⁹"};

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

    /// Вычисление значения полинома по схеме Горнера
    static double evaluate(const Polynomial& p, const double x)
    {
        double result = p.front();

        for (size_t i = 1; i < p.size(); ++i)
            result = result * x + p[i];

        return result;
    }

    /// Производная полинома
    static Polynomial derivative(const Polynomial& p)
    {
        if (p.size() < 2)
            return Polynomial{0.0};

        const size_t degree = p.size() - 1;
        Polynomial result;
        result.reserve(degree);

        for (size_t i = 0; i < degree; ++i)
            result.push_back(p[i] * static_cast<double>(degree - i));

        return result;
    }

    /// Метод Ньютона — уточняет корень на интервале [left; right]
    [[nodiscard]] double newton(const Polynomial& dp, double x) const
    {
        for (size_t i = 0; i < maxIterations_; ++i)
        {
            const double fx  = evaluate(polynomial_, x);
            const double dfx = evaluate(dp, x);

            if (abs(dfx) < eps_)
                throw runtime_error("Производная Ньютона слишком мала");

            const double next = x - fx / dfx;

            if (abs(next - x) <= eps_ * (1.0 + abs(next)))
                return next;

            x = next;
        }

        throw runtime_error("Метод Ньютона не сошёлся");
    }

    /// Метод секущих — запасной вариант
    [[nodiscard]] double secant(double a, double b) const
    {
        double fa = evaluate(polynomial_, a);
        double fb = evaluate(polynomial_, b);

        for (size_t i = 0; i < maxIterations_; ++i)
        {
            const double denom = fb - fa;

            if (abs(denom) < eps_)
                throw runtime_error("Знаменатель метода секущих слишком мал");

            const double next = b - fb * (b - a) / denom;
            const double fnext = evaluate(polynomial_, next);

            if (abs(fnext) <= eps_ || abs(next - b) <= eps_ * (1.0 + abs(next)))
                return next;

            a  = b;  fa = fb;
            b  = next; fb = fnext;
        }

        throw runtime_error("Метод секущих не сошёлся");
    }

    /// Поиск всех вещественных корней на [start_; end_]
    [[nodiscard]] vector<double> findRoots() const
    {
        const Polynomial dp = derivative(polynomial_);
        const double step = (end_ - start_) / static_cast<double>(count_ - 1);

        vector<double> roots;

        // Добавляет корень, исключая дубликаты с допуском sqrt(eps_)
        const double dedupTol = sqrt(eps_);
        const auto addRoot = [&](const double root)
        {
            for (const double existing : roots)
                if (abs(existing - root) <= dedupTol * (1.0 + abs(root)))
                    return;

            roots.push_back(root);
        };

        for (size_t i = 0; i < count_ - 1; ++i)
        {
            const double left  = start_ + static_cast<double>(i) * step;
            const double right = left + step;
            const double fl    = evaluate(polynomial_, left);
            const double fr    = evaluate(polynomial_, right);

            if (abs(fl) <= eps_)
            {
                addRoot(left);
                continue;
            }

            if (fl * fr < 0)
            {
                try
                {
                    addRoot(newton(dp, (left + right) / 2.0));
                }
                catch (const runtime_error&)
                {
                    try { addRoot(secant(left, right)); }
                    catch (const runtime_error&) {}
                }
            }
        }

        if (abs(evaluate(polynomial_, end_)) <= eps_)
            addRoot(end_);

        return roots;
    }
};