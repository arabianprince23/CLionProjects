#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int getLCS(string x, string y) {
    vector<vector<int>> subsequence(x.size() + 1);

    for(int i = 0; i <= x.size(); ++i)
        subsequence[i] = vector<int>(y.size() + 1);

    for (int i = x.size() - 1; i >= 0; i--)
        for (int j = y.size() - 1; j >= 0; j--)
            subsequence[i][j] = x[i] == y[j] ? subsequence[i + 1][j + 1] + 1 : max(subsequence[i + 1][j], subsequence[i][j + 1]);

    return subsequence[0][0];
}

int main()
{
    string x;
    string y;
    int res;

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
