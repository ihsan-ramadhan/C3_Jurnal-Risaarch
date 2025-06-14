/*
 * File        : fitur5.c
 * Deskripsi   : Modul untuk menampilkan data jurnal dengan paginasi.
 *               Menyediakan fungsi untuk mencetak header halaman, mencetak entri jurnal,
 *               menampilkan halaman tertentu, dan navigasi halaman dengan input pengguna.
 */

#include <stdio.h>
#include <string.h>
#include "fitur5.h"
#include "dll.h"

#define PAGE_SIZE 15

// Cetak header halaman dengan nomor halaman dan total entri
void print_page_header(int page, int total) 
{
    printf("Page %d\n", page + 1);
    printf("[Total: %d entri]\n\n\n", total);
}

// Cetak satu entri jurnal berdasarkan node dan index
void print_journal_entry(Node* node, int index) 
{
    printf("%d. %s\n", index + 1, node->data.title);
    printf("    %d - %s - %s\n", node->data.year, node->data.authors, node->data.fieldOfStudy);
    printf("    %s\n", strlen(node->data.doiUrl) ? node->data.doiUrl : "-");
    printf("\n\n");    
}

// Cetak halaman jurnal berdasarkan nomor halaman
void display_page(DoubleLinkedList* list, int page) 
{
    int start = page * PAGE_SIZE;
    int end = start + PAGE_SIZE;
    if (start >= list->size) 
    {
        printf("Tidak ada data pada halaman ini.\n");
        return;
    }

    if (end > list->size) end = list->size;

    print_page_header(page, list->size);

    Node* current = list->head;
    int index = 0;

    // Navigasi ke awal halaman
    while (current && index < start) 
    {
        current = current->next;
        index++;
    }

    // Cetak jurnal untuk halaman saat ini
    while (current && index < end) 
    {
        print_journal_entry(current, index);
        current = current->next;
        index++;
    }
}

// Fungsi utama untuk menampilkan jurnal dengan navigasi halaman (next, prev, quit)
void display_journals(DoubleLinkedList* list) 
{
    if (!list || list->size == 0) 
    {
        printf("Tidak ada data jurnal.\n");
        return;
    }

    int page = 0;
    char command;
    char input[10];
    do 
    {
        display_page(list, page);
        printf("\nGunakan 'n' untuk next page, 'p' untuk prev page, 'q' untuk quit.\n");
        while (1)
        {
            printf("Perintah: ");
            if (fgets(input, sizeof(input), stdin) != NULL)
            {
                if (sscanf(input, " %c", &command) == 1) 
                {
                    if (command == 'n' || command == 'p' || command == 'q') 
                    {
                        break;
                    } 
                }
            }
            printf("Perintah tidak valid. Masukan 'n', 'p', atau 'q'.\n\n");
            
        }

        if (command == 'n' && (page + 1) * PAGE_SIZE < list->size) 
        {
            page++;
        } 
        else if (command == 'p' && page > 0) 
        {
            page--;
        }
    } 
    while (command != 'q');
}
