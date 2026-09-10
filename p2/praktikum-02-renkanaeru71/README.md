# Praktikum Struktur Data C++ — Pertemuan 2

## Pointer

Repository ini dibuat otomatis oleh aplikasi praktikum. Setiap kali Anda
melakukan **push**, GitHub Actions akan mengompilasi kode Anda, menjalankan
test, dan mengirim nilainya ke aplikasi.

---

## Tujuan Praktikum

Di Pertemuan 1 Anda mengolah data lewat array dan `struct`. Selama itu, setiap
fungsi hanya menerima **nilai** — dan nilai yang diterima sebuah fungsi adalah
salinan. Perubahan pada salinan tidak pernah terasa oleh pemanggilnya.

Pertemuan ini membahas cara kerja yang berbeda: bukan mengirim nilainya,
melainkan **mengirim keterangan di mana data itu berada**. Dengan itu sebuah
fungsi bisa membaca dan mengubah data yang bukan miliknya, serta menunjuk
bagian tertentu dari sebuah blok data.

Ada tiga soal, dan ketiganya menjawab satu pertanyaan yang berbeda:

1. **`tukarNilai`** — bagaimana sebuah fungsi mengubah data milik pemanggilnya?
2. **`cariElemen`** — bagaimana sebuah fungsi memberi tahu *di mana* sesuatu
   berada, bukan sekadar *apa* isinya?
3. **`perbaruiSensor`** — bagaimana caranya kalau yang ditunjuk bukan satu
   angka, melainkan sebuah `struct`?

Yang ketiga itulah yang nanti menjadi `Node` pada Linked List.

---

## Untuk Mahasiswa

### File yang Harus Dikerjakan

**Satu-satunya file yang dinilai adalah:**

```
src/student.cpp
```

Di bagian paling bawah `src/student.cpp` ada `main()`. Bagian itu membuat file
ini menjadi program C++ utuh yang bisa langsung Anda jalankan untuk mencoba
implementasi Anda — dan `main()` tersebut **tidak ikut dinilai**, jadi **bebas
Anda ubah** sesukanya. Checker tidak memakainya sama sekali.

Jangan mengubah file lain. Perubahan pada `src/student.h`, `tests/checker.cpp`,
`tests/report.h`, atau `.github/workflows/` tidak akan membuat nilai Anda naik
dan dapat menyebabkan penilaian gagal.

### Contract / API

Checker memanggil fungsi Anda secara langsung, jadi baris-baris berikut wajib
persis seperti ini (sudah dideklarasikan di `src/student.h`):

```cpp
void  tukarNilai(int* a, int* b);
int*  cariElemen(int* data, int n, int target);

struct Sensor {
    int suhuTerakhir;
    int suhuTertinggi;
    int totalPembacaan;
};
void  perbaruiSensor(Sensor* sensor, int suhuBaru);
```

Yang **wajib sama**: nama fungsi, nama `struct Sensor` beserta field-nya, tipe
parameter, dan tipe kembalian.

Yang **bebas Anda tentukan**: seluruh isi fungsi, nama variabel, jenis loop,
mau memakai indeks atau tidak, mau menambah fungsi bantu atau tidak. Penilaian
hanya melihat akibat yang teramati oleh pemanggil.

### Istilah yang Dipakai di Seluruh Soal

| Istilah | Artinya |
|---|---|
| **pemanggil** | Kode di luar yang memanggil fungsi Anda — checker saat menilai, atau `main()` di bagian bawah `student.cpp` saat Anda mencoba sendiri. Dialah pemilik datanya, bukan fungsi Anda. |
| **alamat** | Nilai bertipe pointer, misalnya `int*`. Isinya bukan sebuah angka, melainkan keterangan **di mana** sebuah angka disimpan. |
| **deret** | Sekumpulan angka yang tersimpan berurutan, seperti array. |
| `&x` | Alamat dari variabel `x`. |
| `*p` | Isi yang tersimpan di alamat `p` — dipakai untuk membaca maupun menulis. |

### Kondisi Input yang Berlaku untuk Semua Soal

- `n` adalah banyaknya angka pada sebuah deret. Nilainya selalu minimal 1, jadi
  deretnya tidak pernah kosong.
- **Seluruh parameter bertipe pointer selalu berisi alamat yang sah.** Tidak
  ada satu pun yang bisa bernilai `nullptr`, jadi Anda tidak perlu menulis
  pemeriksaan seperti `if (a == nullptr)` di mana pun.
- Seluruh nilai uji berada pada rentang `int` yang wajar; tidak ada test yang
  mengandalkan luapan bilangan.

