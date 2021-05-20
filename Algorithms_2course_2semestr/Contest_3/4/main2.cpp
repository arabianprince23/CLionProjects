

//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//// максимум в массиве
//int arrMax(pair<int, int> *array, size_t n) {
//    int max = array[0].second;
//    for (int i = 1; i < n; ++i) {
//        if (array[i].second > max) {
//            max = array[i].second;
//        }
//    }
//    return max;
//}
//
//// минимум в массиве
//int arrMin(pair<int, int> *array, size_t n) {
//    int min = array[0].second;
//    for (int i = 1; i < n; ++i) {
//        if (array[i].second < min) {
//            min = array[i].second;
//        }
//    }
//    return min;
//}
//
//// Копипаст функции из второй задачи
//void makeHeapFirst(pair<int, int> *data, int array_size, int i) {
//
//    // Корень
//    int largest = i;
//    int left = 2 * i + 1;
//    int right = 2 * i + 2;
//
//    // Сравниваем корень с левым ребенком (и проверяем, что ребенок существует)
//    if (left < array_size && data[left].first > data[largest].first)
//        largest = left;
//
//    // Сравниваем корень с правым ребенком (и проверяем, что ребенок существует)
//    if (right < array_size && data[right].first > data[largest].first)
//        largest = right;
//
//    if (largest != i) {
//        // Меняем родителя и наибольшего ребенка
//        swap(data[i], data[largest]);
//
//        // Рекурсия с проверкой, что перед нами не лист
//        if (largest * 2 + 1 < array_size) {
//            makeHeapFirst(data, array_size, largest);
//        }
//    }
//}
//
//// Функция сортировки подсчетом
//void countingSort(pair<int, int> *numbers, int array_size)
//{
//    vector<pair<int, int>> B;
//    B.reserve(array_size); // Отсортированный массив
//
//    int min = arrMin(numbers, array_size), max = arrMax(numbers, array_size);
//    int k = max - min + 1;
//
//    // Вспомогательный массив С (счетчик)
//    int C[k];
//
//    // Зануляем массивы
//    for (int i = 0; i < k; ++i) {
//        C[i] = 0;
//    }
//
//    // Заполняем массив счетчик
//    for (int i = 0; i < array_size; ++i) {
//        C[numbers[i].second - min] += 1;
//    }
//
//    // Записываем количество элементов "до"
//    for (int i = 1; i <= k; ++i) {
//        C[i] = C[i] + C[i - 1];
//    }
//
//    for (int i = array_size - 1; i >= 0; --i) {
//        B[C[numbers[i].second - min] - 1] = numbers[i];
//        C[numbers[i].second - min] = C[numbers[i].second - min] - 1;
//    }
//
//    for (int i = 0; i < array_size; ++i) {
//        numbers[i] = B[i];
//    }
//}
//
//void heapSortFirst(pair<int, int> *arr, int array_size)
//{
//    // Делаем кучу из массива
//    for (int i = array_size / 2 - 1; i >= 0; i--)
//        makeHeapFirst(arr, array_size, i);
//
//    // Извлечение элементов из кучи
//    for (int i = array_size - 1; i >= 0; i--)
//    {
//        swap(arr[0], arr[i]);
//        makeHeapFirst(arr, i, 0);
//    }
//}
//
//int leastgreaterSecond(pair<int, int> *arr, int low, int high, int key, int array_size)
//{
//    int ans = -1;
//
//    while (low <= high) {
//        int mid;
//        if (low + (high - low + 1) / 2 == array_size) {
//            mid = low + (high - low + 1) / 2 - 1;
//        } else {
//            mid = low + (high - low + 1) / 2;
//        }
//        int midVal = arr[mid].second;
//
//        if (midVal < key) {
//            low = mid + 1;
//        }
//        else if (midVal >= key) {
//            ans = mid;
//            high = mid - 1;
//        }
//        else if (midVal == key) {
//            low = mid + 1;
//        }
//    }
//
//    return ans;
//}
//
//
//int main() {
//
//    int n, k, z, quantity = 0 ;
//    cin >> n; // Количество интвервалов
//
//    // IntervalsFirst - отсортировка по .first, IntervalsSecond - сортировка по .second
//    pair<int, int> intervalsFirst[n], intervalsSecond[n];
//
//    // Заполняем оба вектора одинаково
//    for (int i = 0; i < n; ++i) {
//        cin >> intervalsFirst[i].first >> intervalsFirst[i].second;
//        intervalsSecond[i] = make_pair(intervalsFirst[i].first, intervalsFirst[i].second);
//    }
//
//    // Сортируем оба
//    heapSortFirst(intervalsFirst, n);
//    countingSort(intervalsSecond, n);
//
//    for (auto i: intervalsFirst) {
//        cout << i.first << "-" << i.second << " |";
//    }
//    cout << endl;
//    for (auto i: intervalsSecond) {
//        cout << i.first << "-" << i.second << " |";
//    }
//
//    cin >> k; // Количество запросов
//
//    // Проходим по запросам
//    for (int i = 0; i < k; ++i) {
//
//        // Вводим текущий запрос
//        cin >> z;
//
//
//
//
//    }
//
//    return 0;
//}


