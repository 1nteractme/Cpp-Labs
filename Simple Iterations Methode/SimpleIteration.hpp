#ifndef MSI_SIMPLE_ITERATION_H
#define MSI_SIMPLE_ITERATION_H
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class SimpleIteration
{
private:
    vector<vector<double>> A;
    vector<double> B;
    vector<double> N;

    static void printVector(const auto& vector, auto name)
    {
        cout << "Вектор " << name << ": ";

        for (auto value : vector)
            cout << value << " ";

        cout << "\n" << endl;
    }

    void printMatrix() const
    {
        cout << "Матрица A:" << endl;

        for (auto & i : A)
        {
            for (double j : i)
                cout << j << " ";

            cout << endl;
        }

        cout << "\n";
    }

    void InitN() {  N.assign(A.size(), 0.0); }

    [[nodiscard]] vector<double> Iteration(const vector<double>& x) const
    {
        vector<double> result(A.size());

        for (size_t i = 0; i < A.size(); i++)
        {
            double sum = 0.0;

            for (size_t j = 0; j < A.size(); j++)
            {
                if (i != j)
                    sum += A[i][j] * x[j];
            }

            result[i] = (B[i] - sum) / A[i][i];
        }

        return result;
    }

public:
    SimpleIteration(const vector<vector<double>>& matrix, const vector<double>& vector) : A(matrix), B(vector) { }

    void printData()
    {
        cout << "ИСХОДНЫЕ ДАННЫЕ:\n" << endl;
        printMatrix();
        printVector(B, "B");
        InitN();
        cout << setw(20) << setfill('-') << "–\n" <<endl;
    }

    void MSI(const double epsilon)
    {
        int n = 0;

        while (true)
        {
            auto I = Iteration(N);

            double error(0);

            for (size_t i = 0; i < N.size(); i++)
                error = max(error, abs(I[i] - N[i]));

            N = I;

            n++;

            cout << "ИТЕРАЦИЯ #" << n << ":" << endl;

            for (const double value : N)
                cout << value << endl;

            cout << "\n";

            if (error < epsilon) break;
        }

        cout << "РЕЗУЛЬТАТ: " << endl;
        printVector(N, "N");
    }
};

#endif //MSI_SIMPLE_ITERATION_H