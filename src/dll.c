/*
 * File        : dll.c
 * Deskripsi   : Modul untuk pengelolaan double linked list yang menyimpan keseluruhan data jurnal.
 *               Menyediakan fungsi untuk inisialisasi double linked list, pembuatan node baru,
 *               penyisipan data di akhir list, dan pembersihan seluruh list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"

// Inisialisasi double linked list untuk menyimpan data jurnal
void dll_init(DoubleLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Membuat node baru untuk double linked list dengan data jurnal
Node* dll_createNode(Journal data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(newNode->data.title, data.title);
    strcpy(newNode->data.authors, data.authors);
    strcpy(newNode->data.fieldOfStudy, data.fieldOfStudy);
    newNode->data.year = data.year;
    strcpy(newNode->data.doiUrl, data.doiUrl);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Menyisipkan data jurnal di akhir double linked list
void dll_insertLast(DoubleLinkedList* list, Journal data) {
    Node* newNode = dll_createNode(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

// Membebaskan memori yang digunakan oleh double linked list
void dll_freeList(DoubleLinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}