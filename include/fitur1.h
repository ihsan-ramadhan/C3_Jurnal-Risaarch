#ifndef FITUR1_H
#define FITUR1_H

#include "dll.h"

#define MAX_QUEUE 10

// Node untuk hasil tampilan (Singly Linked List)
typedef struct SLLNode_f1 {
    char title[256];
    char url[256];
    struct SLLNode_f1 *next;
} SLLNode_f1;

// Node Queue
typedef struct QueueNode {
    Node *data;
    struct QueueNode *next;
} QueueNode_f1;

// Queue ADT
typedef struct {
    QueueNode_f1 *front, *rear;
    int size;
} Queue_f1;

// Global navigasi
extern Node *page;

// Fungsi-fungsi
int str_casecmp(const char *a, const char *b);
void queue_init(Queue_f1 *q);
void queue_enqueue(Queue_f1 *q, Node *data);
void queue_clear(Queue_f1 *q);

void sll_buildFromQueue(Queue_f1 *q, SLLNode_f1 **head);
void sll_show(SLLNode_f1 *head);
void sll_clear(SLLNode_f1 **head);

void fitur1_searchField(DoubleLinkedList *dll, const char *field);

#endif
