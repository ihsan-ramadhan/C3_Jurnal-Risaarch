/*
 * File        : fitur4.h
 * Deskripsi   : Header file untuk modul pencarian jurnal berdasarkan kata kunci.
 *               Mendefinisikan struktur data untuk hasil pencarian, single linked list,
 *               serta deklarasi fungsi untuk inisialisasi, pembuatan node, penyisipan data,
 *               pencetakan hasil, pembersihan single linked list, dan pencarian jurnal
 *               berdasarkan kata kunci pada judul.
 */

#ifndef FITUR4_H
#define FITUR4_H

#include "dll.h"
#include "queue.h"

#define MAX_STR 256

// Struktur data untuk menyimpan hasil pencarian jurnal
typedef struct {
    char title[MAX_STR];
    char doiUrl[MAX_STR];
} SearchResult;

// Struktur node untuk single linked list hasil pencarian
typedef struct SLLNode {
    SearchResult data;
    struct SLLNode* next;
} SLLNode;

// Struktur single linked list untuk hasil pencarian
typedef struct {
    SLLNode* head;
    int size;
} SingleLinkedList;

// Deklarasi fungsi untuk modul fitur4
void sll_init(SingleLinkedList* list); // Inisialisasi single linked list
SLLNode* sll_createNode(SearchResult data); // Membuat node baru untuk single linked list
void sll_insertLast(SingleLinkedList* list, SearchResult data); // Menyisipkan data di akhir single linked list
void sll_printList(SingleLinkedList* list); // Mencetak isi single linked list
void sll_freeList(SingleLinkedList* list); // Membebaskan memori single linked list
void search_journals_by_keyword(DoubleLinkedList* sourceList, SingleLinkedList* resultList, const char* keyword); // Mencari jurnal berdasarkan kata kunci pada judul

#endif