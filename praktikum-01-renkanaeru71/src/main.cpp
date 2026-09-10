// =============================================================================
// main.cpp — Runner Latihan (BUKAN bagian dari penilaian)
// Pertemuan 1: Dasar-Dasar Struktur Data C++
// =============================================================================
// File ini disediakan supaya Anda dapat MENJALANKAN dan MENCOBA sendiri
// implementasi Anda di komputer lokal.
//
//   - File ini TIDAK ikut dinilai.
//   - Checker tidak memakai dan tidak bergantung pada file ini sama sekali.
//   - Anda BEBAS mengubah, menambah, atau menghapus isi file ini untuk
//     eksperimen. Mengubahnya tidak mempengaruhi nilai Anda.
//   - Yang dinilai tetap hanya src/student.cpp.
//
// Cara menjalankan:
//
//   g++ -std=c++17 src/student.cpp src/main.cpp -o latihan
//   ./latihan
//
// Runner ini sengaja hanya MEMANGGIL fungsi-fungsi yang harus Anda buat, lalu
// menampilkan apa yang dilaporkan fungsi-fungsi itu. Selama sebuah fungsi belum
// Anda isi, bagian yang bersangkutan masih menampilkan nilai sementara dari
// skeleton (-1 / -1.0) atau array yang belum berubah — itu wajar. Kerjakan satu
// soal, jalankan lagi, dan perhatikan bagian mana yang mulai berubah.
//
// KALAU SEBUAH BAGIAN BERHENTI MENDADAK
// -------------------------------------
// Setiap bagian di bawah dijalankan terpisah satu sama lain (lihat
// src/runner_util.h). Jadi kalau kode Anda membuat satu bagian mati — indeks
// array lewat batas, fungsi lupa `return`, loop tidak berhenti — runner
// mencetak penjelasan sebabnya lalu TETAP LANJUT ke bagian berikutnya.
//
// Artinya soal yang macet tidak menyembunyikan soal sesudahnya: Anda tetap
// bisa melihat hasil semua soal lain dalam sekali jalan.
//
// Silakan tambahkan sendiri percobaan Anda di bawah, misalnya array dengan
// isi negatif semua, target yang tidak ada, atau kelas dengan nilai yang seri.
// =============================================================================

#include <iomanip>
#include <iostream>
#include <string>
#include "runner_util.h"
#include "student.h"

using namespace std;

// -----------------------------------------------------------------------------
// Pembantu tampilan runner. Semuanya hanya menampilkan apa yang dikembalikan
// fungsi Anda, tanpa menilai benar atau salah.
// -----------------------------------------------------------------------------

// Menulis satu baris keterangan dengan lebar label yang seragam.
static ostream& baris(const string& label) {
    return cout << "    " << left << setw(26) << label << ": ";
}

// Menampilkan isi array dalam bentuk {a, b, c}.
static void cetakArray(const int data[], int n) {
    cout << "{";
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << ", ";
        cout << data[i];
    }
    cout << "}";
}

// -----------------------------------------------------------------------------
// Data bersama. Semuanya const: bagian-bagian di bawah hanya membacanya, jadi
// isinya sama persis di setiap bagian.
// -----------------------------------------------------------------------------

static const int angka[] = {4, 8, 15, 16, 23, 42};
static const int jumlahAngka = 6;

static const Mahasiswa kelas[] = {
    {"Andi",  101, 80.0},
    {"Bela",  102, 90.0},
    {"Citra", 103, 70.0},
    {"Dedi",  104, 60.0}
};
static const int jumlahMahasiswa = 4;

// =============================================================================
// BAGIAN A — Operasi baca. Array `angka` tidak boleh berubah setelah dipakai
// oleh fungsi-fungsi bagian ini.
// =============================================================================
// Setiap soal berdiri sendiri di bawah ini. Itu disengaja: kalau satu soal
// membuat program mati, hanya soal itu yang hilang dari keluaran — soal
// lainnya tetap tercetak dalam sekali jalan.

static void bagian_data_angka() {
    cout << "\n[1] Data untuk Bagian A\n";
    baris("isi array");
    cetakArray(angka, jumlahAngka);
    cout << "\n";
    baris("banyaknya elemen") << jumlahAngka << "\n";
}

static void soal1_hitung_total() {
    cout << "\n[2] hitungTotal()  — soal 1\n";
    baris("hitungTotal(...)")        << hitungTotal(angka, jumlahAngka) << "\n";
    baris("hitungTotal(n = 0)")      << hitungTotal(angka, 0)           << "\n";
}

static void soal2_hitung_rata_rata() {
    cout << "\n[3] hitungRataRata()  — soal 2\n";
    baris("hitungRataRata(...)")     << hitungRataRata(angka, jumlahAngka) << "\n";
    baris("hitungRataRata(n = 0)")   << hitungRataRata(angka, 0)           << "\n";

    // Rata-rata yang hasilnya pecahan. Ini yang membedakan pembagian pecahan
    // dari pembagian antar-int yang memotong: {5, 8} seharusnya 6.5, bukan 6.
    const int duaAngka[] = {5, 8};
    baris("hitungRataRata({5, 8})")  << hitungRataRata(duaAngka, 2)        << "\n";
}

static void soal3_cari_max() {
    cout << "\n[4] cariMax()  — soal 3\n";
    const int negatif[] = {-9, -3, -70, -12};
    baris("cariMax(array di atas)")   << cariMax(angka, jumlahAngka) << "\n";
    baris("cariMax({-9,-3,-70,-12})") << cariMax(negatif, 4)         << "\n";
}

