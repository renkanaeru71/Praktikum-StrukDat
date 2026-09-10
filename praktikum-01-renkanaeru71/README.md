# Praktikum Struktur Data C++ — Pertemuan 1

## Dasar-Dasar Struktur Data C++

Repository ini dibuat otomatis oleh aplikasi praktikum. Setiap kali Anda
melakukan **push**, GitHub Actions akan mengompilasi kode Anda, menjalankan
test, dan mengirim nilainya ke aplikasi.

---

## Tujuan Pertemuan Ini

Pertemuan 1 adalah fondasi sebelum masuk ke Pointer, Linked List, Stack, Queue,
PTB, dan Graf. Yang dilatih di sini adalah satu ide dasar:

> **data** + **cara menyimpannya** + **operasi terhadap data** = **struktur data**

Array dan `struct` adalah bentuk penyimpanan paling sederhana. Semua soal di
bawah adalah *operasi* terhadap penyimpanan itu:

| Kelompok | Ide yang dilatih |
|---|---|
| **A. Operasi baca** | menelusuri (traversal) data tanpa mengubahnya |
| **B. Operasi ubah** | mengubah isi penyimpanan di tempat (in-place) |
| **C. Struct** | menyatukan beberapa nilai jadi satu satuan data, lalu mengolah kumpulannya |

Setelah pertemuan ini Anda akan melihat bahwa Stack, Queue, dan List pun cuma
"penyimpanan + sekumpulan operasi yang disepakati".

---

## Untuk Mahasiswa

### File yang Harus Dikerjakan

**Satu-satunya file yang dinilai adalah:**

```
src/student.cpp
```

Selain itu tersedia `src/main.cpp`, yaitu **runner latihan** untuk mencoba
implementasi Anda di komputer sendiri. File itu **tidak ikut dinilai** dan
**bebas Anda ubah** sesukanya — checker tidak memakainya sama sekali.

Jangan mengubah file lain. Perubahan pada `src/student.h`, `tests/checker.cpp`,
`tests/report.h`, atau `.github/workflows/` tidak akan membuat nilai Anda naik
dan dapat menyebabkan penilaian gagal.

### Kontrak / API

Checker memanggil fungsi Anda **secara langsung**, jadi nama dan signature
berikut wajib persis seperti ini (sudah dideklarasikan di `src/student.h`):

```cpp
struct Mahasiswa {
    string nama;
    int         nim;
    double      nilai;
};

int    hitungTotal(const int data[], int n);
double hitungRataRata(const int data[], int n);
int    cariMax(const int data[], int n);
int    cariIndeks(const int data[], int n, int target);
void   balikArray(int data[], int n);
int    hapusNilai(int data[], int n, int target);
double rataRataNilai(const Mahasiswa data[], int n);
int    indeksNilaiTertinggi(const Mahasiswa data[], int n);
int    hitungLulus(const Mahasiswa data[], int n, double kkm);
```

Yang **wajib sama**: nama fungsi, nama `struct Mahasiswa` beserta field-nya,
tipe parameter, dan tipe kembalian.

Yang **bebas Anda tentukan**: nama variabel lokal, jenis loop (`for`/`while`),
indentasi, komentar, urutan penulisan fungsi, dan boleh menambah fungsi helper
sendiri. Penilaian hanya melihat **hasil**, bukan bentuk kode.

Aturan umum untuk semua fungsi:

- `n` adalah banyaknya elemen valid di dalam `data`, tidak pernah negatif,
  tetapi **bisa 0** (array kosong).
- Parameter ber-`const` berarti isi array **tidak boleh** Anda ubah.
- Tanpa `const` berarti fungsi itu memang diminta mengubah array.

### Daftar Soal

#### Bagian A — Operasi Baca

**Soal 1 — `hitungTotal`**
Jumlahkan seluruh elemen array.
`{4, 8, 15}` → `27`. Bila `n == 0` → `0`.

