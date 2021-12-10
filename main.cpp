#pragma warning(disable : 4996)
#include "kuhn.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>"
#include <fstream>
#include <iostream>

#include <cstdlib>
#include <queue>
#include <sstream>
using namespace std;
int rand_graph(int** graph, int size)
{
	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			graph[i][j] = rand()%2;
			graph[j][i] = graph[i][j];
		}
	}


	return 0;

}

int rand_2dol(vector<size_t> first, vector<size_t> second, vector<vector<size_t>> graph_s)
{
	int size1, size2, size3, ** graph;
	printf("Ведите размер доли");
	scanf_s("%d", &size1);
	printf("Ведите размер доли");
	scanf_s("%d", &size2);
	size3 = size1 + size2;

	graph = (int**)malloc(size3 * sizeof(int));
	for (int i = 0; i < size3; i++)
	{
		graph[i] = (int*)malloc(size3 * sizeof(int));
	}
	rand_graph(graph, size3);

	for (int i = 0; i < size3; i++)
	{
		for (int j = 0; j < size3; j++)
		{
			if (i < size1 && j < size1) {
				graph[i][j] = 0;
			}
			

		}
	}

	for (int i = 0; i < size3; i++)
	{
		for (int j = 0; j < size3; j++)
		{
			if (i >= size1 && j>= size1) {
				graph[i][j] = 0;
			}
		}
	}
	
	while (!is_bipartite(graph_s, first, second)) {
		rand_2dol(first, second, graph_s);
	}

	for (int i = 0; i < size3; i++)
	{
		for (int j = 0; j < size3; j++)
		{
			if (i == j) {
				graph[i][j] = 0;
			}
			printf("%2d", graph[i][j]);
		}
		printf("\n");
	}

	
	FILE* file;
	file = fopen("SomeText.txt", "w");
	for (int i = 0; i < size3; i++)
	{
		if (i != 0) {
			fprintf(file, "\n");
		}
		fprintf(file, "%d ", i + 1);
		
		for (int j = 0; j < size3; j++)
		{
			if (graph[i][j] == 1)
			{
				
				fprintf(file, "%d ", j+1);
			}
		}
		
	}
	fclose(file);
	return 0;
}


int main()
{
	srand(time(NULL));
	setlocale(LC_CTYPE, "Russian");
	int k;
	std::cout << "Выбирите способ задачи графа (2 - сущ. из файла | 1 - сгенерировать случайный) ";
	
	
	
	std::cin >> k; 
	std::string filename;
	vector<size_t> first, second;
	vector<vector<size_t>> graph;
	if (k == 1)
	{
		rand_2dol(first, second, graph);
		filename = "SomeText.txt";

	}
	else {
		std::cout << "Введите имя файла: ";
		std::cin >> filename;
	}
	
	
	if (read_graph(filename, graph))
	{
		std::cout << "Граф: " << std::endl;
		write_graph(graph);

		//vector<size_t> first, second;
		if (is_bipartite(graph, first, second))
			algorithm_kuhn(graph, first, second);
		else
			
			std::cout << "Граф не двудольный" << std::endl;
	}
	else
		std::cout << "Файл не найден или возникла ошибка при чтении графа" << std::endl;
}