#include <iostream>
#include <clocale>
#include <random>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int x, y, i;
	bool f = true;
	x = 1 + rand() % (100);
	//cout << x<< endl;
	i = 0;
	cout << "������� ����� �� 1 �� 100 ������������.\n� ��� ����� 7 �������, ����� �������� �������� ��������������� �����. \n���� ��������!"<<endl;
	while (i < 7 && f==true) 
	{
		i += 1;
		cout << i << "-� �������: ";
		cin >> y;
		if (y < x)
			cout << "���������� ����� ������, ��� " << y << "!\n";
		else
			if (y > x)
				cout << "���������� ����� ������ ��� " << y << "\n";
			else
			{
				f = false;
				cout << "����������, �� ������� �����!";
			}	
	}
	if (i == 7 && f == true)
		cout << "\n� ���������, �� �� �������\n" << "\n���������� �����= " << x << "\n\n";
	return 0;
}