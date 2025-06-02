#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"
#include "jurnal.h"
#include "fitur4.h"
#include "fitur1.h"

int main() {
    DoubleLinkedList list;
    SingleLinkedList searchResults;
    dll_init(&list);
    sll_init(&searchResults);

    parse_csv(".\\assets\\data_tubes.csv", &list);

    int pilihan;
    char keyword[MAX_STR];

    while (pilihan != 6) {
        printf("\n=== Jurnal Risaarch ===\n");
        printf("1. Cari Jurnal Berdasarkan Field of Study\n");
        printf("4. Mencari Jurnal Berdasarkan Kata Kunci\n");
        printf("6. Exit\n");
        printf("Masukkan pilihanmu: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
                printf("Masukkan Field of Study: ");
                fgets(keyword, MAX_STR, stdin);
                keyword[strcspn(keyword, "\n")] = '\0';
                fitur1_searchField(&list, keyword); // panggil fungsi dari fitur1.c
                break;
            case 4:
                printf("Masukkan kata kunci yang ingin dicari di Title: ");
                fgets(keyword, MAX_STR, stdin);
                keyword[strcspn(keyword, "\n")] = '\0';
                search_journals(&list, &searchResults, keyword);
                sll_printList(&searchResults);
                sll_freeList(&searchResults);
                break;
            case 6:
                printf("Keluar dari program...\n");
                break;
            default:
                printf("Pilihan invalid!\n");
        }
    }

    dll_freeList(&list);
    sll_freeList(&searchResults);

    return 0;
}