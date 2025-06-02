#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fitur4.h"

void sll_init(SingleLinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

SLLNode* sll_createNode(SearchResult data) {
    SLLNode* newNode = (SLLNode*)malloc(sizeof(SLLNode));
    if (newNode == NULL) {
        printf("Gagal alokasi memori!\n");
        return NULL;
    }
    strcpy(newNode->data.title, data.title);
    strcpy(newNode->data.doiUrl, data.doiUrl);
    newNode->next = NULL;
    return newNode;
}

void sll_insertLast(SingleLinkedList* list, SearchResult data) {
    SLLNode* newNode = sll_createNode(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        SLLNode* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void sll_printList(SingleLinkedList* list) {
    if (list->head == NULL) {
        printf("Tidak ada jurnal yang sesuai.\n");
        return;
    }

    const int label_width = 10;

    printf("\nHasil pencarian:\n");
    SLLNode* current = list->head;
    int row_number = 1;
    while (current != NULL) {
        printf("%d. %-*s %s\n", 
               row_number, 
               label_width, "Title:", 
               current->data.title);
        printf("   %-*s %s\n", 
               label_width, "DOI URL:", 
               strlen(current->data.doiUrl) ? current->data.doiUrl : "-");
        if (current->next != NULL) {
            printf("\n");
        }
        current = current->next;
        row_number++;
    }

    printf("\nTotal jurnal yang sesuai: %d\n", list->size);
}

void sll_freeList(SingleLinkedList* list) {
    SLLNode* current = list->head;
    while (current != NULL) {
        SLLNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}

void queue_init4(Queue4* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

QueueNode4* queue_createNode4(SearchResult data) {
    QueueNode4* newNode = (QueueNode4*)malloc(sizeof(QueueNode4));
    if (newNode == NULL) {
        printf("Gagal alokasi memori!\n");
        return NULL;
    }
    strcpy(newNode->data.title, data.title);
    strcpy(newNode->data.doiUrl, data.doiUrl);
    newNode->next = NULL;
    return newNode;
}

void queue_enqueue4(Queue4* queue, SearchResult data) {
    QueueNode4* newNode = queue_createNode4(data);
    if (newNode == NULL) return;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

SearchResult queue_dequeue4(Queue4* queue) {
    SearchResult empty = {"", ""};
    if (queue->front == NULL) return empty;

    QueueNode4* temp = queue->front;
    SearchResult data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return data;
}

int queue_isEmpty4(Queue4* queue) {
    return queue->front == NULL;
}

void queue_free4(Queue4* queue) {
    while (!queue_isEmpty4(queue)) {
        queue_dequeue4(queue);
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

static int stristr(const char* str, const char* substr) {
    if (!str || !substr) return 0;
    
    int len_str = strlen(str);
    int len_substr = strlen(substr);
    if (len_substr > len_str) return 0;

    char* lower_str = (char*)malloc(len_str + 1);
    char* lower_substr = (char*)malloc(len_substr + 1);
    if (!lower_str || !lower_substr) {
        free(lower_str);
        free(lower_substr);
        return 0;
    }

    for (int i = 0; i < len_str; i++) {
        lower_str[i] = tolower(str[i]);
    }
    lower_str[len_str] = '\0';

    for (int i = 0; i < len_substr; i++) {
        lower_substr[i] = tolower(substr[i]);
    }
    lower_substr[len_substr] = '\0';

    int result = strstr(lower_str, lower_substr) != NULL;

    free(lower_str);
    free(lower_substr);
    return result;
}

void search_journals(DoubleLinkedList* sourceList, SingleLinkedList* resultList, const char* keyword) {
    if (!sourceList || !resultList || !keyword) return;

    sll_init(resultList);
    Queue4 queue;
    queue_init4(&queue);

    Node* current = sourceList->head;
    while (current != NULL) {
        if (stristr(current->data.title, keyword)) {
            SearchResult result;
            strncpy(result.title, current->data.title, MAX_STR - 1);
            result.title[MAX_STR - 1] = '\0';
            strncpy(result.doiUrl, current->data.doiUrl, MAX_STR - 1);
            result.doiUrl[MAX_STR - 1] = '\0';
            queue_enqueue4(&queue, result);
        }
        current = current->next;
    }

    while (!queue_isEmpty4(&queue)) {
        SearchResult result = queue_dequeue4(&queue);
        sll_insertLast(resultList, result);
    }

    queue_free4(&queue);
}