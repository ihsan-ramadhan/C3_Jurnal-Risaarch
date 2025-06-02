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

typedef struct QueueNode {
    SearchResult data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;

void sll_init(SingleLinkedList* list);
SLLNode* sll_createNode(SearchResult data);
void sll_insertLast(SingleLinkedList* list, SearchResult data);
void sll_printList(SingleLinkedList* list);
void sll_freeList(SingleLinkedList* list);

void queue_init(Queue* queue);
void queue_enqueue(Queue* queue, SearchResult data);
SearchResult queue_dequeue(Queue* queue);
int queue_isEmpty(Queue* queue);
void queue_free(Queue* queue);

void search_journals(DoubleLinkedList* sourceList, SingleLinkedList* resultList, const char* keyword);

#endif