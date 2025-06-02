#ifndef FITUR2_H
#define FITUR2_H

#include "dll.h"

typedef struct BSTNode {
    int year;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* insert_bst(BSTNode* root, int year);
void inorder_traversal(BSTNode* root, DoubleLinkedList* list);
void filter_by_year_range(DoubleLinkedList* list, int startYear, int endYear);
void free_bst(BSTNode* root);

#endif