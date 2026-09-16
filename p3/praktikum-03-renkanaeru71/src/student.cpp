// =============================================================================
// student.cpp — Implementasi Mahasiswa
// Pertemuan 3: Linked List Tunggal
// =============================================================================
// FILE YANG BOLEH DIEDIT      : src/student.cpp  ← HANYA FILE INI
// FILE YANG TIDAK BOLEH DIEDIT: src/student.h, tests/checker.cpp, tests/report.h
//
// -----------------------------------------------------------------------------
// DAFTAR PEKERJAAN DAN BOBOTNYA
// -----------------------------------------------------------------------------
//   Soal 1  tambahAkhir   pasien baru mengantre di belakang        30 poin
//   Soal 2  posisi        berapa orang lagi di depan saya          25 poin
//   Soal 3  hapus         pasien membatalkan antreannya            30 poin
//   Soal 4  clear         loket tutup, antrean dibubarkan          15 poin
//
// Sebelum diisi, compiler memunculkan peringatan "unused parameter".
// Itu wajar dan tidak mengurangi nilai.
// =============================================================================

#include "student.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// =============================================================================
// SUDAH DISEDIAKAN — TIDAK DINILAI, TIDAK PERLU DIUBAH & SUDAH LENGKAP
bool tambahAwal(Node*& head, int data) {
    Node* baru = new Node;
    baru->data = data;
    baru->next = head;
    head = baru;
    return true;
}

int panjang(Node* head) {
    int jumlah = 0;
    for (Node* jelajah = head; jelajah != nullptr; jelajah = jelajah->next) {
        ++jumlah;
    }
    return jumlah;
}

Node* cari(Node* head, int data) {
    for (Node* jelajah = head; jelajah != nullptr; jelajah = jelajah->next) {
        if (jelajah->data == data) return jelajah;
    }
    return nullptr;
}
// =============================================================================

// SOAL 01
bool tambahAkhir(Node*& head, int data) {
    Node* baru = new Node;
    baru->data = data;
    baru->next = nullptr;
    
    if (head == nullptr)
    {
        head = baru;
        return true;
    }

    Node* jelajah = head;
    while (jelajah->next != nullptr)
    {
        jelajah = jelajah->next;
    }
    jelajah->next = baru;
    return true;
}

// SOAL 02
int posisi(Node* head, int data) {
    int idx = 0;
    for (Node* jelajah = head; jelajah != nullptr; jelajah = jelajah->next) {
        if (jelajah->data == data) {
            return idx;
        }
        ++idx;
    }
    return -1;
}

// SOAL 03
bool hapus(Node*& head, int data) {
if (head == nullptr) return false;

// Jika node yang dihapus ada di paling depan
    if (head->data == data) {
        Node* hapusNode = head;
        head = head->next;
        delete hapusNode;
        return true;
    }

    // Jika node ada di tengah atau belakang
    Node* jelajah = head;
    while (jelajah->next != nullptr && jelajah->next->data != data) {
        jelajah = jelajah->next;
    }

    // Pastikan node target ditemukan
    if (jelajah->next != nullptr) {
        Node* hapusNode = jelajah->next;
        jelajah->next = hapusNode->next;
        delete hapusNode;
        return true;
    }

    return false;
}

// SOAL 04
void clear(Node*& head) {
    while (head != nullptr) {
        Node* hapusNode = head;
        head = head->next;
        delete hapusNode;
    }
}

// =============================================================================
// MAIN() — memeragakan pagi di loket. TIDAK dinilai, bebas diubah.
// =============================================================================
// Di bawah ini file ini menjadi program C++ biasa. Tekan Run di VS Code, atau
// jalankan lewat terminal:
//
//     g++ -std=c++17 src/student.cpp -o latihan
//     ./latihan
//
// Isinya menjalankan pagi di Klinik Sehat Selalu secara berurutan, dan
// menampilkan hasil tiap langkah berdampingan dengan jawaban yang benar —
// sehingga Anda bisa langsung membandingkan.
//
// SATU ATURAN YANG TIDAK BOLEH DILANGGAR
// --------------------------------------
// cin hanya boleh dipakai DI DALAM main() ini.
//
// (Baris #ifndef di bawah hanya urusan teknis: saat menilai, checker memakai
//  main() miliknya sendiri, jadi main() Anda dilewati supaya tidak bentrok.)
// =============================================================================

#ifndef ADA_MAIN_LAIN

static const char* benarSalah(bool nilai) {
    return nilai ? "true" : "false";
}

static ostream& baris(const string& label) {
    return cout << "    " << left << setw(22) << label << ": ";
}

