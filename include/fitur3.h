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

#include "dll.h"

#define MAX_STRING 150
#define MAX_RESULTS 10

// Struktur data untuk menyimpan hasil pencarian jurnal
typedef struct
{
    char title[MAX_STR];
    char doiUrl[MAX_STR];
    char authors[MAX_STR];
} JournalsData;

// Struktur node untuk single linked list hasil pencarian
typedef struct AuthorNode
{
    JournalsData data;
    struct AuthorNode *next;
} AuthorNode;

// Struktur single linked list untuk hasil pencarian
typedef struct
{
    AuthorNode *head;
    int size;
} AuthorSLL;

// Deklarasi fungsi untuk modul fitur3
void list_init(AuthorSLL *list);                                                                       // Inisialisasi single linked list
AuthorNode *create_node(JournalsData data);                                                               // Membuat node baru untuk single linked list
void insert_last(AuthorSLL *list, JournalsData data);                                                    // Menyisipkan data di akhir single linked list
void user_input(char *output, int max_len, AuthorSLL *searchResults, DoubleLinkedList *data);          // input pengguna dan error checking nya
void print_list(AuthorSLL *list, const char *authorKeyword);                                           // Mencetak isi single linked list dalam format tabel
void free_list(AuthorSLL *list);                                                                       // Membebaskan memori single linked list
void search_by_author(DoubleLinkedList *sourceList, AuthorSLL *resultList, const char *authorKeyword); // Mencari jurnal berdasarkan kata kunci penulis

#endif // FITUR3_H