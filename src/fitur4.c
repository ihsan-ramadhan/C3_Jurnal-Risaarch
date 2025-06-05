/*
 * File        : fitur4.c
 * Deskripsi   : Modul untuk pencarian jurnal berdasarkan kata kunci dan pengelolaan daftar hasil pencarian.
 *               Menyediakan fungsi untuk inisialisasi linked list, pembuatan node, penyisipan data,
 *               pencetakan hasil pencarian, pembersihan linked list, dan pencarian jurnal dengan kata kunci.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fitur4.h"

// Inisialisasi single linked list untuk menyimpan hasil pencarian
void sll_init(SingleLinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

// Membuat node baru untuk single linked list dengan data hasil pencarian
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

// Menyisipkan data hasil pencarian di akhir single linked list
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

// Mencetak semua entri dalam single linked list hasil pencarian
#define LABEL_WIDTH 10

void sll_printList(SingleLinkedList* list) {
    if (list->head == NULL) {
        printf("Tidak ada jurnal yang sesuai.\n");
        return;
    }

    printf("\n=== Hasil Pencarian Jurnal ===\n");
    SLLNode* current = list->head;
    int row_number = 1;
    while (current != NULL) {
        printf("%d.", row_number);
        printf("%-*s %s\n", LABEL_WIDTH, "Title  :", current->data.title);
        printf("  %-*s %s\n", LABEL_WIDTH, "DOI URL:", 
               strlen(current->data.doiUrl) ? current->data.doiUrl : "-");
        if (current->next != NULL) {
            printf("\n");
        }
        current = current->next;
        row_number++;
    }

    printf("\nTotal jurnal yang sesuai: %d\n", list->size);
}

// Membebaskan memori yang digunakan oleh single linked list
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

// Mencari substring secara case-insensitive dalam string
static int stristr(const char* str, const char* substr) {
    if (!str || !substr) return 0;

    int len_str = strlen(str);
    int len_substr = strlen(substr);
    if (len_substr > len_str || len_substr == 0) return 0;

    for (int i = 0; i <= len_str - len_substr; i++) {
        int j;
        for (j = 0; j < len_substr; j++) {
            if (tolower(str[i + j]) != tolower(substr[j])) {
                break;
            }
        }
        if (j == len_substr) return 1; // Substring ditemukan
    }
    return 0;
}

// Mencari jurnal berdasarkan kata kunci dan menyimpan hasilnya dalam single linked list
void search_journals(DoubleLinkedList* sourceList, SingleLinkedList* resultList, const char* keyword) {
    if (!sourceList || !resultList || !keyword) return;

    sll_init(resultList);
    Queue queue;
    queue_init(&queue);

    Node* current = sourceList->head;
    while (current != NULL) {
        if (stristr(current->data.title, keyword)) {
            SearchResult* result = (SearchResult*)malloc(sizeof(SearchResult));
            if (result == NULL) {
                printf("Gagal alokasi memori untuk SearchResult!\n");
                continue;
            }
            strncpy(result->title, current->data.title, MAX_STR - 1);
            result->title[MAX_STR - 1] = '\0';
            strncpy(result->doiUrl, current->data.doiUrl, MAX_STR - 1);
            result->doiUrl[MAX_STR - 1] = '\0';
            queue_enqueue(&queue, result);
        }
        current = current->next;
    }

    while (!queue_isEmpty(&queue)) {
        SearchResult* result = (SearchResult*)queue_dequeue(&queue);
        sll_insertLast(resultList, *result);
        free(result); // Bebaskan memori SearchResult
    }

    queue_free(&queue);
}