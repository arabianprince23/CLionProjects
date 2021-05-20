#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string getLCS(string x, string y) {
    string str;
    int a = 0, b = 0;
    vector<vector<int>> subsequence(x.size() + 1);

    for (int i = 0; i <= x.size(); ++i)
        subsequence[i] = vector<int>(y.size() + 1);

    for (int i = x.size() - 1; i >= 0; i--)
        for (int j = y.size() - 1; j >= 0; j--)
            subsequence[i][j] = x[i] == y[j] ? subsequence[i + 1][j + 1] + 1 : max(subsequence[i + 1][j], subsequence[i][j + 1]);

    while (a < x.size() && b < y.size() && subsequence[a][b] > 0) {
        if (x[a] != y[b] && subsequence[a][b] != subsequence[1 + a][b]) {
            ++b;
            continue;
        }
        else if (x[a] != y[b] && subsequence[a][b] == subsequence[1 + a][b]) {
            ++a;
            continue;
        }
        else {
            str += x[a];
        }
        a++;
        b++;
    }

    return str;
}

int main()
{
    string x;
    string y;
    string res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, x);
        getline(fin, y);
        fin.close();
    }

    res = getLCS(x, y);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}