---

## Daftar Soal

Penjelasan yang sama juga ada di `src/student.cpp`, tepat di atas masing-masing
fungsi, dengan empat bagian yang selalu sama:

| Bagian | Isinya |
|---|---|
| **Ceritanya** | Apa yang sedang terjadi, dan apa yang diminta |
| **Parameternya** | Arti setiap parameter, satu per satu |
| **Contoh** | Kode nyata beserta hasil yang benar |
| **Yang perlu diingat** | Hal khusus yang ikut dinilai |

Setiap soal menjelaskan **hasil yang harus tercapai**, bukan langkah-langkah
pengerjaannya — menentukan caranya adalah bagian dari latihan.

### Soal 1 — `tukarNilai` (30 poin)

**Ceritanya.** Pemanggil punya dua variabel dan ingin isi keduanya bertukar.
Yang ia serahkan ke fungsi ini bukan nilainya, melainkan **alamat** keduanya.
Setelah fungsi selesai, variabel **asli** milik pemanggil harus sudah bertukar
isinya — bukan cuma salinan sementara di dalam fungsi Anda.

**Parameternya.**

| Parameter | Artinya |
|---|---|
| `a` | Alamat variabel pertama milik pemanggil |
| `b` | Alamat variabel kedua milik pemanggil |
| *kembalian* | Tidak ada (fungsi bertipe `void`) |

**Contoh.**

```cpp
int x = 3, y = 8;
tukarNilai(&x, &y);
// sekarang x berisi 8, dan y berisi 3
```

**Yang perlu diingat.**
- `a` dan `b` selalu alamat yang sah, dan selalu menunjuk ke dua variabel yang
  berbeda.

---

### Soal 2 — `cariElemen` (30 poin)

**Ceritanya.** Pemanggil punya satu deret angka. Ia mencari sebuah angka di
dalamnya, lalu ingin **mengubah angka itu langsung di tempatnya**.

Kalau fungsi ini hanya memberi tahu nilainya, pemanggil tidak bisa mengubah
apa-apa — yang ia terima cuma salinan. Karena itu yang dikembalikan adalah
**alamat** elemen tersebut, sehingga pemanggil dapat menulis ke alamat itu dan
deret aslinya ikut berubah.

**Parameternya.**

| Parameter | Artinya |
|---|---|
| `data` | Deret angka tempat pencarian dilakukan |
| `n` | Banyaknya angka di `data` |
| `target` | Angka yang sedang dicari |
| *kembalian* | Alamat elemen **pertama** yang isinya sama dengan `target` |

**Contoh.**

```cpp
int data[] = {4, 9, 15, 9};
int* lokasi = cariElemen(data, 4, 15);
*lokasi = 77;
// sekarang data berisi {4, 9, 77, 9}
```

**Yang perlu diingat.**
- Bila angka yang dicari muncul lebih dari sekali, yang dikembalikan adalah
  alamat kemunculan **pertama**.

  ```cpp
  cariElemen(data, 4, 9);   // alamat data[1], bukan data[3]
  ```
- `target` dijamin ada di dalam `data`, jadi pencarian tidak pernah gagal.
  `n` juga dijamin minimal 1.
- `data` selalu alamat yang sah.

---

### Soal 3 — `perbaruiSensor` (40 poin)

**Ceritanya.** Pemanggil punya satu rekaman sensor. Rekaman itu menyimpan tiga
hal:

| Field | Artinya |
|---|---|
| `suhuTerakhir` | Suhu dari pembacaan yang paling akhir masuk |
| `suhuTertinggi` | Suhu tertinggi dari **seluruh** pembacaan yang pernah masuk |
| `totalPembacaan` | Sudah berapa kali pembacaan masuk ke rekaman ini |

Setiap kali ada satu pembacaan suhu baru, fungsi ini dipanggil untuk memperbarui
rekaman tersebut. Rekaman itu milik pemanggil, dan yang diserahkan ke fungsi ini
adalah alamatnya, sehingga perubahan Anda langsung terlihat oleh pemanggil.

Setelah fungsi selesai: `suhuTerakhir` berisi suhu yang baru saja masuk,
`totalPembacaan` bertambah satu, dan `suhuTertinggi` mencerminkan seluruh
pembacaan yang pernah masuk.

**Parameternya.**

| Parameter | Artinya |
|---|---|
| `sensor` | Alamat rekaman milik pemanggil |
| `suhuBaru` | Suhu dari pembacaan yang baru masuk |
| *kembalian* | Tidak ada (fungsi bertipe `void`) |

**Contoh.**

