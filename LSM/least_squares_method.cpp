#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

///
/// @fun GAUSSIAN_METHOD_BY_SLAQ
void solveSLAQGauss(double* sol, double **A, double *y, const int n) {
	for (int i = 1; i < n; i++) {
		int maxRow = i;

		for (int k = i + 1; k < n; k++)
			if (fabs(A[k][i]) > fabs(A[maxRow][i]))
				maxRow = k;

		if (maxRow != i) {
			swap(A[i], A[maxRow]);
			swap(y[i], y[maxRow]);
		}

		for (int k = i; k < n; k++) {
			long double coief = (-1) * (A[k][i - 1] / A[i - 1][i - 1]);

			for (int p = i - 1; p < n; p++)
				A[k][p] += coief * A[i - 1][p];

			y[k] += coief * y[i - 1];
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		sol[i] = y[i];

		for (int j = i + 1; j < n; j++)
			sol[i] -= A[i][j] * sol[j];

		sol[i] /= A[i][i];
	}
}

///
/// @param n ROW_VALUE
/// @param m COLUMN_VALUE
/// @fun CREATE_MATRIX
double** create_matrix(const int n, const int m) {
	auto **newMatrix = new double*[n];

	for (int i = 0; i < n; i++)
		newMatrix[i] = new double[m];

	return newMatrix;
}

///
/// @fun MATRIX_MULTIPLE
void matrix_multiple(double **matrix1, double **matrix2, const int n, const int m, const int p, double **res) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			double sum = 0;

			for (int k = 0; k < m; k++)
				sum += matrix1[i][k] * matrix2[k][j];

			res[i][j] = sum;
		}
	}
}

///
/// @fun MATRIX_TRANSPOSITION
void T(double **matrix, const int n, const int m, double **t_matrix) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			t_matrix[j][i] = matrix[i][j];
	}
}

void print_matrix(double **matrix, const int n, const int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << matrix[i][j] << " ";

		cout << endl;
	}
}

void print_vector(const double *vector, const int n) {
	for (int i = 0; i < n; i++)
		cout << vector[i] << " ";

	cout << endl;
}

///
/// @param n ROW_VALUE
/// @param m COLUMN_VALUE
/// @fun ALGORITHM_OF_LEAST_SQUARES_METHOD
void alg_lsm(const int n, const int m, double **A, double** b, double* res) {
	double **t_matrix = create_matrix(m, n); // T
	T(A, n, m, t_matrix);

	double **AtA = create_matrix(m, m); // trans(A) * A
	matrix_multiple(t_matrix, A, m, n, m, AtA);

	double **Atb = create_matrix(m, 1); // trans(A) * b
	matrix_multiple(t_matrix, b, m, n, 1, Atb);

	auto *y = new double[m];

	for (int i = 0; i < m; i++)
		y[i] = Atb[i][0];

	solveSLAQGauss(res, AtA, y, m);
}

void matrix_testcase(double*** outA, double*** outB, double** outRes, int& n, int& m) {
	n = 12;
	m = 5;

	*outA = new double*[n];
	*outB = new double*[n];
	*outRes = new double[m];

	for (int i = 0; i < n; i++) {
		(*outA)[i] = new double[m];
		(*outB)[i] = new double[1];
	}

	for (int i = 0; i < n; i++) {
		const double matrix_testcase_a[12][5] = {
			{1, 2, 3, 4, 5},
			{1, 2, 9, 4, 5},
			{2, -11, 6, 8, 10},
			{2, 4, 6, 8, 10},
			{3, 6, 9, 12, 15},
			{0, -1, -2, -3, 0},
			{14, 13, 12, 0, 11},
			{1, 2, 0, -2, -1},
			{3, 0, 17, 0, 7},
			{0, -23, 31, 1, 0},
			{2, 0, 3, 0, 7},
			{1, -13, 0, 5, 7},
		};
		constexpr double matrix_testcase_b[12] = {-1, 1, -1, 2, 0, 3, -2, -3, 0, 7, 13, 17};

		for (int j = 0; j < m; j++)
			(*outA)[i][j] = matrix_testcase_a[i][j];

		(*outB)[i][0] = matrix_testcase_b[i];
	}
}

int main() {
	double **dynamicTestA, **dynamicTestB;
	double *res;
	int N, M;

	matrix_testcase(&dynamicTestA, &dynamicTestB, &res, N, M);
	cout << "\n";

	print_matrix(dynamicTestA, N, M);
	cout << "\n";

	print_matrix(dynamicTestB, N, 1);
	cout << "\n";

	alg_lsm(N, M, dynamicTestA, dynamicTestB, res);

	cout << "solutions: " << endl;
	print_vector(res, M);

	return 0;
}
