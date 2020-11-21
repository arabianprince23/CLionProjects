#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

int n, quantityOfThreads;
thread *threads;
vector<bool> usedMatrixLines;
int rankOfMatrix;
int **matrix;
const double epsilon = 1E-9;

void inputMatrix() {
    int elem;

    matrix = new int* [n]; // Инициализация матрицы
    for (int i = 0; i < n; i++)	{
        matrix[i] = new int[n];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "Введите элемент (" << i << ";" << j << ") : ";
            cin >> elem;
            matrix[i][j] = elem;
        }
    }
}

void computeRank(int temporary) {
    int tmp = 0;

    for (int i = 0; i < n; ++i) {
        if (!usedMatrixLines[i] && abs(matrix[i][temporary]) > epsilon) {
            tmp = i;
            break;
        }
    }

    if (n == tmp) {
        rankOfMatrix -= 1;
    } else {
        usedMatrixLines[tmp] = true;
    }
}

void changeMatrix(int j) {
    int tmp = 0;

    for (int i = 0; i < n; ++i) {
        if (!usedMatrixLines[i] && abs(matrix[i][j]) > epsilon) {
            tmp = i;
            break;
        }
    }

    if (n != tmp) {
        for (int m = j + 1; m < n; ++m) {
            matrix[tmp][m] /= matrix[tmp][j];
        }
        for (int q = 0; q < n; ++q) {
            if (q != tmp && abs(matrix[q][j]) > epsilon) {
                for (int r = j + 1; r < n; ++r) {
                    matrix[q][r] -= matrix[tmp][r] * matrix[q][j];
                }
            }
        }
    }
}

void matrixRankFunc() {
    if (quantityOfThreads == n) {
        for (int i = 0; i < n; ++i) {
            threads[i] = thread(changeMatrix, i);
        }

        for (int i = 0; i < n; ++i) {
            threads[i].join();
            computeRank(i);
        }
    } else {
        int tmp = 0;

        for (int i = 0; i < n; ++i) {
            if (tmp < quantityOfThreads) {
                threads[tmp] = thread(changeMatrix, i);
                ++tmp;
            }
            if (tmp == quantityOfThreads) {
                tmp = 0;
                for (int j = 0; j < quantityOfThreads; ++j) {
                    threads[j].join();
                }
            }
        }

        for (int i = 0; i < tmp; ++i) {
            threads[i].join();
        }

        for (int j = 0; j < n; ++j) {
            computeRank(j);
        }
    }
}

void printMatrix() {
    cout << endl << "Полученная матрица : " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void GetMatrixFromFile(string pathToFile) {
    ifstream in(pathToFile);
    in >> n >> quantityOfThreads;

    cout << "Полученное значение n : " << n << endl << "Полученное значение кол-ва потоков : " << quantityOfThreads << endl;
    rankOfMatrix = n;
    usedMatrixLines = vector<bool>(n);

    matrix = new int *[n];

    for (int i = 0; i < n; i++)	{
        matrix[i] = new int[n];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> matrix[i][j];
        }
    }
}

int main(int argc, char* argv[]) {

    // Начинаем отсчёт времени со старта работы программы
    auto begin = std::chrono::steady_clock::now();

    // В случае, если пользователь не передаёт в программу путь к файлу с матрицей, делаем ручной ввод
    if (argc == 1) {
        cout << "Введите n (размерность матрицы) : ";
        cin >> n;
        cout << "Введите количество потоков : ";
        cin >> quantityOfThreads;

        if (quantityOfThreads > n || n < 1 || quantityOfThreads < 1) {
            cout << endl << "Некорректный ввод!" << endl <<
                 "1. Количество потоков должно быть <= размерности матрицы." << endl <<
                 "2. Размерность матрицы должна быть >= 1." << endl <<
                 "3. Количество потоков должно быть >= 1.";
            return 0;
        }

        rankOfMatrix = n;
        threads = new thread[quantityOfThreads];
        usedMatrixLines = vector<bool>(n);

        inputMatrix(); // ввод пользователем матрицы
        printMatrix(); // вывод матрицы на экран
        matrixRankFunc(); // функция подсчета ранга матрицы

        cout << endl << "Полученный ранг матрицы: " << rankOfMatrix << endl; // Вывод результатов работы потока для ранга

        auto end = chrono::steady_clock::now();
        auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        cout << "Время работы программы : " << elapsed_ms.count() << " ms\n";
    }
    else if (argc == 2) { // Если передан файл с матрицей - считываем его

        GetMatrixFromFile(argv[1]);

        if (quantityOfThreads > n || n < 1 || quantityOfThreads < 1) {
            cout << endl << "Некорректный ввод!" << endl <<
                 "1. Количество потоков должно быть <= размерности матрицы." << endl <<
                 "2. Размерность матрицы должна быть >= 1." << endl <<
                 "3. Количество потоков должно быть >= 1.";
            return 0;
        }

        threads = new thread[quantityOfThreads];

        printMatrix(); // вывод матрицы на экран
        matrixRankFunc(); // функция подсчета ранга матрицы

        cout << endl << "Полученный ранг матрицы : " << rankOfMatrix << endl; // Вывод результатов работы потока для ранга

        auto end = chrono::steady_clock::now();
        auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        cout << "Время работы программы : " << elapsed_ms.count() << " ms\n";
    }

    return 0;
}