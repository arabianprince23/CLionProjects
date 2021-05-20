#include "ReadWriter.h"
#include <vector>
//iostream, fstream включены в ReadWriter.h
using namespace std;

// максимум в массиве
int arrMax(pair<int, int> *array, size_t n) {
    int max = array[0].second;
    for (int i = 1; i < n; ++i) {
        if (array[i].second > max) {
            max = array[i].second;
        }
    }
    return max;
}

// минимум в массиве
int arrMin(pair<int, int> *array, size_t n) {
    int min = array[0].second;
    for (int i = 1; i < n; ++i) {
        if (array[i].second < min) {
            min = array[i].second;
        }
    }
    return min;
}

// Функция сортировки подсчетом
void countingSort(pair<int, int> *numbers, int array_size)
{
    vector<pair<int, int>> B;
    B.reserve(array_size); // Отсортированный массив

    int min = arrMin(numbers, array_size), max = arrMax(numbers, array_size);
    int k = max - min + 1;

    // Вспомогательный массив С (счетчик)
    int C[k];

    // Зануляем массивы
    for (int i = 0; i < k; ++i) {
        C[i] = 0;
    }

    // Заполняем массив счетчик
    for (int i = 0; i < array_size; ++i) {
        C[numbers[i].second - min] += 1;
    }

    // Записываем количество элементов "до"
    for (int i = 1; i <= k; ++i) {
        C[i] = C[i] + C[i - 1];
    }

    for (int i = array_size - 1; i >= 0; --i) {
        B[C[numbers[i].second - min] - 1] = numbers[i];
        C[numbers[i].second - min] = C[numbers[i].second - min] - 1;
    }

    for (int i = 0; i < array_size; ++i) {
        numbers[i] = B[i];
    }
}

// Функция, которая реверсит массив
void reverse(int arr[], int count)
{
    int temp;
    for (int i = 0; i < count/2; ++i)
    {
        temp = arr[i];
        arr[i] = arr[count-i-1];
        arr[count-i-1] = temp;
    }
}

int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    // Кол-во элементов
    int n;

    //Ввод из файла
    n = rw.readInt();
    int arrId[n], arrWeight[n];

    auto *pairs = new pair<int, int>[n];

    rw.readArrays(arrId, arrWeight, n);

    // Из соответствующих айдишников и весов составляем пары
    for (int i = 0; i < n; ++i) {
        pairs[i] = make_pair(arrId[i], arrWeight[i]);
    }

    // Сортируем
    countingSort(pairs, n);

    // Отсортированные айдишники и веса
    for (int i = 0; i < n; ++i) {
        arrId[i] = pairs[i].first;
        arrWeight[i] = pairs[i].second;
    }

    delete [] pairs;

    // реверс - ручной (ф-я сверху)
    reverse(arrId, n);
    reverse(arrWeight, n);
    int quantityOfSameWeights = 1;

    for (int i = 0; i < n - 1; ++i) {

        // Берем первый элемент и считаем количество дальнейших вхождений элементов с таким же весом
        int tmp = arrWeight[i];
        while (i < n - 1 && arrWeight[i + 1] == tmp) {
            quantityOfSameWeights += 1;
            i += 1;
        }

        i -= quantityOfSameWeights - 1;

        // Если нашлись одинаковые веса
        if (quantityOfSameWeights > 1) {

            // Создаем массивы, в который будем элементы с одинаковыми весами запихивать
            int *tmpArrID = new int[quantityOfSameWeights];
            int *tmpArrWeight = new int[quantityOfSameWeights];

            // Загружаем данные в массивы
            for (int j = 0; j < quantityOfSameWeights; ++j) {
                tmpArrID[j] = arrId[i + j];
                tmpArrWeight[j] = arrWeight[i + j];
            }

            // Ревёрсим их
            reverse(tmpArrID, quantityOfSameWeights);
            reverse(tmpArrWeight, quantityOfSameWeights);

            // Теперь реверснутые данные записываем обратно в пары
            for (int j = i; j < i + quantityOfSameWeights; ++j) {
                arrId[j] = tmpArrID[j - i];
                arrWeight[j] = tmpArrWeight[j - i];
            }

            delete[] tmpArrID;
            delete[] tmpArrWeight;
        }

        i += quantityOfSameWeights - 1;
        quantityOfSameWeights = 1;
    }

    //Запись в файл
    rw.writeArrays(arrId, arrWeight, n);

    return 0;
}