#include <iostream>
#include <clocale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int n = 10;
	cout << n << endl;
	n += 10;
	cout << n << endl;
	n--;
	cout << n << endl;
	return 0;
}