#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

///
/// @var R HEMISPHERE_RADIUS
/// @var YSteps VERTICAL_STEPS
/// @var XSteps HORIZONTAL_STEPS
int main() {
    const double R = 1.0;
    constexpr int YSteps = 50;
    const int XSteps = 100;

    ofstream file("hemisphere.dat");

    // СОЗДАНИЕ ТОЧЕК ПОЛУСФЕРЫ
    for (int i = 0; i <= YSteps; ++i) {
        double theta = (M_PI / 2) * i / YSteps;  // [0, pi/2]

        for (int j = 0; j <= XSteps; ++j) {
            double phi = (2 * M_PI) * j / XSteps; // [0, 2*pi]

            double x = R * sin(theta) * cos(phi);
            double y = R * sin(theta) * sin(phi);
            double z = R * cos(theta);

            file << x << " " << y << " " << z << "\n";
        }

        file << "\n";
    }

    file.close();

    // НАСТРОЙКА И ЗАПУСК GNUPLOT
    ofstream gp("show_plot.gp");
    gp << "set view equal xyz\n";
    gp << "set ticslevel 0\n";
    gp << "splot 'hemisphere.dat' with lines\n";
    gp.close();

    system("gnuplot -persist show_plot.gp");

    return 0;
}
