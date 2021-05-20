#include "ReadWriter.h"

using namespace std;

int partition(int *arr, int low, int high) {

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {

        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int *arr, int low, int high) {

    if (low < high) {
        int p = partition(arr, low, high);

        if (low < p - 1) {
            quickSort(arr, low, p - 1);
        }
        if (p + 1 < high) {
            quickSort(arr, p + 1, high);
        }
    }
}

int main() {
    //Объект для работы с файлами
    ReadWriter rw;

    int *data = nullptr;
    int n;

    // Получение данных из файла
    n = rw.readInt();
    data = new int[n];
    rw.readArray(data, n);

    quickSort(data, 0, n - 1);

    //Запись в файл
//    rw.writeInt(quantity);
    rw.writeArray(data, n);

    //освобождаем память
    delete[] data;

    return 0;
}
