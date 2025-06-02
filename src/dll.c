#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"

void dll_init(DoubleLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

Node* dll_createNode(Journal data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(newNode->data.title, data.title);
    strcpy(newNode->data.authors, data.authors);
    strcpy(newNode->data.fieldOfStudy, data.fieldOfStudy);
    newNode->data.year = data.year;
    strcpy(newNode->data.doiUrl, data.doiUrl);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void dll_insertLast(DoubleLinkedList* list, Journal data) {
    Node* newNode = dll_createNode(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"

void dll_printList(DoubleLinkedList* list) {
    if (list->head == NULL) {
        printf("No journals found.\n");
        return;
    }

    const int title_width = 40;
    const int authors_width = 30;
    const int field_width = 20;
    const int year_width = 6;
    const int doi_width = 30;

    printf("\n");
    printf("%-*s | %-*s | %-*s | %-*s | %-*s\n", 
           title_width, "TITLE", 
           authors_width, "AUTHORS", 
           field_width, "FIELD OF STUDY", 
           year_width, "YEAR", 
           doi_width, "DOI URL");

    printf("%-*s-+-%-*s-+-%-*s-+-%-*s-+-%-*s\n",
           title_width, "----------------------------------------",
           authors_width, "------------------------------",
           field_width, "--------------------",
           year_width, "------",
           doi_width, "------------------------------");

    Node* current = list->head;
    int count = 0;
    while (current != NULL && count < 10) {
        char title[title_width + 1];
        strncpy(title, current->data.title, title_width);
        title[title_width] = '\0';

        char authors[authors_width + 1];
        strncpy(authors, current->data.authors, authors_width);
        authors[authors_width] = '\0';

        char field[field_width + 1];
        strncpy(field, current->data.fieldOfStudy, field_width);
        field[field_width] = '\0';

        char doi[doi_width + 1];
        strncpy(doi, current->data.doiUrl, doi_width);
        doi[doi_width] = '\0';

        printf("%-*s | %-*s | %-*s | %-*d | %-*s\n", 
               title_width, title, 
               authors_width, authors, 
               field_width, field, 
               year_width, current->data.year, 
               doi_width, strlen(current->data.doiUrl) ? doi : "-");

        if (count < 9 && current->next != NULL) {
            printf("%-*s-+-%-*s-+-%-*s-+-%-*s-+-%-*s\n",
                   title_width, "----------------------------------------",
                   authors_width, "------------------------------",
                   field_width, "--------------------",
                   year_width, "------",
                   doi_width, "------------------------------");
        }

        current = current->next;
        count++;
    }

    printf("\nTotal journals: %d\n", list->size);
}

void dll_freeList(DoubleLinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}