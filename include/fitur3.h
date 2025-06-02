#ifndef FITUR3_H
#define FITUR3_H

#include "dll.h" // Assuming dll.h contains the Journal struct and DoubleLinkedList

#define MAX_STR 256
#define MAX_RESULTS 10

typedef struct {
    char title[MAX_STR];
    char doiUrl[MAX_STR];
    char authors[MAX_STR];
} SearchResult3;

typedef struct SLLNode3 {
    SearchResult3 data;
    struct SLLNode3* next;
} SLLNode3;

typedef struct {
    SLLNode3* head;
    int size;
} SingleLinkedList3;

void sll3_init(SingleLinkedList3* list);
SLLNode3* sll3_createNode(SearchResult3 data);
void sll3_insertLast(SingleLinkedList3* list, SearchResult3 data);
void sll3_printList(SingleLinkedList3* list);
void sll3_freeList(SingleLinkedList3* list);

void search_journals_by_author(DoubleLinkedList* sourceList, SingleLinkedList3* resultList, const char* authorKeyword);

#endif // FITUR3_H