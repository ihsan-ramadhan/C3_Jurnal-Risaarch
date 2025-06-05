/*
 * File        : queue.c
 * Deskripsi   : Implementasi struktur data Queue (antrian) menggunakan linked list.
 *               Queue bersifat generik dengan tipe data void* untuk fleksibilitas pemakaian.
 *               Digunakan untuk mendukung fitur-fitur seperti pencarian terurut atau penyimpanan hasil sementara.
 */

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

// Inisialisasi Queue menjadi kosong
void queue_init(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

// Membuat node baru untuk queue
QueueNode* queue_createNode(void* data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Gagal alokasi memori untuk QueueNode!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Menambahkan elemen ke belakang queue
void queue_enqueue(Queue* queue, void* data) {
    QueueNode* newNode = queue_createNode(data);
    if (newNode == NULL) return;

    if (queue->rear == NULL) {
        // Jika queue kosong
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

// Menghapus elemen dari depan queue dan mengembalikan datanya
void* queue_dequeue(Queue* queue) {
    if (queue->front == NULL) return NULL;

    QueueNode* temp = queue->front;
    void* data = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;
    return data;
}

// Mengecek apakah queue kosong
int queue_isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Menghapus seluruh elemen dalam queue dan mengosongkan memori
void queue_free(Queue* queue) {
    while (!queue_isEmpty(queue)) {
        queue_dequeue(queue);
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}
