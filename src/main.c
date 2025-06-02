#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"
#include "jurnal.h"
#include "fitur1.h"

int main() {
    DoubleLinkedList list;
    SingleLinkedList searchResults;
    dll_init(&list);
    sll_init(&searchResults);

    parse_csv(".\\assets\\data_tubes_tes.csv", &list);

    int pilihan;
    char keyword[MAX_STR];

    while (pilihan != 2) {
        printf("\n=== Jurnal Risaarch ===\n");
        printf("1. Mencari Jurnal Berdasarkan Kata Kunci\n");
        printf("2. Exit\n");
        printf("Masukkan pilihanmu: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
                printf("Masukkan kata kunci yang ingin dicari di Title: ");
                fgets(keyword, MAX_STR, stdin);
                keyword[strcspn(keyword, "\n")] = '\0';
                search_journals(&list, &searchResults, keyword);
                sll_printList(&searchResults);
                sll_freeList(&searchResults);
                break;
            case 2:
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