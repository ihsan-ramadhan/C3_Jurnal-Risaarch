#ifndef FITUR5_H
#define FITUR5_H

#include "dll.h"

void print_page_header(int page, int total);
void print_journal_entry(Node* node, int index);
void display_page(DoubleLinkedList* list, int page);
void display_journals(DoubleLinkedList* list);

#endif