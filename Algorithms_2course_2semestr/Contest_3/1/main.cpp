#include "ReadWriter.h"

using namespace std;


// Дан массив. Нужно найти индекс первого элемента, который нарушает условие кучи.
// (либо вывести индекс самого последнего элемента, если массив весь является кучей)

int notHeapIndex(int *data, int array_size) {

    int i = 0;

    while (i < array_size) {

        // Проверяем первого ребенка, больше ли он, чем родитель
        if (2 * i + 1 < array_size && data[2 * i + 1] > data[i]) {
            return 2 * i;
        }

        // Проверяем второго ребенка, больше ли он, чем родитель
        if (2 * i + 2 < array_size && data[2 * i + 2] > data[i]) {
            return 2 * i + 1;
        }

        ++i;
    }

    return array_size - 1;
}

int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *data = nullptr;
    int n;

    //Ввод из файла
    n = rw.readInt();

    data = new int[n];
    rw.readArray(data, n);

    //Запись в файл
    rw.writeInt(notHeapIndex(data, n));

    //освобождаем память
    delete[] data;

    return 0;
}
