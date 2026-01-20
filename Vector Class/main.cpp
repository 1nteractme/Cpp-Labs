#include <iostream>
#include "Vector2D.cpp"

void plot_vectors(const Vector2D* v, const size_t n) {
    FILE* gp = popen("gnuplot -persist", "w");

    fprintf(gp, "set grid\n");
    fprintf(gp, "set size square\n");
    fprintf(gp, "set title 'Vector visualization'\n");
    fprintf(gp, "plot '-' with vectors head filled lt 2 lw 2\n");

    for (size_t i = 0; i < n; ++i) {
        fprintf(gp, "%f %f %f %f\n",
                v[i].xs, v[i].ys,
                v[i].x(), v[i].y());
    }

    fprintf(gp, "e\n");
    fflush(gp);
    pclose(gp);
}

int main() {
    double xs, ys, xe, ye;
    int action{}, sub_action{};

    std::cout << "Вектор a\n";
    std::cout << "Введите xs ys xe ye: ";
    std::cin >> xs >> ys >> xe >> ye;
    const Vector2D a(xs, ys, xe, ye);

    std::cout << "\nВектор b\n";
    std::cout << "Введите xs ys xe ye: ";
    std::cin >> xs >> ys >> xe >> ye;
    const Vector2D b(xs, ys, xe, ye);

    do {
        std::cout << "\nВыберите действие:\n"
                  << "1. Информация о векторе\n"
                  << "2. Длина вектора\n"
                  << "3. Сумма векторов\n"
                  << "4. Разность векторов\n"
                  << "5. Скалярное произведение\n"
                  << "6. Угол между векторами\n"
                  << "7. Показать векторы (gnuplot)\n"
                  << "8. Выход\n> ";

        std::cin >> action;

        switch (action) {

            case 1:
                std::cout << "1. a\n2. b\n> ";
                std::cin >> sub_action;
                (sub_action == 1 ? a : b).print();
                break;

            case 2:
                std::cout << "1. a\n2. b\n> ";
                std::cin >> sub_action;
                std::cout << "Длина: "
                          << (sub_action == 1 ? a.length() : b.length())
                          << '\n';
                break;

            case 3: {
                Vector2D sum = a + b;
                std::cout << "Сумма:\n";
                sum.print();
                break;
            }

            case 4: {
                Vector2D diff = a - b;
                std::cout << "Разность:\n";
                diff.print();
                break;
            }

            case 5:
                std::cout << "Скалярное произведение: "
                          << a.dot(b) << '\n';
                break;

            case 6: {
                double angle = Vector2D::angle_rad(a, b);
                std::cout << "Угол (рад): " << angle << '\n';
                std::cout << "Угол (град): " << angle * 180.0 / M_PI << '\n';
                break;
            }

            case 7: {
                const Vector2D arr[] = {a, b};
                plot_vectors(arr, 2);
                break;
            }

            case 8:
                std::cout << "Выход.\n";
                break;

            default:
                std::cout << "Неверное действие.\n";
        }

    } while (action != 8);

    return 0;
}