```cpp
Sensor s = {0, 0, 0};     // rekaman baru, belum pernah dipakai
perbaruiSensor(&s, 25);   // s menjadi {25, 25, 1}
perbaruiSensor(&s, 30);   // s menjadi {30, 30, 2}
perbaruiSensor(&s, 12);   // s menjadi {12, 30, 3}
                          //   suhu terakhir turun jadi 12,
                          //   tetapi tertinggi tetap 30
```

**Yang perlu diingat.**
- Rekaman selalu diserahkan dalam keadaan awal `{0, 0, 0}`, yaitu belum pernah
  menerima pembacaan sama sekali.
- `suhuBaru` tidak pernah negatif.
- `sensor` selalu alamat yang sah.

---

## Penilaian Otomatis

Penilaian sepenuhnya berdasarkan **perilaku** program: checker memanggil fungsi
Anda, lalu memeriksa isi data sesudahnya, nilai yang dikembalikan, dan lokasi
yang ditunjuk.

Yang **tidak** pernah diperiksa: nama variabel, gaya penulisan pointer,
formatting, indentasi, komentar, urutan penulisan fungsi, dan ada tidaknya
fungsi bantu. Dua implementasi yang berbeda jauh tetapi sama-sama memenuhi
kontrak akan sama-sama lolos.

Total **10 test case**, masing-masing bernilai **10 poin**. Bobot tiap soal
ditentukan oleh banyaknya test pada soal tersebut:

| Soal | Fungsi | Test | Bobot |
|---|---|---:|---:|
| 1 | `tukarNilai` | 3 | 30 |
| 2 | `cariElemen` | 3 | 30 |
| 3 | `perbaruiSensor` | 4 | 40 |
| | **Total** | **10** | **100** |

| Kondisi | Score |
|---|---|
| Gagal compile | 0 |
| Sebagian test lolos | jumlah test lolos × 10 |
| Semua test lolos | 100 |

Setiap soal diuji dengan kasus normal, variasi input (nilai negatif, nol, nilai
berulang), dan kasus batas (elemen pertama dan terakhir, deret berisi satu
angka, nilai tertinggi di tengah riwayat). Mengerjakan sebagian soal tetap
mendapat nilai.

Program yang berhenti tidak wajar di tengah penilaian — hal yang mudah terjadi
saat bekerja dengan alamat yang tidak valid — tidak menghanguskan nilai yang
sudah terkumpul: test yang sudah lolos sebelum berhenti tetap dihitung,
sedangkan sisanya dianggap gagal.

### Membaca Hasil

| Status | Artinya |
|---|---|
| ✅ hijau | Semua test berhasil |
| ❌ merah | Ada test yang gagal, compile error, atau program berhenti tidak wajar |

Klik run tersebut, lalu baca **Summary** — ada tabel nilai dan rincian setiap
test beserta keterangan `Expected` vs `Got`.

| Step yang gagal | Penyebab |
|---|---|
| `Periksa penggunaan cin` | Ada `cin`/`scanf` di dalam fungsi yang dinilai |
| `Compile student.cpp` | Ada syntax/compile error di `student.cpp` |
| `Compile checker` | Nama atau signature fungsi tidak sesuai `student.h`, atau `main()` Anda keluar dari blok `#ifndef ADA_MAIN_LAIN` |
| `Jalankan test & hitung score` | Kode berhasil dikompilasi tetapi perilakunya belum sesuai |

---

## Cara Menjalankan Program Anda

`src/student.cpp` adalah program C++ utuh. Ada `main()` di bagian paling
bawahnya, jadi Anda bisa menjalankannya seperti tugas C++ biasa.

**Lewat VS Code (paling gampang).** Buka `src/student.cpp`, lalu tekan **F5**
(Run and Debug) atau **Ctrl+F5** (jalankan tanpa debug). Repo ini sudah membawa
setelannya, jadi tidak ada yang perlu Anda konfigurasi. Program muncul di
terminal terintegrasi, dan `cin` bisa Anda ketik langsung di situ.

**Lewat terminal.**

```bash
g++ -std=c++17 src/student.cpp -o latihan
./latihan
```

`main()` bawaan memanggil ketiga fungsi Anda dengan data contoh, lalu
menampilkan data **milik pemanggil** — yaitu variabel di dalam `main()` itu
sendiri, bukan variabel di dalam fungsi Anda. Itulah inti materi pertemuan ini:
fungsi yang menerima alamat dapat mengubah data pemanggilnya.

