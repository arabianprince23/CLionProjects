#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

class Point
{
public:

    Point() {}

    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    string ToString() {
        return to_string(x)+ " " + to_string(y);
    }

private:
    int x, y;
};


Point startPoint;


template <typename T>
class Stack
{
private:
    vector<Point> VecPoints;
    const int capacity = 1000;

public:
    Stack() {
        VecPoints = { };
    }

    bool isEmpty() {
        return VecPoints.size() == 0;
    }

    void push(T newElement) { // положить элемент на вершину стека
        if (VecPoints.size() >= capacity) {
            throw invalid_argument("Access error. Stack capacity is 1000.");
        }
        VecPoints.insert(VecPoints.end(), newElement);
    }

    void pop() { // убрать элемент с вершины
        if (VecPoints.size() == 0) {
            throw invalid_argument("You can't pop cause of empty stack!");
        }
        VecPoints.pop_back();
    }

    T top() { // вернуть элемент на вершине, не убирая его оттуда;
        if (VecPoints.size() == 0) {
            throw invalid_argument("You can't take top element cause of empty stack!");
        }
        return VecPoints.at(VecPoints.size() - 1);
    }

    unsigned int size() { // вернуть размер стека.
        return VecPoints.size();
    }
};

// Функция, которая находит предпоследний (с конца) элемент в стеке
Point nextToTop(Stack<Point> &S)
{
    Point p = S.top();
    S.pop();

    Point res = S.top();
    S.push(p);

    return res;
}

// Метод определяет, с какой стороны от заданного вектора АВ находится точка С.
// Положительное возвращаемое значение соответствует левой стороне, отрицательное — правой
static int WhichSide(Point A, Point B, Point C)
{
    int whichSide = ((B.getY() - A.getY()) * (C.getX() - B.getX()) - (B.getX() - A.getX()) * (C.getY() - B.getY()));

    if (whichSide == 0)
        return 0;

    return (whichSide > 0) ? 1 : -1;
}

// Метод высчитывает расстояние между двумя точками на плоскости
static int distBetweenPoints(Point p1, Point p2)
{
    return (p1.getX() - p2.getX())*(p1.getX() - p2.getX()) + (p1.getY() - p2.getY())*(p1.getY() - p2.getY());
}


// Сравниваем две точки по углу относительно стартовой.
// Если у них относительно стартовой одинаковый угол, выбираем более дальнюю из них.
int RetLngPoint(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int side = WhichSide(startPoint, *p1, *p2);
    if (side == 0) // Если полярный угол совпадает
        return (distBetweenPoints(startPoint, *p2) >= distBetweenPoints(startPoint, *p1)) ? -1 : 1;

    return (side == 1) ? 1 : -1;
}

