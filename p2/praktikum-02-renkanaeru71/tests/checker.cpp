// =============================================================================
// checker.cpp — Test Harness Instruktur
// Pertemuan 2: Pointer
// =============================================================================
// File ini adalah milik instruktur dan TIDAK boleh diubah mahasiswa.
//
// PRINSIP PENILAIAN (behavior-based):
//   Checker hanya memanggil fungsi mahasiswa lalu memeriksa akibatnya:
//   isi data setelah pemanggilan, nilai yang dikembalikan, dan lokasi yang
//   ditunjuk. Nama variabel, gaya penulisan pointer, urutan kode, komentar,
//   dan formatting tidak pernah diperiksa. Implementasi apa pun yang memenuhi
//   kontrak di student.h akan PASS.
//
// BOBOT:
//   10 test case, bobot rata 100 / 10 = 10 poin per test (lihat report.h).
//   Bobot per soal diatur lewat BANYAKNYA test pada soal tersebut:
//     Soal 1  3 test = 30   Soal 2  3 test = 30   Soal 3  4 test = 40
//
// KETAHANAN TERHADAP CRASH:
//   Praktikum pointer rawan segfault di sisi mahasiswa (mis. menulis lewat
//   alamat yang tidak valid). Karena itu checker menyimpan snapshot result.json
//   setiap kali satu test selesai, dengan test yang belum sempat berjalan
//   dicatat sebagai FAIL. Bila program mahasiswa membuat checker berhenti tidak
//   wajar di tengah jalan, nilai parsial yang sudah diperoleh tetap tercatat
//   dan tidak berubah menjadi 0. Mekanisme grading global (report.h, scripts/,
//   workflow, skema result.json) tidak diubah sama sekali.
//
// CATATAN KEAMANAN:
//   Mahasiswa dapat membaca file ini. Mitigasi:
//   - Setiap kontrak diuji dengan beberapa input berbeda (normal, variasi, batas)
//   - Repository mahasiswa bersifat privat
// =============================================================================

#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
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

// Tidak ada penghitung global di sini. Test suite berjalan di proses
// anak, sehingga variabel apa pun yang dinaikkan di dalamnya ikut
// hilang saat anak selesai. Angka akhir selalu dihitung ulang oleh
// proses induk dari test_records(). Lihat tests/report.h.

// Banyaknya test yang direncanakan pada pertemuan ini. Dipakai untuk menghitung
// skor snapshot supaya test yang belum berjalan tetap terhitung sebagai gagal.
static const int TOTAL_TEST_DIRENCANAKAN = 10;

// Menulis result.json versi sementara setelah setiap SUITE selesai.
//
// Dulu dipanggil dari dalam makro test. Setelah isolasi diterapkan,
// makro berjalan di proses ANAK yang rekamannya kosong (hasil
// dikirim ke induk lewat pipe), sehingga snapshot dari sana akan
// menulis 0 lulus. Pemanggilannya dipindah ke proses induk.
// Test yang belum dijalankan ditambahkan sebagai FAIL, lalu dilepas kembali,
// sehingga isi rekaman sebenarnya tidak terpengaruh.
static void simpanHasilSementara() {
    vector<TestRecord>& rekaman = test_records();
    const size_t jumlahAsli = rekaman.size();

    for (size_t i = jumlahAsli;
         i < static_cast<size_t>(TOTAL_TEST_DIRENCANAKAN); ++i) {
        rekaman.push_back(TestRecord{
            "(test #" + to_string(i + 1) + " belum dijalankan)",
            "FAIL",
            "Checker berhenti sebelum test ini sempat dijalankan."});
    }

    int lulus = 0;
    for (size_t i = 0; i < jumlahAsli; ++i) {
        if (rekaman[i].status == "PASS") lulus++;
    }
    const int skor = lulus * 100 / TOTAL_TEST_DIRENCANAKAN;
    write_result_json("result.json", skor);

    rekaman.resize(jumlahAsli);
}

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

static string arrayKeString(const int* data, int n) {
    ostringstream out;
    out << "{";
    for (int i = 0; i < n; ++i) {
        if (i > 0) out << ", ";
        out << data[i];
    }
    out << "}";
    return out.str();
}

// Menerjemahkan sebuah alamat menjadi keterangan yang mudah dibaca manusia,
// tanpa pernah membaca isi alamat tersebut.
static string posisiPointer(const int* basis, int n, const int* p) {
    if (p == nullptr) return "nullptr";
    for (int i = 0; i < n; ++i) {
        if (p == basis + i) return "lokasi elemen ke-" + to_string(i);
    }
    return "alamat di luar blok data";
}

static string sensorKeString(const Sensor& s) {
    ostringstream out;
    out << "{suhuTerakhir=" << s.suhuTerakhir
        << ", suhuTertinggi=" << s.suhuTertinggi
        << ", totalPembacaan=" << s.totalPembacaan << "}";
    return out.str();
}

