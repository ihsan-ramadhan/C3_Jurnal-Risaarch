#ifndef FITUR1_H
#define FITUR1_H

#include "dll.h"

#define MAX_QUEUE 10

typedef struct QueueNode {
    Node *data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front, *rear;
    int size;
} Queue;

typedef struct SLLNode_f1 {
    char title[MAX_STR];
    char url[MAX_STR];
    struct SLLNode_f1 *next;
} SLLNode_f1;

// Fungsi utama
void fitur1_searchField(DoubleLinkedList *dll, const char *field);

// Queue
void queue_init(Queue *q);
void queue_enqueue(Queue *q, Node *data);
void queue_clear(Queue *q);

// SLL tampilan
void sll_buildFromQueue(Queue *q, SLLNode_f1 **head);
void sll_show(SLLNode_f1 *head);
void sll_clear(SLLNode_f1 **head);

#endif
