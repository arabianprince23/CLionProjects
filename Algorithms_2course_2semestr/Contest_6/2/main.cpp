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
    string str = substring + "*" + source;
    size_t substrSize = substring.size();
    size_t srcSize = source.size();
    size_t strSize = str.size();
    int tmp = 0;
    int tmpArr[strSize];
    tmpArr[0] = 0;

    for (int j = 1; j < strSize; ++j)
    {
        while (str[tmp] != str[j] && tmp != 0)
            tmp = tmpArr[tmp - 1];

        if (str[tmp] == str[j])
            ++tmp;

        tmpArr[j] = tmp;
    }

    for (int i = 0; i < substrSize + srcSize + 1; ++i)
    {
        if (tmpArr[i] == substrSize)
            res.push_back(i - substrSize * 2);
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
    fin.open("/Users/anasbenmustafa/CLionProjects/Algorithms_2course_2semestr/Contest_6/2/input.txt");
    if (fin.is_open())
    {
        getline(fin, t);
        getline(fin, p);
        fin.close();
    }

    getSubstrings(t, p, res);

    fstream fout;
    fout.open("/Users/anasbenmustafa/CLionProjects/Algorithms_2course_2semestr/Contest_6/2/output.txt", ios::out);
    fout << res.size() << "\n";
    for (std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i)
        fout << *i << "\n";
    fout.close();

    return 0;
}