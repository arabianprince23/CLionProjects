// NovoselovAleksandr191_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
#include <sstream>

using namespace std;

class Bitmap
{
private:
    int* container;
public:
    Bitmap()
    {
        container = new int[0];
    }
    Bitmap(int n) // n -  кол-во видео
    {
        int m = ceil(round(n * 9.585)/32); //узнаем кол-во нужных нам 4 байтовых блоков
        container = new int[m];
    }

    void Set(int position, bool value)
    {
        int num = position / 32; // i
        int posNum = position % 32; // shift
        int one = 1;
        container[num] = (value ? container[num] | (one << posNum) : container[num] & ~(one << posNum));
    }

    bool Get(int position)
    {
        std::cout << position << std::endl;
        int num = position / 32;
        int posNum = position % 32;
        return ((container[num] >> posNum) & 1) == 1;
    }
};

class Hashes {
private:
    int m; // кол-во ячеек в битмапе
    hash<string> hash;

public:
    Hashes()
    {
        m = 0;
    }
    Hashes(int n) //n - кол-во видео
    {
        m = round(n * 9.585); //узнаем кол-во нужных нам 4 байтовых блоков
    }

    int Hash1(std::string s)
    {
        return (hash(s)) % m;
    }

    int Hash2(std::string s)
    {
        const int p = 100000002229; //возьмем простое число гаранитрованно большее размера битмапа, т.е. 10^7
        //всего допустимых символов 62
        size_t hash = 0, p_pow = 1;
        for (size_t i = 0; i < s.length(); ++i)
        {
            // желательно отнимать 'a' от кода буквы
            // единицу прибавляем, чтобы у строки вида 'aaaaa' хэш был ненулевой
            hash += (s[i] - 'a' + 1) * p_pow;
            p_pow *= p;
        }

        return hash % m;
    }

    int Hash3(std::string s)
    {
        const int p = 100000002251; // по сравнению с Hash2 здесб берется другое простое число,
        // из-за чего возвращаемые хэши будут совершенно другими
        //всего допустимых символов 62
        size_t hash = 0, p_pow = 1;
        for (size_t i = 0; i < s.length(); ++i)
        {
            // желательно отнимать 'a' от кода буквы
            // единицу прибавляем, чтобы у строки вида 'aaaaa' хэш был ненулевой
            hash += (s[i] - 'a' + 1) * p_pow;
            p_pow *= p;
        }

        return hash % m;
    }

};

class BloomFilter
{
public:
    bool Check(std::string s, Hashes hashes, Bitmap bitmap)
    {
        //std::cout << hashes.Hash1(s) << " " << hashes.Hash2(s) << " " << hashes.Hash3(s) << std::endl;
        return bitmap.Get(hashes.Hash1(s)) & bitmap.Get(hashes.Hash2(s)) & bitmap.Get(hashes.Hash3(s));
    }

    void Add(std::string s,Hashes hashes, Bitmap bitmap)
    {
        int pos1 = hashes.Hash1(s);
        int pos2 = hashes.Hash2(s);
        int pos3 = hashes.Hash3(s);
        bitmap.Set(pos1, true);
        bitmap.Set(pos2, true);
        bitmap.Set(pos3, true);
    }
};

