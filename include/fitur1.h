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
} QueueNode;

// Queue ADT
typedef struct {
    QueueNode *front, *rear;
    int size;
} Queue;

// Global navigasi
extern Node *page;

// Fungsi-fungsi
int str_casecmp(const char *a, const char *b);
void queue_init(Queue *q);
void queue_enqueue(Queue *q, Node *data);
void queue_clear(Queue *q);

void sll_buildFromQueue(Queue *q, SLLNode_f1 **head);
void sll_show(SLLNode_f1 *head);
void sll_clear(SLLNode_f1 **head);

void fitur1_searchField(DoubleLinkedList *dll, const char *field);

#endif
