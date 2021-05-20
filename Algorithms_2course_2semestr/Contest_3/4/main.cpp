#include <iostream>
using namespace std;

// Копипаст функции из второй задачи
void makeHeapFirst(pair<int, int> *data, int array_size, int i) {

    // Корень
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Сравниваем корень с левым ребенком (и проверяем, что ребенок существует)
    if (left < array_size && data[left].first > data[largest].first)
        largest = left;

    // Сравниваем корень с правым ребенком (и проверяем, что ребенок существует)
    if (right < array_size && data[right].first > data[largest].first)
        largest = right;

    if (largest != i) {
        // Меняем родителя и наибольшего ребенка
        swap(data[i], data[largest]);

        // Рекурсия с проверкой, что перед нами не лист
        if (largest * 2 + 1 < array_size) {
            makeHeapFirst(data, array_size, largest);
        }
    }
}

// Копипаст функции из второй задачи
void makeHeapSecond(pair<int, int> *data, int array_size, int i) {

    // Корень
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Сравниваем корень с левым ребенком (и проверяем, что ребенок существует)
    if (left < array_size && data[left].second > data[largest].second)
        largest = left;

    // Сравниваем корень с правым ребенком (и проверяем, что ребенок существует)
    if (right < array_size && data[right].second > data[largest].second)
        largest = right;

    if (largest != i) {
        // Меняем родителя и наибольшего ребенка
        swap(data[i], data[largest]);

        // Рекурсия с проверкой, что перед нами не лист
        if (largest * 2 + 1 < array_size) {
            makeHeapSecond(data, array_size, largest);
        }
    }
}

void heapSortFirst(pair<int, int> *arr, int array_size)
{
    // Делаем кучу из массива
    for (int i = array_size / 2 - 1; i >= 0; i--)
        makeHeapFirst(arr, array_size, i);

    // Извлечение элементов из кучи
    for (int i = array_size - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        makeHeapFirst(arr, i, 0);
    }
}

void heapSortSecond(pair<int, int> *arr, int array_size)
{
    // Делаем кучу из массива
    for (int i = array_size / 2 - 1; i >= 0; i--)
        makeHeapSecond(arr, array_size, i);

    // Извлечение элементов из кучи
    for (int i = array_size - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        makeHeapSecond(arr, i, 0);
    }
}


int leastGreaterEqualSecond(pair<int, int> *arr, int low, int high, int key, int array_size)
{
    int ans = -1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int midVal = arr[mid].second;

        if (midVal < key) {
            low = mid + 1;
        }
        else if (midVal >= key) {
            ans = mid;
            high = mid - 1;
        }
    }

    if (ans < 0)
        return array_size;

    return ans;
}

int leastGreaterFirst(pair<int, int> *arr, int low, int high, int key, int array_size)
{
    int ans = -1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int midVal = arr[mid].first;

        if (midVal <= key) {
            low = mid + 1;
        }
        else if (midVal > key) {
            ans = mid;
            high = mid - 1;
        }
        else if (midVal == key) {
            low = mid + 1;
        }
    }

    if (ans < 0)
        return array_size;

    return ans;
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, z;
    cin >> n; // Количество интвервалов

    // IntervalsFirst - отсортировка по .first, IntervalsSecond - сортировка по .second
    pair<int, int> intervalsFirst[n], intervalsSecond[n];

    // Заполняем оба вектора одинаково
    for (int i = 0; i < n; ++i) {
        cin >> intervalsFirst[i].first >> intervalsFirst[i].second;
        intervalsSecond[i] = make_pair(intervalsFirst[i].first, intervalsFirst[i].second);
    }

    // Сортируем оба
    heapSortFirst(intervalsFirst, n);
    heapSortSecond(intervalsSecond, n);

    cin >> k; // Количество запросов

    for (int i = 0; i < k; ++i) { // Проходим по запросам

        // Вводим текущий запрос
        cin >> z;

        if (z > intervalsSecond[n - 1].second) {
            cout << 0 << "\n";
            continue;
        }
        else if (z < intervalsFirst[0].first) {
            cout << 0 << "\n";
            continue;
        }
        else {

            // Найти все элементы в .second, которые < Z
            // Для этого ищем индекс первого элемента, который >= z
            // И берем кол-во элементов, стоящих до него
            int answerForSecond = leastGreaterEqualSecond(intervalsSecond, 0, n, z, n);


            // Найти все элемент в .first, которые > Z
            // Для этого находим индекс перового элемента, который > z
            // И берем все элементы
            int answerForFirst = leastGreaterFirst(intervalsFirst, 0, n, z, n);

            cout << abs(answerForFirst - answerForSecond) << "\n";
        }
    }

    return 0;
}