// =============================================================================
// checker.cpp — Test Harness Instruktur
// Pertemuan 3: Linked List Tunggal
// =============================================================================
// File ini adalah milik instruktur dan TIDAK boleh diubah mahasiswa.
//
// PRINSIP PENILAIAN (behavior-based):
//   Checker hanya memanggil fungsi mahasiswa lalu memeriksa akibatnya: isi dan
//   urutan daftar setelah pemanggilan, nilai yang dikembalikan, node yang
//   ditunjuk, dan apakah memori node yang dilepas benar-benar dibebaskan.
//   Nama variabel, gaya penulisan pointer, jenis loop, urutan kode, komentar,
//   dan formatting tidak pernah diperiksa. Implementasi apa pun yang memenuhi
//   kontrak di student.h akan PASS.
//
// BOBOT:
//   20 test case, bobot rata 100 / 20 = 5 poin per test (lihat report.h).
//
//   Pertemuan ini hanya punya SATU soal, yaitu study case antrean loket klinik
//   "Sehat Selalu". Keempat fungsi di bawah adalah pekerjaan di dalam study
//   case yang sama, bukan soal yang berdiri sendiri-sendiri. Masing-masing
//   tetap diberi suite terpisah supaya nilai parsial tetap dapat.
//
//     Soal 1  tambahAkhir   6 test = 30   pasien mengantre di belakang
//     Soal 2  posisi        5 test = 25   berapa orang di depan saya
//     Soal 3  hapus         6 test = 30   pasien membatalkan antrean
//     Soal 4  clear         3 test = 15   loket tutup, antrean dibubarkan
//
//   Tiga fungsi lain (tambahAwal, panjang, cari) SUDAH DISEDIAKAN lengkap di
//   src/student.cpp dan TIDAK dinilai. Checker tidak mengujinya, dan tidak
//   memakainya untuk membangun daftar uji.
//
// SOAL SALING BEBAS:
//   Daftar untuk pengujian dibangun oleh checker sendiri (lihat buatList),
//   bukan lewat fungsi mahasiswa. Dengan begitu Soal 1 yang salah tidak ikut
//   menjatuhkan nilai Soal 2 sampai 4.
//
// PEMERIKSAAN PEMBEBASAN MEMORI:
//   Checker mengganti operator new/delete global agar dapat menghitung berapa
//   blok memori dinamis yang masih hidup. Angka itu hanya dibaca sebagai SELISIH
//   pada potongan kode yang sangat pendek (persis sebelum dan sesudah satu
//   pemanggilan fungsi mahasiswa), sehingga alokasi milik checker sendiri tidak
//   ikut terhitung. Ini tetap pengujian perilaku: yang diuji adalah "node yang
//   dilepas benar-benar dibebaskan", bukan cara penulisan kodenya.
//
// KETAHANAN TERHADAP CRASH:
//   Linked list rawan membuat program berhenti tidak wajar di sisi mahasiswa
//   (mis. menelusuri node yang sudah dihapus). Karena itu checker menyimpan
//   snapshot result.json setiap kali satu test selesai, dengan test yang belum
//   sempat berjalan dicatat sebagai FAIL. Nilai parsial yang sudah diperoleh
//   tetap tercatat dan tidak berubah menjadi 0. Penelusuran di dalam checker
//   juga dibatasi jumlah langkahnya supaya daftar yang tidak berujung tidak
//   menggantung selamanya. Mekanisme grading global (report.h, scripts/,
//   workflow, skema result.json) tidak diubah sama sekali.
//
// CATATAN KEAMANAN:
//   Mahasiswa dapat membaca file ini. Mitigasi:
//   - Setiap kontrak diuji dengan beberapa bentuk daftar (kosong, satu node,
//     beberapa node) dan beberapa posisi (depan, tengah, belakang)
//   - Repository mahasiswa bersifat privat
// =============================================================================

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <new>
#include <sstream>
#include <string>
#include <vector>
#include "report.h"
#include "../src/student.h"

