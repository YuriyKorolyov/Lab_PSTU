#include <iostream>
#include <clocale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	const float f = 7.481;
	int n;
	cout << "������� ����� ��������: ";
	cin >> n;
	cout << "����� � ����� ����� " << n / f;
	return 0;
}