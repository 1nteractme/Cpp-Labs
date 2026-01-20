#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void AnalyzeMatrix(size_t rows, size_t cols)
{
    std::vector<std::vector<int>> m(rows, std::vector<int>(cols));

    size_t rowsWithZero = 0;
    size_t maxSeries = 1;
    size_t columnIndex = 0;

    for (size_t i = 0; i < rows; ++i)
    {
        bool hasZero = false;

        for (size_t j = 0; j < cols; ++j)
        {
            m[i][j] = rand() % 6; // [0..5]

            std::cout.width(3);
            std::cout << m[i][j];

            if (m[i][j] == 0)
                hasZero = true;
        }

        std::cout << '\n';

        if (hasZero)
            ++rowsWithZero;
    }

    for (size_t j = 0; j < cols; ++j)
    {
        size_t series = 1;

        for (size_t i = 1; i < rows; ++i)
        {
            if (m[i][j] == m[i - 1][j])
            {
                ++series;
                if (series > maxSeries)
                {
                    maxSeries = series;
                    columnIndex = j;
                }
            }
            else
                series = 1;
        }
    }

    std::cout << "\nКоличество строк, содержащих ноль: " << rowsWithZero << '\n';
    std::cout << "Максимальная серия повторений: " << maxSeries << '\n';
    std::cout << "Номер столбца: " << columnIndex << '\n';
}

int main()
{
    std::srand(std::time(nullptr));

    size_t rows, cols;

    std::cout << "Введите количество строк: ";
    std::cin >> rows;

    std::cout << "Введите количество столбцов: ";
    std::cin >> cols;

    AnalyzeMatrix(rows, cols);
    return 0;
}