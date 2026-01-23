#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

///
/// @vun FUNCTION
double f(const double x) {
	return x * sin(1 / x);
}

///
/// @vun FACTORIAL_FUNCTION
double factorial(const long num) {
	auto res = 1;

	for (int n = 1; n <= num; n++)
		res *= n;

	return res;
}

///
/// @fun SOCHETANIYE BEZ POVTORENIY
double C(const int k, const int n) {
	auto res = 1;

	for (int p = k + 1; p <= n; p++)
		res *= p;

	for (int p = 1; p <= n - k; p++)
		res /= p;

	return res;
}

///
/// @fun FIRST_NEWTON
double calculateFirstNewton(const double x, const double start, const double end, const int n) {
	const double step = (end - start) / (n - 1.0);
	double res = f(start);

	for (int i = 1; i < n; i++) {
		double k = 1;
		for (int j = 0; j < i; j++)
			k *= (x - (start + step * j));

		double resf = 0;
		for (int jf = 0; jf <= i; jf++)
			resf += pow(-1,jf) * C(jf,i) * f(start + step*(i - jf));

		res += (resf * k) / (factorial(i) * pow(step,i));
	}

	return res;
}

///
/// @fun SECOND_NEWTON
double calculateSecondNewton(const double x, const double start, const double end, const int n) {
	const double step = (end - start) / (n - 1.0);
	double res = f(end);

	for (int i = n-1; i >= 1; i--) {
		double k = 1;

		for (int j = n-1; j >= i; j--)
			k *= (x - (start + step * j));

		double resf = 0;

		for (int jf = 0; jf <= n-i; jf++)
			resf += pow(-1,jf) * C(jf,n-i) * f(start + step*(i+jf));

		res += (resf * k) / (factorial(n-i) * pow(step,n-i));
	}

	return res;
}

///
/// @fun GNUPLOT_SETTINGS
void set_gnuplot(const string& datafile) {
	ofstream("show_plot.gp") <<
		"set encoding utf8\n"
		"set title 'Интерполяция функции x*sin(1/x)'\n"
		"set grid\n"
		"set key top left\n"
		"plot '" << datafile << "' index 0 using 1:2 with points pt 7 ps 2 lc rgb 'red' title 'Узлы', \\\n"
		"     '" << datafile << "' index 1 using 1:2 with lines lw 2 lc rgb 'blue' title 'f(x)', \\\n"
		"     '" << datafile << "' index 1 using 1:3 with lines lw 2 lc rgb 'green' title 'Ньютон 1', \\\n"
		"     '" << datafile << "' index 1 using 1:4 with lines lw 2 lc rgb 'orange' title 'Ньютон 2'\n"
		"pause -1\n";

	system("gnuplot -persist show_plot.gp");
}

///
/// @fun SET_DATA_TO_FILE
void set_data(const string& filename, const double start, const double end, const int n, const int points = 1000) {
	const double step = (end - start) / (n - 1.0);
	ofstream file(filename);

	if (!file.is_open()) {
		cerr << "Ошибка открытия файла: " << filename << endl;
		return;
	}

	file << scientific << setprecision(10);
	file << "# Узлы интерполяции\n";
	for (int i = 0; i < n; i++)
		file << start + step * i << " "
			 << f(start + step * i) << "\n";
			 // << calculateFirstNewton(start + step * i, start, end, n) << " "
			 // << calculateFirstNewton(start + step * i, start, end, n) << "\n";
			 // << calculateSecondNewton(start + step * i, start, end, n) << "\n";

	file << "\n\n# Функция и интерполяционный полином\n";
	const double step1 = (end - start) / (points-1);
	for (int i = 0; i < points; i++) {
		const double x = start + i*step1;

		file << x << " " << f(x) << "\n";
			 // << calculateFirstNewton(x, start, end, n) << " "
			 // << calculateFirstNewton(x, start, end, n) << "\n";
			 // << calculateSecondNewton(x, start, end, n) << "\n";
	}

	file.close();

	set_gnuplot(filename);
}

int main() {
	constexpr int N = 15; // [15-20]
	constexpr double START = -0.05;
	constexpr double END = 0.05;

	set_data("interpolation_data.txt", START, END, N);
}