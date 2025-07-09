#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct NOTE
{
    string name, surname, phone_number;
    int birthDate[3];
};

bool Compare(const NOTE &a, const NOTE &b) {
    return a.phone_number.substr(0, 3) < b.phone_number.substr(0, 3);
}

void FindData(int notesCount, NOTE *notes)
{
    string searchSurname;
    bool isFound = false;

    cout << "Введите фамилию для поиска: " << endl;
    cin >> searchSurname;

    for (int i = 0; i < notesCount; ++i)
    {
        const NOTE &note = notes[i];
        if (note.surname == searchSurname)
        {
            isFound = true;

            cout << "Фамилия: " << note.surname << endl;
            cout << "Имя: " << note.name << endl;
            cout << "Телефон: " << note.phone_number << endl;
            cout << "Дата рождения: " << note.birthDate[0] << "."
                 << note.birthDate[1] << "."
                 << note.birthDate[2] << endl;

            break;
        }
    }

    if (!isFound)
    {
        cout << "Запись с такой фамилией не найдена!" << endl;
    }
}

void FillDatabase(int notesCount, NOTE *notes)
{
    for (int i = 0; i < notesCount; i++)
    {
        cout << "Запись №" << i + 1 << endl;
        cout << "Введите фамилию: ";
        cin >> notes[i].surname;

        cout << "Введите имя: ";
        cin >> notes[i].name;

        cout << "Введите номер телефона: ";
        cin >> notes[i].phone_number;

        cout << "Введите дату рождения (день месяц год): ";
        cin >> notes[i].birthDate[0] >> notes[i].birthDate[1] >> notes[i].birthDate[2];
    }
}

void UI(int notesCount, NOTE *notes)
{
    int action;
    
    do {
        cout << "Действия:\n1. Заполнить БД\n2. Найти запись\n3. Отсортировать\n4. Выход" << endl;
        cin >> action;

        switch (action)
        {
            case 1:
                FillDatabase(notesCount, notes);
                break;
            case 2:
                FindData(notesCount, notes);
                break;
            case 3:
                sort(notes, notes + notesCount, Compare);
                break;
            case 4:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
                break;
        }
    } while (action != 4);
}

int main()
{
    int notesCount;

    cout << "Введите размер БД: ";
    cin >> notesCount;

    NOTE *notes = new NOTE[notesCount];

    UI(notesCount, notes);

    delete[] notes;
    return 0;
}