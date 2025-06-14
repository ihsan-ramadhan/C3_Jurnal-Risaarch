/*
 * File        : fitur1.h
 * Deskripsi   : Header file untuk modul pencarian jurnal berdasarkan Field of Study.
 *               Mendefinisikan struktur data untuk single linked list hasil pencarian,
 *               konstanta untuk batas antrian, dan deklarasi fungsi untuk perbandingan string,
 *               pembangunan dan pengelolaan single linked list, serta pencarian dan tampilan
 *               Field of Study dalam format tabel dua kolom.
 */

#ifndef FITUR1_H
#define FITUR1_H

#include "dll.h"
#include "queue.h"

#define MAX_QUEUE 10

// Struktur node untuk single linked list hasil tampilan
typedef struct SLLNode_f1 {
    char title[256];
    char url[256];
    struct SLLNode_f1 *next;
} SLLNode_f1;

// Global pointer untuk navigasi pada double linked list
extern Node *page;

// Deklarasi fungsi untuk modul fitur1
int str_casecmp(const char *a, const char *b); // Membandingkan string tanpa case-sensitive
void sll_buildFromQueue(Queue *q, SLLNode_f1 **head); // Membangun single linked list dari antrian
void sll_show(SLLNode_f1 *head); // Menampilkan isi single linked list
void sll_clear(SLLNode_f1 **head); // Membebaskan memori single linked list
void fitur1_searchField(DoubleLinkedList *dll, const char *field); // Mencari jurnal berdasarkan Field of Study
void tampilkanFieldStatic2Kolom(); // Menampilkan daftar Field of Study dalam format tabel dua kolom
int cekinputfield (const char *input);

#endif