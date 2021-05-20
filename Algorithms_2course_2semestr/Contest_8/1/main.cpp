#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Основная задача - реализовать данный метод
int countMaxCross(string& riverMap)
{
	
}


int main()
{
	string riverMap;
	int res;
	
	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		getline(fin, riverMap);
		fin.close();
	}
	
	res = countMaxCross(riverMap);
	
	fstream fout;
	fout.open("output.txt", ios::out);
	fout << res;
	fout.close();
	
	return 0;
}