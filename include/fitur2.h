
#ifndef FITUR2_H
#define FITUR2_H

#include "dll.h"

#define MAX_RESULTS2 3000
#define PAGE_SIZE 25

typedef struct BSTNode {
    int year;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// BST 
BSTNode* insert_bst(BSTNode* root, int year);
void free_bst(BSTNode* root);
BSTNode* create_bst_from_years(DoubleLinkedList* list, int startYear, int endYear);

// output
void print_journal_table_header(int* titleWidth, int* yearWidth, int* doiWidth);
void print_journal_row(const char* title, int year, const char* doiUrl, int titleWidth, int yearWidth, int doiWidth);
void print_table_page(int page);

// filter
void search_by_year(DoubleLinkedList* list, int year);
void filter_by_year_range(DoubleLinkedList* list, int startYear, int endYear);
int is_valid_year_range(int startYear, int endYear);

#endif
