#include <iostream>
#include "polynom.cpp"

Polynom inputPolynom(const string &name)
{
    Polynom p;
    cout << "Введите коэффициенты для полинома " << name << " (для завершения введите 'q'):" << endl;

    while (true)
    {
        double coeff;

        cout << "Коэффициент при x^" << p.getSize() << ": ";
        cin >> coeff;

        if (cin.fail())
        {
            cin.clear();
            string input;
            cin >> input;

            if (input == "q")
                break;
            else
                cout << "Некорректный ввод. Пожалуйста, введите число или 'q' для завершения." << endl;
        }
        else
            p.addCoefficient(coeff);
    }

    return p;
}

int main()
{
    const Polynom a = inputPolynom("a");
    const Polynom b = inputPolynom("b");

    cout << "Полином 1: ";
    a.print();

    cout << "Полином 2: ";
    b.print();

    const Polynom sum = a + b;
    cout << "Сумма: ";
    sum.print();

    const Polynom diff = a - b;
    cout << "Разность: ";
    diff.print();

    const Polynom prod = a * b;
    cout << "Произведение: ";
    prod.print();

    const Polynom division = a / b;
    cout << "Деление: ";
    division.print();

    return 0;
}