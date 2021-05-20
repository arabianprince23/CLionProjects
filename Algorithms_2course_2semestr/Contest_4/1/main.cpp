#include "ReadWriter.h"

using namespace std;

void printArray(int *array, int array_size)
{
    for (int i = 0; i < array_size; ++i)
        cout << array[i] << " ";
}

int qsort(int *arr, int left, int right) {

    int quantity = 0;
    int i = left;
    int j = right;

    // Серединный элемент массива
    int pivot = arr[(left + right) / 2];

    do {
        // Ищем элементы, которые нужно перекинуть в другую часть
        while(arr[i] < pivot) {
            i++;
        }

        // В правом подмассиве чекаем, элементы, больше среднего
        while(arr[j] > pivot) {
            j--;
        }

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }

    } while(i <= j);


    // Рекурсии
    if (left < j) {
        quantity += qsort(arr, left, j) + 1;
    }
    if (i < right) {
        quantity += qsort(arr, i, right) + 1;
    }

    return quantity;
}

int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *data = nullptr;
    int n;

    // Получение данных из файла
    n = rw.readInt();
    data = new int[n];
    rw.readArray(data, n);

    // Сортируем и высчитываем кол-во рекурсий
    int quantity = qsort(data, 0, n - 1);

    //Запись в файл
    rw.writeInt(quantity);
    rw.writeArray(data, n);

    //освобождаем память
    delete[] data;

    return 0;
}
