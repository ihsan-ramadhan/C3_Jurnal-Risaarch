/*
 * File        : dll.h
 * Deskripsi   : Header file untuk pengelolaan double linked list yang menyimpan semua data jurnal.
 *               Mendefinisikan struktur data Journal, Node, dan DoubleLinkedList, serta
 *               deklarasi fungsi untuk inisialisasi, pembuatan node, penyisipan data,
 *               dan pembersihan double linked list.
 */

#ifndef DLL_H
#define DLL_H

#define MAX_STR 256

// Struktur data untuk menyimpan informasi jurnal
typedef struct {
    char title[MAX_STR];
    char authors[MAX_STR];
    char fieldOfStudy[MAX_STR];
    int year;
    char doiUrl[MAX_STR];
} Journal;

// Struktur node untuk double linked list
typedef struct Node {
    Journal data;
    struct Node* prev;
    struct Node* next;
} Node;

// Struktur double linked list
typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoubleLinkedList;

// Deklarasi fungsi untuk pengelolaan double linked list
void dll_init(DoubleLinkedList* list);
Node* dll_createNode(Journal data);
void dll_insertLast(DoubleLinkedList* list, Journal data);
void dll_freeList(DoubleLinkedList* list);

#endif