static bool sensorSama(const Sensor& s, int terakhir, int tertinggi, int total) {
    return s.suhuTerakhir == terakhir
        && s.suhuTertinggi == tertinggi
        && s.totalPembacaan == total;
}

static string harapanSensor(int terakhir, int tertinggi, int total) {
    Sensor s{terakhir, tertinggi, total};
    return sensorKeString(s);
}

// =============================================================================
// SOAL 1 — tukarNilai  (3 test = 30 poin)
// =============================================================================

void test_tukar_nilai() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] Soal 1 — tukarNilai()" << COLOR_RESET << endl;

    {   // Normal: dua nilai positif berbeda.
        int x = 7, y = 19;
        tukarNilai(&x, &y);
        ostringstream pesan;
        pesan << "Expected: x=19 y=7, Got: x=" << x << " y=" << y;
        RUN_TEST("tukarNilai(7, 19) -> data pemanggil menjadi 19 dan 7",
                 x == 19 && y == 7, pesan.str());
    }

    {   // Variasi: bilangan negatif dan nol.
        int x = -4, y = 0;
        tukarNilai(&x, &y);
        ostringstream pesan;
        pesan << "Expected: x=0 y=-4, Got: x=" << x << " y=" << y;
        RUN_TEST("tukarNilai(-4, 0) -> data pemanggil menjadi 0 dan -4",
                 x == 0 && y == -4, pesan.str());
    }

    {   // Dipakai dua kali berturut-turut: menukar lalu menukar lagi harus
        //   mengembalikan isi kedua variabel seperti semula.
        int m = 3, w = 8;
        tukarNilai(&m, &w);
        bool sekali = (m == 8 && w == 3);
        tukarNilai(&m, &w);
        bool duaKali = (m == 3 && w == 8);

        ostringstream pesan;
        pesan << "Expected: setelah sekali m=8 w=3, setelah dua kali m=3 w=8; "
                 "Got akhir: m=" << m << " w=" << w
              << (sekali ? "" : " (pertukaran pertama sudah tidak sesuai)");
        RUN_TEST("tukarNilai dipakai dua kali mengembalikan isi seperti semula",
                 sekali && duaKali, pesan.str());
    }
}

// =============================================================================
// SOAL 2 — cariElemen  (3 test = 30 poin)
// =============================================================================

void test_cari_elemen() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] Soal 2 — cariElemen()" << COLOR_RESET << endl;

    {   // Normal: lokasi yang dikembalikan harus benar-benar lokasi elemen itu,
        //         sehingga penulisan lewat lokasi tersebut mengubah blok asli.
        int data[] = {4, 9, 15, 9, 2};
        int* hasil = cariElemen(data, 5, 15);
        bool lokasiBenar = (hasil == &data[2]);
        bool tulisanTembus = false;
        if (lokasiBenar) {
            *hasil = 77;                 // aman: alamat sudah terverifikasi
            tulisanTembus = (data[2] == 77);
        }
        ostringstream pesan;
        pesan << "Expected: lokasi elemen ke-2 dan penulisan lewat lokasi itu "
                 "mengubah data, Got: " << posisiPointer(data, 5, hasil)
              << ", data=" << arrayKeString(data, 5);
        RUN_TEST("cariElemen menemukan 15 dan mengembalikan lokasi elemen aslinya",
                 lokasiBenar && tulisanTembus, pesan.str());
    }

    {   // Ada duplikat: yang diminta adalah kemunculan pertama.
        int data[] = {4, 9, 15, 9, 2};
        int* hasil = cariElemen(data, 5, 9);
        ostringstream pesan;
        pesan << "Expected: lokasi elemen ke-1 (kemunculan pertama), Got: "
              << posisiPointer(data, 5, hasil);
        RUN_TEST("cariElemen mengembalikan kemunculan pertama saat ada duplikat",
                 hasil == &data[1], pesan.str());
    }

    {   // Boundary: elemen paling depan, elemen paling belakang, dan deret
        //           yang hanya berisi satu angka.
        int data[] = {4, 9, 15, 9, 2};
        int* depan = cariElemen(data, 5, 4);
        int* belakang = cariElemen(data, 5, 2);

        int tunggal[] = {6};
        int* satuElemen = cariElemen(tunggal, 1, 6);

        ostringstream pesan;
        pesan << "Expected: lokasi elemen ke-0, lokasi elemen ke-4, dan lokasi "
                 "elemen ke-0 pada deret berisi satu angka; Got: "
              << posisiPointer(data, 5, depan) << ", "
              << posisiPointer(data, 5, belakang) << ", "
              << posisiPointer(tunggal, 1, satuElemen);
        RUN_TEST("cariElemen menemukan elemen pertama, elemen terakhir, dan deret satu angka",
                 depan == &data[0] && belakang == &data[4]
                     && satuElemen == &tunggal[0], pesan.str());
    }
}