static void soal4_cari_indeks() {
    cout << "\n[5] cariIndeks()  — soal 4\n";
    baris("cariIndeks(..., 15)")     << cariIndeks(angka, jumlahAngka, 15) << "\n";
    baris("cariIndeks(..., 99)")     << cariIndeks(angka, jumlahAngka, 99) << "\n";
}

// =============================================================================
// BAGIAN B — Operasi ubah. Array di bawah TIDAK ber-const karena memang akan
// diubah isinya oleh fungsi-fungsi bagian ini.
// =============================================================================

static void soal5_balik_array() {
    cout << "\n[6] balikArray()  — soal 5\n";
    int urutan[] = {1, 2, 3, 4, 5};
    baris("sebelum");
    cetakArray(urutan, 5);
    cout << "\n";
    balikArray(urutan, 5);
    baris("sesudah");
    cetakArray(urutan, 5);
    cout << "\n";
}

static void soal6_hapus_nilai() {
    cout << "\n[7] hapusNilai(..., target 5)  — soal 6\n";
    int daftar[] = {5, 2, 5, 9, 5, 1};
    baris("sebelum");
    cetakArray(daftar, 6);
    cout << "\n";
    int ukuranBaru = hapusNilai(daftar, 6, 5);
    baris("ukuran baru") << ukuranBaru << "\n";
    baris("isi yang tersisa");
    if (ukuranBaru >= 0 && ukuranBaru <= 6) {
        cetakArray(daftar, ukuranBaru);
    } else {
        cout << "(ukuran baru tidak masuk akal)";
    }
    cout << "\n";
}

// =============================================================================
// BAGIAN C — Struct: satu satuan data berisi beberapa field sekaligus.
// =============================================================================

static void bagian_data_mahasiswa() {
    cout << "\n[8] Data mahasiswa untuk Bagian C\n";
    for (int i = 0; i < jumlahMahasiswa; ++i) {
        baris("mahasiswa[" + to_string(i) + "]")
            << kelas[i].nama << " (nim " << kelas[i].nim
            << ", nilai " << kelas[i].nilai << ")\n";
    }
}

static void soal7_rata_rata_nilai() {
    cout << "\n[9] rataRataNilai()  — soal 7\n";
    baris("rataRataNilai(...)") << rataRataNilai(kelas, jumlahMahasiswa) << "\n";
    baris("rataRataNilai(n = 0)") << rataRataNilai(kelas, 0)             << "\n";
}

static void soal8_indeks_nilai_tertinggi() {
    cout << "\n[10] indeksNilaiTertinggi()  — soal 8\n";
    baris("indeksNilaiTertinggi(...)") << indeksNilaiTertinggi(kelas, jumlahMahasiswa) << "\n";

    // Menampilkan nama mahasiswa terbaik lewat indeks yang dikembalikan fungsi
    // Anda. Inilah gunanya mengembalikan indeks, bukan nilainya.
    int terbaik = indeksNilaiTertinggi(kelas, jumlahMahasiswa);
    baris("nilai tertinggi atas nama");
    if (terbaik >= 0 && terbaik < jumlahMahasiswa) {
        cout << kelas[terbaik].nama << "\n";
    } else {
        cout << "(indeks belum benar)\n";
    }
}

static void soal9_hitung_lulus() {
    cout << "\n[11] hitungLulus()  — soal 9\n";
    baris("hitungLulus(kkm = 75)")    << hitungLulus(kelas, jumlahMahasiswa, 75.0)  << "\n";
    baris("hitungLulus(kkm = 100.1)") << hitungLulus(kelas, jumlahMahasiswa, 100.1) << "\n";
}

// =============================================================================
// Daftar bagian yang dijalankan runner
// =============================================================================
// Tiap baris di bawah dijalankan di prosesnya sendiri. Menambah percobaan
// Anda sendiri: tulis fungsi `static void ...()` baru di atas, lalu
// daftarkan namanya di daftar ini.

static void (*const BAGIAN[])() = {
    bagian_data_angka,
    soal1_hitung_total,
    soal2_hitung_rata_rata,
    soal3_cari_max,
    soal4_cari_indeks,
    soal5_balik_array,
    soal6_hapus_nilai,
    bagian_data_mahasiswa,
    soal7_rata_rata_nilai,
    soal8_indeks_nilai_tertinggi,
    soal9_hitung_lulus,
};

// Batas waktu per bagian. Longgar untuk laptop yang sedang sibuk, tetapi
// mencegah loop tak berujung menggantung runner selamanya.
static const int BATAS_DETIK_PER_BAGIAN = 5;

int main() {
    cout << "==========================================\n";
    cout << " Runner Latihan — Dasar Struktur Data C++\n";
    cout << " (file ini tidak ikut dinilai)\n";
    cout << "==========================================\n";

    int bagian_mati = 0;
    for (void (*const fn)() : BAGIAN) {
        if (!jalankan_bagian(fn, BATAS_DETIK_PER_BAGIAN)) {
            bagian_mati++;
        }
    }

    cout << "\n==========================================\n";
    if (bagian_mati > 0) {
        cout << " " << bagian_mati << " bagian berhenti mendadak.\n";
        cout << " Baca penjelasan di bagian yang bersangkutan,\n";
        cout << " perbaiki fungsinya, lalu jalankan lagi.\n";
    } else {
        cout << " Selesai. Silakan ubah file ini untuk\n";
        cout << " mencoba percobaan Anda sendiri.\n";
    }
    cout << "==========================================\n";

    return 0;
}
