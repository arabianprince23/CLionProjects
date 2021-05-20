#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

void way(int** data, pair<int, int>* items, vector<pair<int, int>>& res, int i, int j) {
    if (data[i][j] == 0)
        return;
    else if (data[i - 1][j] != data[i][j]) {
        way(data, items, res, i - 1, j - items[i - 1].first);
        res.push_back(items[i - 1]);
    }
    else {
        way(data, items, res, i - 1, j);
    }
}

//Задача реализовать этот метод
//param N - количество предметов
//param W - ограничения на вес рюкзака
//param items - массив размера N, с предметами - first = вес, second = стоимость
//param res - вектор результатов (предметы, которые надо взять)
void solve(int N, int W, pair<int, int>* items, vector<pair<int, int>>& res)
{
    int** data = new int*[N + 1];

    for (int i = 0; i <= N; ++i) {
        data[i] = new int[W + 1];
    }

    for (int i = 0; i <= W; ++i) {
        data[0][i] = 0;
    }

    for (int i = 1; i <= N; ++i) {
        for(int j = 0; j <= W; ++j) {
            data[i][j] = data[i - 1][j];
            if (j >= items[i - 1].first) {
                if (data[i - 1][j - items[i - 1].first] + items[i - 1].second > data[i][j]) {
                    data[i][j] = data[i - 1][j - items[i - 1].first] + items[i - 1].second;
                }
            }
        }
    }

    way(data, items, res, N, W);

    for (int i = 0; i <= N; i++)
        delete[] data[i];
    delete[] data;
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //количество предметов
    int W = rw.readInt(); //ограничения на вес рюкзака

    //структура массив pair выбрана, так как известно количество и у объекта всего 2 характеристики
    //first = вес(weight), second = стоимость (cost)
    //Можно переложить данные в любую другую удобную струтуру
    //Внимание(!) данные не упорядочены, но можно это сделать если вам требуется
    pair<int, int>* arr = new pair<int, int>[N];
    rw.readArr(arr, N);

    //структура вектор pair выбрана, так как неизвестно количество элементов, и у объекта всего 2 характеристики
    //результат, также first = вес(weight), second = стоимость (cost)
    vector<pair<int, int>> res;
    solve(N, W, arr, res);

    int sumCost = 0, sumWeight = 0;
    for (int i = 0; i < res.size(); i++)
    {
        sumWeight += res[i].first;
        sumCost += res[i].second;
    }
    //записываем ответ в файл
    rw.writeInt(sumCost);
    rw.writeInt(sumWeight);
    rw.writeInt(res.size());
    rw.writeVector(res);

    delete[] arr;
    return 0;
}