// =============================================================================
// SOAL 3 — perbaruiSensor  (4 test = 40 poin)
// =============================================================================

void test_perbarui_sensor() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] Soal 3 — perbaruiSensor()" << COLOR_RESET << endl;

    {   // Normal: pembacaan pertama pada rekaman yang belum pernah dipakai.
        Sensor s{0, 0, 0};
        perbaruiSensor(&s, 25);

        ostringstream pesan;
        pesan << "Expected: " << harapanSensor(25, 25, 1)
              << ", Got: " << sensorKeString(s);
        RUN_TEST("perbaruiSensor mencatat pembacaan pertama pada rekaman baru",
                 sensorSama(s, 25, 25, 1), pesan.str());
    }

    {   // Beberapa pembacaan berturut-turut, termasuk suhu yang turun.
        Sensor s{0, 0, 0};
        perbaruiSensor(&s, 25);
        perbaruiSensor(&s, 30);
        bool naik = sensorSama(s, 30, 30, 2);
        perbaruiSensor(&s, 12);
        bool turun = sensorSama(s, 12, 30, 3);

        ostringstream pesan;
        pesan << "Expected: " << harapanSensor(30, 30, 2) << " lalu "
              << harapanSensor(12, 30, 3) << ", Got akhir: " << sensorKeString(s);
        RUN_TEST("perbaruiSensor berturut-turut: suhu tertinggi bertahan saat suhu turun",
                 naik && turun, pesan.str());
    }

    {   // Variasi: suhu bernilai nol dan pembacaan yang isinya berulang.
        Sensor s{0, 0, 0};
        perbaruiSensor(&s, 0);
        bool nol = sensorSama(s, 0, 0, 1);
        perbaruiSensor(&s, 7);
        perbaruiSensor(&s, 7);
        bool berulang = sensorSama(s, 7, 7, 3);

        ostringstream pesan;
        pesan << "Expected: " << harapanSensor(0, 0, 1) << " lalu "
              << harapanSensor(7, 7, 3) << ", Got akhir: " << sensorKeString(s);
        RUN_TEST("perbaruiSensor pada suhu nol dan pembacaan yang berulang",
                 nol && berulang, pesan.str());
    }

    {   // Batas: suhu tertinggi berada di tengah riwayat, bukan di awal atau
        //        di akhir; totalPembacaan harus ikut semua pembacaan.
        Sensor s{0, 0, 0};
        const int pembacaan[] = {3, 9, 4, 9, 1};
        for (int i = 0; i < 5; ++i) perbaruiSensor(&s, pembacaan[i]);

        ostringstream pesan;
        pesan << "Expected: " << harapanSensor(1, 9, 5)
              << " setelah pembacaan " << arrayKeString(pembacaan, 5)
              << ", Got: " << sensorKeString(s);
        RUN_TEST("perbaruiSensor menjaga suhu tertinggi sepanjang lima pembacaan",
                 sensorSama(s, 1, 9, 5), pesan.str());
    }
}

// =============================================================================
// Daftar test suite
// =============================================================================
// `jumlah` adalah banyaknya test di dalam sebuah suite, dipakai sebagai
// PENYEBUT TETAP. Bila suite mati di tengah jalan, hanya sebagian test yang
// sempat tercatat; kalau penyebutnya ikut mengecil, mahasiswa yang programnya
// crash pada test terakhir akan tercatat "semua lulus". Sisa test dicatat SKIP
// dan tetap ikut dihitung.
struct Suite {
    const char* nama;
    void (*fn)();
    int jumlah;
};

static const Suite SUITES[] = {
    {"test_tukar_nilai", test_tukar_nilai, 3},
    {"test_cari_elemen", test_cari_elemen, 3},
    {"test_perbarui_sensor", test_perbarui_sensor, 4},
};

// Batas waktu per suite. Longgar untuk runner CI yang sedang sibuk, tetapi
// mencegah loop tak berujung menggantungkan job sampai batas 6 jam GitHub.
static const int BATAS_DETIK_PER_SUITE = 10;

int main() {
    cout << COLOR_BOLD
              << "============================================" << endl;
    cout << " Praktikum Struktur Data C++ — Auto Checker" << endl;
    cout << " Pertemuan 2: Pointer" << endl;
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
        // sana -- SIGILL, SIGSEGV, SIGFPE, loop tak berujung -- hanya membunuh
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
                        alasan.empty() ? string("Test tidak dijalankan.")
                                       : alasan);
        }
        simpanHasilSementara();
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

    string score_color = (score == 100) ? COLOR_GREEN
                            : (score > 0)    ? COLOR_YELLOW
                                             : COLOR_RED;
    cout << " Score          : " << score_color << COLOR_BOLD
              << score << " / 100" << COLOR_RESET << "\n";

    cout << COLOR_BOLD
              << "============================================\n"
              << COLOR_RESET;

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
