#ifndef FITUR4_H
#define FITUR4_H

#include "dll.h"

#define MAX_STR 256

typedef struct {
    char title[MAX_STR];
    char doiUrl[MAX_STR];
} SearchResult;

typedef struct SLLNode {
    SearchResult data;
    struct SLLNode* next;
} SLLNode;

typedef struct {
    SLLNode* head;
    int size;
} SingleLinkedList;

void sll_init(SingleLinkedList* list);
SLLNode* sll_createNode(SearchResult data);
void sll_insertLast(SingleLinkedList* list, SearchResult data);
void sll_printList(SingleLinkedList* list);
void sll_freeList(SingleLinkedList* list);

void search_journals(DoubleLinkedList* sourceList, SingleLinkedList* resultList, const char* keyword);

#endif