#include <iostream>
#include <clocale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	float F, C;
	cout << "Введите температуру в грудусах по Фаренгейту: ";
	cin >> F;
	C = 5.0 / 9.0 * (F - 32);
	cout << "Температура в градусах Цельсия: " << C;
	return 0;
}