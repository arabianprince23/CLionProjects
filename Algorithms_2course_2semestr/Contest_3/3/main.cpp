#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Копипаст функции из второй задачи
void makeHeap(int *data, int array_size, int i) {

    // Корень
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Сравниваем корень с левым ребенком (и проверяем, что ребенок существует)
    if (left < array_size && data[left] > data[largest])
        largest = left;

    // Сравниваем корень с правым ребенком (и проверяем, что ребенок существует)
    if (right < array_size && data[right] > data[largest])
        largest = right;

    if (largest != i) {
        // Меняем родителя и наибольшего ребенка
        swap(data[i], data[largest]);

        // Рекурсия с проверкой, что перед нами не лист
        if (largest * 2 + 1 < array_size) {
            makeHeap(data, array_size, largest);
        }
    }
}

void heapSort(int *arr, int array_size)
{
    // Делаем кучу из массива
    for (int i = array_size / 2 - 1; i >= 0; i--)
        makeHeap(arr, array_size, i);

    // Извлечение элементов из кучи
    for (int i = array_size - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        makeHeap(arr, i, 0);
    }
}

int main() {

    int *data;
    int n;

    // Чтение из файла
    fstream fin;
    fin.open("input.txt",ios::in);
    fin >> n;
    data = new int[n];
    for (int i = 0; i < n; i++) {
        fin >> data[i];
    }
    fin.close();
    // ---------------

    heapSort(data, n);

    // Запись в файл
    fstream fout;
    fout.open("output.txt",ios::out);
    for (int i = 0; i < n; i++)
        fout << data[i] << " ";
    fout.close();
    // ---------------


    delete[] data;

    return 0;
}

