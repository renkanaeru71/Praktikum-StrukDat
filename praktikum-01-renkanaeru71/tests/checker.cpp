// =============================================================================
// checker.cpp — Test Harness Instruktur
// Pertemuan 1: Dasar-Dasar Struktur Data C++
// =============================================================================
// File ini adalah milik instruktur dan TIDAK boleh diubah mahasiswa.
//
// PRINSIP PENILAIAN (behavior-based):
//   Checker hanya MEMANGGIL fungsi mahasiswa dan memeriksa hasilnya.
//   Nama variabel lokal, gaya looping, indentasi, komentar, dan urutan
//   implementasi tidak pernah diperiksa. Dua implementasi berbeda yang
//   menghasilkan perilaku sama akan sama-sama PASS.
//
// BOBOT:
//   25 test case, bobot rata (100 / 25 = 4 poin per test) — lihat report.h.
//   Jumlahnya dipilih agar score selalu bilangan bulat 0-100.
//
// CATATAN KEAMANAN:
//   Mahasiswa dapat membaca file ini. Mitigasi:
//   - Setiap fungsi diuji dengan beberapa input berbeda (normal, edge, batas)
//   - Repository mahasiswa bersifat privat
// =============================================================================

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include "report.h"
#include "../src/student.h"

using namespace std;

// =============================================================================
// Test Framework (sederhana, tanpa dependency eksternal)
// =============================================================================

// ANSI color codes untuk output terminal yang jelas
#define COLOR_GREEN "\033[32m"
#define COLOR_RED   "\033[31m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN  "\033[36m"
#define COLOR_RESET "\033[0m"
#define COLOR_BOLD  "\033[1m"

// Tidak ada penghitung global di sini. Test suite berjalan di proses anak,
// sehingga variabel apa pun yang dinaikkan di dalamnya ikut hilang saat anak
// selesai. Angka akhir selalu dihitung ulang oleh proses induk dari
// test_records(), yang diisi lewat pipe. Lihat tests/report.h.

// Macro untuk menjalankan satu test case
// Penggunaan: RUN_TEST("nama test", ekspresi_bool, "pesan jika gagal")
#define RUN_TEST(name, condition, msg) do { \
    bool _ok = (condition); \
    ostringstream _detail; \
    if (_ok) { \
        cout << COLOR_GREEN << "  [PASS]" << COLOR_RESET \
                  << " " << (name) << endl; \
    } else { \
        _detail << (msg); \
        cout << COLOR_RED << "  [FAIL]" << COLOR_RESET \
                  << " " << (name) << endl; \
        cout << "         Keterangan: " << (msg) << endl; \
    } \
    record_test((name), _ok, _detail.str()); \
} while(0)

// Macro untuk test kesetaraan nilai
// Penggunaan: ASSERT_EQ("nama", nilai_aktual, nilai_ekspektasi)
#define ASSERT_EQ(name, actual, expected) do { \
    bool _ok = ((actual) == (expected)); \
    ostringstream _detail; \
    if (_ok) { \
        cout << COLOR_GREEN << "  [PASS]" << COLOR_RESET \
                  << " " << (name) << endl; \
    } else { \
        _detail << "Expected: " << (expected) << ", Got: " << (actual); \
        cout << COLOR_RED << "  [FAIL]" << COLOR_RESET \
                  << " " << (name) << endl; \
        cout << "         Expected : " << (expected) << endl; \
        cout << "         Got      : " << (actual) << endl; \
    } \
    record_test((name), _ok, _detail.str()); \
} while(0)

// =============================================================================
// Utilitas pembanding
// =============================================================================

// Perbandingan double memakai toleransi, supaya cara perhitungan yang berbeda
// (misal menjumlah dulu lalu membagi, atau membagi satu per satu) tetap PASS.
static bool hampirSama(double a, double b) {
    return fabs(a - b) < 1e-9;
}

static string pesanDouble(double harapan, double didapat) {
    ostringstream out;
    out << "Expected: " << harapan << ", Got: " << didapat;
    return out.str();
}

