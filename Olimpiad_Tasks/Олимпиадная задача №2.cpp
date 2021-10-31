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
	cout << "Введите число от 1 до 100 включительно.\nУ Вас будет 7 попыток, чтобы отгадать случайно сгенерированное число. \nИгра началась!"<<endl;
	while (i < 7 && f==true) 
	{
		i += 1;
		cout << i << "-я попытка: ";
		cin >> y;
		if (y < x)
			cout << "Загаданное число больше, чем " << y << "!\n";
		else
			if (y > x)
				cout << "Загаданное число меньше чем " << y << "\n";
			else
			{
				f = false;
				cout << "Поздравяем, Вы угадали число!";
			}	
	}
	if (i == 7 && f == true)
		cout << "\nК сожалению, Вы не угадали\n" << "\nЗагаданное число= " << x << "\n\n";
	return 0;
}

