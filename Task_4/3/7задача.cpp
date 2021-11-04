#include <iostream>
#include <clocale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	float a, b, c, d, e;
	cout << "¬ведите п€ть чисел: ";
	cin >> a >> b >> c >> d >> e;
	cout << "„исла в обратной последовательности: " << e << " " << d << " " << c << " " << b << " " << a;
	return 0;
}