static string arrayKeString(const int data[], int n) {
    ostringstream out;
    out << "{";
    for (int i = 0; i < n; ++i) {
        if (i > 0) out << ", ";
        out << data[i];
    }
    out << "}";
    return out.str();
}

static bool arraySama(const int a[], const int b[], int n) {
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// =============================================================================
// BAGIAN A — Operasi Baca
// =============================================================================

void test_hitung_total() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] hitungTotal()" << COLOR_RESET << endl;

    const int data[] = {4, 8, 15, 16, 23, 42};
    ASSERT_EQ("hitungTotal({4,8,15,16,23,42}) == 108", hitungTotal(data, 6), 108);

    // Bilangan negatif: hasil akhir tetap harus dijumlahkan apa adanya.
    const int campur[] = {-5, 10, -20, 3};
    ASSERT_EQ("hitungTotal({-5,10,-20,3}) == -12", hitungTotal(campur, 4), -12);

    // Edge case: array kosong.
    const int kosong[] = {0};
    ASSERT_EQ("hitungTotal(kosong, 0) == 0", hitungTotal(kosong, 0), 0);
}

void test_hitung_rata_rata() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] hitungRataRata()" << COLOR_RESET << endl;

    // Menangkap kesalahan klasik: pembagian int yang memotong pecahan.
    const int dua[] = {5, 8};
    RUN_TEST("hitungRataRata({5,8}) == 6.5",
             hampirSama(hitungRataRata(dua, 2), 6.5),
             pesanDouble(6.5, hitungRataRata(dua, 2)));

    const int empat[] = {10, 20, 30, 41};
    RUN_TEST("hitungRataRata({10,20,30,41}) == 25.25",
             hampirSama(hitungRataRata(empat, 4), 25.25),
             pesanDouble(25.25, hitungRataRata(empat, 4)));

    // Edge case: array kosong tidak boleh membagi dengan nol.
    const int kosong[] = {0};
    RUN_TEST("hitungRataRata(kosong, 0) == 0.0",
             hampirSama(hitungRataRata(kosong, 0), 0.0),
             pesanDouble(0.0, hitungRataRata(kosong, 0)));
}

void test_cari_max() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] cariMax()" << COLOR_RESET << endl;

    const int data[] = {3, 17, 4, 9};
    ASSERT_EQ("cariMax({3,17,4,9}) == 17", cariMax(data, 4), 17);

    // Menangkap kesalahan klasik: kandidat maksimum diawali angka 0.
    const int negatif[] = {-9, -3, -70, -12};
    ASSERT_EQ("cariMax({-9,-3,-70,-12}) == -3", cariMax(negatif, 4), -3);

    // Boundary: satu elemen saja.
    const int satu[] = {-8};
    ASSERT_EQ("cariMax({-8}) == -8", cariMax(satu, 1), -8);

    // Edge case: array kosong.
    const int kosong[] = {0};
    ASSERT_EQ("cariMax(kosong, 0) == 0", cariMax(kosong, 0), 0);
}

void test_cari_indeks() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] cariIndeks()" << COLOR_RESET << endl;

    const int data[] = {10, 25, 30, 45};
    ASSERT_EQ("cariIndeks({10,25,30,45}, 30) == 2", cariIndeks(data, 4, 30), 2);

    // Ada duplikat: yang diminta adalah kemunculan PERTAMA.
    const int duplikat[] = {7, 3, 7, 7};
    ASSERT_EQ("cariIndeks({7,3,7,7}, 7) == 0", cariIndeks(duplikat, 4, 7), 0);

    // Tidak ditemukan -> -1.
    ASSERT_EQ("cariIndeks({10,25,30,45}, 99) == -1", cariIndeks(data, 4, 99), -1);
}

// =============================================================================
// BAGIAN B — Operasi Ubah (in-place)
// =============================================================================

