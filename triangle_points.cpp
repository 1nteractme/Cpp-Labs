#include <iostream>
#include <cmath>
#include <limits>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

// Визуализацяи с помощью Gnuplot (опиционально)
class GnuplotVisualizer
{
private:
    string m_gnuplotPath;

public:
    GnuplotVisualizer(const string &gnuplotPath = "gnuplot") : m_gnuplotPath(gnuplotPath) {}

    void visualizeTriangleWithPoint(const vector<pair<float, float>> &trianglePoints, const pair<float, float> &testPoint, bool isInside)
    {
        ofstream dataFile("triangle_data.dat");

        for (const auto &point : trianglePoints)
            dataFile << point.first << " " << point.second << "\n";

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

// Расстояние между двумя точками
float calculateDistance(float x1, float y1, float x2, float y2)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

// формула Герона
float calculateTriangleArea(float a, float b, float c)
{
    float p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// Ввода координат точки с проверкой
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

    float a = calculateDistance(x1, y1, x2, y2);
    float b = calculateDistance(x2, y2, x3, y3);
    float c = calculateDistance(x3, y3, x1, y1);

    float d1 = calculateDistance(x1, y1, x4, y4);
    float d2 = calculateDistance(x2, y2, x4, y4);
    float d3 = calculateDistance(x3, y3, x4, y4);

    float mainArea = calculateTriangleArea(a, b, c);
    float area1 = calculateTriangleArea(a, d1, d2);
    float area2 = calculateTriangleArea(b, d2, d3);
    float area3 = calculateTriangleArea(c, d1, d3);

    float sumAreas = area1 + area2 + area3;

    const float epsilon = 0.001f;
    bool isInside = abs(mainArea - sumAreas) < epsilon;

    cout << "Точка с координатами (" << x4 << "; " << y4 << ") ";
    if (isInside)
        cout << "лежит внутри треугольника." << endl;
    else
        cout << "лежит вне треугольника." << endl;

    // Визуализация
    GnuplotVisualizer visualizer;
    vector<pair<float, float>> trianglePoints = {{x1, y1}, {x2, y2}, {x3, y3}};
    pair<float, float> testPoint = {x4, y4};

    cout << "\nЗапуск визуализации... (должно открыться окно Gnuplot)" << endl;
    visualizer.visualizeTriangleWithPoint(trianglePoints, testPoint, isInside);

    return 0;
}