**Soal 2 — `hitungRataRata`**
Rata-rata seluruh elemen, hasilnya **pecahan**.
`{5, 8}` → `6.5` (bukan `6` — hati-hati pembagian antar-`int` memotong pecahan).
Bila `n == 0` → `0.0` (jangan membagi dengan nol).

**Soal 3 — `cariMax`**
Nilai terbesar dalam array.
`{3, 17, 4, 9}` → `17`. Array bisa berisi **negatif semua**:
`{-9, -3, -70}` → `-3`, jadi jangan memulai kandidat maksimum dari `0`.
Bila `n == 0` → `0`.

**Soal 4 — `cariIndeks`** (pencarian sekuensial / *linear search*)
Indeks kemunculan **pertama** dari `target`, atau `-1` bila tidak ada.
`{7, 3, 7}` dengan target `7` → `0`.

#### Bagian B — Operasi Ubah (in-place)

**Soal 5 — `balikArray`**
Balik urutan isi array **di tempat**, tanpa mengembalikan nilai.
`{1, 2, 3, 4}` menjadi `{4, 3, 2, 1}`. Jumlah elemen ganjil juga harus benar:
`{5, -2, 9, 0, 7}` menjadi `{7, 0, 9, -2, 5}`. Bila `n <= 1`, array tidak berubah.

**Soal 6 — `hapusNilai`**
Hapus **semua** elemen yang sama dengan `target`, rapatkan sisanya ke depan
tanpa mengubah urutan relatifnya, lalu kembalikan **ukuran baru**.
`{5, 2, 5, 9}` dengan target `5` → array menjadi `{2, 9, ...}`, fungsi
mengembalikan `2`. Elemen di posisi ≥ ukuran baru dianggap sampah dan tidak
diperiksa, jadi tidak perlu dibersihkan. Bila target tidak ada, kembalikan `n`.

#### Bagian C — Struct

**Soal 7 — `rataRataNilai`**
Rata-rata field `nilai` dari sekumpulan mahasiswa. Bila `n == 0` → `0.0`.
Akses field dengan tanda titik: `data[i].nilai`.

**Soal 8 — `indeksNilaiTertinggi`**
Indeks mahasiswa dengan `nilai` tertinggi, atau `-1` bila `n == 0`.
Bila nilai tertingginya seri, kembalikan indeks yang **paling awal**.

**Soal 9 — `hitungLulus`**
Banyaknya mahasiswa dengan `nilai >= kkm`. Nilai yang **tepat sama** dengan
`kkm` dihitung **lulus**.

### Penilaian

25 test case, masing-masing bernilai **4 poin**, total **100**.

| Kondisi | Score |
|---|---|
| Gagal compile | 0 |
| Sebagian test lolos | jumlah test lolos × 4 |
| Semua test lolos | 100 |

Setiap fungsi diuji dengan beberapa kondisi: kasus normal, kasus batas
(array kosong, satu elemen), dan kasus khusus (semua negatif, ada duplikat,
nilai tepat di batas kelulusan). Mengerjakan sebagian soal tetap mendapat nilai.

### Cara Mengumpulkan

Tidak ada tombol "submit". **Push adalah pengumpulan.**

```bash
git clone https://github.com/<ORG>/praktikum-01-<username>.git
cd praktikum-01-<username>
# edit src/student.cpp
git add src/student.cpp
git commit -m "Kerjakan pertemuan 1"
git push
```

Lalu buka tab **Actions** di GitHub, atau lihat nilainya di aplikasi praktikum.

Anda boleh push berkali-kali. **Setiap percobaan tersimpan**, misalnya
40 → 72 → 100. Bergantung pada pengaturan tugas, yang dipakai adalah nilai
terbaik atau nilai terakhir.

### Membaca Hasil

| Status | Artinya |
|---|---|
| ✅ hijau | Semua test berhasil |
| ❌ merah | Ada test yang gagal atau compile error |

Klik run tersebut, lalu baca **Summary** — ada tabel nilai dan rincian setiap
test beserta keterangan kegagalannya (`Expected` vs `Got`).

