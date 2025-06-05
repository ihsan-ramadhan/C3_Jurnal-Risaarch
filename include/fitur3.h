/*
 * File        : fitur3.h
 * Deskripsi   : Header file untuk modul pencarian jurnal berdasarkan nama penulis.
 *               Mendefinisikan struktur data untuk hasil pencarian, single linked list,
 *               serta deklarasi fungsi untuk inisialisasi, pembuatan node, penyisipan data,
 *               pencetakan hasil, pembersihan single linked list, dan pencarian jurnal
 *               berdasarkan kata kunci penulis dengan batasan jumlah hasil maksimum.
 */

#ifndef FITUR3_H
#define FITUR3_H

#include "dll.h" // Mengasumsikan dll.h berisi struktur Journal dan DoubleLinkedList

#define MAX_STR 256
#define MAX_RESULTS 10

// Struktur data untuk menyimpan hasil pencarian jurnal
typedef struct {
    char title[MAX_STR];
    char doiUrl[MAX_STR];
    char authors[MAX_STR];
} SearchResult3;

// Struktur node untuk single linked list hasil pencarian
typedef struct SLLNode3 {
    SearchResult3 data;
    struct SLLNode3* next;
} SLLNode3;

// Struktur single linked list untuk hasil pencarian
typedef struct {
    SLLNode3* head;
    int size;
} SingleLinkedList3;

// Deklarasi fungsi untuk modul fitur3
void sll3_init(SingleLinkedList3* list); // Inisialisasi single linked list
SLLNode3* sll3_createNode(SearchResult3 data); // Membuat node baru untuk single linked list
void sll3_insertLast(SingleLinkedList3* list, SearchResult3 data); // Menyisipkan data di akhir single linked list
void sll3_printList(SingleLinkedList3* list); // Mencetak isi single linked list dalam format tabel
void sll3_freeList(SingleLinkedList3* list); // Membebaskan memori single linked list
void search_journals_by_author(DoubleLinkedList* sourceList, SingleLinkedList3* resultList, const char* authorKeyword); // Mencari jurnal berdasarkan kata kunci penulis

#endif // FITUR3_H