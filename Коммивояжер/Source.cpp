#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include "Graph.h"
using namespace std;
using namespace sf;

const int Width = 1280;//ширина окна по умолчанию
const int Height = 900;//высота окна по умолчанию

//коллизии кругов
bool CheckCollisionC(CircleShape& its, CircleShape& other, float push);
//коллизии прямоугольника и круга
bool CheckCollisionR(RectangleShape& its, CircleShape& other, float push);

int main()
{
	setlocale(LC_ALL, "ru");

	Graph<string> g;//экземпляр класса Graph

	RenderWindow window(VideoMode(Width, Height), L"Коммивояжер");//создание окна
	
	int index;
	bool isMove = false;//переменная для щелчка мыши по спрайту
	float dX = 0;//корректировка нажатия по х
	float dY = 0;//по у
	
	//шрифт текста Tahoma
	Font font;
	font.loadFromFile("tahoma.ttf");
	
	//иконка окна
	Image icon;
	icon.loadFromFile("3.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	while (window.isOpen())
	{
		window.clear(Color::Cyan);//фон окна
		
		//фоновый прямоугольник для меню
		RectangleShape rectangle(Vector2f(440, window.getSize().y));
		rectangle.setOrigin(220.f, window.getSize().y / 2);
		rectangle.setFillColor(Color::White);
		rectangle.setPosition(220.f, window.getSize().y / 2);
		window.draw(rectangle);

		////////////////МЕНЮ////////////////
		Text menu1, menu2, menu3, menu4, menu5, menu6;
		menu1.setFont(font);
		menu1.setFillColor(Color(0, 119, 255));
		menu1.setCharacterSize(30);
		menu2 = menu1;
		menu3 = menu1;
		menu4 = menu1;
		menu5 = menu1;
		menu6 = menu1;

		//текст меню
		menu1.setString(L"Новый граф");
		menu2.setString(L"Добавить вершину");
		menu3.setString(L"Удалить вершину");
		menu4.setString(L"Показать матрицу смежности");
		menu5.setString(L"Создать матрицу смежности");
		menu6.setString(L"Задача коммивояжера");

		//определяем начало координат для меню
		menu1.setOrigin(0.f, menu1.getLocalBounds().top + menu1.getLocalBounds().height / 2.0f);
		menu2.setOrigin(0.f, menu2.getLocalBounds().top + menu2.getLocalBounds().height / 2.0f);
		menu3.setOrigin(0.f, menu3.getLocalBounds().top + menu3.getLocalBounds().height / 2.0f);
		menu4.setOrigin(0.f, menu4.getLocalBounds().top + menu4.getLocalBounds().height / 2.0f);
		menu5.setOrigin(0.f, menu5.getLocalBounds().top + menu5.getLocalBounds().height / 2.0f);
		menu6.setOrigin(0.f, menu6.getLocalBounds().top + menu6.getLocalBounds().height / 2.0f);

		//располагаем меню в окне
		menu1.setPosition(10, window.getSize().y / 2 - 150);
		menu2.setPosition(10, window.getSize().y / 2 - 90);
		menu3.setPosition(10, window.getSize().y / 2 - 30);
		menu4.setPosition(10, window.getSize().y / 2 + 30);
		menu5.setPosition(10, window.getSize().y / 2 + 90);
		menu6.setPosition(10, window.getSize().y / 2 + 150);

		int menuNum = 0;

		//если кнопка меню содержит координаты курсора, то красим её в черный цвет и запоминаем выполняемое действие
		if (IntRect(menu1.getGlobalBounds().left, menu1.getGlobalBounds().top, menu1.getGlobalBounds().width, menu1.getGlobalBounds().height).contains(Mouse::getPosition(window))) { menu1.setFillColor(Color(0, 0, 0)); menuNum = 1; }
		if (IntRect(menu2.getGlobalBounds().left, menu2.getGlobalBounds().top, menu2.getGlobalBounds().width, menu2.getGlobalBounds().height).contains(Mouse::getPosition(window))) { menu2.setFillColor(Color(0, 0, 0)); menuNum = 2; }
		if (IntRect(menu3.getGlobalBounds().left, menu3.getGlobalBounds().top, menu3.getGlobalBounds().width, menu3.getGlobalBounds().height).contains(Mouse::getPosition(window))) { menu3.setFillColor(Color(0, 0, 0)); menuNum = 3; }
		if (IntRect(menu4.getGlobalBounds().left, menu4.getGlobalBounds().top, menu4.getGlobalBounds().width, menu4.getGlobalBounds().height).contains(Mouse::getPosition(window))) { menu4.setFillColor(Color(0, 0, 0)); menuNum = 4; }
		if (IntRect(menu5.getGlobalBounds().left, menu5.getGlobalBounds().top, menu5.getGlobalBounds().width, menu5.getGlobalBounds().height).contains(Mouse::getPosition(window))) { menu5.setFillColor(Color(0, 0, 0)); menuNum = 5; }
		if (IntRect(menu6.getGlobalBounds().left, menu6.getGlobalBounds().top, menu6.getGlobalBounds().width, menu6.getGlobalBounds().height).contains(Mouse::getPosition(window))) { menu6.setFillColor(Color(0, 0, 0)); menuNum = 6; }

		Vector2i pixelPos = Mouse::getPosition(window);//сохраняем координаты курсора
		
		Event event;
		while (window.pollEvent(event))//работа с событиями
		{
			if (event.type == Event::Closed)//закрытие окна
				window.close();
			if (event.type == sf::Event::Resized)//регулировка размера окна
			{
				FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(View(visibleArea));
			}
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left)//а именно левая
					for (int i = 0; i < g.GetAmountVerts(); i++)
						if (g.circles[i].getGlobalBounds().contains(pixelPos.x, pixelPos.y))//и при этом координата курсора попадает в вершину графа
						{
							dX = pixelPos.x - g.circles[i].getPosition().x;//сохраняем разность между позицией курсора и круга для корректировки нажатия
							dY = pixelPos.y - g.circles[i].getPosition().y;//тоже самое по Y
							isMove = true;//можем двигать вершину
							index = i;//запоминаем индекс вершины графа, которая двигается
						}
			if (event.type == Event::MouseButtonReleased)//если отпустили клавишу
				if (event.key.code == Mouse::Left && isMove == true) //а именно левую
				{
					for (int i = 0; i < g.GetAmountVerts(); i++)
						if (g.circles[i].getGlobalBounds().contains(pixelPos.x, pixelPos.y))
							isMove = false; //то не можем двигать вершину
					g.circles[index].setFillColor(Color(100, 250, 50));//и окрашиваем в прежний цвет
				}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{//если нажали на меню левой кнопкой мыши
					if (menuNum == 1)
					{//создание пустого графа
						g.MakeGraph(window);
					}
					if (menuNum == 2)
					{//добавление вершины
						g.insertVertex(window);
					}
					if (menuNum == 3)
					{//удаление вершины
						g.DeleteVertex();
					}
					if (menuNum == 4)
					{//печать матрицы смежности
						g.Print();
					}
					if (menuNum == 5)
					{//заполнение матрицы смежности
						g.MakeMatrix();
					}
					if (menuNum == 6)
					{//задача коммивояжера
						float inf = 1e10;
						vector<vector<float>> D((1 << g.GetAmountVerts()), vector<float>(g.GetAmountVerts(), inf));
						g.d = D;
						g.d[0][0] = 0;
						cout << "Кратчайшее расстояние: " << g.findshortest(0, (1 << g.GetAmountVerts()) - 1) << endl;
						g.findway();
					}
				}
			}
		}
		if (isMove)
		{//если можем двигать
			for (int i = 0; i < g.GetAmountVerts(); i++)
			{
				CheckCollisionC(g.circles[index], g.circles[i], 1.0f);//проверям на коллизии с другими вершинами графа
				g.circles[index].setFillColor(Color(255, 215, 0));//красим спрайт в желтый 
				g.circles[index].setPosition(pixelPos.x - dX, pixelPos.y - dY);//двигаем спрайт по Х //двигаем по Y
			}
		}
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);
		window.draw(menu5);
		window.draw(menu6);

		//граница окна сверху
		RectangleShape rectangle1(Vector2f(window.getSize().x, 50.0f));
		rectangle1.setOrigin(rectangle1.getSize() / 2.0f);
		rectangle1.setPosition(window.getSize().x / 2.0f, 0.0f);

		//граница окна справа
		RectangleShape rectangle2(Vector2f(50.0f, window.getSize().y));
		rectangle2.setOrigin(rectangle2.getSize() / 2.0f);
		rectangle2.setPosition(window.getSize().x, window.getSize().y / 2.0f);

		//граница окна снизу
		RectangleShape rectangle3(Vector2f(window.getSize().x, 50.0f));
		rectangle3.setOrigin(rectangle3.getSize() / 2.0f);
		rectangle3.setPosition(window.getSize().x / 2.0f, window.getSize().y);

		for (int i = 0; i < g.GetAmountVerts(); i++)
		{//проверяем коллизии для границы окна и вершин графа
			CheckCollisionR(rectangle, g.circles[i], 1.0f);//слева
			CheckCollisionR(rectangle1, g.circles[i], 1.0f);//сверху
			CheckCollisionR(rectangle2, g.circles[i], 1.0f);//справа
			CheckCollisionR(rectangle3, g.circles[i], 1.0f);//снизу
		}
		g.Draw(window);

		for (int i = 0; i < g.lines.size(); i++)
			window.draw(g.lines[i]);
		for (int i = 0; i < g.edges.size(); i++)
		{
			g.edges[i].setFont(font);
			window.draw(g.edges[i]);
		}
		for (int i = 0; i < g.GetAmountVerts(); i++)
		{
			window.draw(g.circles[i]);
			g.textes[i].setFont(font);
			window.draw(g.textes[i]);
		}
		window.display();
	}
	return 0;
}

