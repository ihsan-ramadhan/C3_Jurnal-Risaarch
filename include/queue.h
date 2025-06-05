/*
 * File        : queue.h
 * Deskripsi   : Header file untuk pengelolaan struktur data antrian (queue).
 *               Mendefinisikan struktur data untuk node antrian dan antrian itu sendiri,
 *               serta deklarasi fungsi untuk inisialisasi, pembuatan node, penambahan data,
 *               pengambilan data, pengecekan kekosongan, dan pembersihan antrian.
 */

#ifndef QUEUE_H
#define QUEUE_H

// Struktur node untuk antrian
typedef struct QueueNode {
    void* data;
    struct QueueNode* next;
} QueueNode;

// Struktur antrian
typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;

// Deklarasi fungsi untuk modul queue
void queue_init(Queue* queue); // Inisialisasi antrian
QueueNode* queue_createNode(void* data); // Membuat node baru untuk antrian
void queue_enqueue(Queue* queue, void* data); // Menambahkan data ke akhir antrian
void* queue_dequeue(Queue* queue); // Mengambil dan menghapus data dari depan antrian
int queue_isEmpty(Queue* queue); // Memeriksa apakah antrian kosong
void queue_free(Queue* queue); // Membebaskan memori yang digunakan oleh antrian

#endif