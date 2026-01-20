#include <iostream>
#include <cmath>
#include <limits>
#include <fstream>
#include <utility>
#include <vector>
#include <cstdlib>

using namespace std;

/// Визуализацяи с помощью Gnuplot (опиционально) ///

class GnuplotVisualizer
{
private:
    string m_gnuplotPath;

public:
    explicit GnuplotVisualizer(string gnuplotPath = "gnuplot") : m_gnuplotPath(std::move(gnuplotPath)) {}

    void visualizeTriangleWithPoint(const vector<pair<float, float>> &trianglePoints, const pair<float, float> &testPoint, bool isInside) const {
        ofstream dataFile("triangle_data.dat");

        for (const auto &[fst, snd] : trianglePoints)
            dataFile << fst << " " << snd << "\n";

        dataFile << trianglePoints[0].first << " " << trianglePoints[0].second << "\n";

        dataFile << "\n\n";
        dataFile << testPoint.first << " " << testPoint.second << "\n";

        dataFile.close();

        ofstream scriptFile("plot_script.gp");

        scriptFile << "set title 'Проверка точки в треугольнике'\n";
        scriptFile << "set xlabel 'X'\n";
        scriptFile << "set ylabel 'Y'\n";
        scriptFile << "set grid\n";
        scriptFile << "set size ratio -1\n";

        scriptFile << "plot 'triangle_data.dat' index 0 with lines lw 2 lc rgb 'blue' title 'Треугольник', ";

        if (isInside)
            scriptFile << "'triangle_data.dat' index 1 with points pt 7 ps 1.5 lc rgb 'green' title 'Точка внутри'\n";
        else
            scriptFile << "'triangle_data.dat' index 1 with points pt 7 ps 1.5 lc rgb 'red' title 'Точка снаружи'\n";

        scriptFile << "pause -1 'Нажмите Enter для выхода...'\n";
        scriptFile.close();

        string command = m_gnuplotPath + " plot_script.gp";
        system(command.c_str());
    }
};

///
/// @return DISTANCE BETWEEN 2 POINTS
double calculateDistance(const double x1, const double y1, const double x2, const double y2)
{
    const auto dx = x1 - x2;
    const auto dy = y1 - y2;

    return sqrt(dx * dx + dy * dy);
}

///
/// @return GERONE METHODE
double calculateTriangleArea(const double a, const double b, const double c)
{
    const auto p = (a + b + c) / 2;

    return sqrt(p * (p - a) * (p - b) * (p - c));
}

///
/// @fun INPUT COORDINATES
void inputPointCoordinates(const string &pointName, float &x, float &y)
{
    cout << "Введите координаты для точки " << pointName << " (x y): ";

    while (!(cin >> x >> y))
    {
        cout << "Ошибка ввода! Пожалуйста, введите два числа: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main()
{
    float x1, y1, x2, y2, x3, y3, x4, y4;
    inputPointCoordinates("1", x1, y1);
    inputPointCoordinates("2", x2, y2);
    inputPointCoordinates("3", x3, y3);
    inputPointCoordinates("4", x4, y4);

    const double a = calculateDistance(x1, y1, x2, y2);
    const double b = calculateDistance(x2, y2, x3, y3);
    const double c = calculateDistance(x3, y3, x1, y1);

    const double d1 = calculateDistance(x1, y1, x4, y4);
    const double d2 = calculateDistance(x2, y2, x4, y4);
    const double d3 = calculateDistance(x3, y3, x4, y4);

    const double mainArea = calculateTriangleArea(a, b, c);
    const double area1 = calculateTriangleArea(a, d1, d2);
    const double area2 = calculateTriangleArea(b, d2, d3);
    const double area3 = calculateTriangleArea(c, d1, d3);

    const double sumAreas = area1 + area2 + area3;

    constexpr double epsilon = 0.001f;
    const bool isInside = abs(mainArea - sumAreas) < epsilon;

    cout << "Точка с координатами (" << x4 << "; " << y4 << ") ";

    if (isInside)
        cout << "лежит внутри треугольника." << endl;
    else
        cout << "лежит вне треугольника." << endl;

    // VISUALIZATION
    const GnuplotVisualizer visualizer;
    const vector<pair<float, float>> trianglePoints = {{x1, y1}, {x2, y2}, {x3, y3}};
    const pair<float, float> testPoint = {x4, y4};

    cout << "\nЗапуск визуализации... (должно открыться окно Gnuplot)" << endl;
    visualizer.visualizeTriangleWithPoint(trianglePoints, testPoint, isInside);

    return 0;
}