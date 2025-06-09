/*
 * File        : fitur3.c
 * Deskripsi   : Modul untuk pencarian jurnal berdasarkan nama penulis dan pengelolaan daftar hasil pencarian.
 *               Menyediakan fungsi untuk inisialisasi linked list, pembuatan node, penyisipan data,
 *               pencetakan hasil pencarian dalam format tabel, pembersihan linked list, dan pencarian
 *               jurnal berdasarkan kata kunci penulis dengan batasan jumlah hasil maksimum.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fitur3.h"

// Inisialisasi single linked list untuk menyimpan hasil pencarian berdasarkan penulis
void sll3_init(SingleLinkedList3 *list) {
    list->head = NULL;
    list->size = 0;
}

// Membuat node baru untuk single linked list dengan data hasil pencarian
SLLNode3 *sll3_createNode(SearchResult3 data) {
    SLLNode3 *newNode = (SLLNode3 *)malloc(sizeof(SLLNode3));
    if (newNode == NULL) {
        printf("Gagal alokasi memori untuk SLLNode3!\n");
        return NULL;
    }
    strncpy(newNode->data.title, data.title, MAX_STR - 1);
    newNode->data.title[MAX_STR - 1] = '\0';
    strncpy(newNode->data.doiUrl, data.doiUrl, MAX_STR - 1);
    newNode->data.doiUrl[MAX_STR - 1] = '\0';
    strncpy(newNode->data.authors, data.authors, MAX_STR - 1);
    newNode->data.authors[MAX_STR - 1] = '\0';
    newNode->next = NULL;
    return newNode;
}

// Menyisipkan data hasil pencarian di akhir single linked list dengan batasan jumlah maksimum
void sll3_insertLast(SingleLinkedList3 *list, SearchResult3 data) {
    if (list->size >= MAX_RESULTS) {
        return;
    }

    SLLNode3 *newNode = sll3_createNode(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        SLLNode3 *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// Mencetak isi single linked list dalam format tabel
void sll3_printList(SingleLinkedList3 *list, const char *authorKeyword) {
    if (!list->head) {
        printf("Author tidak ditemukan.\n");
        return;
    }

    // Mencetak header dengan nama penulis yang dicari
    printf("\nPaper dari Author: %s\n", authorKeyword);

     SLLNode3 *current = list->head;
    int index = 1;
    while (current) {
        printf("%d. Title   : %s\n", index, current->data.title);
        printf("   DOI URL : %s\n", strlen(current->data.doiUrl) > 0 ? current->data.doiUrl : "-");
        printf("   Authors : %s\n\n", current->data.authors); 

        current = current->next;
        index++;
    }

    printf("\nTotal jurnal yang ditampilkan: %d\n", list->size);
}

// Membebaskan memori yang digunakan oleh single linked list
void sll3_freeList(SingleLinkedList3 *list) {
    SLLNode3 *current = list->head;
    while (current != NULL) {
        SLLNode3 *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}

// Mencari substring secara case-insensitive dalam string
static int stristr_custom(const char *str, const char *substr) {
    if (!str || !substr) return 0;

    int len_str = strlen(str);
    int len_substr = strlen(substr);
    if (len_substr > len_str) return 0;

    char *lower_str = (char *)malloc(len_str + 1);
    char *lower_substr = (char *)malloc(len_substr + 1);
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

// Mencari jurnal berdasarkan kata kunci penulis dan menyimpan hasilnya dalam single linked list
void search_journals_by_author(DoubleLinkedList *sourceList, SingleLinkedList3 *resultList, const char *authorKeyword) {
    if (!sourceList || !resultList || !authorKeyword) return;

    sll3_init(resultList); // Inisialisasi daftar hasil

    Node *current = sourceList->head;
    while (current != NULL && resultList->size < MAX_RESULTS) {
        if (stristr_custom(current->data.authors, authorKeyword)) {
            SearchResult3 result;
            strncpy(result.title, current->data.title, MAX_STR - 1);
            result.title[MAX_STR - 1] = '\0';
            strncpy(result.doiUrl, current->data.doiUrl, MAX_STR - 1);
            result.doiUrl[MAX_STR - 1] = '\0';
            strncpy(result.authors, current->data.authors, MAX_STR - 1);
            result.authors[MAX_STR - 1] = '\0';
            sll3_insertLast(resultList, result);
        }
        current = current->next;
    }
}