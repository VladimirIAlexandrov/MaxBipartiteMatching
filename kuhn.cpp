#include "kuhn.h"
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

// Попытка выполнить алгоритм Куна
bool try_algorithm_kuhn(size_t from, const vector<vector<size_t>>& graph, vector<int>& pairs,
	vector<bool>& visited, const vector<size_t>& first, const vector<size_t>& second)
{
    int vfrom = std::distance(first.begin(), std::find(first.begin(), first.end(), from));
    if (visited[vfrom])
        return false;
    visited[vfrom] = true;
    for (size_t i = 0; i < graph[from].size(); i++) 
    {
        int to = std::distance(second.begin(), std::find(second.begin(), second.end(), graph[from][i]));
        if (pairs[to] == -1 || try_algorithm_kuhn(pairs[to], graph, pairs, visited, first, second))
        {
            pairs[to] = from;
            return true;
        }
    }
    return false;
}
// Запуск алгоритма Куна
void algorithm_kuhn(const vector<vector<size_t>>& graph,
    const vector<size_t>& first, const vector<size_t>& second)
{
    size_t n = first.size(); 
    size_t k = second.size();

    vector<int> pairs;
    pairs.assign(k, -1);

    for (size_t v = 0; v < n; v++) 
    {
        vector<bool> visited;
        visited.assign(n, false);
        try_algorithm_kuhn(first[v], graph, pairs, visited, first, second);
    }

    ofstream fout("rez.txt");
    std::cout << "Максимальное паросочетание:" << std::endl;
    fout << "Максимальное паросочетание:" << std::endl;
    for (size_t i = 0; i < k; ++i) {
        if (pairs[i] != -1) {
            std::cout << pairs[i] + 1 << " - " << second[i] + 1 << std::endl;
            fout <<  pairs[i] + 1 << "-" <<second[i] + 1 << std::endl;

        }
    }
    fout.close();
    system("pause");
}