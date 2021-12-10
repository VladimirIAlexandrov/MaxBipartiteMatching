#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <string>
#include <vector>

// ������ ����� �� �����
bool read_graph(std::string filename, std::vector<std::vector<size_t>>& graph);

// ����� ����� �� �����
void write_graph(const std::vector<std::vector<size_t>>& graph);

// �������� ����� �� ������������
bool is_bipartite(const std::vector<std::vector<size_t>>& graph,
	std::vector<size_t>& first, std::vector<size_t>& second);

#endif // UTILS_H

