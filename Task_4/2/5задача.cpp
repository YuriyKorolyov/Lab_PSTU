#include <iostream>
#include <clocale>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int h1, min1, sec1, h2, min2, sec2, x1, x2;
    cout << "Введите начало и конец промежутка времени в пределах одних сутках с точностью до секунд: " << endl;
    cout << "Начало промежутка: " << endl;
    cout << "Часы ";
    cin >> h1;
    cout << "Минуты ";
    cin >> min1;
    cout << "Секунды ";
    cin >> sec1;
    cout << "Конец промежутка: " << endl;
    cout << "Часы ";
    cin >> h2;
    cout << "Минуты ";
    cin >> min2;
    cout << "Секунды ";
    cin >> sec2;
    x1 = h1 * 3600 + min1 * 60 + sec1;
    x2 = h2 * 3600 + min2 * 60 + sec2;
    cout << "Промежуток времени равен: " << endl;
    cout << "Часы " << (x2 - x1) / 3600;
    cout << " Минуты " << ((x2 - x1) % 3600) / 60;
    cout << " Секунды " << ((x2 - x1) % 3600) % 60;
}