#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"
#include "jurnal.h"
#include "fitur2.h"
#include "fitur3.h"
#include "fitur4.h"
#include "fitur1.h"
#include "fitur5.h"

int main() {
    DoubleLinkedList list;
    SingleLinkedList searchResults;
    dll_init(&list);
    sll_init(&searchResults);
    

    parse_csv(".\\assets\\data_tubes.csv", &list);

    int pilihan;
    char keyword[MAX_STR];

    while (pilihan != 6) {
        printf("\n\n\n\n======================================================== Jurnal Risaarch ========================================================\n");
        printf("                                                            Menu Utama\n\n");
        printf("1. Mencari Jurnal Berdasarkan Field of Study\n");
        printf("2. Mencari Jurnal Berdasarkan Rentang Tahun\n");
        printf("3. Mencari Jurnal Berdasarkan Author\n");
        printf("4. Mencari Jurnal Berdasarkan Kata Kunci\n");
        printf("5. Menampilkan Daftar Jurnal\n");
        printf("6. Exit\n\n");
        printf("Masukkan pilihanmu: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
                printf("\nMasukkan Field of Study: ");
                fgets(keyword, MAX_STR, stdin);
                keyword[strcspn(keyword, "\n")] = '\0';
                fitur1_searchField(&list, keyword); // panggil fungsi dari fitur1.c
                break;
            case 2: {
                int tahunAwal, tahunAkhir;
                printf("\nMasukkan tahun awal: ");
                scanf("%d", &tahunAwal);
                printf("Masukkan tahun akhir: ");
                scanf("%d", &tahunAkhir);
                getchar(); // Clear newline
                filter_by_year_range(&list, tahunAwal, tahunAkhir);
                break;
            }
            case 3:
                SingleLinkedList3 searchResults3;
                sll3_init(&searchResults3);
                printf("\nMasukkan nama author yang ingin dicari secara spesifik: ");
                fgets(keyword, MAX_STR, stdin);
                keyword[strcspn(keyword, "\n")] = '\0';
                search_journals_by_author(&list, &searchResults3, keyword);
                sll3_printList(&searchResults3);
                sll3_freeList(&searchResults3);
                break;
            case 4:
                printf("\nMasukkan kata kunci yang ingin dicari di Title: ");
                fgets(keyword, MAX_STR, stdin);
                keyword[strcspn(keyword, "\n")] = '\0';
                search_journals(&list, &searchResults, keyword);
                sll_printList(&searchResults);
                sll_freeList(&searchResults);
                break;
            case 5:
                printf("\n--------------------------------------------------------- Daftar Jurnal ---------------------------------------------------------\n");
                display_journals(&list);
                break;
            case 6:
                printf("\nTerima Kasih...\n");
                printf("Anda keluar dari aplikasi...\n");
                break;
            default:
                printf("Pilihan invalid! Silahkan pilih lagi\n");
        }
    }

    dll_freeList(&list);
    sll_freeList(&searchResults);

    return 0;
}