void test_balik_array() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] balikArray()" << COLOR_RESET << endl;

    {   // Jumlah elemen genap.
        int data[] = {1, 2, 3, 4};
        const int harapan[] = {4, 3, 2, 1};
        balikArray(data, 4);
        RUN_TEST("balikArray({1,2,3,4}) -> {4,3,2,1}",
                 arraySama(data, harapan, 4),
                 "Expected: " + arrayKeString(harapan, 4) +
                 ", Got: " + arrayKeString(data, 4));
    }

    {   // Jumlah elemen ganjil: elemen tengah harus tetap di tempatnya.
        int data[] = {5, -2, 9, 0, 7};
        const int harapan[] = {7, 0, 9, -2, 5};
        balikArray(data, 5);
        RUN_TEST("balikArray({5,-2,9,0,7}) -> {7,0,9,-2,5}",
                 arraySama(data, harapan, 5),
                 "Expected: " + arrayKeString(harapan, 5) +
                 ", Got: " + arrayKeString(data, 5));
    }

    {   // Boundary: n == 1 tidak mengubah apa pun, n == 2 menukar dua elemen.
        int data[] = {42, 99};
        const int setelahSatu[] = {42, 99};
        const int setelahDua[]  = {99, 42};

        balikArray(data, 1);
        bool tetap = arraySama(data, setelahSatu, 2);
        string jejak = "setelah n=1: " + arrayKeString(data, 2);

        balikArray(data, 2);
        bool tertukar = arraySama(data, setelahDua, 2);
        jejak += ", setelah n=2: " + arrayKeString(data, 2);

        RUN_TEST("balikArray n=1 tidak berubah, lalu n=2 -> {99,42}",
                 tetap && tertukar,
                 "Expected: setelah n=1 " + arrayKeString(setelahSatu, 2) +
                 " lalu setelah n=2 " + arrayKeString(setelahDua, 2) +
                 ", Got: " + jejak);
    }
}

void test_hapus_nilai() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] hapusNilai()" << COLOR_RESET << endl;

    {   // Beberapa kemunculan dihapus; urutan sisanya harus tetap.
        int data[] = {5, 2, 5, 9, 5, 1};
        const int harapan[] = {2, 9, 1};
        int ukuran = hapusNilai(data, 6, 5);
        ostringstream pesan;
        pesan << "Expected: ukuran 3 & " << arrayKeString(harapan, 3)
              << ", Got: ukuran " << ukuran << " & "
              << arrayKeString(data, ukuran > 0 && ukuran <= 6 ? ukuran : 0);
        RUN_TEST("hapusNilai({5,2,5,9,5,1}, 5) -> ukuran 3, isi {2,9,1}",
                 ukuran == 3 && arraySama(data, harapan, 3), pesan.str());
    }

    {   // Target tidak ada: array utuh, ukuran tetap.
        int data[] = {4, 8, 15};
        const int harapan[] = {4, 8, 15};
        int ukuran = hapusNilai(data, 3, 99);
        ostringstream pesan;
        pesan << "Expected: ukuran 3 & " << arrayKeString(harapan, 3)
              << ", Got: ukuran " << ukuran;
        RUN_TEST("hapusNilai({4,8,15}, 99) -> ukuran 3, isi tetap",
                 ukuran == 3 && arraySama(data, harapan, 3), pesan.str());
    }

    {   // Edge case: semua elemen terhapus -> ukuran 0.
        int data[] = {6, 6, 6};
        int ukuran = hapusNilai(data, 3, 6);
        ostringstream pesan;
        pesan << "Expected: ukuran 0, Got: ukuran " << ukuran;
        RUN_TEST("hapusNilai({6,6,6}, 6) -> ukuran 0", ukuran == 0, pesan.str());
    }
}

// =============================================================================
// BAGIAN C — Operasi pada kumpulan data bertipe struct
// =============================================================================

void test_rata_rata_nilai() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] rataRataNilai()" << COLOR_RESET << endl;

    const Mahasiswa kelas[] = {
        {"Andi",  101, 80.0},
        {"Bela",  102, 90.0},
        {"Citra", 103, 70.0},
        {"Dedi",  104, 60.0}
    };
    RUN_TEST("rataRataNilai(4 mahasiswa) == 75.0",
             hampirSama(rataRataNilai(kelas, 4), 75.0),
             pesanDouble(75.0, rataRataNilai(kelas, 4)));

    // Edge case: tidak ada mahasiswa sama sekali.
    RUN_TEST("rataRataNilai(kelas, 0) == 0.0",
             hampirSama(rataRataNilai(kelas, 0), 0.0),
             pesanDouble(0.0, rataRataNilai(kelas, 0)));
}

