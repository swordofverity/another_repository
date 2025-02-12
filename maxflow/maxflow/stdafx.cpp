#include "stdafx.h"
// Алгоритм Форда — Фалкерсона c++
#include <iostream>
#include <algorithm>
#include <clocale>
#include<Windows.h>

using namespace std;

const int MAX_E = (int) 1e6;
const int MAX_V = (int) 1e3;
const int INF = (int) 1e9;

int numOfVertex, numOfEdge, sourceVertex, destinationVertex;
int capacity[MAX_E], onEnd[MAX_E], nextEdge[MAX_E], edgeCount;
int firstEdge[MAX_V], visited[MAX_V];

void addEdge(int u, int v, int cap) {
	// Прямое ребро
	onEnd[edgeCount] = v;                   // на конце прямого v
	nextEdge[edgeCount] = firstEdge[u];     // добавляем в начало списка для u
	firstEdge[u] = edgeCount;               // теперь начало списка - новое ребро
	capacity[edgeCount++] = cap;            // устанавливаем пропускную способность
	// Обратное ребро
	onEnd[edgeCount] = u;                   // на конце обратного u
	nextEdge[edgeCount] = firstEdge[v];     // добавляем в начало списка для v
	firstEdge[v] = edgeCount;               // теперь начало списка - новое ребро
	capacity[edgeCount++] = 0;              // устанавливаем пропускную способность
}

int findFlow(int u, int flow) {
	if (u == destinationVertex) return flow; // возвращаем полученный минимум на пути
	visited[u] = true;
	for (int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) {
		int to = onEnd[edge];
		if (!visited[to] && capacity[edge] > 0) {
			int minResult = findFlow(to, min(flow, capacity[edge])); // ищем поток в поддереве
			if (minResult > 0) {                    // если нашли
				capacity[edge] -= minResult;   // у прямых ребер вычетаем поток
				capacity[edge ^ 1] += minResult;   // к обратным прибавляем
				return minResult;
			}
		}
	}
	return 0; // если не нашли поток из этой вершины вернем 0
}

int main() {

	int a;
	cout << "Welcome to the Ford-Fulkerson programm"<< endl ;
	cout << "This programm should count the maximal flow of the graph that you will enter, " << endl;
	cout << "so you shouldnt do it by yourself :) " << endl;
	cout << " " << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << " " << endl;

	label:

	fill(firstEdge, firstEdge + MAX_V, -1);  	// -1 означает ребра нет
	cout << "First of all, you should enter the number of vertices: ";
	cin >> numOfVertex;
	cout << endl;
	cout << "Then please, enter the number of edges: ";
	cin >> numOfEdge;            // считываем количество вершин и ребер
	cout  << endl;
	cout << "Then enter the source of the graph: ";
	cin >> sourceVertex;
	cout << endl;
	cout << "And finnaly, enter the sink of the graph: " << endl;
	cin	>> destinationVertex;   // считываем источник и сток
	cout << " " << endl;
	cout << "------------------------------------------" << endl;
	cout << " " << endl;
	cout << "Now please enter the capacity of the edges (you should enter the initial verticle, " << endl;
	cout << "the final verticle and their capacity) " << endl;
	cout << " " << endl;
	cout << "------------------------------------------" << endl;
	cout << " " << endl;
	for (int i = 0, u, v, cap; i < numOfEdge; i++) {
		cout << "From the verticle: "; 
		cin >> u;
		cout << endl;;
		cout << "To verticle: ";
		cin >> v;
		cout << endl;;
		cout << "Please enter the edge capacity: ";
		cin >> cap;
		cout << endl;;
		addEdge(u, v, cap);
	}
	cout << " " << endl;
	cout << "------------------------------------------" << endl;
	cout <<  endl;
	// Нахождение максимального потока
	int maxFlow = 0;
	int iterationResult = 0;
	while ((iterationResult = findFlow(sourceVertex, INF)) > 0) {
		fill(visited, visited + MAX_V, false);
		maxFlow += iterationResult;
	}
	// Выводим максимальный поток

	cout << "Okay, so that's all." << endl;
	cout << "The Max Flow is " << maxFlow << endl;
	cout << " " << endl;


	cout << "If you want to repeat the maxflow searching procces enter 1 " << endl;
	cout << "If you want to exit the programm enter 0 " << endl;
	cin >> a;

	switch (a) // начало оператора switch
	{
	case 1: goto label;	break;

	case 0: cout << "Thank you for using this programm." << endl; system("pause"); exit(0);

	}

	system("pause");
	return 0;
}