#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

class TreeNode {
    friend class BTree;
    pair<int, int> *keyValue;  // Пары ключ-значение
    int t;      // степень
    TreeNode **NodeChildren; // ссылки на потомков
    int n;     // кол-во элементов (ключ-значение) в конкретном узле
    bool isNodeList; // Является ли узел листом

public:
    TreeNode(int t, bool isNodeLeaf) {
        n = 0;
        this->isNodeList = isNodeLeaf;
        this->t = t;
        NodeChildren = new TreeNode* [2 * t];
        keyValue = new pair<int, int>[2 * t - 1];
    }

    // Возвращаем предшественника пары по индексу atIndex
    pair<int, int> ancestorFunc(int atIndex) {
        TreeNode *curNode = NodeChildren[atIndex];
        while (!curNode->isNodeList)
            curNode = curNode->NodeChildren[curNode->n];
        return curNode->keyValue[curNode->n - 1];
    }

    // Возвращаем потомка пары по индексу atIndex
    pair<int, int> successorFunc(int atIndex) {
        TreeNode *cureNode = NodeChildren[atIndex + 1];
        while (!cureNode->isNodeList)
            cureNode = cureNode->NodeChildren[0];
        return cureNode->keyValue[0];
    }

    // Поиск значения по ключу keyToSearch в паре с ключом keyToSearch
    pair<int,int> searchPairByKey(int keyToSearch) {
        int temp = 0;

        // Если оказывается, что поиск происходит в узле, которого не существует, возвращаем любую пару, не равную по ключу и значению искомой паре
        if (this == nullptr) {
            return make_pair(keyToSearch - 1, keyToSearch - 1);
        }

        // Находим индекс первого ключа, большего или равного искомому ключу
        while (temp < n && keyToSearch > keyValue[temp].first) {
            temp++;
        }

        // Если нашли такой ключ, возвращаем пару ключ-значение
        if ((keyValue[temp].first == keyToSearch) && (temp != n)) {
            return keyValue[temp];
        }

        // Если ключ не найден и узел является листом (то есть ниже уже спускаться некуда)
        // Возвращаем любую пару, не равную по ключу и значению искомой паре
        if (isNodeList) {
            return make_pair(keyToSearch - 1, keyToSearch - 1) ;
        }

        // Переходим к поиску в ребенке
        return NodeChildren[temp]->searchPairByKey(keyToSearch);
    }

    // Забираем ключ из потомка с индексом (index-1) и размещаем его в (index)-ом узле
    void borrowFromPreviousNode(int index) {

        TreeNode *adjacentNode = NodeChildren[index - 1];
        TreeNode *ChildrenNode = NodeChildren[index];

        for (int i = ChildrenNode->n - 1; i >= 0; --i) {
            ChildrenNode->keyValue[i + 1] = ChildrenNode->keyValue[i];
        }
        if (!ChildrenNode->isNodeList) {
            for (int i = ChildrenNode->n; i >= 0; --i) {
                ChildrenNode->NodeChildren[i + 1] = ChildrenNode->NodeChildren[i];
            }
        }
        ChildrenNode->keyValue[0] = keyValue[index - 1];
        if (!ChildrenNode->isNodeList) {
            ChildrenNode->NodeChildren[0] = adjacentNode->NodeChildren[adjacentNode->n];
        }
        keyValue[index - 1] = adjacentNode->keyValue[adjacentNode->n - 1]; // берем пару из сиблинга и вставляем в parent'a
        ChildrenNode->n = ChildrenNode->n + 1;
        adjacentNode->n = adjacentNode->n - 1;
    }

