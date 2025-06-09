/*
 * File        : main.c
 * Deskripsi   : Program utama untuk aplikasi "Jurnal Risaarch" - Sistem pencarian dan pengelolaan jurnal berbasis CSV
 *               menggunakan struktur data modular (Double Linked List, Single Linked List).
 *               Program ini mendukung pencarian jurnal berdasarkan Field of Study, Tahun, Author, dan Kata Kunci.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"       // Modul struktur Double Linked List untuk data jurnal utama
#include "jurnal.h"    // Modul parsing file CSV dan definisi struktur Jurnal
#include "fitur2.h"    // Fitur pencarian jurnal berdasarkan rentang tahun
#include "fitur3.h"    // Fitur pencarian jurnal berdasarkan Author
#include "fitur4.h"    // Fitur pencarian jurnal berdasarkan Kata Kunci di judul
#include "fitur1.h"    // Fitur pencarian berdasarkan Field of Study
#include "fitur5.h"    // Menampilkan daftar jurnal lengkap

int main()
{
    DoubleLinkedList list;            // Menyimpan semua data jurnal yang telah di-parse dari CSV
    SingleLinkedList searchResults;   // Menyimpan hasil pencarian fitur kata kunci (fitur 4)
    dll_init(&list);                  // Inisialisasi DLL
    sll_init(&searchResults);        // Inisialisasi SLL

    // Load dan parsing file CSV ke struktur double linked list
    parse_csv(".\\assets\\data_tubes.csv", &list);

    int pilihan;
    char keyword[MAX_STR];

    while (1)
    {
        // Tampilan menu utama
        printf("\n========================================================== Menu Utama ===========================================================\n");
        printf("======================================================== Jurnal Risaarch ========================================================\n");
        printf("1. Mencari Jurnal Berdasarkan Field of Study\n");
        printf("2. Mencari Jurnal Berdasarkan Rentang Tahun\n");
        printf("3. Mencari Jurnal Berdasarkan Author\n");
        printf("4. Mencari Jurnal Berdasarkan Kata Kunci\n");
        printf("5. Menampilkan Daftar Jurnal\n");
        printf("6. Exit\n\n");
        printf("Masukkan pilihanmu: ");

        if (scanf("%d", &pilihan) != 1) {
            printf("\nPilihan invalid! Silahkan masukkan angka.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar(); // Menangkap newline setelah angka

        if (pilihan < 1 || pilihan > 6) {
            printf("\nPilihan invalid! Silahkan pilih angka antara 1 dan 6.\n");
            continue;
        }

        switch (pilihan)
        {
        case 1:
            // Fitur 1: Pencarian berdasarkan Field of Study
            tampilkanFieldStatic2Kolom();  // Menampilkan list Field yang tersedia
            printf("\nMasukkan Field of Study: ");
            fgets(keyword, MAX_STR, stdin);
            keyword[strcspn(keyword, "\n")] = '\0'; // Menghapus newline
            fitur1_searchField(&list, keyword);
            break;

        case 2:
        {
            // Fitur 2: Pencarian berdasarkan Rentang Tahun
            int tahunAwal, tahunAkhir;
            printf("\nMasukkan tahun awal: ");
            if (scanf("%d", &tahunAwal) != 1) {
                printf("Input tahun invalid! Silahkan masukkan angka.\n");
                while (getchar() != '\n');
                break;
            }
            printf("Masukkan tahun akhir: ");
            if (scanf("%d", &tahunAkhir) != 1) {
                printf("Input tahun invalid! Silahkan masukkan angka.\n");
                while (getchar() != '\n');
                break;
            }
            getchar(); // Tangkap newline
            filter_by_year_range(&list, tahunAwal, tahunAkhir);
            break;
        }

        case 3:
        {
            // Fitur 3: Pencarian berdasarkan Author
            SingleLinkedList3 searchResults3; // Struktur hasil pencarian fitur 3
            sll3_init(&searchResults3);
            printf("\nMasukkan nama author yang ingin dicari secara spesifik: ");
            fgets(keyword, MAX_STR, stdin);
            keyword[strcspn(keyword, "\n")] = '\0';
            search_journals_by_author(&list, &searchResults3, keyword);
            sll3_printList(&searchResults3, keyword);
            sll3_freeList(&searchResults3);
            break;
        }

        case 4:
            // Fitur 4: Pencarian berdasarkan Kata Kunci di Judul
            printf("\nMasukkan kata kunci yang ingin dicari di Title: ");
            fgets(keyword, MAX_STR, stdin);
            keyword[strcspn(keyword, "\n")] = '\0';
            search_journals(&list, &searchResults, keyword);
            sll_printList(&searchResults);
            sll_freeList(&searchResults);
            break;

        case 5:
            // Fitur 5: Menampilkan semua jurnal
            printf("\n--------------------------------------------------------- Daftar Jurnal ---------------------------------------------------------\n");
            display_journals(&list);
            break;

        case 6:
            // Keluar program
            printf("\nTerima Kasih...\n");
            printf("Anda keluar dari aplikasi...\n");
            dll_freeList(&list);
            sll_freeList(&searchResults);
            return 0;
        }
    }

    // Free memory (tidak akan pernah dijalankan karena return 0 di atas, tapi disimpan untuk jaga-jaga)
    dll_freeList(&list);
    sll_freeList(&searchResults);
    return 0;
}
