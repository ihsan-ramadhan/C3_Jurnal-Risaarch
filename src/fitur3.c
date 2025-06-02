#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fitur3.h"

// Initializes a SingleLinkedList3
void sll3_init(SingleLinkedList3* list) {
    list->head = NULL;
    list->size = 0;
}

// Creates a new SLLNode3 with the given data
SLLNode3* sll3_createNode(SearchResult3 data) {
    SLLNode3* newNode = (SLLNode3*)malloc(sizeof(SLLNode3));
    if (newNode == NULL) {
        printf("Gagal alokasi memori untuk SLLNode3!\n");
        return NULL;
    }
    strncpy(newNode->data.title, data.title, MAX_STR - 1);
    newNode->data.title[MAX_STR - 1] = '\0';
    strncpy(newNode->data.doiUrl, data.doiUrl, MAX_STR - 1);
    newNode->data.doiUrl[MAX_STR - 1] = '\0';
    strncpy(newNode->data.authors, data.authors, MAX_STR - 1);
    newNode->data.authors[MAX_STR - 1] = '\0';
    newNode->next = NULL;
    return newNode;
}

// Inserts a new node at the end of the SingleLinkedList3
void sll3_insertLast(SingleLinkedList3* list, SearchResult3 data) {
    if (list->size >= MAX_RESULTS) { // Limit to 10 results
        return;
    }

    SLLNode3* newNode = sll3_createNode(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        SLLNode3* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// Prints the contents of the SingleLinkedList3
void sll3_printList(SingleLinkedList3* list) {
    if (list->head == NULL) {
        printf("Tidak ada jurnal yang sesuai.\n");
        return;
    }

    const int title_width = 40;
    const int doi_width = 30; // Increased DOI width
    const int authors_width = 30; // Added authors width

    printf("\nHasil pencarian (maksimal %d):\n", MAX_RESULTS);
    printf("%-*s | %-*s | %-*s\n", title_width, "TITLE", doi_width, "DOI URL", authors_width, "AUTHORS");

    char* title_sep = (char*)malloc(title_width + 1);
    char* doi_sep = (char*)malloc(doi_width + 1);
    char* authors_sep = (char*)malloc(authors_width + 1);
    
    memset(title_sep, '-', title_width);
    title_sep[title_width] = '\0';
    memset(doi_sep, '-', doi_width);
    doi_sep[doi_width] = '\0';
    memset(authors_sep, '-', authors_width);
    authors_sep[authors_width] = '\0';
    printf("%s-+-%s-+-%s\n", title_sep, doi_sep, authors_sep);
    free(title_sep);
    free(doi_sep);
    free(authors_sep);

    SLLNode3* current = list->head;
    while (current != NULL) {
        char title[title_width + 1];
        strncpy(title, current->data.title, title_width);
        title[title_width] = '\0';

        char authors[authors_width + 1];
        strncpy(authors, current->data.authors, authors_width);
        authors[authors_width] = '\0';

        printf("%-*s | %-*s | %-*s\n", 
               title_width, title, 
               doi_width, strlen(current->data.doiUrl) ? current->data.doiUrl : "-",
               authors_width, authors);

        if (current->next != NULL) {
            title_sep = (char*)malloc(title_width + 1);
            doi_sep = (char*)malloc(doi_width + 1);
            authors_sep = (char*)malloc(authors_width + 1);
            
            memset(title_sep, '-', title_width);
            title_sep[title_width] = '\0';
            memset(doi_sep, '-', doi_width);
            doi_sep[doi_width] = '\0';
            memset(authors_sep, '-', authors_width);
            authors_sep[authors_width] = '\0';
            printf("%s-+-%s-+-%s\n", title_sep, doi_sep, authors_sep);
            free(title_sep);
            free(doi_sep);
            free(authors_sep);
        }

        current = current->next;
    }

    printf("\nTotal jurnal yang sesuai: %d\n", list->size);
}

// Frees all nodes in the SingleLinkedList3
void sll3_freeList(SingleLinkedList3* list) {
    SLLNode3* current = list->head;
    while (current != NULL) {
        SLLNode3* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}

// Case-insensitive substring search
static int stristr_custom(const char* str, const char* substr) {
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

// Searches for journals by author keyword and populates the result list (up to MAX_RESULTS)
void search_journals_by_author(DoubleLinkedList* sourceList, SingleLinkedList3* resultList, const char* authorKeyword) {
    if (!sourceList || !resultList || !authorKeyword) return;

    sll3_init(resultList); // Initialize the result list

    Node* current = sourceList->head;
    while (current != NULL && resultList->size < MAX_RESULTS) {
        if (stristr_custom(current->data.authors, authorKeyword)) {
            SearchResult3 result;
            strncpy(result.title, current->data.title, MAX_STR - 1);
            result.title[MAX_STR - 1] = '\0';
            strncpy(result.doiUrl, current->data.doiUrl, MAX_STR - 1);
            result.doiUrl[MAX_STR - 1] = '\0';
            strncpy(result.authors, current->data.authors, MAX_STR - 1);
            result.authors[MAX_STR - 1] = '\0';
            sll3_insertLast(resultList, result);
        }
        current = current->next;
    }
}