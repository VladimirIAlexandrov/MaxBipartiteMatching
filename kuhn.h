#ifndef KUHN_H
#define KUHN_H

#include <vector>

using std::vector;

// Запуск алгоритма Куна
void algorithm_kuhn(const vector<vector<size_t>>& graph,
	const vector<size_t>& first, const vector<size_t>& second);

#endif // KUHN_H