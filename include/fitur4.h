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

typedef struct QueueNode4 {
    SearchResult data;
    struct QueueNode4* next;
} QueueNode4;

typedef struct {
    QueueNode4* front;
    QueueNode4* rear;
    int size;
} Queue4;

void sll_init(SingleLinkedList* list);
SLLNode* sll_createNode(SearchResult data);
void sll_insertLast(SingleLinkedList* list, SearchResult data);
void sll_printList(SingleLinkedList* list);
void sll_freeList(SingleLinkedList* list);

void queue_init4(Queue4* queue);
void queue_enqueue4(Queue4* queue, SearchResult data);
SearchResult queue_dequeue4(Queue4* queue);
int queue_isEmpty4(Queue4* queue);
void queue_free4(Queue4* queue);

void search_journals(DoubleLinkedList* sourceList, SingleLinkedList* resultList, const char* keyword);

#endif