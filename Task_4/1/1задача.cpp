#include <iostream>
#include <clocale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int i = 1;
	cout << "Результат: " << ++i * i++ << endl;
	return 0;
}