    // Забираем ключ из потомка с индексом (index+1) и размещаем его в (index)-ом узле
    void borrowFromNextNode(int index) {

        TreeNode *adjacentNode = NodeChildren[index + 1];
        TreeNode *childrenNode = NodeChildren[index];

        childrenNode->keyValue[(childrenNode->n)] = keyValue[index];

        if (!(childrenNode->isNodeList)) {
            childrenNode->NodeChildren[(childrenNode->n) + 1] = adjacentNode->NodeChildren[0];
        }
        keyValue[index] = adjacentNode->keyValue[0];

        for (int i = 1; i < adjacentNode->n; ++i) {
            adjacentNode->keyValue[i - 1] = adjacentNode->keyValue[i];
        }

        if (!adjacentNode->isNodeList) {
            for (int i = 1; i <= adjacentNode->n; ++i) {
                adjacentNode->NodeChildren[i - 1] = adjacentNode->NodeChildren[i];
            }
        }
        adjacentNode->n = adjacentNode->n - 1;
        childrenNode->n = childrenNode->n + 1;
    }

    // Вставка элемента в узел, если он ещё не заполнен
    void insertIfNodeIsNotFull(pair<int, int> pairToInsert) {

        int indexOfEmptyPlace = n - 1; // Индекс самого правого элемента в узле

        // Если узел является листом, находим в нем место для новой пары ключ-значение и передвигаем правые элементы вправо
        if (isNodeList) {
            while (indexOfEmptyPlace >= 0 && keyValue[indexOfEmptyPlace].first > pairToInsert.first) {
                keyValue[indexOfEmptyPlace + 1] = keyValue[indexOfEmptyPlace];
                indexOfEmptyPlace = indexOfEmptyPlace - 1;
            }
            keyValue[indexOfEmptyPlace + 1] = pairToInsert; // по нужному индексу вставляем элемент
            n++; // Добавили новый элемент - увеличили количество элементов в узле
        } else {

            // Поиск потомка
            while (keyValue[indexOfEmptyPlace].first > pairToInsert.first && indexOfEmptyPlace >= 0) {
                indexOfEmptyPlace -= 1;
            }

            // Если в найденном потомке нет места
            if (NodeChildren[indexOfEmptyPlace + 1]->n == 2 * t - 1) {

                // Разделяем этого потомка
                separateDescendantNode(indexOfEmptyPlace + 1, NodeChildren[indexOfEmptyPlace + 1]);

                if (pairToInsert.first > keyValue[indexOfEmptyPlace + 1].first) {
                    indexOfEmptyPlace = indexOfEmptyPlace + 1;
                }
            }

            NodeChildren[indexOfEmptyPlace + 1]->insertIfNodeIsNotFull(pairToInsert);
        }
    }

    // Удаление по переданному ключу
    void removePairByKey(int keyToDelete) {
        int indexOfPair = 0;

        while (keyValue[indexOfPair].first < keyToDelete && indexOfPair < n) {
            indexOfPair = indexOfPair + 1;
        }

        // Ниже просто проверяем перед удалением, существует ли такой пара с таким ключом в дереве
        if (keyValue[indexOfPair].first == keyToDelete && indexOfPair < n) {
            isNodeList ? removeIfNodeIsLeaf(indexOfPair) : removeIfNodeIsNotLeaf(indexOfPair);
        } else {
            if (isNodeList) {
                return;
            }
            if (NodeChildren[indexOfPair]->n < t)
                populateChildNode(indexOfPair);

            (indexOfPair > n && (indexOfPair == n)) ? NodeChildren[indexOfPair - 1]->removePairByKey(keyToDelete) : NodeChildren[indexOfPair]->removePairByKey(
                    keyToDelete);
        }
    }

    // Удаление пары по индексу ключа keyIndex в листе
    void removeIfNodeIsLeaf(int keyIndex) {
        for (int i = keyIndex + 1; i < n; ++i) {
            keyValue[i - 1] = keyValue[i];
        }
        n = n - 1;
    }

