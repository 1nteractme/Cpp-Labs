#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class vect
{
public:
    double x, y, d;
    double xe, ye, xs, ys;

    vect() : xe(0), ye(0), xs(0), ys(0), d(0), x(0), y(0) {}

    vect(double vxs, double vys, double vxe, double vye) : xs(vxs), ys(vys), xe(vxe), ye(vye)
    {
        x = vxe - vxs;
        y = vye - vys;
        calculate_length();
    }

    vect(const vect &v) : xe(v.xe), ye(v.ye), xs(v.xs), ys(v.ys), x(v.x), y(v.y), d(v.d) {}

    void vinfo() const
    {
        cout << "Начальные координаты: (" << xs << "," << ys << ")\nКонечные координаты: (" << xe << "," << ye << ")" << endl;
    }

    void vdist()
    {
        calculate_length();
        cout << "Длина вектора: " << d << endl;
    }

    vect operator+(const vect &other) const
    {
        return vect(xs + other.xs, ys + other.ys, xe + other.xe, ye + other.ye);
    }

    vect operator-(const vect &other) const
    {
        return vect(xs - other.xs, ys - other.ys, xe - other.xe, ye - other.ye);
    }

    vect operator*(double scalar) const
    {
        return vect(xs * scalar, ys * scalar, xe * scalar, ye * scalar);
    }

    double dot_product(const vect &other) const
    {
        return (x * other.x) + (y * other.y);
    }

    double vect_angle(const vect &a, const vect &b) const
    {
        return cosf((a.x * b.x + a.y * b.y) / (a.d * b.d));
    }
    ~vect()
    {
        // x(0), y(0), d(0), xe(0), ye(0), xs(0), ys(0);
    }

private:
    void calculate_length()
    {
        d = sqrt(pow(x, 2) + pow(y, 2));
    }
};
