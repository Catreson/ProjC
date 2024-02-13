#include <string>
#ifndef STRUCTS_H
#define STRUCTS_H

// STRUCTURES
template <typename T> struct List {
    struct List *next;
    T value;
    int arr;
};

struct Triplet {
    int weight;
    std::string path;
    int arr;
};

#endif // STRUCTS_H