    // Удаление пары по индексу ключа keyIndex не в листе
    void removeIfNodeIsNotLeaf(int keyIndex) {
        if (NodeChildren[keyIndex]->n >= t) {
            pair<int, int> ancestor = ancestorFunc(keyIndex);
            keyValue[keyIndex] = ancestor;
            NodeChildren[keyIndex]->removePairByKey(ancestor.first);
        }
        else if (NodeChildren[keyIndex + 1]->n >= t) {
            pair<int, int> ss = successorFunc(keyIndex);
            keyValue[keyIndex] = ss;
            NodeChildren[keyIndex + 1]->removePairByKey(ss.first);
        }
        else {
            uniteTwoChildren(keyIndex);
            NodeChildren[keyIndex]->removePairByKey(keyValue[keyIndex].first);
        }
    }

    // Разделение потомка на две части
    void separateDescendantNode(int tmp, TreeNode *NodeToSeparate) {

        auto *newChildNode = new TreeNode(NodeToSeparate->t, NodeToSeparate->isNodeList);
        newChildNode->n = t - 1; // Размерность нового потомка

        // Последние t - 1 элементов из старого узла перекидываем в новый узел
        for (int index = 0; index < t - 1; index++) {
            newChildNode->keyValue[index] = NodeToSeparate->keyValue[index + t];
        }

        if (!NodeToSeparate->isNodeList) {
            // Копируем последние t элементов в новый узел из старого. При этом элемент, которых находился по середине старого
            // Уходит наверх, и разбиение старого узла происходит относительно этого элемента
            for (int index = 0; index < t; index++) {
                newChildNode->NodeChildren[index] = NodeToSeparate->NodeChildren[index + t];
            }
        }

        NodeToSeparate->n = t - 1;

        // Сдвигаем элементы в новом ребенке, чтобы освободить место для новой пары
        for (int index = n; index >= tmp + 1; index--) {
            NodeChildren[index + 1] = NodeChildren[index];
        }

        NodeChildren[tmp + 1] = newChildNode;
        for (int index = n - 1; index >= tmp; index--) {
            keyValue[index + 1] = keyValue[index];
        }
        keyValue[tmp] = NodeToSeparate->keyValue[t - 1];
        n += 1;
    }

    // Функция для заполнения дочернего узла на atIndex-й позиции массива потомков, если этот дочерний узел имеет меньше t элементов
    void populateChildNode(int atIndex) {
        if (atIndex != n && NodeChildren[atIndex + 1]->n >= t) {
            borrowFromNextNode(atIndex);
        } else if (atIndex != 0 && NodeChildren[atIndex - 1]->n >= t) {
            borrowFromPreviousNode(atIndex);
        } else {
            (atIndex == n) ? uniteTwoChildren(atIndex - 1) : uniteTwoChildren(atIndex);
        }
    }

    // Объединение NodeChildren[atIndex] с NodeChildren[atIndex+1] в один узел
    void uniteTwoChildren(int atIndex) {

        TreeNode *adjacentNode = NodeChildren[atIndex + 1];
        TreeNode *childrenNode = NodeChildren[atIndex];

        childrenNode->keyValue[t - 1] = keyValue[atIndex];

        for (int index = 0; index < adjacentNode->n; ++index) {
            childrenNode->keyValue[index + t] = adjacentNode->keyValue[index]; // копируем пары из NodeChildren[atIndex+1] в NodeChildren[atIndex] конец
        }

        // Все ссылки на детей из NodeChildren[atIndex + 1] передаем на соотв. позиции в NodeChildren[atIndex]
        if (!childrenNode->isNodeList) {
            for (int index = 0; index <= adjacentNode->n; ++index) {
                childrenNode->NodeChildren[index + t] = adjacentNode->NodeChildren[index]; // копируем пары из NodeChildren[atIndex+1] в NodeChildren[atIndex]
            }
        }

        for (int i = atIndex + 1; i < n; ++i)
            keyValue[i - 1] = keyValue[i];
        for (int i = atIndex + 2; i <= n; ++i)
            NodeChildren[i - 1] = NodeChildren[i];

        childrenNode->n += adjacentNode->n + 1;
        delete (adjacentNode);
        --n;
    }
};

