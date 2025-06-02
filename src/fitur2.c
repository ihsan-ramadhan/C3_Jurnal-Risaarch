#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fitur2.h"
#include "dll.h"

#define MAX_RESULTS 1000
#define PAGE_SIZE 25

int hasil_count = 0;
Node* hasil[MAX_RESULTS];

void print_journal_table_header(int* titleWidth, int* yearWidth, int* doiWidth) {
    *titleWidth = 40;
    *yearWidth = strlen("TAHUN");
    *doiWidth = strlen("DOI URL");

    // Print header
    printf("%-*s | %-*s | %-*s\n", *titleWidth, "TITLE", *yearWidth, "TAHUN", *doiWidth, "DOI URL");

    // Print separator
    for (int i = 0; i < *titleWidth; i++) printf("-");
    printf("-+-");
    for (int i = 0; i < *yearWidth; i++) printf("-");
    printf("-+-");
    for (int i = 0; i < *doiWidth; i++) printf("-");
    printf("\n");
}

void print_journal_row(const char* title, int year, const char* doiUrl, int titleWidth, int yearWidth, int doiWidth) {
    char shortTitle[titleWidth + 1];
    strncpy(shortTitle, title, titleWidth);
    shortTitle[titleWidth] = '\0';

    printf("%-*s | %-*d | %-*s\n", 
        titleWidth, shortTitle,
        yearWidth, year,
        doiWidth, strlen(doiUrl) ? doiUrl : "-");
}

void search_and_print(DoubleLinkedList* list, int year) {
    Node* current = list->head;
    int titleWidth, yearWidth, doiWidth;
    int printed = 0;

    while (current) {
        if (current->data.year == year) {
            if (!printed) {
                print_journal_table_header(&titleWidth, &yearWidth, &doiWidth);
                printed = 1;
            }

            // update max doiWidth if necessary
            int len = strlen(current->data.doiUrl);
            if (len > doiWidth) doiWidth = len;
        }
        current = current->next;
    }

    if (!printed) return; // tidak ada data tahun ini

    current = list->head;
    while (current) {
        if (current->data.year == year) {
            print_journal_row(current->data.title, current->data.year, current->data.doiUrl, titleWidth, yearWidth, doiWidth);
        }
        current = current->next;
    }

    printf("\n");
}

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

void inorder_traversal(BSTNode* root, DoubleLinkedList* list) {
    if (!root) return;
    inorder_traversal(root->left, list);
    search_and_print(list, root->year);
    inorder_traversal(root->right, list);
}

void free_bst(BSTNode* root) {
    if (!root) return;
    free_bst(root->left);
    free_bst(root->right);
    free(root);
}

void kumpulkan_jurnal(BSTNode* root, DoubleLinkedList* list) {
    if (!root) return;
    kumpulkan_jurnal(root->left, list);  

    Node* current = list->head;
    while (current) {
        if (current->data.year == root->year) {
            if (hasil_count < MAX_RESULTS) {
                hasil[hasil_count++] = current;
            }
        }
        current = current->next;
    }

    kumpulkan_jurnal(root->right, list);
}

void tampilkan_halaman(int page) {
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

void filter_by_year_range(DoubleLinkedList* list, int startYear, int endYear) {
    if (!list || startYear > endYear) return;

    hasil_count = 0;

    BSTNode* root = NULL;
    Node* current = list->head;

    while (current) {
        int year = current->data.year;
        if (year >= startYear && year <= endYear) {
            root = insert_bst(root, year);
        }
        current = current->next;
    }

    kumpulkan_jurnal(root, list);

    if (hasil_count == 0) {
        printf("Tidak ada data pada rentang tahun tersebut.\n");
        free_bst(root);
        return;
    }

    int page = 0;
    char command;
    do {
        tampilkan_halaman(page);
        printf("Perintah: ");
        scanf(" %c", &command);
        if (command == 'n' && (page + 1) * PAGE_SIZE < hasil_count) {
            page++;
        } else if (command == 'p' && page > 0) {
            page--;
        }
    } while (command != 'q');

    free_bst(root);
}