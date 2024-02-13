#include<string>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// FUNCTION DECLARATIONS
int CharToInt(char a);
void PrintCurrState(int currState[][3]);
int NodeWeightBase(int tmpStaten[][3]);
int NodeWeight(int currState[][3], int side);
std::pair<int, int> CalculateCorrPosition(int index);
void Monke(int currState[][3], int prev, bool &solv);
void Shuffel(int currState[][3], int steps);
bool MonkeV2(int currState[][3], std::string path);
inline int MakeCharNumberInt(char a) { return (int)(a - '0'); }
int (*(IntToArray)(int input))[3];
int ArrayToInt(int arr[][3]);
void startQueue(struct Triplet trip);
#endif // FUNCTIONS_H
