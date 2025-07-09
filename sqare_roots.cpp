#include <iostream>
#include <math.h>

using namespace std;

void main()
{
    int a, b, c;

    cout << "Input the A: " << endl;
    cin >> a;

    cout << "Input the B: " << endl;
    cin >> b;

    cout << "Input the C: " << endl;
    cin >> c;

    float d = pow(b, 2) - 4 * a * c;

    if (d > 0)
    {
        float k1 = (-1 * b) / 2 * a;
        float k2 = b / 2 * a;
        cout << "Roots: " << k1 << "," << k2 << endl;
    }
    else if (d == 0)
    {
        float k = b / 2 * a;
        cout << "Root: " << k << endl;
    }
    else
        cout << "Zero Roots" << endl;
}