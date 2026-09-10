// =============================================================================
// student.cpp — Implementasi Mahasiswa
// Pertemuan 2: Pointer
// =============================================================================
// FILE YANG BOLEH DIEDIT      : src/student.cpp  ← HANYA FILE INI
// FILE YANG TIDAK BOLEH DIEDIT: src/student.h, tests/checker.cpp, tests/report.h
//
// -----------------------------------------------------------------------------
// CARA MEMBACA SOAL DI FILE INI
// -----------------------------------------------------------------------------
// Setiap soal ditulis tepat di atas fungsinya, dengan empat bagian yang sama:
//
//     Ceritanya          — apa yang sedang terjadi, dan apa yang diminta
//     Parameternya       — arti setiap parameter, satu per satu
//     Contoh             — kode nyata beserta hasil yang benar
//     Yang perlu diingat — hal khusus yang ikut dinilai
//
// Nama parameter dan nama field selalu ditulis di antara tanda petik miring,
// misalnya `n` atau `target`, supaya mudah dibedakan dari kata biasa.
//
// Soal hanya menjelaskan HASIL yang harus tercapai, bukan langkah-langkah
// pengerjaannya. Menentukan caranya adalah bagian dari latihan ini.
//
// -----------------------------------------------------------------------------
// ISTILAH YANG DIPAKAI DI SELURUH SOAL
// -----------------------------------------------------------------------------
//   "pemanggil"  Kode di luar yang memanggil fungsi Anda — checker saat
//                menilai, atau main() di bagian bawah file ini saat Anda
//                mencoba sendiri. Dialah pemilik datanya, bukan fungsi Anda.
//
//   "alamat"     Nilai bertipe pointer, misalnya `int*`. Isinya bukan sebuah
//                angka, melainkan keterangan DI MANA sebuah angka disimpan.
//
//   "deret"      Sekumpulan angka yang tersimpan berurutan, seperti array.
//
//   `&x`         Alamat dari variabel x.
//   `*p`         Isi yang tersimpan di alamat p — dipakai untuk membaca
//                maupun untuk menulis.
//
//   `n`          Banyaknya angka pada sebuah deret. Di pertemuan ini nilainya
//                selalu minimal 1, jadi deretnya tidak pernah kosong.
//
// -----------------------------------------------------------------------------
// SATU HAL YANG MENGHEMAT WAKTU ANDA
// -----------------------------------------------------------------------------
// Seluruh parameter bertipe pointer di pertemuan ini SELALU berisi alamat yang
// sah. Tidak ada satu pun yang bisa bernilai `nullptr`. Anda tidak perlu
// menulis pemeriksaan seperti `if (a == nullptr)` di mana pun.
//
// -----------------------------------------------------------------------------
// ATURAN LAIN
// -----------------------------------------------------------------------------
//   - Signature fungsi adalah kontrak dan tidak boleh diubah. Isi fungsi, nama
//     variabel, dan struktur kode di dalamnya sepenuhnya bebas.
//   - Anda boleh menambah fungsi bantu sendiri.
//   - Anda BOLEH menulis main() sendiri di file ini, di bagian paling bawah
//     yang sudah disediakan. Pakai cin dan cout sebebasnya di sana.
//
// MENCOBA SENDIRI:
//   File ini adalah program C++ utuh. Tekan tombol Run di VS Code, atau:
//     g++ -std=c++17 src/student.cpp -o latihan && ./latihan
//   Yang dijalankan adalah main() di bagian paling bawah file ini. main() itu
//   tidak ikut dinilai dan bebas Anda ubah sesuka hati.
//
// Sebelum diisi, compiler memunculkan peringatan "unused parameter".
// Itu wajar dan tidak mengurangi nilai.
// =============================================================================

