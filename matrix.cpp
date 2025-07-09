#include <iostream>
#include <ctime>
using namespace std;

void Matrix(const int N, const int M)
{
    srand(time(0));
    
    int a = 0;
    int b = 5;
    int num, ser, maxSer(0), c(0);

    int MTR[N][M];
    bool isNull;

    for (int i(0); i < N; i++)
    {
        isNull = false;

        for (int j(0); j < M; j++)
        {
            MTR[i][j] = rand() % (b - a + 1) - a;
            cout.width(3);
            cout << MTR[i][j];

            if (MTR[i][j] == 0)
                isNull = true;
        }

        cout << endl;
        if (isNull)
            c++;
    }

    for (int i(0); i < M; i++)
    {
        ser = 1;
        for (int j(0); j < N; j++)
        {
            if (j && (MTR[j][i] == MTR[j - 1][i]))
            {
                ser++;
                if (ser > maxSer)
                {
                    maxSer = ser;
                    num = i;
                }
            }
            else
                ser = 1;
        }
    }

    cout << "Количество строк, содержащих ноль: " << c << endl;
    cout << "Максимальная серия повторяющихся элементов в столбце: " << maxSer << endl;
    cout << "Номер столбца, с макс серией: " << num << endl;
}

int main()
{
    int i, j;
    cout << "Введите количество столбцов: " << endl;
    cin >> i;

    cout << "Введите количество строк: " << endl;
    cin >> j;

    Matrix(i, j);
    return 0;
}