#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Основная задача - реализовать данный метод
// Результат поместить в переменную res, она как раз доступна для изменения
// Можно добавлять любое количество любых вспомогательных методов, структур и классов
void getBorders(string &s, string& res) 
{
    res = "";
    for (int i = 1; i < s.size(); i++)
    {
        if (s.substr(0, i) == s.substr(s.size() - i, i))
        {
            res += s.substr(0, i);
            res += "\n";
        }
    }
}

// Не изменять метод main без крайней необходимости
// ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
	string input;
	string res;

	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		getline(fin, input);
		fin.close();
	}

	getBorders(input, res);

	fstream fout;
	fout.open("output.txt", ios::out);
	fout << res;
	fout.close();

	return 0;
}