using namespace std;

// =============================================================================
// Penghitung blok memori dinamis yang masih hidup
// =============================================================================
// Mengganti operator new/delete global adalah cara yang sah dalam C++ dan
// berlaku untuk seluruh program, termasuk `new Node` di dalam student.cpp.

static long long g_blokHidup = 0;

void* operator new(size_t ukuran) {
    if (ukuran == 0) ukuran = 1;
    void* blok = malloc(ukuran);
    if (blok == nullptr) throw bad_alloc();
    ++g_blokHidup;
    return blok;
}

void* operator new[](size_t ukuran) {
    return ::operator new(ukuran);
}

void operator delete(void* blok) noexcept {
    if (blok != nullptr) {
        --g_blokHidup;
        free(blok);
    }
}

void operator delete[](void* blok) noexcept {
    ::operator delete(blok);
}

void operator delete(void* blok, size_t) noexcept {
    ::operator delete(blok);
}

void operator delete[](void* blok, size_t) noexcept {
    ::operator delete(blok);
}

static long long blokHidup() {
    return g_blokHidup;
}

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
static const int TOTAL_TEST_DIRENCANAKAN = 20;

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
// Utilitas daftar milik checker
// =============================================================================
// Batas langkah penelusuran. Daftar mahasiswa yang tidak pernah berujung
// (mis. sebuah node menunjuk kembali ke node sebelumnya) tidak boleh membuat
// checker menggantung selamanya.
static const int BATAS_TELUSUR = 100000;

// Membangun daftar uji tanpa memakai fungsi mahasiswa, supaya setiap soal
// dinilai berdiri sendiri.
static Node* buatList(const int* nilai, int n) {
    Node* head = nullptr;
    Node* ekor = nullptr;
    for (int i = 0; i < n; ++i) {
        Node* baru = new Node;
        baru->data = nilai[i];
        baru->next = nullptr;
        if (ekor == nullptr) {
            head = baru;
        } else {
            ekor->next = baru;
        }
        ekor = baru;
    }
    return head;
}

// Membebaskan daftar uji setelah sebuah test selesai. Memakai penelusuran
// checker sendiri, bukan clear() mahasiswa.
static void bebaskanList(Node*& head) {
    int langkah = 0;
    while (head != nullptr && langkah++ < BATAS_TELUSUR) {
        Node* berikut = head->next;
        delete head;
        head = berikut;
    }
    head = nullptr;
}

// Banyaknya node menurut penelusuran checker; -1 bila daftar tidak berujung.
static int hitungNode(Node* head) {
    int n = 0;
    for (Node* p = head; p != nullptr; p = p->next) {
        if (++n > BATAS_TELUSUR) return -1;
    }
    return n;
}

// Node ke-`indeks` (0 = elemen pertama), atau nullptr bila di luar jangkauan.
static Node* nodeKe(Node* head, int indeks) {
    Node* p = head;
    for (int i = 0; i < indeks && p != nullptr; ++i) p = p->next;
    return p;
}

// Isi dan urutan daftar harus sama persis dengan `nilai`, tidak kurang dan
// tidak lebih, serta harus berakhir pada nullptr.
static bool listCocok(Node* head, const int* nilai, int n) {
    Node* p = head;
    for (int i = 0; i < n; ++i) {
        if (p == nullptr) return false;
        if (p->data != nilai[i]) return false;
        p = p->next;
    }
    return p == nullptr;
}

static string listKeString(Node* head) {
    if (head == nullptr) return "(kosong)";
    ostringstream out;
    int n = 0;
    for (Node* p = head; p != nullptr; p = p->next) {
        if (n > 0) out << " -> ";
        out << p->data;
        if (++n >= 40) { out << " -> ..."; break; }
    }
    return out.str();
}

