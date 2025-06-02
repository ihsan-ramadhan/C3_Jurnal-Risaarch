#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fitur1.h"

void sll_init(SingleLinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

SLLNode* sll_createNode(SearchResult data) {
    SLLNode* newNode = (SLLNode*)malloc(sizeof(SLLNode));
    if (newNode == NULL) {
        printf("Gagal alokasi memori!\n");
        return NULL;
    }
    strcpy(newNode->data.title, data.title);
    strcpy(newNode->data.doiUrl, data.doiUrl);
    newNode->next = NULL;
    return newNode;
}

void sll_insertLast(SingleLinkedList* list, SearchResult data) {
    SLLNode* newNode = sll_createNode(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        SLLNode* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void sll_printList(SingleLinkedList* list) {
    if (list->head == NULL) {
        printf("Tidak ada jurnal yang sesuai.\n");
        return;
    }

    const int title_width = 40;
    int doi_width = strlen("DOI URL");

    SLLNode* current = list->head;
    while (current != NULL) {
        int doi_len = strlen(current->data.doiUrl);
        if (doi_len > doi_width) doi_width = doi_len;
        current = current->next;
    }

    if (doi_width < strlen("DOI URL")) doi_width = strlen("DOI URL");

    printf("\nHasil pencarian:\n");
    printf("%-*s | %-*s\n", title_width, "TITLE", doi_width, "DOI URL");

    char* title_sep = (char*)malloc(title_width + 1);
    char* doi_sep = (char*)malloc(doi_width + 1);
    memset(title_sep, '-', title_width);
    title_sep[title_width] = '\0';
    memset(doi_sep, '-', doi_width);
    doi_sep[doi_width] = '\0';
    printf("%s-+-%s\n", title_sep, doi_sep);
    free(title_sep);
    free(doi_sep);

    current = list->head;
    while (current != NULL) {
        char title[title_width + 1];
        strncpy(title, current->data.title, title_width);
        title[title_width] = '\0';

        printf("%-*s | %-*s\n", 
               title_width, title, 
               doi_width, strlen(current->data.doiUrl) ? current->data.doiUrl : "-");

        if (current->next != NULL) {
            title_sep = (char*)malloc(title_width + 1);
            doi_sep = (char*)malloc(doi_width + 1);
            memset(title_sep, '-', title_width);
            title_sep[title_width] = '\0';
            memset(doi_sep, '-', doi_width);
            doi_sep[doi_width] = '\0';
            printf("%s-+-%s\n", title_sep, doi_sep);
            free(title_sep);
            free(doi_sep);
        }

        current = current->next;
    }

    printf("\nTotal jurnal yang sesuai: %d\n", list->size);
}

void sll_freeList(SingleLinkedList* list) {
    SLLNode* current = list->head;
    while (current != NULL) {
        SLLNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}

static int stristr(const char* str, const char* substr) {
    if (!str || !substr) return 0;
    
    int len_str = strlen(str);
    int len_substr = strlen(substr);
    if (len_substr > len_str) return 0;

    char* lower_str = (char*)malloc(len_str + 1);
    char* lower_substr = (char*)malloc(len_substr + 1);
    if (!lower_str || !lower_substr) {
        free(lower_str);
        free(lower_substr);
        return 0;
    }

    for (int i = 0; i < len_str; i++) {
        lower_str[i] = tolower(str[i]);
    }
    lower_str[len_str] = '\0';

    for (int i = 0; i < len_substr; i++) {
        lower_substr[i] = tolower(substr[i]);
    }
    lower_substr[len_substr] = '\0';

    int result = strstr(lower_str, lower_substr) != NULL;

    free(lower_str);
    free(lower_substr);
    return result;
}

void search_journals(DoubleLinkedList* sourceList, SingleLinkedList* resultList, const char* keyword) {
    if (!sourceList || !resultList || !keyword) return;

    sll_init(resultList);

    Node* current = sourceList->head;
    while (current != NULL) {
        if (stristr(current->data.title, keyword)) {
            SearchResult result;
            strncpy(result.title, current->data.title, MAX_STR - 1);
            result.title[MAX_STR - 1] = '\0';
            strncpy(result.doiUrl, current->data.doiUrl, MAX_STR - 1);
            result.doiUrl[MAX_STR - 1] = '\0';
            sll_insertLast(resultList, result);
        }
        current = current->next;
    }
}