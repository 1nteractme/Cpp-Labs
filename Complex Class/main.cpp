#include <iostream>
#include "complex.cpp"

Complex inputComplex(const string &name)
{
    Complex p;
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
    const Complex a = inputComplex("a");
    const Complex b = inputComplex("b");

    cout << "Полином 1: ";
    a.print();

    cout << "Полином 2: ";
    b.print();

    const Complex sum = a + b;
    cout << "Сумма: ";
    sum.print();

    const Complex diff = a - b;
    cout << "Разность: ";
    diff.print();

    const Complex prod = a * b;
    cout << "Произведение: ";
    prod.print();

    const Complex division = a / b;
    cout << "Деление: ";
    division.print();

    return 0;
}