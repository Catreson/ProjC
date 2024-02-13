#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "structs.h"
#include "functions.h"
#include "queue.h"

#define INT_MAXIMUM 2147483647
#define SIDE_UP 0
#define SIDE_RIGHT 1
#define SIDE_DOWN 2
#define SIDE_LEFT 3

using namespace std;

// MAIN
int main() {
    int(*initState)[3];
    initState = IntToArray(123456780);
    //char tmpChar;
    string path;
    int inputInt, mode, steps;
    //bool solv = false;
    //pair<int, int> blank;
    srand(time(NULL));
    cout << "Select mode, 0 for user input 1 for randomised table:\t";
    cin >> mode;
    cout << "Input values separated by spaces, 0 is blank spot\n";
    if (mode == 0) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cin >> inputInt;
                /*if (inputInt == 0) {
                    blank.first = i;
                    blank.second = j;
                }*/
                initState[i][j] = inputInt;
            }
        }
        cout << "Input complete";
        cout << "\nInputINT\t" << ArrayToInt(initState) << "\n";
        cout << "InputArray\n";
        PrintCurrState(initState);
    } else {
        /*for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        initState[i][j] = 3 * i + j + 1;
    }
}*/
        initState = IntToArray(123456780);
        cout << "How many steps?\n";
        cin >> steps;
        initState[3 - 1][3 - 1] = 0;
        //blank.first = 3 - 1;
        //blank.second = 3 - 1;
        Shuffel(initState, steps);
        cout << "RANDOMISED TABLE:\n";
        PrintCurrState(initState);
    }
    int iterationLimit = 0;
    cout << "Enter iteration limit:\t";
    cin >> iterationLimit;
    struct Triplet tmpTriplet;
    tmpTriplet.arr = ArrayToInt(initState);
    tmpTriplet.path = "";
    tmpTriplet.weight = INT_MAXIMUM;
    startQueue(tmpTriplet);
    for (int i = 0; i < iterationLimit; ++i) {
        cout << "\nIteration:\t" << i << "\n";
        if (MonkeV2(initState, path))
            break;
    }

    cout << "FINISH\n";

    cout << "PROGRAM ENDS\n";

    return 0;
}


