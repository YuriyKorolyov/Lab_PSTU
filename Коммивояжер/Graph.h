#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;
using namespace sf;

const int R = 40.f;
const float pi = 3.14159f;

template <class T>
class Graph
{
private:
	vector<T> vertexList;//Вектор вершин
	vector<vector<int>> adjMatrix;//Матрица смежности
	int maxSize;//Размер вектора вершин и матрицы смежности
public:
	vector<vector<float>> d;

	vector<CircleShape> circles;//вектор вершин
	vector<Text> textes;//вектор названий вершин
	vector<Text> edges;//вектор весов ребер
	vector<VertexArray> lines;//вектор ребер

	void findway();                            //нахождение кратчайшего пути
	float findshortest(int i, int mask);       //нахождение кратчайшего расстояния
	Graph(const int& size);                    //конструктор графа с параметрами
	Graph() : Graph(0) {};                     //конструктор графа без параметров
	void MakeGraph(RenderWindow& window);      //создание графа, определение расположения вершин в окне
	void MakeMatrix();                         //заполнение матрицы смежности
	void Draw(RenderWindow& window);           //инициализация векторов названий вершин, ребер и их весов
	void insertVertex(RenderWindow& window);   //дабавление вершины
	void InsertEdge(const T&, const T&, int&); //инициализация величины ребра между вершинами
	void DeleteVertex();                       //удаление вершины
	void Print();                              //печать матрицы смежности
	bool isEmpty();                            //true, если граф пустой
	bool isFull();                             //true, если граф полный
	int GetVertPos(const T&);                  //Возвращает позицию вершины в списке вершин
	int GetAmountVerts();                      //Возвращает количество вершин
	int GetAmountEdges();                      //Количество ребер для неориентированного графа
	int GetWeight(const T&, const T&);         //получить вес ребра
};

//нахождение кратчайшего пути
template<class T>
inline void Graph<T>::findway()
{
	vector<int> path;
	int i = 0;
	int n = GetAmountVerts();
	int mask = (1 << n) - 1;
	path.push_back(0);
	while (mask != 0)
	{
		for (int j = 0; j < n; j++)
		{
			if (adjMatrix[i][j])
				if ((mask & (1 << j)))
					if (d[mask][i] == adjMatrix[i][j] + d[mask ^ (1 << j)][j])
					{
						path.push_back(j);
						i = j;
						mask = mask ^ (1 << j);
					}
		}
	}
	cout << "Кратчайший путь: ";
	for (int i = 0; i < n; i++)
		cout << vertexList[path[i]] << "->";
	cout << vertexList[path[i]] << endl;
}

//нахождение кратчайшего расстояния
template<class T>
inline float Graph<T>::findshortest(int i, int mask)
{
	float inf = 1e10;
	int n = GetAmountVerts();
	if (d[mask][i] != inf)
	{
		return d[mask][i];
	}
	for (int j = 0; j < n; j++)
	{
		if (adjMatrix[i][j])
			if ((mask & (1 << j)))
			{

				d[mask][i] = min(d[mask][i], findshortest(j, mask - (1 << j)) + adjMatrix[i][j]);
			}
	}
	return d[mask][i];
}

//инициализация векторов названий вершин, ребер и их весов
template<class T>
inline void Graph<T>::Draw(RenderWindow& window)
{
	textes.clear();
	edges.clear();
	lines.clear();
	
	Font font1;
	font1.loadFromFile("tahoma.ttf");

	Text text;
	text.setFont(font1);
	text.setFillColor(Color::White);
	text.setCharacterSize(50);

	for (int i = 0; i < vertexList.size(); i++)//названия
	{
		text.setString(vertexList[i]);
		FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		text.setPosition(circles[i].getPosition());
		textes.push_back(text);
	}

	text.setFillColor(Color::White);
	text.setCharacterSize(30);

	for (int i = 0; i < vertexList.size(); i++)//ребра и их веса		
		for (int j = 0; j < vertexList.size(); j++)
			if (adjMatrix[i][j] != 0)
			{
				VertexArray liness(LineStrip, 2);
				liness[0].position = Vector2f(circles[i].getPosition().x, circles[i].getPosition().y);
				liness[1].position = Vector2f(circles[j].getPosition().x, circles[j].getPosition().y);
				liness[0].color = Color(0, 119, 255);
				liness[1].color = Color(0, 119, 255);
				lines.push_back(liness);
				text.setString(to_string(adjMatrix[i][j]));
				FloatRect textRect = text.getLocalBounds();
				text.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				text.setPosition((circles[i].getPosition().x + circles[j].getPosition().x) / 2, 
					(circles[i].getPosition().y + circles[j].getPosition().y) / 2);
				edges.push_back(text);
			}
}

//конструктор графа
template<class T>
inline Graph<T>::Graph(const int& size)
{
	this->maxSize = size;
	this->adjMatrix = vector<vector<int>>(size, vector<int>(size));
	for (int i = 0; i < this->maxSize; ++i)
	{
		for (int j = 0; j < this->maxSize; ++j)
		{
			this->adjMatrix[i][j] = 0;
		};
	};
};

//создание вершины
template<class T>
inline void Graph<T>::insertVertex(RenderWindow& window)
{
	if (isFull())
	{
		maxSize++;
		insertVertex(window);
		vector<int> temp(maxSize);
		for (int i = 0; i < vertexList.size() - 1; i++)
		{
			cout << "Введите расстояние до " << vertexList[i] << ": ";
			cin >> temp[i];
		}
		temp[maxSize - 1] = 0;
		adjMatrix.push_back(temp);
		for (int i = 0; i < maxSize - 1; i++)
		{
			adjMatrix[i].push_back(temp[i]);
		}
		CircleShape circle(R);
		circle.setFillColor(Color(100, 250, 50));
		circle.setPointCount(100);
		circle.setOrigin(R, R);
		circle.setPosition(window.getSize().x / 2 + 200, window.getSize().y / 2);
		circles.push_back(circle);
	}
	else
	{
		cout << "Введите название вершины: ";
		T vert;
		cin >> vert;
		vertexList.push_back(vert);
	}
};