void test_indeks_nilai_tertinggi() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] indeksNilaiTertinggi()" << COLOR_RESET << endl;

    const Mahasiswa kelas[] = {
        {"Andi",  101, 78.5},
        {"Bela",  102, 65.0},
        {"Citra", 103, 91.25},
        {"Dedi",  104, 88.0}
    };
    ASSERT_EQ("indeksNilaiTertinggi(kelas) == 2", indeksNilaiTertinggi(kelas, 4), 2);

    // Nilai tertinggi seri: yang diminta adalah indeks paling awal.
    const Mahasiswa seri[] = {
        {"Eka",  105, 70.0},
        {"Fajar", 106, 95.0},
        {"Gita", 107, 95.0}
    };
    ASSERT_EQ("indeksNilaiTertinggi(nilai tertinggi seri) == 1",
              indeksNilaiTertinggi(seri, 3), 1);
}

void test_hitung_lulus() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] hitungLulus()" << COLOR_RESET << endl;

    const Mahasiswa kelas[] = {
        {"Andi",  101, 75.0},   // tepat di batas -> LULUS
        {"Bela",  102, 74.9},   // sedikit di bawah batas -> tidak lulus
        {"Citra", 103, 88.0},
        {"Dedi",  104, 40.0},
        {"Endah", 105, 100.0}
    };
    ASSERT_EQ("hitungLulus(kelas, kkm=75.0) == 3", hitungLulus(kelas, 5, 75.0), 3);

    // Kombinasi input lain: batas dinaikkan sehingga tidak ada yang lulus.
    ASSERT_EQ("hitungLulus(kelas, kkm=100.1) == 0", hitungLulus(kelas, 5, 100.1), 0);
}

// =============================================================================
// Main
// =============================================================================

// =============================================================================
// Daftar test suite
// =============================================================================
// `jumlah` adalah banyaknya test di dalam sebuah suite. Angka ini dipakai
// sebagai PENYEBUT TETAP saat menghitung score.
//
// Kenapa penyebut harus tetap: bila suite mati di tengah jalan, hanya sebagian
// test yang sempat tercatat. Kalau penyebutnya ikut mengecil, mahasiswa yang
// programnya crash pada test ke-7 akan tercatat "6 dari 6 lulus" alias score
// 100. Dengan penyebut tetap, sisa test dicatat SKIP dan tetap dihitung.
//
// Bila angka di bawah tidak cocok dengan jumlah test yang benar-benar dicatat,
// checker mencetak peringatan ke stderr. Peringatan itu untuk INSTRUKTUR
// (tandanya daftar ini lupa diperbarui saat test ditambah), bukan untuk
// mahasiswa.
struct Suite {
    const char* nama;
    void (*fn)();
    int jumlah;
};

static const Suite SUITES[] = {
    {"hitungTotal()",           test_hitung_total,             3},
    {"hitungRataRata()",        test_hitung_rata_rata,         3},
    {"cariMax()",               test_cari_max,                 4},
    {"cariIndeks()",            test_cari_indeks,              3},
    {"balikArray()",            test_balik_array,              3},
    {"hapusNilai()",            test_hapus_nilai,              3},
    {"rataRataNilai()",         test_rata_rata_nilai,          2},
    {"indeksNilaiTertinggi()",  test_indeks_nilai_tertinggi,   2},
    {"hitungLulus()",           test_hitung_lulus,             2},
};

// Batas waktu per suite. Longgar untuk runner CI yang sedang sibuk, tetapi
// mencegah loop tak berujung menggantungkan job sampai batas 6 jam GitHub.
static const int BATAS_DETIK_PER_SUITE = 10;

// =============================================================================
// Main
// =============================================================================

