#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fitur1.h"

static Node *page = NULL; // Pointer untuk navigasi

// Fungsi bantu: perbandingan string tanpa case-sensitive
int str_casecmp(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (tolower(*a) != tolower(*b))
            return tolower(*a) - tolower(*b);
        a++;
        b++;
    }
    return *a - *b;
}

// Queue
void queue_init(Queue *q)
{
    q->front = q->rear = NULL;
    q->size = 0;
}

void queue_enqueue(Queue *q, Node *data)
{
    if (q->size >= MAX_QUEUE)
        return;
    QueueNode *newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    if (!q->front)
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

void queue_clear(Queue *q)
{
    while (q->front)
    {
        QueueNode *temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
    q->size = 0;
}

// SLL untuk tampilan
void sll_buildFromQueue(Queue *q, SLLNode_f1 **head)
{
    *head = NULL;
    SLLNode_f1 *tail = NULL;

    QueueNode *curr = q->front;
    while (curr)
    {
        SLLNode_f1 *newNode = malloc(sizeof(SLLNode_f1));
        strcpy(newNode->title, curr->data->data.title);
        strcpy(newNode->url, curr->data->data.doiUrl);
        newNode->next = NULL;
        if (!*head)
        {
            *head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        curr = curr->next;
    }
}

void sll_show(SLLNode_f1 *head)
{
    int i = 1;
    while (head)
    {
        printf("%d. %s\n   URL: %s\n", i++, head->title, head->url);
        head = head->next;
    }
}

void sll_clear(SLLNode_f1 **head)
{
    while (*head)
    {
        SLLNode_f1 *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Fitur 1 utama
void fitur1_searchField(DoubleLinkedList *dll, const char *field)
{
    page = dll->head;

    while (1)
    {
        Queue q;
        queue_init(&q);
        Node *curr = page;
        int found = 0;

        // Masukkan max 10 yang cocok ke queue
        while (curr && q.size < MAX_QUEUE)
        {
            if (str_casecmp(curr->data.fieldOfStudy, field) == 0)
            {
                queue_enqueue(&q, curr);
                if (!found)
                    page = curr; // simpan posisi
                found = 1;
            }
            curr = curr->next;
        }

        if (q.size == 0)
        {
            printf("Tidak ditemukan jurnal dengan Field of Study: %s\n", field);
            return;
        }

        SLLNode_f1 *result = NULL;
        sll_buildFromQueue(&q, &result);
        sll_show(result);
        sll_clear(&result);

        // Navigasi
        char nav;
        printf("\n[n] Next | [q] Quit: ");
        scanf(" %c", &nav);

        if (nav == 'n')
        {
            int steps = 0;
            while (page && steps < MAX_QUEUE)
            {
                page = page->next;
                steps++;
            }
            if (!page)
            {
                printf("Sudah di akhir data.\n");
                break;
            }
        }
        else
        {
            break;
        }

        queue_clear(&q);
    }
}
