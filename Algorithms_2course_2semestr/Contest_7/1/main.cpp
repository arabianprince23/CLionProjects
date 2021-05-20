#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Необходимо реализовать метод используя рекурсивный подход
int LevenshteinDistance(string& s, int len_s, string& t, int len_t)
{
    if (min(len_s, len_t) == 0)
        return max(len_s, len_t);
    else
        return min((LevenshteinDistance(s, len_s, t, len_t - 1) + 1), min((LevenshteinDistance(s, len_s - 1, t, len_t) + 1),(LevenshteinDistance(s, len_s - 1, t, len_t - 1) + (s[len_s - 1] == t[len_t - 1] ? 0 : 1))));
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
    fstream fin;
    fstream fout;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);
    if(fin.is_open()) {
        string N;
        getline(fin,N);
        int n = atoi(N.c_str());
        for (int i = 0; i < n; i++) {
            string s;
            string t;
            getline(fin,s);
            getline(fin,t);
            fout << LevenshteinDistance(s,s.length(), t, t.length()) << (i == n-1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }
    return 0;
}