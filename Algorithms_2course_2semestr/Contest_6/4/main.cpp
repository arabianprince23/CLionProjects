#include <iostream>
using namespace std;

void palLengths(string palStr)
{
    int leftBr = 0, rightBr = -1;
    size_t inputStrSize = palStr.size();
    int lengthsArr[inputStrSize];

    for (int i = 0; i < inputStrSize; ++i) {

        int tmp;
        if (rightBr > i) {
            if (lengthsArr[leftBr + rightBr - i] <= rightBr - i + 1) {
                tmp = lengthsArr[leftBr + rightBr - i];
            } else {
                tmp = rightBr - i + 1;
            }
        } else {
            tmp = 1;
        }

        while (i - tmp > -1 && palStr[i + tmp] == palStr[i - tmp] && inputStrSize > i + tmp)
            tmp += 1;

        lengthsArr[i] = tmp;

        if (tmp + i - 1 > rightBr) {
            leftBr = i - tmp + 1;
            rightBr = leftBr + 2 * (tmp - 1);
        }
    }

    leftBr = 0;
    while (leftBr < inputStrSize) {
        cout << 2 * lengthsArr[leftBr] - 1 << " ";
        ++leftBr;
    }
}


int main() {
    string palStr;
    cin >> palStr;
    palLengths(palStr);
    return 0;
}