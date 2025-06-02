#ifndef DLL_H
#define DLL_H

#define MAX_STR 256

typedef struct {
    char title[MAX_STR];
    char authors[MAX_STR];
    char fieldOfStudy[MAX_STR];
    int year;
    char doiUrl[MAX_STR];
} Journal;

typedef struct Node {
    Journal data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoubleLinkedList;

void dll_init(DoubleLinkedList* list);
Node* dll_createNode(Journal data);
void dll_insertLast(DoubleLinkedList* list, Journal data);
void dll_freeList(DoubleLinkedList* list);

#endif