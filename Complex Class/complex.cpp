#include <iostream>
#include <vector>

using namespace std;

class Complex
{
private:
    size_t size;
    double *coefficients;

public:
    Complex() : size(0), coefficients(nullptr) {}

    Complex(const size_t n, const double *coeffs) : size(n)
    {
        coefficients = new double[size];

        for (size_t i = 0; i < size; ++i)
            coefficients[i] = coeffs[i];
    }

    Complex(const Complex &other) : size(other.size)
    {
        coefficients = new double[size];

        for (size_t i = 0; i < size; ++i)
            coefficients[i] = other.coefficients[i];
    }

    Complex &operator=(const Complex &other)
    {
        if (this != &other)
        {
            delete[] coefficients;
            size = other.size;
            coefficients = new double[size];

            for (size_t i = 0; i < size; ++i)
                coefficients[i] = other.coefficients[i];
        }
        return *this;
    }

    ~Complex()
    {
        delete[] coefficients;
    }

    Complex operator+(const Complex &other) const
    {
        const size_t maxSize = max(size, other.size);
        auto *resultCoeffs = new double[maxSize]();

        for (size_t i = 0; i < size; ++i)
            resultCoeffs[i] += coefficients[i];

        for (size_t i = 0; i < other.size; ++i)
            resultCoeffs[i] += other.coefficients[i];

        Complex result(maxSize, resultCoeffs);
        delete[] resultCoeffs;
        return result;
    }

    Complex operator-(const Complex &other) const
    {
        const size_t maxSize = max(size, other.size);
        auto *resultCoeffs = new double[maxSize]();

        for (size_t i = 0; i < size; ++i)
            resultCoeffs[i] += coefficients[i];

        for (size_t i = 0; i < other.size; ++i)
            resultCoeffs[i] -= other.coefficients[i];

        Complex result(maxSize, resultCoeffs);
        delete[] resultCoeffs;
        return result;
    }

    Complex operator*(const Complex &other) const
    {
        const size_t resultSize = size + other.size - 1;
        auto *resultCoeffs = new double[resultSize]();

        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < other.size; ++j)
            {
                resultCoeffs[i + j] += coefficients[i] * other.coefficients[j];
            }
        }

        Complex result(resultSize, resultCoeffs);
        delete[] resultCoeffs;
        return result;
    }

    Complex operator/(const Complex &other) const
    {
        const size_t dividendSize = size;
        const size_t divisorSize = other.size;

        if (divisorSize == 0)
        {
            cout << "Деление на нулевой полином!" << endl;
            return {};
        }

        if (dividendSize < divisorSize)
        {
            cout << "Деление на больший полином!" << endl;
            return {};
        }

        const size_t resultSize = dividendSize - divisorSize + 1;

        auto *resultCoeffs = new double[resultSize]();
        auto *dividendCoeffs = new double[dividendSize];

        for (size_t i = 0; i < dividendSize; ++i)
            dividendCoeffs[i] = coefficients[i];

        for (size_t i = 0; i < resultSize; ++i)
        {
            resultCoeffs[i] = dividendCoeffs[i] / other.coefficients[0];

            for (size_t j = 0; j < divisorSize; ++j)
            {
                dividendCoeffs[i + j] -= resultCoeffs[i] * other.coefficients[j];
            }
        }

        delete[] dividendCoeffs;

        return {resultSize, resultCoeffs};
    }

    void print() const
    {
        for (size_t i = 0; i < size; ++i)
        {
            cout << coefficients[i];
            if (i > 0)
                cout << "x^" << i;

            if (i < size - 1)
                cout << " + ";
        }

        cout << endl;
    }

    void addCoefficient(double coeff)
    {
        auto *newCoeffs = new double[size + 1];

        for (size_t i = 0; i < size; ++i)
            newCoeffs[i] = coefficients[i];

        newCoeffs[size] = coeff;

        delete[] coefficients;
        coefficients = newCoeffs;
        size++;
    }

    [[nodiscard]] size_t getSize() const
    {
        return size;
    }

    [[nodiscard]] double* getCoefficients() const
    {
        return coefficients;
    }
};