static string arrayKeString(const int* nilai, int n) {
    if (n <= 0) return "(kosong)";
    ostringstream out;
    for (int i = 0; i < n; ++i) {
        if (i > 0) out << " -> ";
        out << nilai[i];
    }
    return out.str();
}



// =============================================================================
// SOAL 1b — tambahAkhir  (4 test = 16 poin)
// =============================================================================

void test_tambah_akhir() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] Soal 1 — tambahAkhir()   (pasien mengantre di belakang)" << COLOR_RESET << endl;

    {   // Daftar kosong -> data baru sekaligus menjadi elemen pertama.
        Node* head = nullptr;
        bool kembalian = tambahAkhir(head, 10);
        const int harapan[] = {10};
        bool benar = kembalian && listCocok(head, harapan, 1);

        ostringstream pesan;
        pesan << "Expected: 10 dengan kembalian true, Got: " << listKeString(head)
              << " dengan kembalian " << (kembalian ? "true" : "false");
        RUN_TEST("tambahAkhir pada daftar kosong menghasilkan daftar berisi 10",
                 benar, pesan.str());
        bebaskanList(head);
    }

    {   // Daftar berisi satu data.
        const int awal[] = {10};
        Node* head = buatList(awal, 1);
        bool kembalian = tambahAkhir(head, 20);
        const int harapan[] = {10, 20};
        bool benar = kembalian && listCocok(head, harapan, 2);

        ostringstream pesan;
        pesan << "Expected: " << arrayKeString(harapan, 2) << ", Got: "
              << listKeString(head);
        RUN_TEST("tambahAkhir pada daftar satu node: 10 + 20 di belakang -> 10 -> 20",
                 benar, pesan.str());
        bebaskanList(head);
    }

    {   // Daftar berisi beberapa data; daftar harus tetap berakhir dengan benar.
        const int awal[] = {10, 20, 30};
        Node* head = buatList(awal, 3);
        bool kembalian = tambahAkhir(head, 40);
        const int harapan[] = {10, 20, 30, 40};
        bool benar = kembalian && listCocok(head, harapan, 4);

        ostringstream pesan;
        pesan << "Expected: " << arrayKeString(harapan, 4)
              << " dan berakhir setelah elemen terakhir, Got: "
              << listKeString(head);
        RUN_TEST("tambahAkhir pada 10 -> 20 -> 30 menghasilkan 10 -> 20 -> 30 -> 40",
                 benar, pesan.str());
        bebaskanList(head);
    }

    {   // Membangun daftar dari kosong hanya dengan tambahAkhir, termasuk nilai
        //   negatif, nol, dan nilai berulang.
        long long sebelum = blokHidup();
        Node* head = nullptr;
        tambahAkhir(head, 5);
        tambahAkhir(head, -3);
        tambahAkhir(head, 5);
        tambahAkhir(head, 0);
        long long sesudah = blokHidup();

        const int harapan[] = {5, -3, 5, 0};
        bool urutanBenar = listCocok(head, harapan, 4);
        bool nodeBaru = (sesudah - sebelum) >= 4;

        ostringstream pesan;
        pesan << "Expected: " << arrayKeString(harapan, 4)
              << " dan empat node baru dialokasikan, Got: " << listKeString(head)
              << " dengan " << (sesudah - sebelum) << " node baru";
        RUN_TEST("tambahAkhir berturut-turut (5, -3, 5, 0) menjaga urutan masuk",
                 urutanBenar && nodeBaru, pesan.str());
        bebaskanList(head);
    }
    {   // Antrean panjang dibangun satu per satu. Yang diuji: `head` TIDAK
        //   boleh bergeser sesudah pasien pertama, dan urutan masuk terjaga
        //   sampai node terakhir.
        Node* head = nullptr;
        const int isi[] = {21, 47, 33, 58, 62, 70, 84, 99};

        tambahAkhir(head, isi[0]);
        Node* terdepan = head;              // dicatat sesudah pasien pertama

        bool semua = true;
        for (int i = 1; i < 8; ++i) {
            if (!tambahAkhir(head, isi[i])) semua = false;
        }

        bool headTetap = (head == terdepan);
        bool isiBenar = listCocok(head, isi, 8);
        bool ujungBenar = (nodeKe(head, 7) != nullptr
                           && nodeKe(head, 7)->next == nullptr);

        bool benar = semua && headTetap && isiBenar && ujungBenar;

        ostringstream pesan;
        pesan << "Expected: " << arrayKeString(isi, 8)
              << " dengan head tetap menunjuk pasien pertama dan node terakhir "
                 "next=nullptr; Got: " << listKeString(head)
              << ", headTetap=" << (headTetap ? "ya" : "tidak")
              << ", ujungNullptr=" << (ujungBenar ? "ya" : "tidak");
        RUN_TEST("tambahAkhir pada antrean panjang tidak menggeser head dan "
                 "menutup ujung dengan nullptr",
                 benar, pesan.str());
        bebaskanList(head);
    }

    {   // Setiap pemanggilan harus menyediakan TEPAT satu node, tidak lebih.
        Node* head = nullptr;

        long long sebelum = blokHidup();
        bool semua = true;
        for (int i = 0; i < 5; ++i) {
            if (!tambahAkhir(head, i * 10)) semua = false;
        }
        long long sesudah = blokHidup();

        const int harapan[] = {0, 10, 20, 30, 40};
        long long dibuat = sebelum - sesudah;
        bool benar = semua && listCocok(head, harapan, 5) && (dibuat == -5);

        ostringstream pesan;
        pesan << "Expected: " << arrayKeString(harapan, 5)
              << " dengan tepat 5 node baru; Got: " << listKeString(head)
              << ", node baru: " << (-dibuat);
        RUN_TEST("tambahAkhir menyediakan tepat satu node baru per pemanggilan",
                 benar, pesan.str());
        bebaskanList(head);
    }

}



