#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

struct User
{
    string name, email, phone_number, password;
};

bool UserExists(const User &user)
{
    if (ifstream in("database.txt"); in.is_open())
    {
        string line;

        while (getline(in, line))
        {
            istringstream iss(line);
            User existingUser;
            iss >> existingUser.name >> existingUser.email >> existingUser.phone_number >> existingUser.password;

            if (existingUser.name == user.name || existingUser.email == user.email || existingUser.phone_number == user.phone_number)
            {
                in.close();
                return true; // Пользователь уже существует
            }
        }
        in.close();
    }
    else
        cout << "Ошибка при открытии файла!" << endl;

    return false; // Пользователь не найден
}

void SaveToFile(const User &bd)
{
    if (ofstream out("database.txt", ios::app); out.is_open())
    {
        out << bd.name << " "
            << bd.email << " "
            << bd.phone_number << " "
            << bd.password << endl;
        out.close();
    }
    else
        cout << "Ошибка при открытии файла!" << endl;
}

void FindData(const string& out, const string& action)
{
    string search;
    bool isFound = false;

    cout << "Введите " << out << " для поиска: " << endl;
    cin >> search;

    if (ifstream in("database.txt"); in.is_open())
    {
        string line;
        while (getline(in, line))
        {
            istringstream iss(line);
            User user;
            iss >> user.name >> user.email >> user.phone_number >> user.password;

            if (action == "phone" && user.phone_number == search || action == "email" && user.email == search || action == "name" && user.name == search)
            {
                isFound = true;

                cout << "Имя: " << user.name << endl;
                cout << "Почта: " << user.email << endl;
                cout << "Телефон: " << user.phone_number << endl;
                cout << "Пароль: " << user.password << endl;

                break;
            }
        }
        in.close();
    }
    else
        cout << "Ошибка при открытии файла!" << endl;

    if (!isFound)
        cout << "Пользователь не найден!" << endl;
}

void FillDatabase()
{
    User user;

    cout << "Введите имя: ";
    cin >> user.name;

    cout << "Введите почту: ";
    cin >> user.email;

    cout << "Введите номер телефона: ";
    cin >> user.phone_number;

    cout << "Введите пароль: ";
    cin >> user.password;

    if (UserExists(user))
        cout << "Пользователь с таким именем, почтой или номером телефона уже существует!" << endl;
    else
    {
        SaveToFile(user);
        cout << "Пользователь успешно зарегистрирован!" << endl;
    }
}

void UI()
{
    int action, sub_action;

    do
    {
        cout << "\nДействия:\n1. Зарегистрировать\n2. Найти\n3. Выход"
             << endl;
        cin >> action;

        switch (action)
        {
        case 1:
            FillDatabase();
            break;
        case 2:
            cout << "Найти:\n1. По email\n2. По номеру телефона\n3. По логину" << endl;
            cin >> sub_action;

            if (sub_action == 1)
                FindData("почту", "email");
            else if (sub_action == 2)
                FindData("номер телефона", "phone");
            else if (sub_action == 3)
                FindData("логин", "name");
            else
                cout << "Неверное действие" << endl;
            break;
        case 3:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
            break;
        }
    } while (action != 3);
}

int main()
{
    UI();
    return 0;
}