#include "student.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Soal 01
void tukarNilai(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Soal 02
int* cariElemen(int* data, int n, int target) {
    for (int i = 0; i < n; ++i) {
        if (data[i] == target) {
            return &data[i];
        }
    }
    return data;
}

// Soal 03
void perbaruiSensor(Sensor* sensor, int suhuBaru) {
    sensor->suhuTerakhir = suhuBaru;
    if (sensor->totalPembacaan == 0 || suhuBaru > sensor->suhuTertinggi) {
        sensor->suhuTertinggi = suhuBaru;
    }
    sensor->totalPembacaan++;
}

// =============================================================================
// MAIN() -  TIDAK dinilai - bebas diubah.
// =============================================================================
// Tekan Run di VS Code, atau
// jalankan lewat terminal:
//
//     g++ -std=c++17 src/student.cpp -o latihan
//     ./latihan
//
// Isinya boleh Anda ganti total: tambah cin, ubah datanya, coba kasus aneh,
// hapus yang tidak perlu. Tidak ada satu pun di bawah sini yang mempengaruhi
// nilai Anda.
//
// main() ini sengaja hanya MEMANGGIL fungsi-fungsi Anda, lalu menampilkan data
// MILIK PEMANGGIL — yaitu variabel di dalam main() ini, bukan variabel di dalam
// fungsi Anda. Itulah inti materi pertemuan ini: fungsi yang menerima alamat
// dapat mengubah data pemanggilnya. Selama sebuah fungsi belum Anda isi, data
// pemanggil akan tampak belum berubah — itu wajar. Kerjakan satu soal,
// jalankan lagi, lalu perhatikan bagian mana yang mulai berubah.
//
// SATU ATURAN YANG TIDAK BOLEH DILANGGAR
// --------------------------------------
// cin hanya boleh dipakai DI DALAM main() ini. JANGAN menaruh cin di dalam
// ketiga fungsi di atas. Saat menilai, checker memanggil fungsi-fungsi itu
// tanpa memberi masukan apa pun, jadi cin di sana akan membaca sampah — dan
// nilai Anda berubah-ubah setiap kali dinilai, dari kode yang sama persis.
//
// Ketiga fungsi di atas menerima datanya lewat PARAMETER. Itulah gunanya
// parameter: satu fungsi yang sama bisa dipakai berkali-kali dengan data yang
// berbeda-beda.
//
// (Baris #ifndef di bawah hanya urusan teknis: saat menilai, checker memakai
//  main() miliknya sendiri, jadi main() Anda dilewati supaya tidak bentrok.
//  Anda tidak perlu menyentuhnya.)
// =============================================================================

#ifndef ADA_MAIN_LAIN

// -----------------------------------------------------------------------------
// Dua pembantu tampilan di bawah ini hanya menampilkan apa yang terjadi pada
// data milik pemanggil, tanpa menilai benar atau salah. Boleh Anda ubah atau
// hapus.
// -----------------------------------------------------------------------------

// Menulis satu baris keterangan dengan lebar label yang seragam.
static ostream& baris(const string& label) {
    return cout << "    " << left << setw(26) << label << ": ";
}

// Menampilkan isi deret dalam bentuk {a, b, c}.
static void cetakDeret(const int* data, int n) {
    cout << "{";
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << ", ";
        cout << data[i];
    }
    cout << "}";
}

int main() {
    cout << "==========================================\n";
    cout << " Latihan — Pointer\n";
    cout << " (bagian ini tidak ikut dinilai)\n";
    cout << "==========================================\n";

    // -------------------------------------------------------------------------
    // Soal 1 — tukarNilai: efeknya harus terlihat pada variabel milik main().
    // -------------------------------------------------------------------------
    cout << "\n[1] tukarNilai(&x, &y)\n";
    int x = 7;
    int y = 19;
    baris("sebelum") << "x = " << x << ", y = " << y << "\n";
    tukarNilai(&x, &y);
    baris("sesudah") << "x = " << x << ", y = " << y << "\n";

    // -------------------------------------------------------------------------
    // Soal 2 — cariElemen: yang dikembalikan LOKASI, sehingga pemanggil bisa
    // menulis ke lokasi itu dan deret aslinya ikut berubah.
    // -------------------------------------------------------------------------
    cout << "\n[2] cariElemen()\n";
    int deretCari[] = {3, 14, 15, 92, 65};
    baris("sebelum");
    cetakDeret(deretCari, 5);
    cout << "\n";

    int* lokasi = cariElemen(deretCari, 5, 15);
    baris("cariElemen(..., 15)") << "isinya " << *lokasi << "\n";
    *lokasi = 100;   // menulis lewat lokasi -> deret aslinya ikut berubah
    baris("sesudah *lokasi = 100");
    cetakDeret(deretCari, 5);
    cout << "\n";

    // Angka yang muncul dua kali: yang dipakai harus kemunculan pertama.
    int deretKembar[] = {5, 8, 4, 8, 1};
    int* pertama = cariElemen(deretKembar, 5, 8);
    baris("angka 8 muncul 2 kali")
        << "menunjuk indeks " << (pertama - deretKembar)
        << " (seharusnya 1)\n";

    // -------------------------------------------------------------------------
    // Soal 3 — perbaruiSensor: rekaman milik pemanggil yang harus ikut berubah.
    // -------------------------------------------------------------------------
    cout << "\n[3] perbaruiSensor()\n";
    Sensor sensor = {0, 0, 0};   // rekaman baru, belum pernah menerima pembacaan
    const int pembacaan[] = {25, 30, 12};
    for (int i = 0; i < 3; ++i) {
        perbaruiSensor(&sensor, pembacaan[i]);
        baris("setelah suhu " + to_string(pembacaan[i]))
            << "terakhir = "    << sensor.suhuTerakhir
            << ", tertinggi = " << sensor.suhuTertinggi
            << ", total = "     << sensor.totalPembacaan << "\n";
    }

    // -------------------------------------------------------------------------
    // Mau mencoba dengan data yang Anda ketik sendiri? Hapus tanda // di
    // bawah ini, lalu jalankan lagi.
    // -------------------------------------------------------------------------
    // int p, q;
    // cout << "\nKetik dua angka: ";
    // cin >> p >> q;
    // tukarNilai(&p, &q);
    // cout << "setelah ditukar: " << p << " dan " << q << endl;

    cout << "\n==========================================\n";
    cout << " Selesai. Silakan ubah bagian ini untuk\n";
    cout << " mencoba percobaan Anda sendiri.\n";
    cout << "==========================================\n";

    return 0;
}
#endif
