# C3_Jurnal-Risaarch
## Kelompok C-3
### Anggota Kelompok:

| Nama | NIM | ID GitHub |
| ---- | --- | --- |
| Alda Pujama | 241511066 | Arud4Alda |
| Fairuz Sheva Muhammad | 241511073 | pairus-portofolio |
| Gema Adzan Firdaus | 241511075 | Gema1407 |
| Muhammad Ihsan Ramadhan | 241511083 | ihsan-ramadhan |
| Rahma Attaya Tamimah | 241511088 | rahmaattayat |

# Deskripsi Program
*Jurnal Risaarch* adalah aplikasi berbasis terminal yang dikembangkan untuk memudahkan pengguna dalam melakukan pencarian dan pengelolaan data jurnal ilmiah. Aplikasi ini membaca data dari file CSV dan menyimpannya ke dalam struktur data Double Linked List untuk memungkinkan operasi pencarian dan penampilan data secara efisien.

# Struktur Data Program
1. *Double Linked List (DLL)*: Menyimpan seluruh data jurnal dari CSV.
2. *Single Linked List (SLL)*: Menyimpan hasil pencarian untuk ditampilkan (fitur 1, 3, dan 4).
3. *Queue*: Menyimpan sementara hasil pencarian untuk dikonversi ke list (fitur 1 dan 4).
4. *Binary Search Tree (BST)*: Digunakan dalam pencarian jurnal berdasarkan rentang tahun.

## 🔍 Fitur-Fitur Aplikasi Jurnal Risaarch
1. *Pencarian Jurnal Berdasarkan Field of Study*

   * Menampilkan daftar Field of Study (bidang ilmu) yang tersedia.
   * Pengguna memasukkan nama bidang, dan aplikasi mencari jurnal yang sesuai.
   * Navigasi hasil pencarian disediakan jika jumlah data banyak.
   * Validasi input memastikan pengguna tidak memasukkan angka atau bidang yang tidak tersedia.

2. *Pencarian Jurnal Berdasarkan Rentang Tahun*

   * Meminta input tahun awal dan tahun akhir dari pengguna.
   * Jika tahun sama, maka pencarian dilakukan secara langsung.
   * Jika rentang tahun, maka data disusun menggunakan *Binary Search Tree* untuk efisiensi pencarian dan penampilan terurut.
   * Hasil ditampilkan dengan *paginasi* (25 data per halaman) beserta navigasi halaman (next, prev, quit).

3. *Pencarian Jurnal Berdasarkan Author*

   * Pengguna dapat mencari jurnal dari penulis tertentu (misal: “Isaac Newton”).
   * Hasil pencarian ditampilkan dalam format tabel dengan total maksimum 10 hasil pertama.
   * Validasi input mencegah karakter ilegal dan input kosong.

4. *Pencarian Jurnal Berdasarkan Kata Kunci di Judul*

   * Pengguna memasukkan keyword untuk dicari dalam judul jurnal.
   * Hasil pencarian disimpan sementara dalam *Queue, lalu dimasukkan ke **Single Linked List* dan ditampilkan.
   * Menampilkan informasi: judul jurnal dan URL DOI.

5. *Menampilkan Seluruh Daftar Jurnal*

   * Menampilkan seluruh data jurnal dalam urutan penyimpanan.
   * Disediakan fitur *paginasi* (15 data per halaman).
   * Pengguna dapat menavigasi menggunakan perintah (n untuk next, p untuk prev, q untuk keluar).

6. *Keluar dari Aplikasi*

   * Menghentikan program dan membebaskan seluruh alokasi memori.
