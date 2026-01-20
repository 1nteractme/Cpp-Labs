#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, c;

    cout << "Input the A: " << endl;
    cin >> a;

    cout << "Input the B: " << endl;
    cin >> b;

    cout << "Input the C: " << endl;
    cin >> c;

    if (const double d = pow(b, 2) - 4 * a * c; d > 0)
    {
        const double k1 = (-1 * b) / 2 * a;
        const double k2 = b / 2 * a;

        cout << "Roots: " << k1 << "," << k2 << endl;
    }
    else if (d == 0)
    {
        const double k = b / 2 * a;
        cout << "Root: " << k << endl;
    }
    else
        cout << "Zero Roots" << endl;

    return 0;
}