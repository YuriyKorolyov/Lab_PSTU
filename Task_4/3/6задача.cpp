#include <iostream>
#include <clocale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	float n, m;
	cout << "������� ��� �����: ";
	cin >> n >> m;
	cout << "���������: " << n * m;
	return 0;
}