//инициализация величины ребра между вершинами
template<class T>
void Graph<T>::InsertEdge(const T& vertex1, const T& vertex2, int& weight)
{
	if (GetVertPos(vertex1) != (-1) && this->GetVertPos(vertex2) != (-1)) {
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2);

		if (this->adjMatrix[vertPos1][vertPos2] != 0)
		{
			cout << "Ребро между вершинами уже есть" << endl;
			return;
		}
		else
		{
			this->adjMatrix[vertPos1][vertPos2] = weight;
			this->adjMatrix[vertPos2][vertPos1] = weight;
		}
	}
	else
	{
		cout << "Обеих вершин (или одной из них) нет в графе " << endl;
		return;
	}
}

//удаление вершины
template<class T>
inline void Graph<T>::DeleteVertex()
{
	cout << "Введите название вершины для удаления: ";
	T vertex;
	cin >> vertex;
	if (maxSize == 0 || GetVertPos(vertex) == -1)
	{
		cout << "Удаление невозможно" << endl;
		return;
	}
	int c = GetVertPos(vertex);
	maxSize--;
	vertexList.erase(vertexList.begin() + c);
	adjMatrix.erase(adjMatrix.begin() + c);
	for (int i = 0; i < adjMatrix.size(); i++)
		adjMatrix[i].erase(adjMatrix[i].begin() + c);
	circles.erase(circles.begin() + c);
}

//создание графа, определение расположения вершин в окне
template<class T>
inline void Graph<T>::MakeGraph(RenderWindow& window)
{
	adjMatrix.clear();
	vertexList.clear();
	circles.clear();
	
	int size;
	cout << "Введите число вершин графа: ";
	cin >> size;
	maxSize = size;
	adjMatrix = vector<vector<int>>(maxSize, vector<int>(maxSize));
	for (int i = 0; i < maxSize; ++i)
	{
		for (int j = 0; j < maxSize; ++j)
		{
			adjMatrix[i][j] = 0;
		};
	};
	CircleShape circle(R);
	circle.setFillColor(Color(100, 250, 50));
	circle.setPointCount(100);
	circle.setOrigin(R, R);

	for (int i = 0; i < maxSize; i++)//позиция вершин в окне
	{
		circle.setPosition(window.getSize().x / 2 + 220 + 6 * R * cos(i * 2 * pi / maxSize),
			window.getSize().y / 2 + 6 * R * sin(i * 2 * pi / maxSize));
		circles.push_back(circle);
	}
}

//заполнение матрицы смежности
template<class T>
inline void Graph<T>::MakeMatrix()
{
	for (int i = 0; i < vertexList.size(); i++)
		for (int j = 0; j < vertexList.size() && j != i; j++)
		{
			cout << "Введите расстояние между: " << vertexList[i] << " и " << vertexList[j] << ": ";
			int weight;
			cin >> weight;
			InsertEdge(vertexList[i], vertexList[j], weight);
		}
}

//проверка на пустоту графа
template<class T>
inline bool Graph<T>::isEmpty()
{
	return this->vertexList.size() == 0;
};

//проверка на заполненность графа
template<class T>
inline bool Graph<T>::isFull()
{
	return this->vertexList.size() == this->maxSize;
};

//получение индекса вершины
template<class T>
inline int Graph<T>::GetVertPos(const T& v)
{
	for (int i = 0; i < this->vertexList.size(); ++i)
	{
		if (this->vertexList[i] == v)
		{
			return i;
		}
	}
	return -1;
};

//сколько вершин добавлено в граф
template<class T>
inline int Graph<T>::GetAmountVerts()
{
	return this->vertexList.size();
};

//сколько ребер в графе, соединяющих вершины
template<class T>
int Graph<T>::GetAmountEdges()
{
	int amount = 0;
	if (!this->IsEmpty())
	{
		for (int i = 0; i < this->vertexList.size(); ++i)
		{
			for (int j = 0; j < this->vertexList.size(); ++j)
			{
				if (this->adjMatrix[i][j] != 0)
				{
					amount++;
				}
			}
		}
	}
	return amount;
};

//величина ребра между двумя вершинами
template<class T>
inline int Graph<T>::GetWeight(const T& v1, const T& v2)
{
	if (this->isEmpty())
	{
		return 0;
	};

	int v1_p = this->GetVertPos(v1);
	int v2_p = this->GetVertPos(v2);

	if (v1_p == -1 || v2_p == -1)
	{
		cout << "Одного из узлов в графе не существует." << endl;
		return 0;
	};

	return this->adjMatrix[v1_p][v2_p];
};

//печать матрицы смежности графа
template<class T>
void Graph<T>::Print() {
	if (!this->isEmpty())
	{
		cout << "Матрица смежности графа: " << endl;

		cout << "-  ";
		for (int i = 0; i < vertexList.size(); ++i)
		{
			cout << vertexList[i] << "  ";
		}
		cout << endl;

		for (int i = 0; i < this->vertexList.size(); ++i) {
			cout << this->vertexList[i] << " ";
			for (int j = 0; j < this->vertexList.size(); ++j) {
				cout << " " << this->adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "Граф пуст " << endl;
	}
}