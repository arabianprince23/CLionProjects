#include <iostream>
#include <fstream>

using namespace std;

// Метод для поиска индекса первого элемента в массиве А, который больше или равен ключу
int leastGreaterEqual(int *a, int low, int high, int key)
{
    int ans = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int midVal = a[mid];

        if (midVal < key) {
            low = mid + 1;
        }
        else if (midVal >= key) {
            ans = mid;
            high = mid - 1;
        }
    }
    return ans;
}

void qsort(int *arr, int left, int right) {

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
        qsort(arr, left, j);
    }
    if (i < right) {
        qsort(arr, i, right);
    }
}

long long* checkElemsOtherArrays(int otherMassLength, int* otherMass, int currentElem) {
    long long *data = nullptr;

    int firstElemBiggerInOtherArray = leastGreaterEqual(otherMass, 0, otherMassLength - 1, currentElem);

    if (firstElemBiggerInOtherArray == -1) {
        data = new long long[1];
        data[0] = otherMass[otherMassLength - 1];
    }
    else {
        if (firstElemBiggerInOtherArray == 0) {
            data = new long long[1];
            data[0] = otherMass[firstElemBiggerInOtherArray];
        }
        else {
            if (otherMass[firstElemBiggerInOtherArray] == currentElem) {
                    data = new long long[1];
                    data[0] = otherMass[firstElemBiggerInOtherArray];
            } else {
                data = new long long[2];
                data[0] = otherMass[firstElemBiggerInOtherArray - 1];
                data[1] = otherMass[firstElemBiggerInOtherArray];
            }
        }
    }

    return data;
}

int* solve(int nr, int ng, int nb, int* r, int* g, int* b)
{
    int* ans = new int[3];
    long long tmp1, tmp2, tmp3;
    long long minimalSum;
    long long *data1, *data2;

    // Сортируем все три массива по неубыванию
    qsort(r, 0, nr - 1);
    qsort(g, 0, ng - 1);
    qsort(b, 0, nb - 1);

    // Проходим по всем элементам массива красных самоцветов
    for (int i = 0; i < nr; ++i) {

        data1 = checkElemsOtherArrays(ng, g, r[i]); // зеленые
        data2 = checkElemsOtherArrays(nb, b, r[i]); // синие

        long long lenData1 = (sizeof(data1)/sizeof(*data1)); // длина зеленых
        long long lenData2 = (sizeof(data2)/sizeof(*data2)); // длина синих

        for (int j = 0; j < lenData1; ++j) {
            for (int k = 0; k < lenData2; ++k) {
                if (k == 0 && j == 0) {
                    minimalSum = (r[i] - data1[j])*(r[i] - data1[j]) + (data1[j] - data2[k])*(data1[j] - data2[k]) + (r[i] - data2[j])*(r[i] - data2[j]);
                    tmp1 = r[i]; // Красный
                    tmp2 = data1[j]; // Зеленый
                    tmp3 = data2[k]; // Синий
                }
                else {
                    if (minimalSum > (r[i] - data1[j])*(r[i] - data1[j]) + (data1[j] - data2[k])*(data1[j] - data2[k]) + (r[i] - data2[j])*(r[i] - data2[j])) {
                        minimalSum = (r[i] - data1[j])*(r[i] - data1[j]) + (data1[j] - data2[k])*(data1[j] - data2[k]) + (r[i] - data2[j])*(r[i] - data2[j]);
                        tmp1 = r[i]; // Красный
                        tmp2 = data1[j]; // Зеленый
                        tmp3 = data2[k]; // Синий
                    }
                }
            }
        }
    }

    // Проходим по всем элементам массива зеленых самоцветов
    for (int i = 0; i < ng; ++i) {

        data1 = checkElemsOtherArrays(nr, r, g[i]); // красные
        data2 = checkElemsOtherArrays(nb, b, g[i]); // синие

        long long lenData1 = (sizeof(data1)/sizeof(*data1)); // длина красных
        long long lenData2 = (sizeof(data2)/sizeof(*data2)); // длина синих

        for (int j = 0; j < lenData1; ++j) {
            for (int k = 0; k < lenData2; ++k) {
                if (minimalSum > (data1[j] - g[i])*(data1[j] - g[i]) + (g[i] - data2[k])*(g[i] - data2[k]) + (data1[j] - data2[k])*(data1[j] - data2[k])) {
                    minimalSum = (data1[j] - g[i])*(data1[j] - g[i]) + (g[i] - data2[k])*(g[i] - data2[k]) + (data1[j] - data2[k])*(data1[j] - data2[k]);
                    tmp1 = data1[j]; // Красный
                    tmp2 = g[i]; // Зеленый
                    tmp3 = data2[k]; // Синий
                }
            }
        }
    }

    // Проходим по всем элементам массива зеленых самоцветов
    for (int i = 0; i < nb; ++i) {

        data1 = checkElemsOtherArrays(nr, r, b[i]); // красные
        data2 = checkElemsOtherArrays(ng, g, b[i]); // зеленые

        long long lenData1 = (sizeof(data1)/sizeof(*data1)); // длина красных
        long long lenData2 = (sizeof(data2)/sizeof(*data2)); // длина зеленых

        for (int j = 0; j < lenData1; ++j) {
            for (int k = 0; k < lenData2; ++k) {
                if (minimalSum > (data1[j] - data2[k])*(data1[j] - data2[k]) + (data2[k] - b[i])*(data2[k] - b[i]) + (data1[j] - b[i])*(data1[j] - b[i])) {
                    minimalSum = (data1[j] - data2[k])*(data1[j] - data2[k]) + (data2[k] - b[i])*(data2[k] - b[i]) + (data1[j] - b[i])*(data1[j] - b[i]);
                    tmp1 = data1[j]; // Красный
                    tmp2 = data2[k]; // Зеленые
                    tmp3 = b[i]; // Синие
                }
            }
        }
    }

    cout << tmp1 << " " << tmp2 << " " << tmp3 << endl;

    delete[] data1;
    delete[] data2;
    return ans;
}

int main() {
    fstream fin;
    fstream fout;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);

    if(fin.is_open()) {
        int t;
        fin >> t;
        while (t--) {
            int nr, ng, nb;
            fin >> nr >> ng >> nb;

            int* r = new int[nr];
            int* g = new int[ng];
            int* b = new int[nb];
            for (int i = 0; i < nr; ++i)
                fin >> r[i];
            for (int i = 0; i < ng; ++i)
                fin >> g[i];
            for (int i = 0; i < nb; ++i)
                fin >> b[i];

            int* ans = solve(nr, ng, nb, r, g, b);

            fout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << endl;

            delete[] r;
            delete[] g;
            delete[] b;
            delete[] ans;
        }
    }
    fin.close();
    fout.close();
    return 0;
}