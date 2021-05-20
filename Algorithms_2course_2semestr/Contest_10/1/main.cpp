#include "ReadWriter.cpp"
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

//Можно добавлять любые методы для решения задачи.
bool comparator(const Node &first, const Node &second) {
    return first.name < second.name;
}

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node> &graph, int start, std::vector<std::string> &result)
{
    queue<Node> queue;
    queue.push(graph[start]);
    graph[start].visited = true;

    while (!queue.empty()) {
        vector<Node> tmp;
        int queueSize = queue.size();
        for (int i = 0; i < queueSize; ++i) {
            Node first = queue.front();
            queue.pop();
            tmp.push_back(first);
            for (Node *neighbour : first.neighbours)
                if (!neighbour->visited) {
                    neighbour->visited = true;
                    queue.push(*neighbour);
                }
        }

        sort(tmp.begin(), tmp.end(), comparator);
        for (int i = 0; i < tmp.size(); ++i) {
            result.push_back(tmp[i].name);
        }
    }
}

int main() {
    std::vector<Node> graph;
    std::vector<std::string> result;
    int start;

    ReadWriter rw;
    rw.readGraph(graph, start);
    solve(graph, start, result);
    rw.writeAnswer(result);
    return 0;
}
