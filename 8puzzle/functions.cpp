#include <iostream>
#include "functions.h"
#include "structs.h"
#include "queue.h"

#define INT_MAXIMUM 2147483647
#define SIDE_UP 0
#define SIDE_RIGHT 1
#define SIDE_DOWN 2
#define SIDE_LEFT 3

std::pair<int, int> blank;
Queue<struct Triplet> queue;

void PrintCurrState(int currState[][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            std::cout << currState[i][j] << "\t";
        std::cout << "\n";
    }
    std::cout<< "-----------------\n\n";
}

std::pair<int, int> CalculateCorrPosition(int index) {
    std::pair<int, int> position;
    position.first = (int)(index - 1) / 3;
    position.second = (index - 1) % 3;
    return position;
}

void MakeMove(int currState[][3], int indexMinimum) {
    int tmpInt;
    switch (indexMinimum) {
    case SIDE_UP:
        tmpInt = currState[blank.first - 1][blank.second];
        currState[blank.first - 1][blank.second] = 0;
        currState[blank.first][blank.second] = tmpInt;
        blank.first--;
        break;
    case SIDE_RIGHT:
        tmpInt = currState[blank.first][blank.second + 1];
        currState[blank.first][blank.second + 1] = 0;
        currState[blank.first][blank.second] = tmpInt;
        blank.second++;
        break;
    case SIDE_DOWN:
        tmpInt = currState[blank.first + 1][blank.second];
        currState[blank.first + 1][blank.second] = 0;
        currState[blank.first][blank.second] = tmpInt;
        blank.first++;
        break;
    case SIDE_LEFT:
        tmpInt = currState[blank.first][blank.second - 1];
        currState[blank.first][blank.second - 1] = 0;
        currState[blank.first][blank.second] = tmpInt;
        blank.second--;
        break;
    }
    return;
}

int CalculatePuzzleWeight(int index, int i, int j) {
    std::pair<int, int> corrPosition;
    int puzzelWeight = 0;
    corrPosition = CalculateCorrPosition(index);
    puzzelWeight += abs(i - corrPosition.first);
    puzzelWeight += abs(j - corrPosition.second);
    return puzzelWeight;
}

int NodeWeightBase(int tmpStaten[][3]) {
    std::pair<int, int> corrPosition;
    int nodeWeight = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tmpStaten[i][j] != 0)
                nodeWeight += CalculatePuzzleWeight(tmpStaten[i][j], i, j);
        }
    }
    return nodeWeight;
}

int NodeWeight(int tmpStaten[][3], int side) {
    std::pair<int, int> corrPosition;
    int nodeWeight = 0;
    switch (side) {
    case -1:
        nodeWeight = NodeWeightBase(tmpStaten);
        break;

    case SIDE_UP:
        nodeWeight = NodeWeightBase(tmpStaten);
        if (blank.first == 0) {
            nodeWeight = INT_MAXIMUM;
            break;
        }
        nodeWeight -=
            CalculatePuzzleWeight(tmpStaten[blank.first - 1][blank.second],
                                  blank.first - 1, blank.second);
        nodeWeight += CalculatePuzzleWeight(
            tmpStaten[blank.first - 1][blank.second], blank.first, blank.second);
        break;

    case SIDE_RIGHT:
        nodeWeight = NodeWeightBase(tmpStaten);
        if (blank.second == 3 - 1) {
            nodeWeight = INT_MAXIMUM;
            break;
        }
        nodeWeight -=
            CalculatePuzzleWeight(tmpStaten[blank.first][blank.second + 1],
                                  blank.first, blank.second + 1);
        nodeWeight += CalculatePuzzleWeight(
            tmpStaten[blank.first][blank.second + 1], blank.first, blank.second);
        break;

    case SIDE_DOWN:
        nodeWeight = NodeWeightBase(tmpStaten);
        if (blank.first == 3 - 1) {
            nodeWeight = INT_MAXIMUM;
            break;
        }
        nodeWeight -=
            CalculatePuzzleWeight(tmpStaten[blank.first + 1][blank.second],
                                  blank.first + 1, blank.second);
        nodeWeight += CalculatePuzzleWeight(
            tmpStaten[blank.first + 1][blank.second], blank.first, blank.second);
        break;

    case SIDE_LEFT:
        nodeWeight = NodeWeightBase(tmpStaten);
        if (blank.second == 0) {
            nodeWeight = INT_MAXIMUM;
            break;
        }
        nodeWeight -=
            CalculatePuzzleWeight(tmpStaten[blank.first][blank.second - 1],
                                  blank.first, blank.second - 1);
        nodeWeight += CalculatePuzzleWeight(
            tmpStaten[blank.first][blank.second - 1], blank.first, blank.second);
        break;
    }
    // std::cout << "Masa " << side << ":" << nodeWeight << "\n";
    return (int)nodeWeight;
}

