#include <stdio.h>
#include <string.h>
#include "fitur5.h"
#include "dll.h"

#define PAGE_SIZE 15

// Fungsi untuk mencetak header halaman
void print_page_header(int page, int total) 
{
    printf("Page %d\n", page + 1);
    printf("[Total: %d entri]\n\n\n", total);
}

// Fungsi untuk mencetak satu entri jurnal
void print_journal_entry(Node* node, int index) 
{
    printf("%d. %s\n", index + 1, node->data.title);
    printf("    %d - %s - %s\n", node->data.year, node->data.authors, node->data.fieldOfStudy);
    printf("    %s\n", strlen(node->data.doiUrl) ? node->data.doiUrl : "-");
    printf("\n\n");    
    //printf("------------------------------------------------------------------------------------------------------------------------------------\n");
}

// Fungsi untuk mencetak halaman tertentu
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

// Fungsi utama untuk menampilkan jurnal dengan paginasi
void display_journals(DoubleLinkedList* list) 
{
    if (!list || list->size == 0) 
    {
        printf("Tidak ada data jurnal.\n");
        return;
    }

    int page = 0;
    char command;
    do 
    {
        display_page(list, page);
        printf("\nGunakan 'n' untuk next, 'p' untuk prev, 'q' untuk quit.\n");
        printf("Perintah: ");
        scanf(" %c", &command);

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