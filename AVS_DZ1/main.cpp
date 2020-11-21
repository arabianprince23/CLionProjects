#include <iostream>
#include <vector>
#include <thread>

using namespace std;

const double EPS = 1E-9;

void printMatrix(vector<vector<int>> matrix) {
    cout << endl << "Inputted matrix is : " << endl;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void inputMatrix(vector<vector<int>> &matrix, int n) {
    int elem;

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "Введите элемент (" << i << ";" << j << ") : ";
            cin >> elem;
            matrix[i].push_back(elem);
        }
    }
}

void swap(vector<vector<int>> &matrix, int row1, int row2, int col) {
    for (int i = 0; i < col; i++) {
        int temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

int rankOfMatrix(vector<vector<int>> &matrix, int n) {
    int rank = n;

    for (int row = 0; row < rank; row++) {
        if (matrix[row][row]) {
            for (int col = 0; col < n; col++) {
                if (col != row) {
                    double mult = (double)matrix[col][row] / matrix[row][row];
                    for (int i = 0; i < rank; i++)
                        matrix[col][i] -= mult * matrix[row][i];
                }
            }
        }
        else {
            bool reduce = true;

            for (int i = row + 1; i < n;  i++) {
                if (matrix[i][row]) {
                    swap(matrix, row, i, rank);
                    reduce = false;
                    break ;
                }
            }
            if (reduce) {
                rank--;

                for (int i = 0; i < n; i ++)
                    matrix[i][row] = matrix[i][rank];
            }
            row--;
        }
    }
    return rank;
}

void Compute(int quantityOfThreads, int n, vector<vector<int>> matrix) {
    int loop_size = n / quantityOfThreads; // Количество итераций цикла в зависимости от количества потоков
    vector<thread> threads(quantityOfThreads);

    for (int i = 0; i < loop_size; ++i) {
        if (i != loop_size - 1) {
            threads[i] = std::thread{rankOfMatrix, n};
        } else {
            threads[i] = std::thread{rankOfMatrix, n};
        }
    }
}

int main() {
    int quantityOfThreads; // Количество потоков, которые будут использоваться в функции поиска ранга
    cout << "Введите количество потоков : ";
    cin >> quantityOfThreads;
    int n; // Размерность матрицы
    cout << "Введите n (размерность матрицы) : ";
    cin >> n;

    if (quantityOfThreads > n || n < 1 || quantityOfThreads < 1) {
        cout << endl << "Некорректный ввод!" << endl <<
                "1. Количество потоков должно быть <= размерности матрицы." << endl <<
                "2. Размерность матрицы должна быть >= 1." << endl <<
                "3. Количество потоков должно быть >= 1.";
        return 0;
    }

    int rank = n;
    vector<vector<int>> matrix(n); // Матрица

    thread inputThread(inputMatrix, ref(matrix), n); // Запускаем поток, отвечающий за ввод пользователем матрицы
    inputThread.join(); // Ожидаем его завершения, дабы получить верные значения в матрице

    thread printThread(printMatrix, ref(matrix)); // Запускаем поток, занимающийся выводом полученной матрицы на экран
    thread rankThread(rankOfMatrix, ref(matrix), n); // Параллельно запускаем поток, занимающийся поиском ранга введенной матрицы

    printThread.join(); // Во избежание ошибок сначала ожидаем завершения потока с выводом
    rankThread.join(); // Главный поток ожидает завершение поиска ранга матрицы

    cout << endl << "Rank of matrix is : " << rank << endl; // Вывод результатов работы потока для ранга

    return 0;
}