void split(const std::string& str, std::vector<std::string>& strs, char ch)
{
    size_t pos = str.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos) {
        strs.push_back(str.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = str.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(str.substr(initialPos, std::min(pos, str.size()) - initialPos + 1));

}

int findNumOfVideos(std::string line)
{
    const std::string delimiter = " ";
    const std::string num = line.substr(line.find(delimiter) + 1,
                                        line.size() - 1);
    return std::stoi(num);
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        // throw std::exception("Недостаточно аргументов");
    }
    //0 - имя програм, 1 - ввод, 2 - вывод
    std::string input = argv[1];
    std::string output = argv[2];

    //Считаем и запишем в массив строк
    std::ifstream in(input);
    std::vector<std::string> lines; // будут хранится все считанные данные
    std::string line;
    if (in.is_open())
    {
        while (getline(in, line))
        {
            lines.push_back(line);
        }
    }
    in.close();

    //найдем кол-во видео в системе из 1 строки
    int numOfVideos = findNumOfVideos(lines[0]);


    //Создадим нужные нам обьекты классов
    Hashes hashes = Hashes(numOfVideos);
    std::map<std::string, Bitmap> dictionary;
    std::map<std::string, Bitmap> ::iterator it;
    BloomFilter bloom_filter;

    //Соаздаем поток для записи в файл
    std::ofstream out;
    out.open(output);

    for (int i = 1; i < lines.size(); ++i)
    {
        //1 - тип команды, 2 - юзер, 3 - видео
        std::vector<std::string> splitedData;
        split(lines[i], splitedData, ' ');

        if (splitedData[0] == ("watch"))
        {
            it = dictionary.find(splitedData[1]);

            //проверим есть ли такой юзер
            if (it == dictionary.end())
            {
                Bitmap userBitmap = Bitmap(numOfVideos);
                dictionary[splitedData[1]] = userBitmap;
            }
            //Добавим видео для пользователя
            bloom_filter.Add(splitedData[2], hashes, dictionary[splitedData[1]]);
            out << "Ok" << std::endl;
        }
        else
        {
            if (bloom_filter.Check(splitedData[2], hashes, dictionary[splitedData[1]]))
            {
                out << "Probably" << std::endl;
            }
            else
            {
                out << "No" << std::endl;
            }
        }

    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

/*#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class BitMapForBloom {

private:
    int *array;
    int m = -1;
    hash<string> hashObj;

public:
    BitMapForBloom(int n) {
        m = round(n * 9.585);
        array = new int[m]; // Инициализировали массив array (играющий роль битмапа) и установили ему переданный размер - size

        for (int i = 0; i < m; ++i) {
            array[i] = 0; // Инициализируем массив нулями
        }
    }

    BitMapForBloom() = default;

    void Set(string str) {
        array[HashFunc1(str)] = 1;
        array[HashFunc2(str)] = 1;
        array[HashFunc3(str)] = 1;
    }

    bool Get(string str) {
        int h1 = HashFunc1(str), h2 = HashFunc2(str), h3 = HashFunc3(str);
        if (array[h1] * array[h2] * array[h3] == 0) {
            return false;
        }
        return true;
    }

    size_t HashFunc1(string str) {
        return (hashObj(str)) % m; // Первый хеш - встроенный
    }

    size_t HashFunc2(string str) { // Второй - свой хэш

        const int p = 100000002251; // Простое число, большее чем m для хэша
        size_t hash = 0, p_pow = 1;

        for (size_t i = 0; i < str.length(); ++i)
        {
            hash += (str[i] - 'a' + 1) * p_pow;
            p_pow *= p;
        }

        return hash % m;
    }

    size_t HashFunc3(string str) // Третий - свой хэш
    {
        unsigned int hash = 0;

        for(int i = 0; i < str.length(); ++i)
            hash = (hash * 1664525) + (unsigned char)(str[i]) + 1013904223;

        return hash % m;

    }
};

class BloomContainer {

private:
    int _n;
    map<string, BitMapForBloom> container;

public:

    BloomContainer(int n) {
        _n = n;
        container = map<string, BitMapForBloom>();
    }

    void Set(string user, string video) {
        if (container.find(user) == container.end()) { // Ищем название пользователя среди словаря
            container[user] = BitMapForBloom(_n);
        }
        container[user].Set(video);
    }

    bool Get(string user, string str) {
        if (container.find(user) == container.end()) {
            // Если пользователя нет в "системе"
            return false;
        }
        return container[user].Get(str);
    }
};

int main(int argc, const char *argv[]) {

    if (argc == 3) {

        ifstream readFile(argv[1]); // Файл, из которого читаем
        ofstream writeToFile(argv[2]); // Файл, в который записываем

        int n;
        string watchOrCheck, UserName, VideoNumber, str;
        readFile >> str >> n; // Считываем из файла первую строку, получаем количество видосов
        writeToFile << "Ok" << endl;

        BloomContainer bloom = BloomContainer(
                n); // БлумКонтейнер, который содержит пользователей и соответствующие им битмапы

        while (readFile >> watchOrCheck >> UserName >> VideoNumber) {

            if (watchOrCheck == "watch") {
                bloom.Set(UserName, VideoNumber);
                writeToFile << "Ok" << endl;
            }
            if (watchOrCheck == "check") {
                bool a = bloom.Get(UserName, VideoNumber);
                writeToFile << (a ? "Probably" : "No") << endl;
            }
        }
    }

    return 0;
}
*/