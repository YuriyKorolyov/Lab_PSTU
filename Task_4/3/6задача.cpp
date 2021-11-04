#include <iostream>
#include <clocale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	float n, m;
	cout << "¬ведите два числа: ";
	cin >> n >> m;
	cout << "–езультат: " << n * m;
	return 0;
}