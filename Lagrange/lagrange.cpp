#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

///
/// @fun RESULT_OF_LAGRANGE_METHOD
double lagrange(const double x, const double *a, const double *b, const int n) {
    double res = 0;

    for (int i = 0; i < n; i++) {
        double k = 1;

        for (int j = 0; j < n; j++) {
            if (j == i) continue;

            k *= (x - a[j]);
            k /= (a[i] - a[j]);
        }

        res += k * b[i];
    }

    return res;
}

///
/// @fun PRINTING_TABLE_WITH_DATA
void print_table(const auto &names, const auto &values, const size_t rows, const size_t cols, const size_t precision = 3) {
    constexpr int s = 20;

    // Заголовки
    cout << right;
    for (size_t j = 0; j < cols; ++j)
        cout << setw(s) << names[j] << " " << setfill(' ') << "|";
    cout << '\n';

    // Разделительная линия
    cout << setfill('-') << setw((s * cols) + (cols * 2)) << "-" << setfill(' ') << '\n';

    // Значения
    cout << right << fixed << setprecision(precision);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            cout << setw(s) << values[i][j] << " " << setfill(' ') << "|";

        cout << endl;
    }
    cout << '\n';
}

///
/// @fun SETTING_UP_GNUPLOT
void set_gnuplot(const string& datafile) {
    ofstream ("plot.gp") <<
        "set encoding utf8\n"
        "set title 'Интерполяция функции ln(x) методом Лагранжа'\n"
        "set grid\n"
        "set key top left\n"
        "plot '" << datafile << "' index 0 with points ls 1 title 'Узлы интерполяции', \\\n"
        "     '" << datafile << "' index 1 using 1:2 with lines ls 2 title 'ln(x)', \\\n"
        "     '" << datafile << "' index 1 using 1:3 with lines ls 3 title 'Лагранж', \\\n"
        "     '" << datafile << "' index 2 with lines ls 4 title 'Погрешность'\n"
        "pause -1\n";

    system("gnuplot -persist plot_script.gp");
}

///
/// @fun SET_GNUPLOT_DATA
void set_data(auto A, auto B, auto values, auto n, auto nodes) {
    ofstream datafile("interpolation_data.dat");

    // Запись узлов интерполяции
    datafile << "# Узлы интерполяции\n";
    const int step = n / nodes;
    for (int i = 0; i < nodes; i++) {
        int index = i * step;
        datafile << A[index] << " " << B[index] << "\n";
    }

    datafile << "\n\n";

    // Запись точной функции и интерполяции
    datafile << "# Точная функция и интерполяция (x, ln(x), Лагранж)\n";
    for (int i = 0; i < n; i++)
        datafile << values[i][0] << " " << values[i][1] << " " << values[i][2] << "\n";
    datafile << "\n\n";

    // Запись погрешности
    datafile << "# Погрешность интерполяции (x, погрешность)\n";
    for (int i = 0; i < n; i++)
        datafile << values[i][0] << " " << values[i][3] << "\n";

    datafile.close();
}

int main() {
    constexpr size_t N = 100;

    // Узлы интерполяции
    double A[N];
    double B[N];

    for (int i = 0; i < N; ++i) {
        const auto x = (i + 1) / 10.0;
        A[i] = x;
        B[i] = log(x);
    }

    const char *names[4] = {"X", "Log(x)", "Lagrange(X)", "E"};
    double values[N][4];

    for (int i = 0; i < 100; ++i) {
        const double X = A[i];
        const double LOG_X = log(X);
        const double LAG_X = lagrange(X, A, B, N);
        const double E = fabs(LOG_X - LAG_X);

        values[i][0] = X;
        values[i][1] = LOG_X;
        values[i][2] = LAG_X;
        values[i][3] = E;
    }

    print_table(names, values, N, 4, 5);

    set_data(A, B, values, N, 5);
    set_gnuplot("interpolation_data.dat");

    return 0;
}
