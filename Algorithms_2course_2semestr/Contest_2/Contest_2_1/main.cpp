#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

// максимум в массиве
int arrMax(int* array, size_t n) {
    int max = array[0];
    for (int i = 1; i < n; ++i) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

// минимум в массиве
int arrMin(int* array, size_t n) {
    int min = array[0];
    for (int i = 1; i < n; ++i) {
        if (array[i] < min) {
            min = array[i];
        }
    }
    return min;
}

// Функция сортировки подсчетом
void countingSort(int *numbers, int array_size)
{
    int *B, *C;
    B = new int[array_size]; // Отсортированный массив

    int min = arrMin(numbers, array_size), max = arrMax(numbers, array_size);
    int k = max - min + 1;

    // Вспомогательный массив С (счетчик)
    C = new int[k];

    // Зануляем массивы
    for (int i = 0; i < k; ++i) {
        C[i] = 0;
    }

    // Заполняем массив счетчик
    for (int i = 0; i < array_size; ++i) {
        C[numbers[i] - min] += 1;
    }

    // Записываем количество элементов "до"
    for (int i = 1; i <= k; ++i) {
        C[i] = C[i] + C[i - 1];
    }

    for (int i = array_size - 1; i >= 0; --i) {
        B[C[numbers[i] - min] - 1] = numbers[i];
        C[numbers[i] - min] = C[numbers[i] - min] - 1;
    }

    for (int i = 0; i < array_size; ++i) {
        numbers[i] = B[i];
    }

    delete [] B;
    delete [] C;
}

//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *brr = nullptr;
    int n;

    //Ввод из файла
    n = rw.readInt();

    brr = new int[n];
    rw.readArray(brr, n);

    //Запуск сортировки, ответ в том же массиве (brr)
    countingSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}
