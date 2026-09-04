#ifndef MSI_DATA
#define MSI_DATA
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Data
{
private:
    static vector<vector<double>> readMatrix(const string& fileName)
    {
        ifstream file(fileName);

        if (!file.is_open())
            throw runtime_error("Не удалось прочитать матрицу");

        vector<vector<double>> matrix;
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            vector<double> row;
            string value;

            while (getline(ss, value, ',')) {
                if (!value.empty())
                    row.push_back(std::stod(value));
            }

            if (!row.empty())
                matrix.push_back(row);
        }

        return matrix;
    }

    static vector<double> readVector(const string& fileName)
    {
        ifstream file(fileName);

        if (!file.is_open())
            throw runtime_error("Не удалось прочитать вектор");

        vector<double> vector;
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string value;

            while (getline(ss, value, ','))
            {
                if (!value.empty())
                    vector.push_back(stod(value));
            }
        }

        return vector;
    }

public:
    vector<vector<double>> Matrix = readMatrix("../Simple Iterations Methode/data/matrix.txt");
    vector<double> Vector = readVector("../Simple Iterations Methode/data/vector.txt");
};

#endif //MSI_DATA