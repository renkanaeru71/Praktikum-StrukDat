// =============================================================================
// student.h — Interface Praktikum
// Pertemuan 3: Linked List Tunggal
// =============================================================================
// INSTRUKSI UNTUK MAHASISWA:
//   - JANGAN mengubah file ini.
//   - Implementasikan seluruh fungsi di dalam src/student.cpp.
//   - Nama struct, nama field, nama fungsi, tipe parameter, dan tipe kembalian
//     adalah KONTRAK: checker memanggilnya langsung, jadi tidak boleh diubah.
//   - Cara Anda memenuhi kontrak sepenuhnya bebas. Penilaian hanya melihat
//     perilaku yang teramati oleh pemanggil.
//
// -----------------------------------------------------------------------------
// STUDY CASE: ANTREAN LOKET KLINIK "SEHAT SELALU"
// -----------------------------------------------------------------------------
// Pertemuan ini hanya punya SATU soal, yaitu study case antrean loket klinik.
// Ceritanya lengkap ada di src/student.cpp. File ini hanya ringkasan kontraknya.
//
// Ada EMPAT pekerjaan yang dinilai:
//
//     Soal 1  tambahAkhir   pasien baru mengantre di belakang       30 poin
//     Soal 2  posisi        berapa orang lagi di depan saya         25 poin
//     Soal 3  hapus         pasien membatalkan antreannya           30 poin
//     Soal 4  clear         loket tutup, antrean dibubarkan         15 poin
//
// Tiga fungsi lain SUDAH DISEDIAKAN lengkap di src/student.cpp dan tidak
// dinilai: `tambahAwal`, `panjang`, dan `cari`.
//
// -----------------------------------------------------------------------------
// KONVENSI UMUM
// -----------------------------------------------------------------------------
//   - Setiap pasien dikenali dari sebuah NOMOR ANTREAN bertipe `int`. Nomor
//     boleh negatif, boleh nol, dan boleh muncul lebih dari sekali.
//   - `head` bernilai `nullptr` berarti antreannya sedang KOSONG. Itu keadaan
//     yang sah, bukan kesalahan.
//   - Parameter bertanda `&` berarti `head` milik pemanggil ikut berubah.
//   - Tidak ada fungsi yang mencetak apa pun ke layar.
// =============================================================================

#ifndef STUDENT_H
#define STUDENT_H

/**
 * Satu orang di dalam antrean.
 *
 *   `data`   nomor antreannya
 *   `next`   alamat orang BERIKUTNYA, atau `nullptr` bila dia paling belakang
 *
 * Antrean seluruhnya dikenali dari satu penanda saja, yaitu `head` — alamat
 * orang paling depan.
 *
 *     head
 *      |
 *     [21] -> [47] -> [33] -> [58] -> nullptr
 *      ^                        ^
 *  dilayani duluan         paling belakang
 */
struct Node {
    int data;
    Node* next;
};

/**
 * SOAL 1 — Seorang pasien baru mengambil nomor dan berdiri di posisi PALING
 * BELAKANG antrean.
 *
 * Kontrak:
 *   - Setelah pemanggilan, pasien baru itulah orang terakhir di antrean, dan
 *     `next` miliknya bernilai `nullptr`.
 *   - Seluruh pasien yang sudah ada tetap berada di depannya dengan urutan yang
 *     sama persis.
 *   - Pada antrean yang semula KOSONG, pasien baru sekaligus menjadi orang
 *     paling depan, sehingga `head` milik pemanggil ikut berubah.
 *   - Pada antrean yang SUDAH BERISI, `head` TIDAK boleh berpindah.
 *   - Kembaliannya `true` bila pasien baru berhasil masuk antrean.
 */
bool tambahAkhir(Node*& head, int data);

/**
 * SOAL 2 — Banyaknya orang yang berada DI DEPAN pasien bernomor `data`.
 *
 * Orang paling depan tidak punya siapa-siapa di depannya, sehingga hasilnya 0.
 * Orang kedua hasilnya 1, orang ketiga hasilnya 2, dan seterusnya.
 *
 * Kontrak:
 *   - Bila `data` muncul lebih dari sekali, yang dihitung adalah kemunculan
 *     PERTAMA.
 *   - Bila `data` tidak ada di antrean, atau antrean sedang kosong,
 *     kembaliannya -1. Nilai 0 dan -1 punya arti yang sangat berbeda dan tidak
 *     boleh tertukar.
 *   - Antrean tidak boleh berubah oleh pemanggilan ini.
 */
int posisi(Node* head, int data);

/**
 * SOAL 3 — Seorang pasien membatalkan antreannya dan pergi. Ia dikeluarkan dari
 * antrean, lalu datanya dibuang dari memori.
 *
 * Kontrak:
 *   - Yang dikeluarkan adalah orang PERTAMA yang nomornya sama dengan `data`.
 *     Kemunculan berikutnya tetap tinggal di antrean.
 *   - Orang sebelum dan sesudahnya harus tersambung kembali, sehingga antrean
 *     tetap dapat ditelusuri utuh dari depan sampai belakang.
 *   - Bila yang keluar adalah orang PALING DEPAN, `head` milik pemanggil harus
 *     berpindah ke orang sesudahnya.
 *   - Bila dia satu-satunya orang di antrean, antrean menjadi kosong dan `head`
 *     milik pemanggil bernilai `nullptr`.
 *   - Orang yang keluar memorinya harus dibuang dengan `delete`.
 *   - Kembaliannya `true` bila memang ada yang dikeluarkan. Bila nomornya tidak
 *     ada, atau antrean sedang kosong, kembaliannya `false` dan antrean tidak
 *     boleh berubah sedikit pun.
 */
bool hapus(Node*& head, int data);

/**
 * SOAL 4 — Jam layanan habis. Loket ditutup dan seluruh antrean dibubarkan.
 *
 * Kontrak:
 *   - Setelah pemanggilan, `head` milik pemanggil bernilai `nullptr`.
 *   - SELURUH orang harus dibuang dari memori dengan `delete`, bukan hanya yang
 *     paling depan.
 *   - Memanggil fungsi ini pada antrean yang sudah kosong, atau memanggilnya
 *     berkali-kali berturut-turut, harus aman.
 */
void clear(Node*& head);

// =============================================================================
// SUDAH DISEDIAKAN — TIDAK DINILAI
// =============================================================================
// Ketiga fungsi di bawah sudah ditulis lengkap di src/student.cpp. Anda tidak
// perlu mengerjakannya.
// =============================================================================

/** Menyisipkan pasien PRIORITAS di posisi paling depan antrean. Disediakan
 *  sebagai PEMBANDING untuk Soal 1 — perhatikan betapa pendeknya fungsi ini,
 *  lalu pikirkan kenapa `tambahAkhir` tidak bisa sependek itu. */
bool tambahAwal(Node*& head, int data);

/** Banyaknya orang yang sedang mengantre. Antrean kosong bernilai 0. */
int panjang(Node* head);

/** Alamat node orang PERTAMA yang nomornya sama dengan `data`, atau `nullptr`
 *  bila tidak ada. Dipakai petugas untuk membetulkan data seorang pasien. */
Node* cari(Node* head, int data);

#endif // STUDENT_H
