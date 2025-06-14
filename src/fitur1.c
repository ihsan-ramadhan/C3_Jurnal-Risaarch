/*
 * File        : fitur1.c
 * Deskripsi   : Modul untuk pencarian jurnal berdasarkan Field of Study dengan paginasi.
 *               Menyediakan fungsi untuk perbandingan string tanpa case-sensitive, membangun
 *               single linked list dari antrian hasil pencarian, menampilkan hasil pencarian,
 *               membersihkan single linked list, mencari jurnal berdasarkan Field of Study
 *               dengan navigasi halaman, dan menampilkan daftar Field of Study dalam format tabel dua kolom.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fitur1.h"

Node *page = NULL; // Global pointer untuk navigasi

// Mengecek apakah field termasuk field valid
int cekinputfield(const char *input)
{
    const char *fields[] = {
        "Art", "Biology", "Business", "Chemistry", "Computer Science",
        "Economics", "Engineering", "Environmental Science", "Geography", "Geology",
        "History", "Materials Science", "Mathematics", "Medicine", "Philosophy",
        "Physics", "Political Science", "Psychology", "Sociology"};
    int jumlahField = sizeof(fields) / sizeof(fields[0]);

    for (int i = 0; i < jumlahField; i++)
    {
        if (str_casecmp(input, fields[i]) == 0)
        {
            return 1; // Valid
        }
    }
    return 0; // Tidak ditemukan
}

// Membandingkan dua string tanpa memperhatikan case-sensitive
int str_casecmp(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (tolower(*a) != tolower(*b))
            return tolower(*a) - tolower(*b);
        a++;
        b++;
    }
    return *a - *b;
}

// Membangun single linked list dari antrian hasil pencarian
void sll_buildFromQueue(Queue *q, SLLNode_f1 **head)
{
    *head = NULL;
    SLLNode_f1 *tail = NULL;

    while (!queue_isEmpty(q))
    {
        Node *curr = (Node *)queue_dequeue(q);
        SLLNode_f1 *newNode = (SLLNode_f1 *)malloc(sizeof(SLLNode_f1));
        strcpy(newNode->title, curr->data.title);
        strcpy(newNode->url, curr->data.doiUrl);
        newNode->next = NULL;

        if (!*head)
        {
            *head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
}

// Menampilkan isi single linked list hasil pencarian
void sll_show(SLLNode_f1 *head)
{
    int i = 1;
    while (head)
    {
        printf("%d. %s\n   URL: %s\n", i++, head->title, head->url);
        head = head->next;
    }
}

// Membebaskan memori yang digunakan oleh single linked list
void sll_clear(SLLNode_f1 **head)
{
    while (*head)
    {
        SLLNode_f1 *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Mencari jurnal berdasarkan Field of Study dengan navigasi halaman (hanya next dan quit)
void fitur1_searchField(DoubleLinkedList *dll, const char *field)
{
    // Cek apakah field hanya berisi angka
    int hanyaAngka = 1;
    for (int i = 0; field[i] != '\0'; i++)
    {
        if (!isdigit(field[i]))
        {
            hanyaAngka = 0;
            break;
        }
    }

    if (hanyaAngka)
    {
        printf("Masukkan nama Field of Study yang valid, bukan angka.\n");
        return;
    }

    // Cek apakah field termasuk dalam daftar field yang valid
    if (!cekinputfield(field))
    {
        printf("Field of Study '%s' tidak valid. Gunakan salah satu dari daftar berikut:\n", field);
        tampilkanFieldStatic2Kolom(); // Tampilkan ulang daftar field
        return;
    }

    page = dll->head;

    while (1)
    {
        Queue q;
        queue_init(&q);
        Node *curr = page;
        int found = 0;

        // Mengumpulkan hingga maksimum 10 data yang sesuai
        while (curr && q.size < MAX_QUEUE)
        {
            if (str_casecmp(curr->data.fieldOfStudy, field) == 0)
            {
                queue_enqueue(&q, curr);
                if (!found)
                    page = curr;
                found = 1;
            }
            curr = curr->next;
        }

        if (q.size == 0)
        {
            printf("Tidak ditemukan jurnal dengan Field of Study: %s\n", field);
            queue_free(&q);
            return;
        }

        // ... lanjutan tampilan dan navigasi page
    }
}

// Menampilkan daftar Field of Study dalam format tabel dua kolom
void tampilkanFieldStatic2Kolom()
{
    const char *fields[] = {
        "Art", "Biology", "Business", "Chemistry", "Computer Science",
        "Economics", "Engineering", "Environmental Science", "Geography", "Geology",
        "History", "Materials Science", "Mathematics", "Medicine", "Philosophy",
        "Physics", "Political Science", "Psychology", "Sociology"};
    int jumlahField = sizeof(fields) / sizeof(fields[0]);
    int tengah = (jumlahField + 1) / 2;

    printf("\n================== List Field of Study ==================\n");
    printf("| No | Field of Study        || No | Field of Study         |\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < tengah; i++)
    {
        int kananIndex = i + tengah;

        printf("| %-2d | %-22s", i + 1, fields[i]);

        if (kananIndex < jumlahField)
        {
            printf("|| %-2d | %-22s |\n", kananIndex + 1, fields[kananIndex]);
        }
        else
        {
            printf("||    |                        |\n");
        }
    }

    printf("===========================================================\n");
}