class BTree {
    TreeNode *firstRoot;
    int t;

public:

    BTree(int _t) {
        // firstRoot пока делаем NULL, т.к в нём нет ни одной пары ключ-значение
        firstRoot = nullptr;
        t = _t;
    }

    // Вставка в дерево пары ключ-значение
    void insert(pair<int, int> keyValue) {
        if (firstRoot == nullptr) {
            firstRoot = new TreeNode(t, true); // Т.к был налл => это лист, создаем его объект
            firstRoot->keyValue[0] = keyValue;
            firstRoot->n = 1;
            return;
        }
        else
        {
            if (firstRoot->n == 2 * t - 1) {
                auto *newFirstRoot = new TreeNode(t, false);
                newFirstRoot->NodeChildren[0] = firstRoot;
                newFirstRoot->separateDescendantNode(0, firstRoot);
                int counter = 0;
                if (keyValue > newFirstRoot->keyValue[0])
                    counter = counter + 1;
                newFirstRoot->NodeChildren[counter]->insertIfNodeIsNotFull(keyValue);
                firstRoot = newFirstRoot;
            } else {
                firstRoot->insertIfNodeIsNotFull(keyValue);
            }
        }
    }

    // Поиск значение по ключу
    pair<bool,int> search(int keyToSearch) {
        pair<int,int> temporaryPair;
        temporaryPair = firstRoot->searchPairByKey(keyToSearch);
        return temporaryPair.first == keyToSearch ? make_pair(true, temporaryPair.second) : make_pair(false, 1000000001);
    }

    // Удаление по переданному ключу
    void removeByKey(int key) {
        if (!firstRoot) {
            return;
        }

        firstRoot->removePairByKey(key);

        if (firstRoot->n == 0) {
            TreeNode *temporaryTreeNode = firstRoot;
            firstRoot = (firstRoot->isNodeList) ? nullptr : firstRoot->NodeChildren[0];
            delete temporaryTreeNode;
        }
    }
};

int main(int args, const char *argv[]) {
    string pathToRead = argv[2];
    string pathToWrite = argv[3];
    ifstream in = ifstream (pathToRead);
    ofstream out = ofstream (pathToWrite);
    string currentOperation;
    BTree bTree =  BTree(int(*argv[1]));
    vector<string> answers;

    while (in >> currentOperation) { // Пока операции не закончатся, продолжаем считывание
        if (currentOperation == "find") {
            int keyToSearch;
            in >> keyToSearch;
            pair<int,int> pair = bTree.search(int(keyToSearch));
            if (pair.first == false) {
                answers.push_back("null");
                continue;
            }
            answers.push_back(to_string(pair.second));
        } else if (currentOperation == "insert") {
            int keyToSearch, value;
            in >> keyToSearch >> value;
            pair<int,int> pairToInsert = bTree.search(int(keyToSearch));
            if (pairToInsert.first == false) {
                bTree.insert(pair<int, int>(int(keyToSearch), int(value)));
                answers.push_back("true");
                continue;
            }
            answers.push_back("false");
        } else if (currentOperation == "delete") {
            int keyToSearch;
            in >> keyToSearch;
            pair<int,int> tmpPair = bTree.search(int(keyToSearch));
            if (tmpPair.first == true) {
                answers.push_back(to_string(tmpPair.second));
                bTree.removeByKey(int(keyToSearch));
                continue;
            }
            answers.push_back("null");
        }
    }

    // Выводим в файл (сделал через вектор, чтобы не записывалась пустая строка в конец файла)
    for (int i = 0; i < answers.size(); ++i) {
        if (i == answers.size() - 1) {
            out << answers.at(i);
            break;
        }
        out << answers.at(i) << endl;
    }

    return 0;
}