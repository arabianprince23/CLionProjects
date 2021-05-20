#include <iostream>
using namespace std;

int bag(int N, int M, int* buys, int* weights)
{
    int** data = new int*[N + 1];

    for (int i = 0; i <= N; i++)
        data[i] = new int[M + 1];

    for(int i = 0; i <= M; i++)
        data[0][i] = 0;

    for(int i = 1; i <= N; i++) {
        for(int j = 0; j <= M; j++) {
            data[i][j] = data[i - 1][j];
            if (weights[i - 1] <= j) {
                if (data[i][j] < buys[i - 1] + data[i - 1][j - weights[i - 1]]) {
                    data[i][j] = buys[i - 1] + data[i - 1][j - weights[i - 1]];
                }
            }
        }
    }

    int res = data[N][M];

    for (int i = 0; i <= N; i++)
        delete[] data[i];
    delete[] data;

    return res;
}

int main() {
    int N, M;
    int* weights;
    int* buys;

    cin >> N >> M;
    weights = new int[N];
    buys = new int[N];

    for (int i = 0; i < N; i++) {
        cin >> weights[i];
    }

    for (int i = 0; i < N; i++) {
        cin >> buys[i];
    }

    cout << bag(N, M, buys, weights);

    return 0;
}