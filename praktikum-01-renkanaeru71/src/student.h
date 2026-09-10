// =============================================================================
// student.h — Interface Praktikum
// Pertemuan 1: Dasar-Dasar Struktur Data C++
// =============================================================================
// INSTRUKSI UNTUK MAHASISWA:
//   - JANGAN mengubah file ini.
//   - Implementasikan seluruh fungsi berikut di dalam src/student.cpp.
//   - Checker memakai deklarasi di file ini untuk menguji program Anda, jadi
//     nama dan signature fungsi adalah KONTRAK yang tidak boleh diubah.
//   - Nama variabel lokal, cara looping, dan gaya penulisan Anda BEBAS.
//     Penilaian hanya melihat perilaku (hasil) fungsi, bukan bentuk kodenya.
//
// KONVENSI UMUM:
//   - `data` adalah array, `n` adalah banyaknya elemen yang valid di dalamnya.
//   - `n` tidak pernah negatif, tetapi BISA bernilai 0 (array kosong).
//     Perilaku untuk n == 0 didokumentasikan pada tiap fungsi di bawah.
//   - Parameter ber-`const` berarti fungsi TIDAK boleh mengubah isi array.
//     Tanpa `const` berarti fungsi memang diminta mengubah array (in-place).
// =============================================================================

#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

// =============================================================================
// BAGIAN A — Operasi Baca (traversal & statistik pada array)
// =============================================================================

/**
 * Menjumlahkan seluruh elemen array.
 *
 * @param data  array bilangan bulat (tidak boleh diubah)
 * @param n     banyaknya elemen
 * @return      jumlah semua elemen; 0 bila n == 0
 *
 * Contoh: {4, 8, 15} -> 27
 */
int hitungTotal(const int data[], int n);

/**
 * Menghitung rata-rata (mean) seluruh elemen array.
 *
 * @return  rata-rata dalam bentuk pecahan; 0.0 bila n == 0
 *
 * PERHATIAN: hasilnya double, jadi pembagiannya harus pembagian pecahan.
 * Contoh: {5, 8} -> 6.5   (bukan 6)
 */
double hitungRataRata(const int data[], int n);

/**
 * Mencari nilai TERBESAR di dalam array.
 *
 * @return  nilai terbesar; 0 bila n == 0
 *
 * PERHATIAN: array bisa berisi bilangan negatif semua, misalnya
 * {-9, -3, -70} -> -3. Jangan memulai pencarian dari angka 0.
 */
int cariMax(const int data[], int n);

/**
 * Mencari posisi (indeks) kemunculan PERTAMA dari `target`.
 * Ini adalah pencarian sekuensial / linear search.
 *
 * @return  indeks pertama yang isinya sama dengan target (mulai dari 0),
 *          atau -1 bila target tidak ada di dalam array (termasuk saat n == 0)
 *
 * Contoh: {7, 3, 7}, target 7 -> 0   (indeks pertama, bukan yang terakhir)
 */
int cariIndeks(const int data[], int n, int target);

// =============================================================================
// BAGIAN B — Operasi Ubah (memodifikasi isi array secara in-place)
// =============================================================================

/**
 * Membalik urutan elemen array DI TEMPAT (in-place), tanpa mengembalikan nilai.
 * Isi array asli yang berubah.
 *
 * Contoh: {1, 2, 3, 4} menjadi {4, 3, 2, 1}
 * Bila n == 0 atau n == 1, array tidak berubah.
 */
void balikArray(int data[], int n);

/**
 * Menghapus SEMUA elemen yang nilainya sama dengan `target` dari array,
 * lalu merapatkan elemen sisanya ke depan tanpa mengubah urutan relatifnya.
 *
 * @return  ukuran baru array setelah penghapusan
 *
 * Contoh: data {5, 2, 5, 9}, target 5
 *         -> data menjadi {2, 9, ...} dan fungsi mengembalikan 2
 *
 * Elemen di posisi >= ukuran baru dianggap sampah dan tidak diperiksa checker,
 * jadi Anda tidak perlu membersihkannya.
 * Bila target tidak ditemukan, array tetap dan fungsi mengembalikan n.
 */
int hapusNilai(int data[], int n, int target);

// =============================================================================
// BAGIAN C — Struct: menyatukan beberapa data menjadi satu satuan
// =============================================================================

/**
 * Satu baris data mahasiswa. Sebuah struct membungkus beberapa nilai yang
 * berbeda tipe menjadi SATU satuan data, sehingga sekumpulan mahasiswa cukup
 * disimpan dalam satu array saja.
 *
 * JANGAN mengubah definisi struct ini — checker membuat data ujinya
 * berdasarkan bentuk di bawah.
 */
struct Mahasiswa {
    string nama;
    int         nim;
    double      nilai;   // 0.0 - 100.0
};

/**
 * Menghitung rata-rata field `nilai` dari sekumpulan mahasiswa.
 *
 * @return  rata-rata nilai; 0.0 bila n == 0
 */
double rataRataNilai(const Mahasiswa data[], int n);

/**
 * Mencari indeks mahasiswa dengan `nilai` tertinggi.
 *
 * @return  indeks mahasiswa bernilai tertinggi, atau -1 bila n == 0
 *
 * Bila ada beberapa mahasiswa dengan nilai tertinggi yang sama,
 * kembalikan indeks yang PALING AWAL.
 */
int indeksNilaiTertinggi(const Mahasiswa data[], int n);

/**
 * Menghitung berapa mahasiswa yang lulus, yaitu yang `nilai`-nya
 * lebih besar atau SAMA DENGAN kkm (nilai == kkm dihitung LULUS).
 *
 * @param kkm  batas nilai kelulusan
 * @return     banyaknya mahasiswa yang lulus; 0 bila n == 0
 */
int hitungLulus(const Mahasiswa data[], int n, double kkm);

#endif // STUDENT_H
