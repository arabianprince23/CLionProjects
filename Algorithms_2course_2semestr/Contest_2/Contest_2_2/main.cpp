#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

// максимум в массиве
int arrMax(int* array, size_t n) {
    int max = array[0];
    for (int i = 1; i < n; ++i) {
        if (max <= array[i]) {
            max = array[i];
        }
    }
    return max;
}

// Функция цифровой сортировки
void radixSort(int *numbers, int array_size)
{
    int max = arrMax(numbers, array_size); // Максимум в массиве

    for (int i = 0; max >> (8 * i) > 0; ++i) {

        int *C = new int[256];
        int *B = new int[array_size];

        for (int j = 0; j < 256; ++j) {
            C[j] = 0;
        }

        for (int j = 0; j < array_size; ++j) {
            C[(numbers[j] >> (8 * i)) & 255] = C[(numbers[j] >> (8 * i)) & 255] + 1;
        }

        for (int j = 1; j < 256; ++j) {
            C[j] = C[j] + C[j - 1];
        }

        for (int j = array_size - 1; j >= 0; --j) {
            B[C[(numbers[j] >> (8 * i)) & 255] - 1] = numbers[j];
            C[(numbers[j] >> (8 * i)) & 255] = C[(numbers[j] >> (8 * i)) & 255] - 1;
        }

        for (int j = 0; j < array_size; ++j) {
            numbers[j] = B[j];
        }

        delete [] C;
        delete [] B;
    }
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
    radixSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}
