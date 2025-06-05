/*
 * File        : jurnal.c
 * Deskripsi   : Modul untuk membaca dan mem-parsing file CSV yang berisi data jurnal.
 *               Setiap baris data akan dimasukkan ke dalam Double Linked List sebagai elemen Journal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jurnal.h"
#include "dll.h"

// Menghapus whitespace (spasi, tab, newline) di awal dan akhir string
static char* trim(char* str) {
    char* end;

    // Hilangkan whitespace di awal
    while (*str == ' ' || *str == '\t') str++;
    if (*str == 0) return str; // String kosong

    // Hilangkan whitespace di akhir
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) end--;
    *(end + 1) = 0;

    return str;
}

// Membaca file CSV dan memasukkan datanya ke DoubleLinkedList
void parse_csv(const char* filename, DoubleLinkedList* list) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error membuka file %s\n", filename);
        return;
    }

    char line[1024];

    // Lewati baris pertama (header CSV)
    if (!fgets(line, sizeof(line), file)) {
        fclose(file);
        return;
    }

    // Baca setiap baris data
    while (fgets(line, sizeof(line), file)) {
        Journal journal = {0}; // Buffer untuk menyimpan data jurnal sementara
        char* ptr = line;
        char* token;
        int field = 0;
        int in_quotes = 0;
        char temp[MAX_STR] = {0}; // Menyimpan satu token data

        // Parsing manual satu baris CSV
        while (*ptr) {
            if (*ptr == '"') {
                in_quotes = !in_quotes;
                ptr++;
                continue;
            }

            if (*ptr == ',' && !in_quotes) {
                *ptr = '\0';
                token = trim(temp);
                switch (field) {
                    case 0: strncpy(journal.title, token, MAX_STR - 1); break;
                    case 1: strncpy(journal.authors, token, MAX_STR - 1); break;
                    case 2: strncpy(journal.fieldOfStudy, token, MAX_STR - 1); break;
                    case 3: journal.year = atoi(token); break;
                    case 4: strncpy(journal.doiUrl, token, MAX_STR - 1); break;
                }
                field++;
                memset(temp, 0, sizeof(temp));
                ptr++;
            } else {
                strncat(temp, ptr, 1);
                ptr++;
            }
        }

        // Handle kolom terakhir (setelah koma terakhir)
        if (strlen(temp) > 0) {
            token = trim(temp);
            switch (field) {
                case 4: strncpy(journal.doiUrl, token, MAX_STR - 1); break;
            }
        }

        // Jika data valid, masukkan ke list
        if (strlen(journal.title) > 0) {
            dll_insertLast(list, journal);
        }
    }

    fclose(file);
}
