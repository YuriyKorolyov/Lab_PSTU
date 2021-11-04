#include <iostream>
#include <clocale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	const float f = 7.481;
	int n;
	cout << "¬ведите число галлонов: ";
	cin >> n;
	cout << "ќбъЄм в футах равен " << n / f;
	return 0;
}