int main() {
    cout << COLOR_BOLD
              << "============================================" << endl;
    cout << " Praktikum Struktur Data C++ — Auto Checker" << endl;
    cout << " Pertemuan 1: Dasar-Dasar Struktur Data C++" << endl;
    cout << "============================================"
              << COLOR_RESET << endl;

    int total_tests = 0;
    for (const Suite& s : SUITES) total_tests += s.jumlah;

    // Diisi bila ada suite yang mati; ikut ditulis ke result.json supaya
    // aplikasi web bisa membedakan "jawaban salah" dari "program crash".
    string error_code;

    for (const Suite& s : SUITES) {
        const size_t sebelum = test_records().size();

        // Kode mahasiswa dipanggil di proses anak. Apa pun yang terjadi di
        // sana — SIGILL, SIGSEGV, SIGFPE, loop tak berujung — hanya membunuh
        // anaknya. Proses ini tetap hidup dan lanjut ke suite berikutnya.
        const string alasan = jalankan_terisolasi(s.fn, BATAS_DETIK_PER_SUITE);

        const int direkam = static_cast<int>(test_records().size() - sebelum);

        if (!alasan.empty()) {
            error_code = "RUNTIME_CRASH";
            cout << COLOR_RED << COLOR_BOLD << "  [CRASH]" << COLOR_RESET
                 << " " << s.nama << " berhenti tidak wajar." << endl;
            cout << "         " << alasan << endl;
            cout << "         " << (s.jumlah - direkam)
                 << " test pada bagian ini tidak sempat dijalankan." << endl;
        } else if (direkam != s.jumlah) {
            cerr << "PERINGATAN INSTRUKTUR: suite " << s.nama << " mencatat "
                 << direkam << " test, daftar SUITES menyebut " << s.jumlah
                 << ". Perbarui daftar SUITES di checker.cpp." << endl;
        }

        for (int i = direkam; i < s.jumlah; ++i) {
            record_skip(string(s.nama) + " — test #" + to_string(i + 1) +
                            " tidak dijalankan",
                        alasan.empty()
                            ? string("Test tidak dijalankan.")
                            : alasan);
        }
    }

    // -----------------------------------------------------------------------
    // Scoring Summary — dihitung dari test_records(), bukan dari penghitung
    // yang dinaikkan di dalam proses anak.
    // -----------------------------------------------------------------------
    int passed_tests = 0;
    for (const TestRecord& r : test_records()) {
        if (r.status == "PASS") passed_tests++;
    }
    const int failed_tests = total_tests - passed_tests;
    const int score = (total_tests > 0)
                          ? (passed_tests * 100 / total_tests)
                          : 0;

    cout << "\n" << COLOR_BOLD
              << "============================================\n"
              << " SCORING SUMMARY\n"
              << "============================================\n"
              << COLOR_RESET;

    cout << " Tests Berhasil : " << COLOR_GREEN << COLOR_BOLD
              << passed_tests << COLOR_RESET << " / " << total_tests << "\n";
    cout << " Tests Gagal    : " << COLOR_RED << COLOR_BOLD
              << failed_tests << COLOR_RESET << " / " << total_tests << "\n";

    // Score line — warna hijau jika sempurna, kuning jika sebagian, merah jika 0
    string score_color = (score == 100) ? COLOR_GREEN
                            : (score > 0)    ? COLOR_YELLOW
                                             : COLOR_RED;
    cout << " Score          : " << score_color << COLOR_BOLD
              << score << " / 100" << COLOR_RESET << "\n";

    cout << COLOR_BOLD
              << "============================================\n"
              << COLOR_RESET;

    // -----------------------------------------------------------------------
    // Hasil yang dapat dibaca mesin.
    // Berkas inilah yang diunggah sebagai artifact dan dibaca aplikasi web.
    // -----------------------------------------------------------------------
    if (!write_result_json("result.json", score, total_tests, error_code)) {
        cerr << "PERINGATAN: gagal menulis result.json" << endl;
    }

    if (failed_tests == 0) {
        cout << COLOR_GREEN << COLOR_BOLD
                  << " STATUS: SEMUA TEST BERHASIL ✓\n"
                  << COLOR_RESET;
        return 0; // exit code 0 = GitHub Actions SUCCESS
    } else {
        cout << COLOR_RED << COLOR_BOLD
                  << " STATUS: " << failed_tests << " TEST GAGAL ✗\n"
                  << COLOR_RESET;
        return 1; // exit code non-zero = GitHub Actions FAIL
    }
}
