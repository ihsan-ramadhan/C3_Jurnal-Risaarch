/*
 * File        : fitur3.c
 * Deskripsi   : Modul untuk pencarian Jurnal berdasarkan nama penulis dan pengelolaan daftar hasil pencarian.
 *               Menyediakan fungsi untuk inisialisasi linked list, pembuatan node, penyisipan data,
 *               pencetakan hasil pencarian dalam format tabel, pembersihan linked list, dan pencarian
 *               Jurnal berdasarkan kata kunci penulis dengan batasan jumlah hasil maksimum.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fitur3.h"

// Inisialisasi single linked list untuk menyimpan hasil pencarian berdasarkan penulis
void list_init(AuthorSLL *list) {
    list->head = NULL;
    list->size = 0;
}

// Membuat node baru untuk single linked list dengan data hasil pencarian
AuthorNode *create_node(JournalsData data) {
    AuthorNode *newNode = (AuthorNode *)malloc(sizeof(AuthorNode));
    if (newNode == NULL) {
        printf("Gagal alokasi memori untuk AuthorNode!\n");
        return NULL;
    }
    strncpy(newNode->data.title, data.title, MAX_STRING - 1);
    newNode->data.title[MAX_STRING - 1] = '\0';
    strncpy(newNode->data.doiUrl, data.doiUrl, MAX_STRING - 1);
    newNode->data.doiUrl[MAX_STRING - 1] = '\0';
    strncpy(newNode->data.authors, data.authors, MAX_STRING - 1);
    newNode->data.authors[MAX_STRING - 30] = '\0';
    newNode->next = NULL;
    return newNode;
}

// Menyisipkan data hasil pencarian di akhir single linked list dengan batasan jumlah maksimum
void insert_last(AuthorSLL *list, JournalsData data) {
    if (list->size >= MAX_RESULTS) {
        return;
    }

    AuthorNode *newNode = create_node(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        AuthorNode *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void user_input(char *output, int max_len, AuthorSLL *searchResults, DoubleLinkedList *data) {
    while (1) {
        printf("Masukkan nama Author yang ingin dicari secara spesifik (Contoh: Isaac Newton): ");
        fgets(output, max_len, stdin);
        output[strcspn(output, "\n")] = '\0';

        if (strlen(output) == 0) {
            printf("Input tidak boleh kosong.\n\n");
            continue;
        }

        int valid = 1;
        for (int i = 0; output[i]; i++) {
            if (!isalpha(output[i]) && !isspace(output[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Input tidak valid. Jangan masukkan angka atau simbol, hanya huruf dan spasi saja.\n\n");
            continue;
        }

        search_by_author(data, searchResults, output);

        if (searchResults->size == 0) {
            printf("Author \"%s\" tidak ditemukan.\n\n", output);
            continue;
        }

        break;
    }
}


// Mencetak isi single linked list dalam format tabel
void print_list(AuthorSLL *list, const char *authorKeyword) {

    // Mencetak header dengan nama penulis yang dicari
    printf("\nJurnal dari Author: %s\n", authorKeyword);

     AuthorNode *current = list->head;
    int index = 1;
    while (current) {
        printf("%d. Title   : %s\n", index, current->data.title);
        printf("   DOI URL : %s\n", strlen(current->data.doiUrl) > 0 ? current->data.doiUrl : "-");
        printf("   Authors : %s\n\n", current->data.authors); 

        current = current->next;
        index++;
    }

    printf("\nTotal Jurnal yang ditampilkan: %d\n", list->size);
}

// Membebaskan memori yang digunakan oleh single linked list
void free_list(AuthorSLL *list) {
    AuthorNode *current = list->head;
    while (current != NULL) {
        AuthorNode *temp = current;
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

// Mencari Jurnal berdasarkan kata kunci penulis dan menyimpan hasilnya dalam single linked list
void search_by_author(DoubleLinkedList *sourceList, AuthorSLL *resultList, const char *authorKeyword) {
    if (!sourceList || !resultList || !authorKeyword) return;

    list_init(resultList); // Inisialisasi daftar hasil

    Node *current = sourceList->head;
    while (current != NULL && resultList->size < MAX_RESULTS) {
        if (stristr_custom(current->data.authors, authorKeyword)) {
            JournalsData result;
            strncpy(result.title, current->data.title, MAX_STRING - 1);
            result.title[MAX_STRING - 1] = '\0';
            strncpy(result.doiUrl, current->data.doiUrl, MAX_STRING - 1);
            result.doiUrl[MAX_STRING - 1] = '\0';
            strncpy(result.authors, current->data.authors, MAX_STRING - 1);
            result.authors[MAX_STRING - 1] = '\0';
            insert_last(resultList, result);
        }
        current = current->next;
    }
}