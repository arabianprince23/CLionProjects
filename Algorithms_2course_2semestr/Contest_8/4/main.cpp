#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

//// максимум в массиве
//int arrMax(vector<int> array, size_t n) {
//    int max = array[0];
//    for (int i = 1; i < n; ++i) {
//        if (array[i] > max) {
//            max = array[i];
//        }
//    }
//    return max;
//}
//
//// минимум в массиве
//int arrMin(vector<int> array, size_t n) {
//    int min = array[0];
//    for (int i = 1; i < n; ++i) {
//        if (array[i] < min) {
//            min = array[i];
//        }
//    }
//    return min;
//}
//
//// Функция сортировки подсчетом
//void countingSort(vector<int> &numbers, int array_size) {
//    int *B, *C;
//    B = new int[array_size]; // Отсортированный массив
//
//    int min = arrMin(numbers, array_size), max = arrMax(numbers, array_size);
//    int k = max - min + 1;
//
//    // Вспомогательный массив С (счетчик)
//    C = new int[k];
//
//    // Зануляем массивы
//    for (int i = 0; i < k; ++i) {
//        C[i] = 0;
//    }
//
//    // Заполняем массив счетчик
//    for (int i = 0; i < array_size; ++i) {
//        C[numbers[i] - min] += 1;
//    }
//
//    // Записываем количество элементов "до"
//    for (int i = 1; i <= k; ++i) {
//        C[i] = C[i] + C[i - 1];
//    }
//
//    for (int i = array_size - 1; i >= 0; --i) {
//        B[C[numbers[i] - min] - 1] = numbers[i];
//        C[numbers[i] - min] = C[numbers[i] - min] - 1;
//    }
//
//    for (int i = 0; i < array_size; ++i) {
//        numbers[i] = B[i];
//    }
//
//    delete [] B;
//    delete [] C;
//}

void way (int** data, vector<int> &res, int i, int j, int *stones) {
    if (data[i][j] == 0)
        return;
    else if (data[i - 1][j] == data[i][j])
        way(data, res, i - 1, j, stones);
    else {
        way(data, res, i - 1, j - stones[i - 1], stones);
        res.push_back(stones[i - 1]);
    }
}

//Задача реализовать этот метод
//param N - количество камней
//param M - ограничения на вес
//param stones - массив размера N, с весами камней
//param res - вектор результатов (вес камней, которые надо взять)
void solve(int N, int W, int *stones, vector<int> &res) {

    int** data = new int*[N + 1];

    for (int i = 0; i <= N; ++i) {
        data[i] = new int[W + 1];
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= W; ++j) {
            data[i][j] = stones[i - 1] <= j ? max(data[i - 1][j - stones[i - 1]] + stones[i - 1], data[i - 1][j]) : data[i - 1][j];
        }
    }

    way(data, res, N, W, stones);

    for (int i = 0; i <= N; ++i)
        delete[] data[i];

    delete[] data;
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //камни
    int W = rw.readInt(); //ограничения на вес
    int* arr = new int[N]; //имеющиеся камни
    rw.readArr(arr, N);

    //основной структурой выбран вектор, так как заранее неизвестно какое количество камней будет взято
    vector<int> res;
    //решаем задачу
    solve(N, W, arr, res);
    int sum = 0;
    for (int i = 0; i < res.size(); i++)
        sum += res.at(i);

    //записываем ответ в файл
    rw.writeInt(sum); //итоговый вес
    rw.writeInt(res.size()); //количество взятых камней
    rw.writeVector(res); //сами камни

    delete[] arr;
    return 0;
}