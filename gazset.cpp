#include "gazset.h"
#include <vector>
#include <queue>

void gazset::setpipe(pipe p,int id)
{
	Pipe[id] = p;
}

void gazset::setStartCs(cs c,int id)
{
	Cs1[id] = c;
}

void gazset::setEndCs(cs c, int id)
{
	Cs2[id] = c;
}

pipe gazset::getPipe(int id)
{
	return Pipe[id];
}

cs gazset::getStartCs(int id)
{
	return Cs1[id];
}

cs gazset::getEndCs(int id)
{
	return Cs2[id];
}

void gazset::createCon(pipe p, cs c1, cs c2,int i)
{
	Pipe[i] = p;
	Cs1[i] = c1;
	Cs2[i] = c2;
}

vector<int> gazset::topologicalSort() {
    map<int, vector<int>> adjList;  // Список смежности
    map<int, int> inDegree;         // Степень входа для каждой станции

    // Строим список смежности и вычисляем степени входа
    for (const auto& entry : Cs2) {
        for (const auto& e : Cs1) {
            int startId = e.first;  // id начальной компрессорной станции
            int endId = entry.first;   // id конечной компрессорной станции

            adjList[startId].push_back(endId);  // Добавляем ребро
            inDegree[endId]++;  // Увеличиваем степень входа
        }

    }

    // Ищем все вершины с нулевой степенью входа
    queue<int> q;
    for (const auto& entry : Cs1) {
        int csId = entry.first;
        if (inDegree[csId] == 0) {
            q.push(csId);
        }
    }

    // Результат топологической сортировки
    vector<int> topoSorted;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoSorted.push_back(node);

        // Обрабатываем все смежные вершины
        for (int neighbor : adjList[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // Проверяем на наличие циклов в графе
    if (topoSorted.size() != adjList.size()) {
        cout << "Cycle detected! Topological sort not possible." << endl;
        return {};
    }

    return topoSorted;
}