void DoPath(int currState[][3], std::string path) {
    //int dir;
    for (int i = 0; i < path.length(); i++) {
        MakeMove(currState, MakeCharNumberInt(path[i]));
    }
}

int (*(IntToArray)(int input))[3] {
    int tmp;
    static int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    for (int i = 9; i > 0; --i) {
        tmp = input % 10;
        input = input / 10;
        arr[(i - 1) / 3][(i - 1) % 3] = tmp;
    }
    return arr;
}

int ArrayToInt(int arr[][3]) {
    int a = 0;
    int tmp;
    for (int i = 0; i < 9; ++i) {
        tmp = arr[i / 3][i % 3];
        a = a * 10 + tmp;
    }
    return a;
}

void UndoPath(int currState[][3], std::string path) {
    int dir;
    for (int i = path.length() - 1; i >= 0; i--) {
        MakeMove(currState, (MakeCharNumberInt(path[i]) + 2) % 4);
    }
}

std::string DrawPath(std::string inputString) {
    std::string outputString;
    for (int i = 0; i < inputString.length(); i++) {
        switch (inputString[i]) {
        case '0':
            outputString += '^';
            break;
        case '1':
            outputString += '>';
            break;
        case '2':
            outputString += 'v';
            break;
        case '3':
            outputString += '<';
            break;
        }
    }
    return outputString;
}

void Shuffel(int currState[][3], int steps) {
    int dir;
    bool sanity;
    for (int i = 0; i < steps; i++) {
        dir = rand() % 4;
        if ((dir == 0 && blank.first == 0) || (dir == 1 && blank.second == 3 - 1) ||
            (dir == 2 && blank.first == 3 - 1) || (dir == 3 && blank.second == 0)) {
            steps++;
            continue;
        }
        MakeMove(currState, dir);
        // PrintCurrState(currState);
    }
}

std::pair<int, int> BlankFind(int a) {
    std::pair<int, int> vale;
    int tmp;
    for (int i = 9; i > 0; i--) {
        tmp = a % 10;
        a = a / 10;
        if (tmp == 0) {
            vale.first = (i - 1) / 3;
            vale.second = (i - 1) % 3;
        }
    }
    return vale;
}

void startQueue(struct Triplet trip)
{
    queue.Push(trip);
}

bool MonkeV2(int currState[][3], std::string path) {
    int valuesNodes[4];
    int(*tmpState)[3];
    int sortValues[4] = {0, 1, 2, 3};
    int move;
    Queue<int> que;
    struct Triplet tmpPair;
    tmpPair = queue.Pop();
    // std::cout << "\nArray:\t" << tmpPair.arr << "\n";
    tmpState = IntToArray(tmpPair.arr);
    blank = BlankFind(tmpPair.arr);
    PrintCurrState(tmpState);
    if (NodeWeightBase(tmpState) == 0) {
        std::cout << "SOLVED\n";
        return true;
    }
    valuesNodes[SIDE_UP] = NodeWeight(tmpState, SIDE_UP);
    valuesNodes[SIDE_RIGHT] = NodeWeight(tmpState, SIDE_RIGHT);
    valuesNodes[SIDE_DOWN] = NodeWeight(tmpState, SIDE_DOWN);
    valuesNodes[SIDE_LEFT] = NodeWeight(tmpState, SIDE_LEFT);

    int tmpInt;
    for (int i = 0; i < 4 - 1; i++) {
        for (int j = 0; j < 4 - 1 - i; j++) {
            if (valuesNodes[sortValues[j]] > valuesNodes[sortValues[j + 1]]) {
                tmpInt = sortValues[j];
                sortValues[j] = sortValues[j + 1];
                sortValues[j + 1] = tmpInt;
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (valuesNodes[sortValues[i]] != INT_MAXIMUM)
            que.Push(sortValues[i]);
    }

    // struct Triplet tmpPair;

    while (que.length > 0) {
        move = que.Pop();
        tmpPair.weight = NodeWeightBase(tmpState) + valuesNodes[move];
        tmpPair.path = path + std::to_string(move);
        DoPath(tmpState, std::to_string(move));
        tmpPair.arr = ArrayToInt(tmpState);
        UndoPath(tmpState, std::to_string(move));
        queue.PriorityPush(tmpPair);
    }

    // UndoPath(currState, path);
    //  tmpPair = queue.FindMinimum();
    //  queue.Killer(tmpPair);
    // tmpPair = queue.Pop();
    // std::cout << "DEPTH:\t" << tmpPair.path.length() << "\n";
    // std::cout << "PATH:\t" << DrawPath(tmpPair.path) << "\n";
    std::cout << "--------\n";
    // DoPath(currState, tmpPair.path);
    return false;
}
