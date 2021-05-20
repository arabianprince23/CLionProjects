#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

int ableCommandsQuantity(string input, string command, int mistakes) {
    if (abs(int(input.size() - command.size())) <= mistakes) {
        bool flag = true;
        int quantity = 0;
        int arr1[input.size()];
        int arr2[command.size()];

        for (int i = 0; i < command.size(); ++i) {
            arr1[i] = i;
            arr2[i] = command.size() - 1;
        }

        for (int i = 1; i < input.size(); ++i) {
            int m = max(i - mistakes, 1), k = min(int(command.size()), mistakes + i + 1);
            arr2[0] = i;

            for (int j = m; j < k; ++j) {
                if (input[i - 1] == command[j - 1]) {
                    arr2[j] = min(min((arr1[j] + 1), (arr2[j - 1] + 1)),
                                  (arr1[j - 1]));
                } else {
                    arr2[j] = min(min((arr1[j] + 1), (arr2[j - 1] + 1)),
                                  (arr1[j - 1] + 1));
                }
                if (arr2[j] > mistakes)
                    flag = false;
            }

            if (!flag) {
                quantity = input.size() - 1;
                break;
            }

            for (int j = 0; j < command.size(); j++) {
                int tmp = arr2[j];
                arr2[j] = arr1[j];
                arr1[j] = tmp;
                arr2[j] = command.size() - 1;
            }
        }

        if (quantity != input.size() - 1) {
            quantity = arr1[command.size() - 1];
        }

        return quantity;
    } else {
        return command.size() - 1;
    }
}

int main() {
    string input;
    int commandsQuantity;
    cin >> commandsQuantity;
    string arr[commandsQuantity];

    for (int i = 0; i < commandsQuantity; ++i) {
        cin >> input;
        arr[i] = input;
    }

    int maxErrorsQuantity;
    cin >> maxErrorsQuantity;
    int pishnikCommands;
    cin >> pishnikCommands;

    for (int i = 0; i < pishnikCommands; ++i) {
        int quantity = 0;
        cin >> input;
        for (int j = 0; j < commandsQuantity; ++j) {
            if (ableCommandsQuantity(input, arr[j], maxErrorsQuantity) <= maxErrorsQuantity) {
                ++quantity;
            }
        }
        cout << quantity << endl;
    }
    return 0;
}