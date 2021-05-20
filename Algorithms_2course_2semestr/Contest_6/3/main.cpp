#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Основная задача - реализовать данный метод
//Можно изменить передачу параметров на ссылки (&)
//Можно добавлять любое количество любых вспомогательных методов, структур и классов
void getSubstrings(string& source, string& substring, vector<int>& res)
{
    size_t substrSize = substring.size();
    size_t srcSize = source.size();
    int tmp = 0, j = 0;
    int tmpArr[substrSize];
    tmpArr[0] = 0;

    for (int i = 1; i < substrSize; i++) {
        while (substring[i] != substring[tmp] && tmp != 0)
            tmp = tmpArr[tmp - 1];

        if (substring[tmp] == substring[i])
            tmp++;

        tmpArr[i] = tmp;
    }

    for (int i = 0; i < srcSize; ++i) {
        while (substring[j] != source[i] && j != 0)
            j = tmpArr[j - 1];

        if (substring[j] == source[i])
            ++j;

        if (j == substrSize)
            res.push_back(1 + i - substrSize);
    }
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
    string t;
    string p;
    vector<int> res;

    ifstream fin;
    fin.open("/Users/anasbenmustafa/CLionProjects/Algorithms_2course_2semestr/Contest_6/3/input.txt");
    if (fin.is_open())
    {
        getline(fin, t);
        getline(fin, p);
        fin.close();
    }

    getSubstrings(t, p, res);

    fstream fout;
    fout.open("/Users/anasbenmustafa/CLionProjects/Algorithms_2course_2semestr/Contest_6/3/output.txt", ios::out);
    fout << res.size() << "\n";
    for (std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i)
        fout << *i << "\n";
    fout.close();

    return 0;
}