| Step yang gagal | Penyebab |
|---|---|
| `Compile student.cpp` | Ada syntax/compile error di `student.cpp` |
| `Compile checker` | Nama atau signature fungsi tidak sesuai `student.h` |
| `Jalankan test & hitung score` | Kode berhasil dikompilasi tetapi hasilnya salah |

### Cara Menjalankan Program Anda (Runner Latihan)

`src/main.cpp` adalah program kecil yang memanggil fungsi-fungsi Anda supaya
Anda dapat melihat hasilnya langsung. Compile `student.cpp` bersama `main.cpp`:

```bash
g++ -std=c++17 src/student.cpp src/main.cpp -o latihan
./latihan
```

Runner ini **tidak ikut dinilai**, tidak dipakai checker, dan boleh Anda ubah
sebebasnya untuk mencoba data lain atau menambahkan percobaan Anda sendiri.

Selama sebuah fungsi belum Anda isi, bagian yang bersangkutan masih menampilkan
nilai sementara dari skeleton atau data yang belum berubah — itu wajar. Kerjakan
satu soal, jalankan lagi, lalu perhatikan bagian mana yang mulai berubah.

**Contoh keluaran ketika seluruh fungsi sudah benar:**

```
==========================================
 Runner Latihan — Dasar Struktur Data C++
 (file ini tidak ikut dinilai)
==========================================

[1] Data untuk Bagian A
    isi array                 : {4, 8, 15, 16, 23, 42}
    banyaknya elemen          : 6

[2] hitungTotal() & hitungRataRata()
    hitungTotal(...)          : 108
    hitungRataRata(...)       : 18
    hitungTotal(n = 0)        : 0
    hitungRataRata(n = 0)     : 0
    hitungRataRata({5, 8})    : 6.5

[3] cariMax()
    cariMax(array di atas)    : 42
    cariMax({-9,-3,-70,-12})  : -3

[4] cariIndeks()
    cariIndeks(..., 15)       : 2
    cariIndeks(..., 99)       : -1

[5] balikArray()
    sebelum                   : {1, 2, 3, 4, 5}
    sesudah                   : {5, 4, 3, 2, 1}

[6] hapusNilai(..., target 5)
    sebelum                   : {5, 2, 5, 9, 5, 1}
    ukuran baru               : 3
    isi yang tersisa          : {2, 9, 1}

[7] Data mahasiswa untuk Bagian C
    mahasiswa[0]              : Andi (nim 101, nilai 80)
    mahasiswa[1]              : Bela (nim 102, nilai 90)
    mahasiswa[2]              : Citra (nim 103, nilai 70)
    mahasiswa[3]              : Dedi (nim 104, nilai 60)

[8] Operasi pada kumpulan mahasiswa
    rataRataNilai(...)        : 75
    indeksNilaiTertinggi(...) : 1
    hitungLulus(kkm = 75)     : 2
    hitungLulus(kkm = 100.1)  : 0
    nilai tertinggi atas nama : Bela

==========================================
 Selesai. Silakan ubah file ini untuk
 mencoba percobaan Anda sendiri.
==========================================
```

### Menjalankan Test di Komputer Sendiri (opsional)

Butuh `g++` yang mendukung C++17:

```bash
chmod +x scripts/run_tests.sh
./scripts/run_tests.sh
```

Alurnya sama persis dengan yang dijalankan GitHub Actions.

Pada starter code yang belum diisi, compiler memunculkan peringatan
*unused parameter*. Itu wajar, hilang sendiri setelah parameter Anda pakai,
dan **tidak** mengurangi nilai.

---

## Untuk Instruktur

### Yang Diubah dari Template Umum

Hanya tiga berkas soal, sesuai prosedur di template umum:

1. **`src/student.h`** — kontrak: `struct Mahasiswa` + 9 fungsi Pertemuan 1.
2. **`src/student.cpp`** — starter/skeleton, semua badan fungsi berisi `TODO`
   dan mengembalikan nilai sementara yang sengaja salah.
3. **`tests/checker.cpp`** — 25 test case Pertemuan 1.