//коллизии прямоугольника и круга
bool CheckCollisionR(RectangleShape& its, CircleShape& other, float push)
{
	Vector2f otherPosition = other.getPosition();
	Vector2f otherHalfSize = other.getOrigin();
	Vector2f itsPosition = its.getPosition();
	Vector2f itsHalfSize = its.getOrigin();

	float deltaX = otherPosition.x - itsPosition.x;
	float deltaY = otherPosition.y - itsPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + itsHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + itsHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = min(max(push, 0.0f), 1.0f);
		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				its.move(intersectX * (1.0f - push), 0.0f);
				other.move(-intersectX * push, 0.0f);
			}
			else
			{
				its.move(-intersectX * (1.0f - push), 0.0f);
				other.move(intersectX * push, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				its.move(0.0f, intersectY * (1.0f - push));
				other.move(0.0f, -intersectY * push);
			}
			else
			{
				its.move(0.0f, -intersectY * (1.0f - push));
				other.move(0.0f, intersectY * push);
			}
		}
		return true;
	}
	return false;
}

//коллизии кругов
bool CheckCollisionC(CircleShape& its, CircleShape& other, float push)
{
	Vector2f otherPosition = other.getPosition();
	Vector2f otherHalfSize = other.getOrigin();
	Vector2f itsPosition = its.getPosition();
	Vector2f itsHalfSize = its.getOrigin();

	float deltaX = otherPosition.x - itsPosition.x;
	float deltaY = otherPosition.y - itsPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + itsHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + itsHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = min(max(push, 0.0f), 1.0f);
		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				its.move(intersectX * (1.0f - push), 0.0f);
				other.move(-intersectX * push, 0.0f);
			}
			else
			{
				its.move(-intersectX * (1.0f - push), 0.0f);
				other.move(intersectX * push, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				its.move(0.0f, intersectY * (1.0f - push));
				other.move(0.0f, -intersectY * push);
			}
			else
			{
				its.move(0.0f, -intersectY * (1.0f - push));
				other.move(0.0f, intersectY * push);
			}
		}
		return true;
	}
	return false;
}