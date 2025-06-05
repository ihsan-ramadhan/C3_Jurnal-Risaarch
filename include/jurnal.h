#ifndef JURNAL_H
#define JURNAL_H

#include "dll.h"

void parse_csv(const char* filename, DoubleLinkedList* list);

#endif/*
 * File        : jurnal.h
 * Deskripsi   : Header file untuk modul pengelolaan data jurnal dari file CSV.
 *               Mendefinisikan deklarasi fungsi untuk mem-parsing data jurnal dari file CSV
 *               dan menyimpannya ke dalam double linked list.
 */

#ifndef JURNAL_H
#define JURNAL_H

#include "dll.h"

// Deklarasi fungsi untuk modul jurnal
void parse_csv(const char* filename, DoubleLinkedList* list); // Mem-parsing file CSV dan menyimpan data jurnal ke double linked list

#endif