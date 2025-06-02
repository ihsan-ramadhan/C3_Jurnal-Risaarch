#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"
#include "jurnal.h"
#include "fitur1.h"

int main() {
    DoubleLinkedList list;
    dll_init(&list);

    parse_csv(".\\Jurnal-Risaarch\\assets\\data_tubes_tes.csv", &list);

    int pilihan;
    char keyword[MAX_STR];

    while (pilihan != 2) {

    }

    dll_freeList(&list);

    return 0;
}