// Menampilkan isi antrean memakai `panjang` dan penelusuran biasa.
static void tampilkanAntrean(Node* head) {
    baris("isi antrean");
    if (head == nullptr) {
        cout << "(kosong)";
    } else {
        for (Node* p = head; p != nullptr; p = p->next) {
            if (p != head) cout << " -> ";
            cout << p->data;
        }
    }
    cout << "\n";
    baris("panjang(head)") << panjang(head) << "\n";
}

static void langkah(const string& teks) {
    cout << "\n" << teks << "\n";
}

int main() {
    cout << "==================================================\n";
    cout << " Study Case — Antrean Loket Klinik \"Sehat Selalu\"\n";
    cout << " Memeragakan satu pagi di loket\n";
    cout << " (bagian ini tidak ikut dinilai)\n";
    cout << "==================================================\n";

    Node* head = nullptr;

    langkah("[0] Pukul 07.00, loket baru buka. Antrean masih kosong.");
    tampilkanAntrean(head);

    langkah("[1] SOAL 1 — tambahAkhir: pasien 21, 47, lalu 33 mengambil nomor");
    tambahAkhir(head, 21);
    tambahAkhir(head, 47);
    bool hasil1 = tambahAkhir(head, 33);
    baris("kembalian") << benarSalah(hasil1) << "\n";
    tampilkanAntrean(head);
    cout << "\n    Yang benar: 21 -> 47 -> 33, panjang 3\n";

    langkah("[2] Disediakan — tambahAwal: pasien lansia (5) didahulukan");
    tambahAwal(head, 5);
    tampilkanAntrean(head);
    cout << "\n    Yang benar: 5 -> 21 -> 47 -> 33, panjang 4\n";

    langkah("[3] SOAL 2 — posisi: \"masih berapa orang lagi di depan saya?\"");
    baris("posisi(head, 5)") << posisi(head, 5) << "\n";
    baris("posisi(head, 47)") << posisi(head, 47) << "\n";
    baris("posisi(head, 33)") << posisi(head, 33) << "\n";
    baris("posisi(head, 99)") << posisi(head, 99) << "\n";
    cout << "\n    Yang benar: 0, 2, 3, lalu -1 (99 tidak ada di antrean)\n";

    langkah("[4] SOAL 3 — hapus: pasien 47 membatalkan antreannya");
    baris("kembalian") << benarSalah(hapus(head, 47)) << "\n";
    tampilkanAntrean(head);
    cout << "\n    Yang benar: 5 -> 21 -> 33, panjang 3\n";

    langkah("[4b] SOAL 3 — pasien terdepan (5) dan terbelakang (33) ikut batal");
    hapus(head, 5);
    hapus(head, 33);
    tampilkanAntrean(head);
    cout << "\n    Yang benar: 21, panjang 1\n";

    langkah("[4c] SOAL 3 — mencoba menghapus 99 yang tidak ada di antrean");
    baris("kembalian") << benarSalah(hapus(head, 99)) << "\n";
    tampilkanAntrean(head);
    cout << "\n    Yang benar: false, dan antrean tidak berubah\n";

    langkah("[5] Disediakan — cari: petugas membetulkan nomor pasien 21");
    Node* ketemu = cari(head, 21);
    baris("cari(head, 21)") << (ketemu ? "ditemukan" : "tidak ditemukan") << "\n";
    if (ketemu != nullptr) {
        ketemu->data = 77;
        cout << "    (nomornya dibetulkan menjadi 77 lewat node hasil cari)\n";
    }
    tampilkanAntrean(head);
    cout << "\n    Yang benar: ditemukan, lalu antreannya menjadi 77\n";

    langkah("[6] SOAL 4 — clear: pukul 12.00, loket tutup");
    clear(head);
    baris("head") << (head == nullptr ? "nullptr" : "masih terisi") << "\n";
    tampilkanAntrean(head);
    cout << "\n    Yang benar: nullptr, (kosong), panjang 0\n";

    // -------------------------------------------------------------------------
    // Mau mencoba dengan nomor yang Anda ketik sendiri? Hapus tanda // di
    // bawah ini, lalu jalankan lagi.
    // -------------------------------------------------------------------------
    // int nomor;
    // cout << "\nKetik satu nomor antrean: ";
    // cin >> nomor;
    // tambahAkhir(head, nomor);
    // tampilkanAntrean(head);

    cout << "\n==================================================\n";
    cout << " Loket tutup. Silakan ubah bagian ini untuk\n";
    cout << " mencoba percobaan Anda sendiri.\n";
    cout << "==================================================\n";

    clear(head);
    return 0;
}
#endif