`main()` itu **tidak ikut dinilai** dan boleh Anda ubah sebebasnya untuk
mencoba data lain atau menambahkan percobaan Anda sendiri. Di dalamnya juga
sudah ada contoh pemakaian `cin` yang tinggal Anda hapus tanda komentarnya.

Selama sebuah fungsi belum Anda isi, bagian yang bersangkutan masih menampilkan
nilai sementara dari skeleton atau data yang belum berubah — itu wajar. Kerjakan
satu soal, jalankan lagi, lalu perhatikan bagian mana yang mulai berubah.

> **Penting: `cin` hanya di dalam `main()`.**
> Jangan pernah menaruh `cin` di dalam ketiga fungsi yang dinilai. Saat
> menilai, checker memanggil fungsi-fungsi itu tanpa memberi masukan apa pun,
> sehingga `cin` di sana membaca sampah — dan nilai Anda berubah-ubah setiap
> kali dinilai, dari kode yang sama persis. Ketiga fungsi itu menerima datanya
> lewat **parameter**, bukan lewat `cin`. Penilaian menolak lebih awal kode
> yang melanggar aturan ini.

> **Kalau program berhenti mendadak** dengan pesan seperti
> `Segmentation fault`, artinya kode Anda menyentuh memori yang bukan haknya —
> di pertemuan ini paling sering karena melangkah keluar dari deret. Perintah
> ini menunjukkan baris persisnya:
>
> ```bash
> g++ -std=c++17 -g -fsanitize=address src/student.cpp -o latihan && ./latihan
> ```

**Contoh keluaran ketika seluruh fungsi sudah benar:**

```
==========================================
 Latihan — Pointer
 (bagian ini tidak ikut dinilai)
==========================================

[1] tukarNilai(&x, &y)
    sebelum                   : x = 7, y = 19
    sesudah                   : x = 19, y = 7

[2] cariElemen()
    sebelum                   : {3, 14, 15, 92, 65}
    cariElemen(..., 15)       : isinya 15
    sesudah *lokasi = 100     : {3, 14, 100, 92, 65}
    angka 8 muncul 2 kali     : menunjuk indeks 1 (seharusnya 1)

[3] perbaruiSensor()
    setelah suhu 25           : terakhir = 25, tertinggi = 25, total = 1
    setelah suhu 30           : terakhir = 30, tertinggi = 30, total = 2
    setelah suhu 12           : terakhir = 12, tertinggi = 30, total = 3

==========================================
 Selesai. Silakan ubah bagian ini untuk
 mencoba percobaan Anda sendiri.
==========================================
```

## Cara Menjalankan Test di Komputer Sendiri

Butuh `g++` yang mendukung C++17:

```bash
chmod +x scripts/run_tests.sh
./scripts/run_tests.sh
```

Alurnya sama persis dengan yang dijalankan GitHub Actions, termasuk cara
menghitung score.

Pada starter code yang belum diisi, compiler memunculkan peringatan
*unused parameter*. Itu wajar, hilang setelah parameter benar-benar Anda pakai,
dan **tidak** mengurangi nilai.

## Cara Mengumpulkan

Tidak ada tombol "submit". **Push adalah pengumpulan.**

```bash
git clone https://github.com/<ORG>/praktikum-02-<username>.git
cd praktikum-02-<username>
# edit src/student.cpp
git add src/student.cpp
git commit -m "Kerjakan pertemuan 2"
git push
```

Lalu buka tab **Actions** di GitHub, atau lihat nilainya di aplikasi praktikum.

Anda boleh push berkali-kali. **Setiap percobaan tersimpan**, misalnya
30 → 60 → 100. Bergantung pada pengaturan tugas, yang dipakai adalah nilai
terbaik atau nilai terakhir.

---

## Struktur Repository

```
.
├── .github/workflows/test.yml     ← workflow penilaian (jangan diubah)
├── .vscode/                       ← setelan tombol Run (jangan diubah)
├── src/
│   ├── student.h                  ← kontrak/interface (jangan diubah)
│   └── student.cpp                ← KERJAKAN DI SINI ← (main() ada di bawahnya)
├── tests/
│   ├── checker.cpp                ← test instruktur (jangan diubah)
│   └── report.h                   ← penulis result.json (jangan diubah)
├── scripts/
│   ├── run_tests.sh               ← uji lokal
│   ├── periksa_masukan.py         ← menolak cin di dalam fungsi yang dinilai
│   ├── anotasi_gcc.py             ← terjemahan error compiler ke bahasa Indonesia
│   ├── job_summary.py             ← Job Summary dari result.json
│   └── write_error_result.sh      ← result.json saat compile error
└── README.md
```
