#include "ReadWriter.cpp"
#include <algorithm>
using namespace std;

//Можно добавлять любые методы для решения задачи.
bool comparator(Node *n1, const Node *n2) {
    return n2->name >= n1->name;
}

void deep(Node &node, vector<Node> &graph, vector<string> &res) {
    // тк обход в глубину, если уже были в этом узле, закругляемся
    if (node.visited) {
        return;
    }

    node.visited = true;
    vector<Node*> nodes;
    nodes.reserve(node.neighbours.size());

    res.push_back(node.name);

    for (int i = 0; i < node.neighbours.size(); ++i) {
        nodes.push_back(node.neighbours[i]);
    }

    sort(nodes.begin(), nodes.end(), comparator);

    for (int i = 0; i < nodes.size(); ++i) {
        deep(*nodes[i], graph, res);
    }
}

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node> &graph, int start, std::vector<std::string> &result) {
    deep(graph[start], graph, result);
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