// Высчитывает минимальную оболочку для переданного массива точек
void convexHull(Point points[], int n, string typeOfFileWriting, string pathToOutput, const char *typeOfScan)
{
    // Ниже - находим самую нижнюю из точек
    int y_min = points[0].getY(), minimum = 0;

    for (int i = 1; i < n; i++)
    {
        int current_y = points[i].getY();

        // В случае, если ординаты одинаково минимальны, выбираем более левую точку
        if ((current_y < y_min) || (y_min == current_y && points[i].getX() < points[minimum].getX())) {
            y_min = points[i].getY();
            minimum = i;
        }
    }

    // Ставим минимальную точку на первое место в общем списке точек
    Point tmp = points[0];
    points[0] = points[minimum];
    points[minimum] = tmp;
    startPoint = points[0];

    qsort(&points[1], n-1, sizeof(Point), RetLngPoint); // Сортируем n - 1 точку по полярному углу (функцией RetLngPoint)

    for (int i = 0; i < n; ++i) {
        cout << points[i].getX() << " " << points[i].getY() << endl;
    }

    int j = 1; // Счетчик для будущего стека, в который будем закидывать отсортированные точки
    for (int i = 1; i < n; i++)
    {
        // Избавляемся от точек, которые имеют одинаковый полярный угол и отбрасываем ближайшую
        while (i < n - 1 && WhichSide(startPoint, points[i], points[i + 1]) == 0)
            i++;

        points[j] = points[i];
        j++; // Увеличиваем размер будущего стека
    }

    vector<Point> copyOfStack = {};
    Stack<Point> stack = Stack<Point>(); // Создаем стек и добавляем первые 3 точки из отсортированного массива точек (points)
    stack.push(points[0]);
    stack.push(points[1]);
    stack.push(points[2]);
    copyOfStack.push_back(points[0]);
    copyOfStack.push_back(points[1]);
    copyOfStack.push_back(points[2]);

    for (int i = 3; i < j; i++)
    {
        // Ищем оболочку
        while (WhichSide(nextToTop(stack), stack.top(), points[i]) != -1) {
            stack.pop();
            copyOfStack.pop_back();
        }
        stack.push(points[i]); // Если нашли точку из оболочки – добавляем её в стек
        copyOfStack.push_back(points[i]);
    }

    if (strcmp(typeOfScan, "cc") == 0) {

        if (typeOfFileWriting == "wkt") {
            ofstream writeFS(pathToOutput);

            int size = stack.size();

            writeFS << "MULTIPOINT (";
            for (int i = 0; i < n; ++i) {
                if (i == n - 1) {
                    writeFS << "(" << points[i].ToString() << "))" << endl; // Выписали последнюю точку
                    continue;
                }
                writeFS << "(" << points[i].ToString() << "), "; // Выписали последнюю точку
            }

            writeFS << "POLYGON (";
            for (int i = 0; i < copyOfStack.size(); ++i) {
                writeFS << "(" << copyOfStack[i].ToString() << "), "; // Выписали последнюю точку
            }
            writeFS << "(" << startPoint.ToString() << "))";
        }

        if (typeOfFileWriting == "plain") {
            ofstream writeFS(pathToOutput);
            writeFS << copyOfStack.size() << endl;
            for (int i = 0; i < copyOfStack.size(); ++i) {
                writeFS << copyOfStack[i].ToString() << endl;
            }
        }

    }
    else {
        reverse(begin(copyOfStack) + 1, end(copyOfStack));

        if (typeOfFileWriting == "wkt") {
            ofstream writeFS(pathToOutput);

            int size = stack.size();

            writeFS << "MULTIPOINT (";
            for (int i = 0; i < n; ++i) {
                if (i == n - 1) {
                    writeFS << "(" << points[i].ToString() << "))" << endl; // Выписали последнюю точку
                    continue;
                }
                writeFS << "(" << points[i].ToString() << "), "; // Выписали последнюю точку
            }

            writeFS << "POLYGON (";
            for (int i = 0; i < copyOfStack.size(); ++i) {
                writeFS << "(" << copyOfStack[i].ToString() << "), "; // Выписали последнюю точку
            }
            writeFS << "(" << startPoint.ToString() << "))";
        }

        if (typeOfFileWriting == "plain") {
            ofstream writeFS(pathToOutput);
            writeFS << copyOfStack.size() << endl;
            for (int i = 0; i < copyOfStack.size(); ++i) {
                writeFS << copyOfStack[i].ToString() << endl;
            }
        }
    }
}


int main(int argc, const char *argv[]) {

    string inputFilePath = argv[3]; // Путь к файлу, из которого читаем
    string outputFilePath = argv[4]; // Путь к файлу, в который записываем
    int n; // количество точек
    ifstream readFile(inputFilePath);
    int x, y;
    vector<Point> pointsVec = {};

    if (argc == 5) { // 5 аргументов, т.к 1-ый аргумент - имя файла
        if (strcmp(argv[1], "cw") == 0) {

            readFile >> n; // Заполняем переменную n - количество точек
            while (readFile >> x >> y) { // Создаем точки по полученным из файла координатам
                Point tmp = Point(x, y);
                pointsVec.push_back(tmp);
            }

            Point* pointsArr = &pointsVec[0];

            for (int i = 0; i < pointsVec.size(); ++i) {
                cout << pointsVec[i].ToString() << endl;
            }

            if (strcmp(argv[2], "wkt") == 0) {
                convexHull(pointsArr, n, "wkt", outputFilePath, "cw");
            }
            else if (strcmp(argv[2], "plain") == 0) {
                convexHull(pointsArr, n, "plain", outputFilePath, "cw");
            }

        }
        else if (strcmp(argv[1], "cc") == 0) { // Против часовой стрелки

            readFile >> n; // Заполняем переменную n - количество точек
            while (readFile >> x >> y) { // Создаем точки по полученным из файла координатам
                Point tmp = Point(x, y);
                pointsVec.push_back(tmp);
            }

            Point* pointsArr = &pointsVec[0];

            if (strcmp(argv[2], "wkt") == 0) {
                convexHull(pointsArr, n, "wkt", outputFilePath, "cc");
            }
            else if (strcmp(argv[2], "plain") == 0) {
                convexHull(pointsArr, n, "plain", outputFilePath, "cc");
            }
        }
    }
    return 0;
}