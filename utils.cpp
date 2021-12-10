#include "utils.h"
//#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>

// Чтение графа из файла в список смежности
bool read_graph(std::string filename, std::vector<std::vector<size_t>>& graph)
{
	try
	{
		std::ifstream input(filename);
		if (!input.good())
			return 0;
		while (!input.eof())
		{
			graph.push_back(std::vector<size_t>());
			std::string row;
			std::getline(input, row);
			std::stringstream ss(row);
			size_t a;
			ss >> a;
			while (ss >> a)
			{
				graph[graph.size() - 1].push_back(a - 1);
			}
		}
		return 1;
	}
	catch (std::exception&)
	{
		return 0;
	}
}

// Вывод графа на экран
void write_graph(const std::vector<std::vector<size_t>>& graph)
{
	for (size_t i = 0; i < graph.size(); i++)
	{
		std::cout << i + 1 << ": ";
		for (size_t j = 0; j < graph[i].size(); j++)
			std::cout << graph[i][j] + 1 << " ";
		std::cout << std::endl;
	}
}

// Вспомогательная функция для проверки графа на двудольность
bool is_bipartite_util(const std::vector<std::vector<size_t>>& graph,
	int src, std::vector<int>& param)
{
	param[src] = 1;

	std::queue<int> q;
	q.push(src);

	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		if (std::find(graph[u].begin(), graph[u].end(), u) != graph[u].end())
			return false;
		for (size_t v = 0; v < graph[u].size(); v++)
		{
			if (param[graph[u][v]] == -1)
			{
				param[graph[u][v]] = 1 - param[u];
				q.push(graph[u][v]);
			}
			else if (param[graph[u][v]] == param[u])
				return false;
		}
	}

	return true;
}

// Проверка графа на двудольность
bool is_bipartite(const std::vector<std::vector<size_t>>& graph,
	std::vector<size_t>& first, std::vector<size_t>& second)
{
	std::vector<int> param(graph.size(), -1);

	for (size_t i = 0; i < graph.size(); i++)
		if (param[i] == -1)
			if (!is_bipartite_util(graph, i, param))
				return 0;

	for (size_t i = 0; i < param.size(); i++)
		if (param[i])
			first.push_back(i);
		else
			second.push_back(i);
	return 1;
}