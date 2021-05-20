#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int quantity;

bool comparator(vector<string> &first, vector<string> &second) {
    return first.front() < second.front();
}

void dfs0(int v, vector<vector<bool>>& relations, stack<int>& order, vector<bool>& used) {
    used[v] = true;
    for (int i = 0; i < relations.size(); ++i)
        if (!used[i])
            if (relations[v][i])
                dfs0(i, relations, order, used); // Если еще не были и сущ-ет связь, рекурсия
    order.push(v);
}

void dfs1(int v, vector<vector<bool>>& relations, vector<string>& names , stack<int>& order, vector<bool>& used, vector<string>& vec) {
    used[v] = true;
    for (int i = 0; i < relations.size(); ++i)
        if (!used[i])
            if (relations[i][v])
                dfs1(i, relations, names, order, used, vec); // Если еще не были и сущ-ет связь, рекурсия
    quantity += 1;
    vec.emplace_back(names[v]);
}

vector<vector<string>> getList(vector<string>& names, vector<vector<bool>>& relations) {
    vector<vector<string>> data;
    vector<bool> used (names.size(), false);
    stack <int> order;

    for(int i = 0; i < relations.size(); ++i)
        if (!used[i])
            dfs0(i, relations, order, used);

    used.assign(names.size(), false);

    while (quantity < names.size()) {
        if (used[order.top()]) {
            order.pop();
        } else {
            vector<string> tmpResult;
            dfs1(order.top(), relations, names, order, used, tmpResult);
            sort(tmpResult.begin(), tmpResult.end());
            data.emplace_back(tmpResult);
            order.pop();
        }
    }
    sort(data.begin(), data.end(), comparator);
    return data;
}

int main()
{
    vector<string> names = vector<string>();
    vector<vector<bool>> relations;
    int startIndex;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        string str = "";
        getline(fin, str);

        while (str != "#")
        {
            names.emplace_back(str.substr(str.find(' ') + 1));
            getline(fin, str);
        }

        relations = vector<vector<bool>>(names.size());

        for (int i = 0; i < names.size(); i++)
        {
            relations[i] = vector<bool>(names.size());
            for (int j = 0; j < names.size(); j++)
                relations[i][j] = false;
        }

        getline(fin, str);

        while (fin)
        {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            getline(fin, str);
        }

        fin.close();
    }

    vector<vector<string>> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            fout << res[i][j] << "\n";
        fout << "\n";
    }
    fout.close();

    return 0;
}