`.github/workflows/test.yml`, `tests/report.h`, `scripts/`, dan `.gitignore`
**tidak diubah sama sekali** dari template umum.

### Catatan Desain Test

- **25 test** dipilih supaya `100 / 25 = 4` poin bulat per test, sehingga
  `score = passed * 4` selalu bilangan bulat 0-100 (`report.h` membagi bobot
  rata, `checker.cpp` menghitung `passed * 100 / total`).
- **Behavior-based.** Checker hanya memanggil fungsi dan memeriksa nilai
  kembalian / isi array. Sudah diverifikasi bahwa implementasi bergaya sangat
  berbeda (rekursi, `vector`, `max_element`, penyapuan dari belakang)
  mendapat 100 yang sama dengan implementasi loop biasa.
- **Perbandingan `double` memakai toleransi** `1e-9`, sehingga urutan operasi
  aritmetika yang berbeda tidak membuat mahasiswa gagal.
- **Starter code mendapat 0/100**, bukan nilai gratis: nilai sementara pada
  stub sengaja dipilih agar tidak ada test edge-case yang lolos kebetulan.
- Coverage tiap fungsi: kasus normal, batas (`n == 0`, `n == 1`), dan kasus
  jebakan yang umum (pembagian `int`, kandidat maksimum diawali `0`, duplikat,
  nilai tepat di ambang `kkm`).

Verifikasi lokal sebelum dipakai:

```bash
./scripts/run_tests.sh     # starter  -> 0/100
                           # solusi   -> 100/100
```

### Hasil yang Dapat Dibaca Mesin

Checker menulis `result.json` di root repository, lalu workflow mengunggahnya
sebagai artifact bernama **`grading-result`**. Aplikasi praktikum mengunduh
artifact itu memakai GitHub App — nilai tidak pernah disimpulkan dari teks log.

```json
{
  "schema_version": 1,
  "score": 100,
  "passed": 25,
  "total": 25,
  "status": "PASS",
  "commit_sha": "...",
  "timestamp": "2026-08-14T10:00:00Z",
  "tests": [
    { "name": "hitungTotal({4,8,15,16,23,42}) == 108", "status": "PASS", "points": 4.00, "message": "" }
  ]
}
```

Bila compile gagal atau checker crash, `scripts/write_error_result.sh` menulis
`result.json` berstatus `ERROR` dengan score 0, sehingga percobaan tersebut
tetap tercatat dan terlihat oleh asisten.

Bila menambah test suite baru, jangan ubah bentuk JSON-nya. Kalau memang harus
berubah, naikkan `schema_version` dan sesuaikan
`src/lib/grading/result.ts` di aplikasi.

### Catatan Keamanan

Mahasiswa dapat membaca `tests/checker.cpp` di repository-nya sendiri, dan
karena punya akses `push`, secara teknis dapat menyuntingnya.

Mitigasi yang sudah diterapkan:

- Setiap fungsi diuji dengan beberapa input berbeda, bukan satu nilai saja.
- Repository mahasiswa selalu privat.
- Workflow tidak memakai secret apa pun, sehingga tidak ada yang bisa dicuri.

Mitigasi lanjutan yang direkomendasikan (lihat README utama aplikasi):
bandingkan SHA berkas terkunci terhadap template, lalu tandai submission yang
berbeda.

---

## Struktur Repository

```
.
├── .github/workflows/test.yml     ← workflow penilaian (jangan diubah)
├── src/
│   ├── student.h                  ← kontrak/interface (jangan diubah)
│   ├── student.cpp                ← KERJAKAN DI SINI ←
│   └── main.cpp                   ← runner latihan (tidak dinilai, bebas diubah)
├── tests/
│   ├── checker.cpp                ← test instruktur (jangan diubah)
│   └── report.h                   ← penulis result.json (jangan diubah)
├── scripts/
│   ├── run_tests.sh               ← uji lokal
│   ├── job_summary.py             ← Job Summary dari result.json
│   └── write_error_result.sh      ← result.json saat compile error
└── README.md
```
