/*
 * File        : fitur2.c
 * Deskripsi   : Modul untuk pencarian jurnal berdasarkan tahun dan rentang tahun.
 *               Menyediakan fungsi untuk validasi input tahun, pencarian jurnal untuk tahun tunggal,
 *               pencarian berdasarkan rentang tahun menggunakan BST, serta navigasi hasil dengan paginasi.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fitur2.h"
#include "dll.h"

// Variabel global untuk menyimpan hasil pencarian jurnal
int hasil_count = 0;
Node* hasil[MAX_RESULTS2];

// Mengecek apakah startYear lebih kecil/sama dari endYear
int is_valid_year_range(int startYear, int endYear) {
    return startYear <= endYear;
}

// Menampilkan 1 baris jurnal dalam format tabel
void print_journal_row(const char* title, int year, const char* doiUrl, int titleWidth, int yearWidth, int doiWidth) {
    char shortTitle[titleWidth + 1];
    strncpy(shortTitle, title, titleWidth);
    shortTitle[titleWidth] = '\0';

    printf("%-*s | %-*d | %-*s\n", 
        titleWidth, shortTitle,
        yearWidth, year,
        doiWidth, strlen(doiUrl) ? doiUrl : "-");
}

// Menampilkan data hasil pencarian dalam bentuk halaman
void print_table_page(int page) {
    int start = page * PAGE_SIZE;
    int end = start + PAGE_SIZE;
    if (start >= hasil_count) {
        printf("Tidak ada data pada halaman ini.\n");
        return;
    }

    if (end > hasil_count) end = hasil_count;

    int titleWidth = 40, yearWidth = strlen("TAHUN"), doiWidth = strlen("DOI URL");

    printf("\nMenampilkan halaman %d:\n", page + 1);
    printf("%-4s | %-*s | %-*s | %-*s\n", "NO", titleWidth, "TITLE", yearWidth, "TAHUN", doiWidth, "DOI URL");
    for (int i = 0; i < 4; i++) printf("-");
    printf("-+-");
    for (int i = 0; i < titleWidth; i++) printf("-");
    printf("-+-");
    for (int i = 0; i < yearWidth; i++) printf("-");
    printf("-+-");
    for (int i = 0; i < doiWidth; i++) printf("-");
    printf("\n");

    for (int i = start; i < end; ++i) {
        printf("%-4d | ", i + 1);
        print_journal_row(hasil[i]->data.title, hasil[i]->data.year, hasil[i]->data.doiUrl, titleWidth, yearWidth, doiWidth);
    }

    printf("\n[Total: %d entri] Gunakan 'n' untuk next, 'p' untuk prev, 'q' untuk quit.\n", hasil_count);
}

// Fungsi navigasi halaman (paging) untuk hasil pencarian
void navigasi_halaman(const char* info) {
    int page = 0;
    char command;

    do {
        if (info) printf("\n%s - Halaman %d:\n", info, page + 1);
        print_table_page(page);
        printf("Perintah: ");
        scanf(" %c", &command);

        if (command == 'n' && (page + 1) * PAGE_SIZE < hasil_count) {
            page++;
        } else if (command == 'p' && page > 0) {
            page--;
        }
    } while (command != 'q');
}

// Insert dan hapus node BST berdasarkan tahun jurnal
BSTNode* insert_bst(BSTNode* root, int year) {
    if (!root) {
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->year = year;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (year < root->year)
        root->left = insert_bst(root->left, year);
    else if (year > root->year)
        root->right = insert_bst(root->right, year);
    return root;
}

void free_bst(BSTNode* root) {
    if (!root) return;
    free_bst(root->left);
    free_bst(root->right);
    free(root);
}

// Menelusuri seluruh DoubleLinkedList dan memasukkan tahun jurnal ke BST
BSTNode* create_bst_from_years(DoubleLinkedList* list, int startYear, int endYear) {
    BSTNode* root = NULL;
    Node* current = list->head;
    while (current) {
        int year = current->data.year;
        if (year >= startYear && year <= endYear) {
            root = insert_bst(root, year);
        }
        current = current->next;
    }
    return root;
}

// Pencarian jurnal jika 1 tahun
void search_by_year(DoubleLinkedList* list, int year) {
    if (!list || list->head == NULL) return;

    hasil_count = 0;
    Node* current = list->head;
    while (current && hasil_count < MAX_RESULTS2) {
        if (current->data.year == year) {
            hasil[hasil_count++] = current;
        }
        current = current->next;
    }

    if (hasil_count == 0) {
        printf("Tidak ditemukan jurnal untuk tahun %d\n", year);
        return;
    }

    char info[100];
    sprintf(info, "Hasil pencarian untuk tahun %d", year);
    navigasi_halaman(info);
}

// Melakukan inorder traversal pada BST
void kumpulkan_jurnal(BSTNode* root, DoubleLinkedList* list) {
    if (!root) return;

    kumpulkan_jurnal(root->left, list);
    Node* current = list->head;
    while (current) {
        if (current->data.year == root->year && hasil_count < MAX_RESULTS2) {
            hasil[hasil_count++] = current;
        }
        current = current->next;
    }
    kumpulkan_jurnal(root->right, list);
}

// Jika rentang
void filter_by_year_range(DoubleLinkedList* list, int startYear, int endYear) {
    if (!list) return;
    if (!is_valid_year_range(startYear, endYear)) {
        printf("Rentang tahun tidak valid!\n");
        return;
    }

    if (startYear == endYear) {
        search_by_year(list, startYear);
        return;
    }

    hasil_count = 0;
    BSTNode* root = create_bst_from_years(list, startYear, endYear);
    kumpulkan_jurnal(root, list);

    if (hasil_count == 0) {
    printf("Tidak ada data pada rentang tahun tersebut.\n");
    free_bst(root);
    return;
    }

    char info[100];
    sprintf(info, "Hasil pencarian untuk rentang tahun %d - %d", startYear, endYear);
    navigasi_halaman(info);

    free_bst(root);
}