// =============================================================================
// SOAL 3a — hapus  (5 test = 20 poin)
// =============================================================================

void test_hapus() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] Soal 3 — hapus()         (pasien membatalkan antrean)" << COLOR_RESET << endl;

    {   // Menghapus elemen pertama: daftar pemanggil harus mengenali elemen
        //   pertamanya yang baru.
        const int awal[] = {10, 20, 30, 40};
        Node* head = buatList(awal, 4);
        bool kembalian = hapus(head, 10);
        const int harapan[] = {20, 30, 40};
        bool benar = kembalian && listCocok(head, harapan, 3);

        ostringstream pesan;
        pesan << "Expected: " << arrayKeString(harapan, 3)
              << " dengan kembalian true, Got: " << listKeString(head)
              << " dengan kembalian " << (kembalian ? "true" : "false");
        RUN_TEST("hapus(10) pada 10 -> 20 -> 30 -> 40 menghasilkan 20 -> 30 -> 40",
                 benar, pesan.str());
        bebaskanList(head);
    }

    {   // Menghapus elemen tengah dan elemen terakhir. Yang tengah menguji
        //   hubungan antar node tidak putus; yang terakhir menguji daftar
        //   berakhir dengan benar pada elemen terakhirnya yang baru.
        //
        //   Pembebasan memori ikut diperiksa DI SINI, bukan cuma pada test
        //   kemunculan-pertama di bawah. Test itu menghapus node HEAD, sehingga
        //   kebocoran pada jalur node TENGAH — jalur yang justru paling sering
        //   salah — tidak akan tertangkap olehnya.
        const int awalTengah[] = {10, 20, 30, 40};
        Node* tengah = buatList(awalTengah, 4);
        long long sebelumTengah = blokHidup();
        bool kembalianTengah = hapus(tengah, 30);
        long long sesudahTengah = blokHidup();
        const int harapanTengah[] = {10, 20, 40};
        bool tengahBebas = (sebelumTengah - sesudahTengah) >= 1;
        bool tengahBenar = kembalianTengah && listCocok(tengah, harapanTengah, 3)
                        && tengahBebas;

        const int awalBelakang[] = {10, 20, 30};
        Node* belakang = buatList(awalBelakang, 3);
        bool kembalianBelakang = hapus(belakang, 30);
        const int harapanBelakang[] = {10, 20};
        bool belakangBenar = kembalianBelakang
                          && listCocok(belakang, harapanBelakang, 2)
                          && (hitungNode(belakang) == 2);

        ostringstream pesan;
        pesan << "Expected: " << arrayKeString(harapanTengah, 3) << " dan "
              << arrayKeString(harapanBelakang, 2)
              << ", keduanya dengan kembalian true; Got: "
              << listKeString(tengah) << " (kembalian "
              << (kembalianTengah ? "true" : "false") << ") dan "
              << listKeString(belakang) << " (kembalian "
              << (kembalianBelakang ? "true" : "false") << ")"
              << ", node tengah dibebaskan: " << (tengahBebas ? "ya" : "tidak");
        RUN_TEST("hapus elemen tengah (30 dari 10 -> 20 -> 30 -> 40) dan elemen "
                 "terakhir (30 dari 10 -> 20 -> 30), node dibebaskan",
                 tengahBenar && belakangBenar, pesan.str());
        bebaskanList(tengah);
        bebaskanList(belakang);
    }

    {   // Menghapus satu-satunya node: daftar pemanggil menjadi kosong.
        const int awal[] = {10};
        Node* head = buatList(awal, 1);
        bool kembalian = hapus(head, 10);
        bool benar = kembalian && (head == nullptr);

        ostringstream pesan;
        pesan << "Expected: (kosong) dengan kembalian true, Got: "
              << listKeString(head) << " dengan kembalian "
              << (kembalian ? "true" : "false");
        RUN_TEST("hapus(10) pada daftar berisi 10 saja menghasilkan daftar kosong",
                 benar, pesan.str());
        bebaskanList(head);
    }

    {   // Data tidak tersedia dan daftar kosong -> false, tanpa perubahan.
        //   Penghapusan yang berhasil dipakai sebagai kontrol.
        const int awal[] = {10, 20, 30};
        Node* head = buatList(awal, 3);
        bool tidakAda = hapus(head, 99);
        bool utuhSetelahGagal = listCocok(head, awal, 3);

        Node* kosong = nullptr;
        bool dariKosong = hapus(kosong, 10);
        bool tetapKosong = (kosong == nullptr);

        bool kontrol = hapus(head, 20);
        const int harapanKontrol[] = {10, 30};
        bool kontrolBenar = kontrol && listCocok(head, harapanKontrol, 2);

        bool benar = (tidakAda == false) && utuhSetelahGagal
                  && (dariKosong == false) && tetapKosong && kontrolBenar;

        ostringstream pesan;
        pesan << "Expected: hapus(99) false dan daftar tetap "
              << arrayKeString(awal, 3)
              << ", hapus dari daftar kosong false dan tetap kosong, lalu "
                 "hapus(20) true menghasilkan "
              << arrayKeString(harapanKontrol, 2) << "; Got: hapus(99) "
              << (tidakAda ? "true" : "false") << ", hapus dari kosong "
              << (dariKosong ? "true" : "false") << ", daftar akhir "
              << listKeString(head);
        RUN_TEST("hapus data yang tidak tersedia dan hapus dari daftar kosong",
                 benar, pesan.str());
        bebaskanList(head);
    }

    {   // Hanya kemunculan pertama yang dikeluarkan, dan node yang dikeluarkan
        //   benar-benar dibebaskan dari memori.
        const int awal[] = {7, 3, 7};
        Node* head = buatList(awal, 3);

        long long sebelum = blokHidup();
        bool kembalian = hapus(head, 7);
        long long sesudah = blokHidup();

        const int harapan[] = {3, 7};
        bool isiBenar = kembalian && listCocok(head, harapan, 2);
        bool dibebaskan = (sebelum - sesudah) >= 1;

        ostringstream pesan;
        pesan << "Expected: " << arrayKeString(harapan, 2)
              << " dan node yang dihapus dibebaskan dari memori, Got: "
              << listKeString(head) << ", perubahan node hidup: "
              << (sesudah - sebelum);
        RUN_TEST("hapus(7) pada 7 -> 3 -> 7 hanya mengeluarkan kemunculan pertama "
                 "dan membebaskan nodenya",
                 isiBenar && dibebaskan, pesan.str());
        bebaskanList(head);
    }
    {   // Penghapusan BERANTAI sampai antrean habis. Tiap langkah menggeser
        //   head, ujung belakang, atau keduanya, sehingga penanda yang tidak
        //   konsisten pada satu langkah pasti ketahuan di langkah berikutnya.
        const int awal[] = {21, 47, 33};
        Node* head = buatList(awal, 3);

        bool a = hapus(head, 47);                 // di tengah
        const int sisa2[] = {21, 33};
        bool okA = a && listCocok(head, sisa2, 2);

        bool b = hapus(head, 21);                 // sekarang paling depan
        const int sisa1[] = {33};
        bool okB = b && listCocok(head, sisa1, 1);

        bool c = hapus(head, 33);                 // satu-satunya yang tersisa
        bool okC = c && (head == nullptr);

        bool benar = okA && okB && okC;

        ostringstream pesan;
        pesan << "Expected: 21 -> 33, lalu 33, lalu daftar kosong dengan head "
                 "nullptr; Got langkah terakhir: " << listKeString(head)
              << " (head " << (head == nullptr ? "nullptr" : "masih terisi")
              << "), kembalian " << (a ? "true" : "false") << "/"
              << (b ? "true" : "false") << "/" << (c ? "true" : "false");
        RUN_TEST("hapus berantai sampai antrean habis menjaga head tetap "
                 "konsisten di setiap langkah",
                 benar, pesan.str());
        bebaskanList(head);
    }

}

