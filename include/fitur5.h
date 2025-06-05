/*
 * File        : fitur5.h
 * Deskripsi   : Header file untuk modul penampilan data jurnal dengan paginasi.
 *               Mendefinisikan deklarasi fungsi untuk mencetak header halaman,
 *               mencetak entri jurnal, menampilkan halaman tertentu, dan
 *               mengelola navigasi halaman untuk menampilkan seluruh jurnal.
 */

#ifndef FITUR5_H
#define FITUR5_H

#include "dll.h"

// Deklarasi fungsi untuk modul fitur5
void print_page_header(int page, int total); // Mencetak header halaman dengan nomor halaman dan total entri
void print_journal_entry(Node* node, int index); // Mencetak satu entri jurnal berdasarkan node dan indeks
void display_page(DoubleLinkedList* list, int page); // Menampilkan halaman jurnal berdasarkan nomor halaman
void display_journals(DoubleLinkedList* list); // Menampilkan jurnal dengan navigasi halaman (next, prev, quit)

#endif