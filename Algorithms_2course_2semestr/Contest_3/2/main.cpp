#include "ReadWriter.h"
#include <cmath>
#include <vector>

using namespace std;

void makeHeap(int *data, int array_size, int i, int &recDeep) {

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
            makeHeap(data, array_size, largest, ++recDeep);
        }
    }
}

int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *data = nullptr;
    int n, recDeep = 0, maxDeep;

    //Ввод из файла
    n = rw.readInt();

    data = new int[n];
    rw.readArray(data, n);


    // Строим кучу в массиве
    // В n / 2 - 1 содержится индекс последнего элемента, у которого есть потомки
    for (int i = n / 2 - 1; i >= 0; --i) {
        makeHeap(data, n, i, recDeep);

        if (i == n / 2 - 1) {
            maxDeep = recDeep;
        }
        else {
            if (recDeep > maxDeep) {
                maxDeep = recDeep;
            }
        }

        recDeep = 0;
    }

    //Запись в файл итоговых данных
    rw.writeInt(maxDeep);
    rw.writeArray(data, n);

    //освобождаем память
    delete[] data;

    return 0;
}
