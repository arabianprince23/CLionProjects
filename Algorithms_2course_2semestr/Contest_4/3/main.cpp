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

long long checkElemsOtherArrays(int otherMassLength, int* otherMass, int currentElem) {
    long long minAbs = 0;

    int firstElemBiggerInOtherArray = leastGreaterEqual(otherMass, 0, otherMassLength - 1, currentElem);

    if (firstElemBiggerInOtherArray == -1) {
        // Если элементов, больших, чем currentElem не нашлось, возвращаем последний элемент массива
        minAbs = otherMass[otherMassLength - 1]; // 1 2 [3]
    }
    else {
        if (firstElemBiggerInOtherArray == 0) {
            // Если первый же элемент больше currentElem, возвращаем его
            minAbs = otherMass[firstElemBiggerInOtherArray];
        }
        else {
            if (otherMass[firstElemBiggerInOtherArray] == currentElem) {
                minAbs = otherMass[firstElemBiggerInOtherArray];
            }
            else {
                if (abs(currentElem - otherMass[firstElemBiggerInOtherArray])
                    >
                    abs(currentElem - otherMass[firstElemBiggerInOtherArray - 1]))
                {
                    minAbs = otherMass[firstElemBiggerInOtherArray - 1];
                } else {
                    minAbs = otherMass[firstElemBiggerInOtherArray];
                }
            }
        }
    }

    return minAbs;
}

// Необходимо вернуть вектор ans, который содержит три элемента:
// ans[0] - вес найденного самоцвета красного цвета
// ans[1] - вес найденного самоцвета зеленого цвета
// ans[2] - вес найденного самоцвета синего цвета
int* solve(int nr, int ng, int nb, int* r, int* g, int* b)
{
    int* ans = new int[3];
    long long tmp1, tmp2, tmp3;
    long long minimalSum;
    long long minabs1, minabs2;

    // Сортируем все три массива по неубыванию
    qsort(r, 0, nr - 1);
    qsort(g, 0, ng - 1);
    qsort(b, 0, nb - 1);
    int i = 0;

    // Проходим по всем элементам массива красных самоцветов
    while(i < nr) {

        minabs1 = checkElemsOtherArrays(ng, g, r[i]);
        minabs2 = checkElemsOtherArrays(nb, b, r[i]);

        long long sum = ((r[i] - minabs1) * (r[i] - minabs1)) + ((minabs1 - minabs2) * (minabs1 - minabs2)) + ((r[i] - minabs2) * (r[i] - minabs2));

        if (i == 0) {
            minimalSum = sum;
            tmp1 = r[i];
            tmp2 = minabs1;
            tmp3 = minabs2;
        } else {
            if (minimalSum >= sum) {
                minimalSum = sum;
                tmp1 = r[i];
                tmp2 = minabs1;
                tmp3 = minabs2;
            }
        }

        ++i;
    }

    i = 0;

    // Проходим по всем элементам массива зеленых самоцветов
    while (i < ng) {

        minabs1 = checkElemsOtherArrays(nr, r, g[i]);
        minabs2 = checkElemsOtherArrays(nb, b, g[i]);

        long long sum = ((minabs1 - g[i]) * (minabs1 - g[i])) + ((g[i] - minabs2) * (g[i] - minabs2)) + ((minabs1 - minabs2) * (minabs1 - minabs2));

        if (minimalSum >= sum) {
            minimalSum = sum;
            tmp1 = minabs1;
            tmp2 = g[i];
            tmp3 = minabs2;
        }

        ++i;
    }

    i = 0;

    // Проходим по всем элементам массива зеленых самоцветов
    while(i < nb) {

        minabs1 = checkElemsOtherArrays(nr, r, b[i]);
        minabs2 = checkElemsOtherArrays(ng, g, b[i]);

        long long sum = ((minabs1 - minabs2) * (minabs1 - minabs2)) + ((minabs2 - b[i]) * (minabs2 - b[i])) + ((minabs1 - b[i]) * (minabs1 - b[i]));

        if (minimalSum >= sum) {
            minimalSum = sum;
            tmp1 = minabs1;
            tmp2 = minabs2;
            tmp3 = b[i];
        }

        ++i;
    }

    ans[0] = tmp1;
    ans[1] = tmp2;
    ans[2] = tmp3;

    return ans;
}

int main() {
    int* ans;
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

            int r[nr];
            int g[ng];
            int b[nb];
            for (int i = 0; i < nr; ++i)
                fin >> r[i];
            for (int i = 0; i < ng; ++i)
                fin >> g[i];
            for (int i = 0; i < nb; ++i)
                fin >> b[i];

            ans = solve(nr, ng, nb, r, g, b);

            fout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << endl;
        }
    }
    fin.close();
    fout.close();
    delete[] ans;
    return 0;
}

