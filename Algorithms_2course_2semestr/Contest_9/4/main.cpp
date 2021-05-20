#include "ReadWriter.h"
//string, iostream included in "ReadWriter.h"

using namespace std;
//Можно добавлять любые вспомогательные методы и классы для решения задачи.
long long quantityOfCells(long long **data, int N, int M, int i, int j) {

    if (data[i][j] > 0)
        return data[i][j];

    data[i][j] = 0;

    if (i > 0 && j > 1)
        data[i][j] += quantityOfCells(data, N, M, i - 1, j - 2);
    if (i > 1 && j > 0)
        data[i][j] += quantityOfCells(data, N, M, i - 2, j - 1);
    if (i > 1 && j < M - 1)
        data[i][j] += quantityOfCells(data, N, M, i - 2, j + 1);
    if (i < N - 1 && j > 1)
        data[i][j] += quantityOfCells(data, N, M, i + 1, j - 2);

    return data[i][j];
}

//Задача реализовать этот метод
//param N - количество строк (rows) доски
//param M - количество столбцов (columns) доски
//return - количество способов попасть в правый нижний угол доски (клетка N-1, M-1, если считать что первая клетка 0,0)
long long solve(int N, int M)
{
    long long **data = new long long *[N];
    for (int i = 0; i < N; ++i)
        data[i] = new long long[M];

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            data[i][j] = -1;

    data[0][0] = 1;
    int res = quantityOfCells(data, N, M, N - 1, M - 1);

    for (int i = 0; i < N; ++i)
        delete[] data[i];
    delete[] data;

    return res;
    //временная заглушка return 0
//    return 0;
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;

    int N = rw.readInt(); //количество строк (rows)
    int M = rw.readInt(); //количество столбцов (columns)
    //решение
    long long res = solve(N, M);
    //результат в файл
    rw.writeLongLong(res);

    return 0;
}