// =============================================================================
// SOAL 3b — clear  (2 test = 8 poin)
// =============================================================================

void test_clear() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] Soal 4 — clear()         (loket tutup)" << COLOR_RESET << endl;

    {   // Daftar berisi beberapa node: seluruh node harus dibebaskan dan daftar
        //   pemanggil menjadi kosong.
        const int awal[] = {10, 20, 30, 40, 50};
        Node* head = buatList(awal, 5);

        long long sebelum = blokHidup();
        clear(head);
        long long sesudah = blokHidup();

        bool menjadiKosong = (head == nullptr);
        bool semuaDibebaskan = (sebelum - sesudah) >= 5;

        ostringstream pesan;
        pesan << "Expected: daftar kosong dan 5 node dibebaskan, Got: "
              << listKeString(head) << ", node yang dibebaskan: "
              << (sebelum - sesudah);
        RUN_TEST("clear pada 10 -> 20 -> 30 -> 40 -> 50 mengosongkan daftar dan "
                 "membebaskan seluruh node",
                 menjadiKosong && semuaDibebaskan, pesan.str());
        bebaskanList(head);
    }

    {   // Daftar kosong dan pemanggilan berulang harus aman.
        //   Pemanggilan pada daftar berisi dipakai sebagai kontrol.
        Node* kosong = nullptr;
        clear(kosong);
        bool amanSaatKosong = (kosong == nullptr);

        const int awal[] = {10, 20, 30};
        Node* head = buatList(awal, 3);
        clear(head);
        clear(head);
        bool amanSaatBerulang = (head == nullptr);

        Node* kontrol = buatList(awal, 3);
        long long sebelum = blokHidup();
        clear(kontrol);
        long long sesudah = blokHidup();
        bool kontrolBenar = (kontrol == nullptr) && ((sebelum - sesudah) >= 3);

        ostringstream pesan;
        pesan << "Expected: aman pada daftar kosong, aman saat dipanggil dua "
                 "kali, lalu daftar berisi 3 node dikosongkan dan dibebaskan; "
                 "Got: kosong -> " << listKeString(kosong) << ", berulang -> "
              << listKeString(head) << ", kontrol -> " << listKeString(kontrol)
              << " dengan " << (sebelum - sesudah) << " node dibebaskan";
        RUN_TEST("clear aman pada daftar kosong dan saat dipanggil lebih dari sekali",
                 amanSaatKosong && amanSaatBerulang && kontrolBenar, pesan.str());
        bebaskanList(kosong);
        bebaskanList(head);
        bebaskanList(kontrol);
    }
    {   // Banyaknya node yang dibebaskan diperiksa TEPAT, bukan sekadar "ada
        //   yang dibebaskan". Pembebasan yang berhenti di tengah jalan
        //   tertangkap di sini.
        const int satu[] = {21};
        Node* h1 = buatList(satu, 1);
        long long a1 = blokHidup();
        clear(h1);
        long long a2 = blokHidup();
        bool okSatu = (h1 == nullptr) && ((a1 - a2) == 1);

        const int panjangIsi[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        Node* h2 = buatList(panjangIsi, 10);
        long long b1 = blokHidup();
        clear(h2);
        long long b2 = blokHidup();
        bool okPanjang = (h2 == nullptr) && ((b1 - b2) == 10);

        bool benar = okSatu && okPanjang;

        ostringstream pesan;
        pesan << "Expected: 1 node dibebaskan pada antrean satu orang dan 10 "
                 "node pada antrean sepuluh orang, keduanya dengan head "
                 "nullptr; Got: " << (a1 - a2) << " dan " << (b1 - b2)
              << ", head " << (h1 == nullptr ? "nullptr" : "terisi") << "/"
              << (h2 == nullptr ? "nullptr" : "terisi");
        RUN_TEST("clear membebaskan node dalam jumlah yang tepat, baik pada "
                 "antrean satu orang maupun antrean panjang",
                 benar, pesan.str());
    }

}

