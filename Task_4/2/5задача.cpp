#include <iostream>
#include <clocale>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int h1, min1, sec1, h2, min2, sec2, x1, x2;
    cout << "������� ������ � ����� ���������� ������� � �������� ����� ������ � ��������� �� ������: " << endl;
    cout << "������ ����������: " << endl;
    cout << "���� ";
    cin >> h1;
    cout << "������ ";
    cin >> min1;
    cout << "������� ";
    cin >> sec1;
    cout << "����� ����������: " << endl;
    cout << "���� ";
    cin >> h2;
    cout << "������ ";
    cin >> min2;
    cout << "������� ";
    cin >> sec2;
    x1 = h1 * 3600 + min1 * 60 + sec1;
    x2 = h2 * 3600 + min2 * 60 + sec2;
    cout << "���������� ������� �����: " << endl;
    cout << "���� " << (x2 - x1) / 3600;
    cout << " ������ " << ((x2 - x1) % 3600) / 60;
    cout << " ������� " << ((x2 - x1) % 3600) % 60;
}