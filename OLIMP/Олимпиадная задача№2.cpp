#include <iostream>
#include <clocale>
#include <random>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int x, y, i;
	bool f = true;
	
	i = 0;
	x = 1 + rand() % (100);
	
	//cout << x<< endl;	
	cout << "Введите число от 1 до 100 включительно." << endl << "У Вас будет 7 попыток, чтобы отгадать случайно сгенерированное число."<< endl << "Игра началась!"<< endl;
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
				cout << "Поздравляем, Вы угадали число!";
			}	
	}
	if (i == 7 && f == true)
		cout << endl << "К сожалению, Вы не угадали" << endl << "Загаданное число: " << x ;
	return 0;
}