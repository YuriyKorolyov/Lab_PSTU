#include <iostream>
#include <clocale>
#include <random>
using namespace std;
int main()
{
	int x, a, b, c, t;
	bool f = false;
	setlocale(LC_ALL, "Russian");
	cout << "Введите трёхзначное число" << endl;
	cin >> x;
	c = x % 10;
	b = (x/10)%10;
	a = x / 100;
	while ((x < 100) || (x > 999) || (a == b) || (a == c) || (b == c))
	{
		cout << "Введённое число не трёхзначное или во введённом числе есть повторяющиеся цифры. Пожалуйста, повторите ввод"<<endl;
		cin >> x;
		c = x % 10;
		b = (x/10) % 10;
		a = x / 100;
	}
	cout <<endl<<endl<< "Все комбинации цифр числа:"<<endl;
	cout << a << b << c << endl;
	t = c; c = b; b = t;
	cout << a << b << c << endl;
	t = a; a = c; c = t;
	cout << a << b << c << endl;
	t = b; b = c; c = t;
	cout << a << b << c << endl;
    t = a; a = c; c = t; 
	cout << a << b << c << endl;
	t = c; c = b; b = t;
	cout << a << b << c << endl;
	if (a > b && a > c)
	{
		cout <<endl<<endl<< "Наибольшее из этих чисел: " << a;
		if (b > c)
			cout << b << c;
		else
			cout << c << b;
	}
	else
		if (b > a && b > c)
		{
			cout <<endl<<endl<< "Наибольшее из этих чисел: " << b;
			if (a > c)
				cout << a << c;
			else
				cout << c << a;
		}
		else
			if (c > b && c > a)
			{
				cout <<endl<<endl<< "Наибольшее из этих чисел: " << c;
				if (b > a)
					cout << b << a;
				else
					cout << a << b;
			}
			else
				cout << a << b;
	return 0;
}



