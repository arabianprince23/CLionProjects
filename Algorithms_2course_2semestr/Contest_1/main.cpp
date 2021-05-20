#include <iostream>
#include <vector>

using namespace std;


// -----------SECOND MAXIMUM------------



/*
int main() {

    int secondMax = -1, firstMax, currentHeight;

    cin >> currentHeight;
    firstMax = currentHeight;

    while (currentHeight != 0) {
        cin >> currentHeight;
        if (currentHeight > firstMax) {
            secondMax = firstMax;
            firstMax = currentHeight;
        }
        else if (currentHeight < firstMax && currentHeight > secondMax) {
            secondMax = currentHeight;
        }
    }

    cout << firstMax << endl << secondMax;

    return 0;
}
*/



// -----------BINARY SEARCH------------



/*
void BinarySearch(vector<int> &A, int B_i, int left, int right) {

    int search = -1; // найденный индекс элемента равен -1 (элемент не найден)

    while (left <= right) // пока левая граница не "перескочит" правую
    {
        int mid = (left + right) / 2; // ищем середину отрезка

        if (B_i == A[mid]) {  // если ключевое поле равно искомому
            search = 1;     // мы нашли требуемый элемент
            cout << "YES" << endl;
            break;
        }
        if (B_i > A[mid])     // если искомое ключевое поле больше найденной середины
            right = mid - 1;  // смещаем правую границу, продолжим поиск в левой части
        else                  // иначе
            left = mid + 1;   // смещаем левую границу, продолжим поиск в правой части
    }

    if (search == -1) {
        cout << "NO" << endl;
    }
}

int main() {

    int n, k;
    cin >> n >> k; // Размерности

    // Память выделили
    vector<int> A;
    A.reserve(n);
    vector<int> B;
    B.reserve(k);

    // Первый вектор заполнили
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    // Второй вектор заполнили
    for (int i = 0; i < k; ++i) {
        cin >> B[i];
    }

    for (int i = 0; i < k; ++i) {
        BinarySearch(A, B[i], 0, n - 1);
    }

    return 0;
}
 */



// -----------BUBBLE SORT------------

/*
int main() {

    int n, quantityOfChanges = 0;
    cin >> n; // Размерность

    // Память выделили
    vector<int> arr;
    arr.reserve(n);

    // Первый вектор заполнили
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int temp; // временная переменная для обмена элементов местами

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // меняем элементы местами
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                quantityOfChanges += 1;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl << quantityOfChanges;

    return 0;
}
*/



// -----------SELECTION SORT------------

/*
int main() {

    int n, quantityOfChanges = 0;
    cin >> n; // Размерность

    // Память выделили
    vector<int> array;
    array.reserve(n);

    // Первый вектор заполнили
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    bool flag = false;

    for (int i = 0; i < n - 1; ++i)
    {
        // индекс наименьшего значения, которое мы нашли в этой итерации
        int k = i;

        // Затем ищем элемент меньший в оставшейся части
        for (int j = i + 1; j < n; ++j)
        {
            // Если мы нашли такой, запоминаем его
            if (array[j] < array[k]) {
                k = j;
                flag = true;
            }
        }

        swap(array[i], array[k]);
        if (flag) {
            quantityOfChanges += 1;
        }
        flag = false;
    }

    for (int index = 0; index < n; ++index) {
        cout << array[index] << " ";
    }
    cout << endl << quantityOfChanges;

    return 0;
}
*/



// -----------INSERT SORT------------

/*
int main() {

    int n, quantityOfElems = 0;
    cin >> n; // Размерность

    // Память выделили
    vector<int> array;
    array.reserve(n);

    // Первый вектор заполнили
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    bool flag;

    for (int i = 1; i < n; ++i) {
        int k = i;

        while (k > 0 && array[k - 1] > array[k]) {
            flag = true;
            int tmp = array[k - 1];
            array[k - 1] = array[k];
            array[k] = tmp;
            k -= 1;
        }

        if (!flag) {
            quantityOfElems += 1;
        } else {
            flag = false;
        }
    }

    for (int index = 0; index < n; ++index) {
        cout << array[index] << " ";
    }
    cout << endl << quantityOfElems;

    return 0;
}
*/



// -----------BINARY INSERT SORT------------

int binarySearch(int array[], int value, int left, int right) {

    if (right <= left) {
        return (value > array[left]) ? (left + 1) : left;
    }

    int mid = (left + right) / 2;

    if (value == array[mid]) {
        return mid + 1;
    }

    if (value > array[mid]) {
        return binarySearch(array, value, mid + 1, right);
    }

    return binarySearch(array, value, left,mid - 1);
}

void insertSort(int array[], int n, int &quantity)
{
    int i, position, j, tmp;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        position = binarySearch(array, array[i], 0, j);
        for (int m = j; m >= position; --m) {
            if (array[m] != array[m + 1]) {
                swap(array[m], array[m + 1]);
                quantity += 1;
            }
        }
    }
}

int main() {

    int n, quantityOfElems = 0;
    cin >> n; // Размерность

    // Память выделили
    int array[n];

    // Первый вектор заполнили
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    insertSort(array, n, quantityOfElems);

    for (int index = 0; index < n; ++index) {
        cout << array[index] << " ";
    }

    cout << endl << quantityOfElems;
}