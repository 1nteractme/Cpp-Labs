#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

///
/// @return ANY_FUNCTION_YOU_SET
double f(const long double x) {
    return x * sin(x);
}

///
/// @return INTERPOLATE_POLYNOMIAL_FUNCTION
double polynomial(const long double x, const long double *arr, const int n) {
    double result = 0.0;

    for (int i = 0; i < n; i++)
        result += arr[i] * pow(x, i);
    return result;
}

///
/// @return MATRIX_WITH_GAUSSIAN_EFFECT
void gaussian(long double **A, long double *y, long double *arr, int n) {
    ///
    /// ПРЯМОЙ ХОД
    ///
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > fabs(A[maxRow][i]))
                maxRow = k;
        }

        if (maxRow != i) {
            swap(A[i], A[maxRow]);
            swap(y[i], y[maxRow]);
        }

        for (int k = i + 1; k < n; k++) {
            double D_A = A[k][i] / A[i][i];
            for (int j = i; j < n; j++)
                A[k][j] -= D_A * A[i][j];
            y[k] -= D_A * y[i];
        }
    }

    ///
    /// ОБРАТНЫЙ ХОД
    ///
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = y[i];
        for (int j = i + 1; j < n; j++)
            arr[i] -= A[i][j] * arr[j];
        arr[i] /= A[i][i];
    }
}

///
/// @def GNUPLOT_SETTINGS
void set_gnuplot(const string &datafile) {
    ofstream script("show_plot.gp");
    script << "set title 'Интерполяция функции x*sin(x)'\n";
    script << "set grid\n";
    script << "set key top left\n";

    script << "plot'" << datafile << "' index 0 with points pt 1 ps 2 lc rgb 'red' title 'Узлы', \\\n";
    script << "    '" << datafile <<
            "' index 1 using 1:2 with lines lw 2 lc rgb 'blue' title 'f(x) = x * sin(x)', \\\n";
    script << "    '" << datafile << "' index 1 using 1:3 with lines lw 2 lc rgb 'green' title 'Полином'\n";

    script << "pause -1\n";

    script.close();

    system("gnuplot -persist show_plot.gp");
}


void set_data(const string &filename, long double *x, long double *y, int n,
              long double *arr, int points = 1000) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    file << scientific << setprecision(10);

    file << "# Узлы интерполяции\n";
    for (int i = 0; i < n; i++)
        file << x[i] << " " << y[i] << " " << polynomial(x[i], arr, n) << "\n";
    file << "\n\n";

    file << "# Функция и интерполяционный полином\n";
    long double step = (x[n - 1] - x[0]) / (points - 1);

    for (int i = 0; i < points; i++) {
        long double current_x = x[0] + i * step;
        file << current_x << " " << f(current_x) << " " << polynomial(current_x, arr, n) << "\n";
    }

    file.close();
    set_gnuplot(filename);
}

void polynomial_coeffs(auto arr, int n) {
    cout << "\nКоэффициенты полинома:" << endl;

    for (int i = 0; i < n; i++)
        cout << "a[" << i << "] = " << scientific << setprecision(10) << arr[i] << endl;
}

void check_interpolation(auto arr, int n, const auto x, const auto y) {
    cout << "\nПроверка интерполяции:" << endl;

    cout << setw(10) << "x" << setw(15) << "f(x)" << setw(15) << "P(x)" << setw(15) << "Error" << endl;

    for (int i = 0; i < n; i++) {
        long double p_val = polynomial(x[i], arr, n);
        long double f_val = f(x[i]);
        long double abs_error = fabs(f_val - p_val);
        cout << x[i] << setw(15) << y[i] << setw(15) << p_val << setw(15) << abs_error << endl;
    }
}

void print_info(auto x, auto y, auto steps, auto nodes, auto start) {
    cout << "Шаг = " << steps << endl;

    for (int i = 0; i < nodes; i++) {
        x[i] = start + i * steps;
        y[i] = f(x[i]);
        cout << "x[" << i << "] = " << x[i] << ", f(x) = " << y[i] << endl;
    }
}

int main() {
    constexpr int nodes = 6;
    constexpr double start = 1.0;
    constexpr double end = 10.0;
    constexpr long double steps = (end - start) / nodes;

    long double x[nodes];
    long double y[nodes];
    long double arr[nodes];

    print_info(x, y, steps, nodes, start);

    auto **A = new long double *[nodes];
    for (int i = 0; i < nodes; i++) {
        A[i] = new long double[nodes];
        for (int j = 0; j < nodes; j++)
            A[i][j] = pow(x[i], j);
    }


    gaussian(A, y, arr, nodes);
    // polynomial_coeffs(arr, nodes);
    // check_interpolation(arr, nodes, x, y);

    set_data("interpolation_data.txt", x, y, nodes, arr);

    for (int i = 0; i < nodes; i++)
        delete[] A[i];

    delete[] A;

    return 0;
}
