#include "structs.h"
#ifndef QUEUE_H
#define QUEUE_H




// CLASSES
template <typename T> class Queue {
private:
    List<T> root;
    List<T> *curr;
    List<T> *tmp;

public:
    int length;
    Queue() {
        length = 0;
        root.next = nullptr;
    }
    ~Queue() {
        curr = &root;
        curr = curr->next != nullptr ? curr->next : curr;
        while (curr->next != nullptr) {
            tmp = curr->next;
            delete curr;
            curr = tmp;
        }
        curr = nullptr;
        tmp = nullptr;
    }

    void Push(T a) {
        curr = &root;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = new List<T>;
        curr = curr->next;
        curr->next = nullptr;
        curr->value = a;
        length++;
    }
    void PriorityPush(T a) {
        curr = &root;

        while (curr->next != nullptr) {
            if (curr->next->value.weight > a.weight) {
                tmp = new List<T>;
                tmp->value = a;
                tmp->next = curr->next;
                curr->next = tmp;
                length++;
                // cout << "In the middle\n";
                return;
            }
            curr = curr->next;
        }
        curr->next = new List<T>;
        curr = curr->next;
        curr->next = nullptr;
        curr->value = a;
        length++;
        // cout << "At end\n";
    }
    T Pop() {
        T a;
        curr = &root;
        a = curr->next->value;
        tmp = curr->next;
        curr->next = curr->next->next;
        length--;
        delete tmp;
        return a;
    }
};

#endif // QUEUE_H