// =============================================================================
// Main
// =============================================================================

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

// =============================================================================
// SOAL 4 — posisi  (soal cerita, 5 test = 20 poin)
// =============================================================================
// Kembalian 0 dan -1 punya arti yang sangat berbeda: 0 berarti "ada, dan paling
// depan", -1 berarti "tidak ada sama sekali". Beberapa test di bawah sengaja
// menguji keduanya berdampingan supaya implementasi yang menukar keduanya
// pasti tertangkap.

void test_posisi() {
    cout << COLOR_CYAN << COLOR_BOLD
              << "\n[TEST SUITE] Soal 2 — posisi()        (berapa orang di depan saya)" << COLOR_RESET << endl;

    {   // Ketiga posisi pokok: paling depan, tengah, dan paling belakang.
        const int isi[] = {21, 47, 33, 58};
        Node* head = buatList(isi, 4);

        int depan = posisi(head, 21);
        int tengah = posisi(head, 47);
        int tengah2 = posisi(head, 33);
        int belakang = posisi(head, 58);

        bool benar = (depan == 0) && (tengah == 1) && (tengah2 == 2)
                     && (belakang == 3);

        ostringstream pesan;
        pesan << "Expected: 0, 1, 2, 3; Got: " << depan << ", " << tengah
              << ", " << tengah2 << ", " << belakang;
        RUN_TEST("posisi pada elemen pertama, tengah, dan terakhir",
                 benar, pesan.str());
        bebaskanList(head);
    }

    {   // Nomor yang tidak tersedia dan daftar kosong sama-sama -1. Nilai yang
        //   ADA disertakan sebagai pembanding, supaya implementasi yang selalu
        //   mengembalikan -1 tidak lolos test ini.
        const int isi[] = {21, 47, 33};
        Node* head = buatList(isi, 3);

        int tidakAda = posisi(head, 99);
        int terlaluKecil = posisi(head, 1);
        int kosong = posisi(nullptr, 21);
        int pembanding = posisi(head, 47);

        bool benar = (tidakAda == -1) && (terlaluKecil == -1) && (kosong == -1)
                     && (pembanding == 1);

        ostringstream pesan;
        pesan << "Expected: -1, -1, -1, dan 1 sebagai pembanding; Got: "
              << tidakAda << ", " << terlaluKecil << ", " << kosong << ", "
              << pembanding;
        RUN_TEST("posisi memberi -1 saat nomor tidak tersedia dan saat daftar "
                 "kosong",
                 benar, pesan.str());
        bebaskanList(head);
    }

    {   // Daftar satu node. Membedakan 0 ("ada, paling depan") dari -1
        //   ("tidak ada") pada daftar sependek mungkin.
        const int isi[] = {7};
        Node* head = buatList(isi, 1);

        int ada = posisi(head, 7);
        int tidakAda = posisi(head, 8);

        bool benar = (ada == 0) && (tidakAda == -1);

        ostringstream pesan;
        pesan << "Expected: 0 lalu -1; Got: " << ada << " lalu " << tidakAda;
        RUN_TEST("posisi pada daftar satu node membedakan 0 dari -1",
                 benar, pesan.str());
        bebaskanList(head);
    }

    {   // Nilai berulang: yang dihitung kemunculan PERTAMA, sama seperti cari.
        //   Ditambah nilai negatif dan nol.
        const int isi[] = {7, -3, 7, 0, 7};
        Node* head = buatList(isi, 5);

        int berulang = posisi(head, 7);
        int negatif = posisi(head, -3);
        int nol = posisi(head, 0);

        bool benar = (berulang == 0) && (negatif == 1) && (nol == 3);

        ostringstream pesan;
        pesan << "Expected: 0 (kemunculan pertama), 1, dan 3; Got: "
              << berulang << ", " << negatif << ", " << nol;
        RUN_TEST("posisi memakai kemunculan pertama, dan menerima nilai "
                 "negatif serta nol",
                 benar, pesan.str());
        bebaskanList(head);
    }

    {   // Dipanggil dua kali berturut-turut: hasilnya harus sama dan daftar
        //   tidak boleh berubah sedikit pun.
        const int isi[] = {5, 15, 25, 35, 45};
        Node* head = buatList(isi, 5);

        int pertama = posisi(head, 35);
        int kedua = posisi(head, 35);
        bool daftarUtuh = listCocok(head, isi, 5);

        bool benar = (pertama == 3) && (kedua == 3) && daftarUtuh;

        ostringstream pesan;
        pesan << "Expected: 3 pada kedua pemanggilan dan daftar tetap "
              << arrayKeString(isi, 5) << "; Got: " << pertama << " lalu "
              << kedua << ", daftar " << listKeString(head);
        RUN_TEST("posisi tidak mengubah daftar dan sama saat dipanggil dua kali",
                 benar, pesan.str());
        bebaskanList(head);
    }
}

static const Suite SUITES[] = {
    {"test_tambah_akhir", test_tambah_akhir, 6},
    {"test_posisi", test_posisi, 5},
    {"test_hapus", test_hapus, 6},
    {"test_clear", test_clear, 3},
};

// Batas waktu per suite. Longgar untuk runner CI yang sedang sibuk, tetapi
// mencegah loop tak berujung menggantungkan job sampai batas 6 jam GitHub.
static const int BATAS_DETIK_PER_SUITE = 10;

int main() {
    cout << COLOR_BOLD
              << "============================================" << endl;
    cout << " Praktikum Struktur Data C++ — Auto Checker" << endl;
    cout << " Pertemuan 3: Study Case Antrean Loket Klinik" << endl;
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
