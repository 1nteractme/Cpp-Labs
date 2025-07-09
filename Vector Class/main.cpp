#include <iostream>
#include <fstream>
#include "vect.cpp"

using namespace std;

int main()
{
    double xs, xe, ys, ye;
    int action, sub_action;

    cout << "Вектор a" << endl;
    cout << "Введите начальную координату x: ";
    cin >> xs;
    cout << "Введите конечную координату x: ";
    cin >> xe;
    cout << "Введите начальную координату y: ";
    cin >> ys;
    cout << "Введите конечную координату y: ";
    cin >> ye;
    vect a(xs, ys, xe, ye);

    cout << "\nВектор b" << endl;
    cout << "Введите начальную координату x: ";
    cin >> xs;
    cout << "Введите конечную координату x: ";
    cin >> xe;
    cout << "Введите начальную координату y: ";
    cin >> ys;
    cout << "Введите конечную координату y: ";
    cin >> ye;
    vect b(xs, ys, xe, ye);

    do
    {
        cout << "\nВыберите действие:\n"
             << "1. Посмотреть информацию о векторе\n"
             << "2. Найти длину вектора\n"
             << "3. Посчитать сумму векторов\n"
             << "4. Посчитать разность векторов\n"
             << "5. Посчитать скалярное произведение\n"
             << "6. Посчитать угол между векторами\n"
             << "7. Выход\n"
             << endl;

        cin >> action;

        switch (action)
        {
        case 1:
            cout << "Вектор:\n1. a\n2. b" << endl;
            cin >> sub_action;

            if (sub_action == 1)
            {
                cout << "\nИнформация о векторе a:" << endl;
                a.vinfo();
            }
            else if (sub_action == 2)
            {
                cout << "\nИнформация о векторе b:" << endl;
                b.vinfo();
            }
            else
                cout << "Выбран некорректный вектор!" << endl;

            break;

        case 2:
            cout << "Вектор:\n1. a\n2. b" << endl;
            cin >> sub_action;

            if (sub_action == 1)
            {
                cout << "\nДлина вектора a:" << endl;
                a.vdist();
            }
            else if (sub_action == 2)
            {
                cout << "\nДлина вектора b:" << endl;
                b.vdist();
            }
            else
                cout << "Выбран некорректный вектор!" << endl;

            break;

        case 3:
        {
            vect sum = a + b;
            cout << "\nСумма векторов a и b:" << endl;
            sum.vinfo();
            sum.vdist();
            break;
        }

        case 4:
        {
            vect diff = a - b;
            cout << "\nРазность векторов a и b:" << endl;
            diff.vinfo();
            diff.vdist();
            break;
        }

        case 5:
        {
            double scalar;

            cout << "\nВведите скаляр для умножения вектора a: ";
            cin >> scalar;

            vect scaled = a * scalar;
            cout << "\nВектор a, умноженный на " << scalar << ":" << endl;
            scaled.vinfo();
            scaled.vdist();

            double dot = a.dot_product(b);
            cout << "\nСкалярное произведение векторов a и b: " << dot << endl;
            break;
        }

        case 6:
            cout << "Вектор между a и b: " << a.vect_angle(a, b) << endl;
            break;

        case 7:
        {
            cout << "Выход из программы." << endl;
            break;
        }

        default:
            cout << "Выбрано неверное действие!" << endl;
            break;
        }
    } while (action != 7);

    return 0;
}