#include <iostream>
using namespace std;

void artemy(int N, int A, int B, int C) {

    int* levels = new int[N];

    levels[0] = 1;
    for (int i = 1; i < N; ++i)
        levels[i] = 0;

    for (int i = 0; i < N - 1; i++)
        if (levels[i] == 1) {
            if (i < N - A) { levels[i + A] = 1; }
            if (i < N - B) { levels[i + B] = 1; }
            if (i < N - C) { levels[i + C] = 1; }
        }

    int result = 0;
    for (int i = 0; i < N; i++)
        result += levels[i];

    cout << result;

    delete[] levels;
}

int main() {
    int N, A, B, C;
    cin >> N >> A >> B >> C;
    artemy(N, A, B, C);
    return 0;
}