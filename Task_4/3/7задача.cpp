#include <iostream>
#include <clocale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	float a, b, c, d, e;
	cout << "������� ���� �����: ";
	cin >> a >> b >> c >> d >> e;
	cout << "����� � �������� ������������������: " << e << " " << d << " " << c << " " << b << " " << a;
	return 0;
}