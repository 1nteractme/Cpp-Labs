#include <iostream>
#include <vector>

using namespace std;

class Polynom
{
private:
    size_t size;
    double *coefficients;

public:
    Polynom() : size(0), coefficients(nullptr) {}

    Polynom(size_t n, const double *coeffs) : size(n)
    {
        coefficients = new double[size];

        for (size_t i = 0; i < size; ++i)
            coefficients[i] = coeffs[i];
    }

    Polynom(const Polynom &other) : size(other.size)
    {
        coefficients = new double[size];

        for (size_t i = 0; i < size; ++i)
            coefficients[i] = other.coefficients[i];
    }

    Polynom &operator=(const Polynom &other)
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

    ~Polynom()
    {
        delete[] coefficients;
    }

    Polynom operator+(const Polynom &other) const
    {
        size_t maxSize = max(size, other.size);
        double *resultCoeffs = new double[maxSize]();

        for (size_t i = 0; i < size; ++i)
            resultCoeffs[i] += coefficients[i];

        for (size_t i = 0; i < other.size; ++i)
            resultCoeffs[i] += other.coefficients[i];

        Polynom result(maxSize, resultCoeffs);
        delete[] resultCoeffs;
        return result;
    }

    Polynom operator-(const Polynom &other) const
    {
        size_t maxSize = max(size, other.size);
        double *resultCoeffs = new double[maxSize]();

        for (size_t i = 0; i < size; ++i)
            resultCoeffs[i] += coefficients[i];

        for (size_t i = 0; i < other.size; ++i)
            resultCoeffs[i] -= other.coefficients[i];

        Polynom result(maxSize, resultCoeffs);
        delete[] resultCoeffs;
        return result;
    }

    Polynom operator*(const Polynom &other) const
    {
        size_t resultSize = size + other.size - 1;
        double *resultCoeffs = new double[resultSize]();

        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < other.size; ++j)
            {
                resultCoeffs[i + j] += coefficients[i] * other.coefficients[j];
            }
        }

        Polynom result(resultSize, resultCoeffs);
        delete[] resultCoeffs;
        return result;
    }

    Polynom operator/(const Polynom &other) const
    {
        size_t dividendSize = size;
        size_t divisorSize = other.size;

        if (divisorSize == 0)
        {
            cout << "Деление на нулевой полином!" << endl;
            return Polynom();
        }

        if (dividendSize < divisorSize)
        {
            cout << "Деление на больший полином!" << endl;
            return Polynom();
        }

        size_t resultSize = dividendSize - divisorSize + 1;
        double *resultCoeffs = new double[resultSize]();

        double *dividendCoeffs = new double[dividendSize];
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

        return Polynom(resultSize, resultCoeffs);
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
        double *newCoeffs = new double[size + 1];

        for (size_t i = 0; i < size; ++i)
            newCoeffs[i] = coefficients[i];

        newCoeffs[size] = coeff;

        delete[] coefficients;
        coefficients = newCoeffs;
        size++;
    }

    size_t getSize() const
    {
        return size;
    }

    double* getCoefficients() const
    {
        return coefficients;
    }
};