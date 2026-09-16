# Praktikum Struktur Data C++ — Pertemuan 3

## Study Case: Antrean Loket Klinik "Sehat Selalu"

Repository ini dibuat otomatis oleh aplikasi praktikum. Setiap kali Anda
melakukan **push**, GitHub Actions akan mengompilasi kode Anda, menjalankan
test, dan mengirim nilainya ke aplikasi.

---

# Study Case

Pertemuan ini hanya punya **satu soal**, yaitu study case di bawah ini. Empat
pekerjaan yang Anda kerjakan semuanya berasal dari cerita yang sama — tidak ada
cerita baru lagi sesudahnya.

## Latar

Klinik Sehat Selalu baru memasang sistem antrean digital. Layarnya sudah
terpasang di ruang tunggu dan mesin nomornya sudah menyala, tetapi bagian
dalamnya masih kosong — belum ada satu pun yang benar-benar menyimpan siapa saja
yang sedang mengantre. Layarnya masih menampilkan angka nol terus.

Tugas Anda mengisi bagian dalam itu.

## Kenapa satu arah sudah cukup

Antrean dilayani dari depan ke belakang, satu per satu, dan tidak pernah mundur.
Petugas tidak pernah perlu bertanya "siapa yang ada **di depan** orang ini?" —
yang ia perlukan cuma satu, yaitu "siapa **berikutnya**".

Karena itu antrean disimpan sebagai **linked list tunggal**: tiap orang hanya
menyimpan alamat orang **sesudahnya**, dan tidak menyimpan apa pun tentang orang
sebelumnya.

```
    head
     |
    [21] -> [47] -> [33] -> [58] -> nullptr
     ^                        ^
 dilayani duluan         paling belakang
```

| Istilah | Artinya |
|---|---|
| `head` | Alamat orang **paling depan**. Cukup dengan memegang `head`, seluruh antrean bisa dicapai. |
| `next` | Alamat orang berikutnya. Orang **paling belakang** ditandai `next` bernilai `nullptr`. |
| `nullptr` | Alamat kosong. `head` bernilai `nullptr` berarti antrean sedang **kosong**. |

> **Perhatikan akibatnya.** Dari sebuah node, Anda hanya bisa bergerak **maju**.
> Tidak ada jalan pintas untuk mundur, dan **tidak ada penanda khusus untuk ujung
> belakang**. Satu-satunya yang Anda pegang cuma `head`. Sifat inilah yang
> membuat beberapa pekerjaan di bawah lebih menantang daripada kelihatannya.

## Satu pagi di loket

Berikut satu pagi di Klinik Sehat Selalu. **Empat langkah bertanda Soal adalah
pekerjaan yang harus Anda kerjakan.**

| # | Yang terjadi | Pekerjaan |
|---:|---|---|
| 1 | Pukul 07.00 loket buka. Pasien berdatangan, mengambil nomor, dan berdiri di posisi **paling belakang** antrean. | **Soal 1** `tambahAkhir` |
| 2 | Petugas melirik layar untuk tahu ada berapa orang yang menunggu. Datang juga pasien lansia yang didahulukan dan langsung ditempatkan di **paling depan**. | *sudah disediakan* (`panjang`, `tambahAwal`) |
| 3 | Seorang pasien bertanya, "Mbak, masih berapa orang lagi di depan saya?" | **Soal 2** `posisi` |
| 4 | Ada pasien yang membatalkan antreannya. Ia dikeluarkan, dan antreannya **tidak boleh putus**. | **Soal 3** `hapus` |
| 5 | Petugas membetulkan nomor seorang pasien yang salah ketik, jadi ia mencari data orang itu lebih dulu. | *sudah disediakan* (`cari`) |
| 6 | Pukul 12.00 jam layanan habis. Loket ditutup dan seluruh sisa antrean dibubarkan. | **Soal 4** `clear` |

Keempat pekerjaan bertanda **Soal** itulah seluruh isi pertemuan ini. Di bawah
nanti Anda tidak akan menemukan cerita baru, hanya **rincian teknis** tiap
pekerjaan.

### Yang sudah disediakan (tidak dinilai)

| Fungsi | Gunanya |
|---|---|
| `tambahAwal` | menyisipkan pasien prioritas di paling depan — **pembanding untuk Soal 1** |
| `panjang` | banyaknya orang yang sedang mengantre |
| `cari` | menemukan node seorang pasien |

Ketiganya sudah ditulis lengkap di `src/student.cpp`. Pakai `panjang` sesering
mungkin untuk memeriksa hasil kerja Anda sendiri.

---

## Tujuan Praktikum

Setelah pertemuan ini Anda diharapkan mampu:

- menjelaskan kapan penyimpanan satu arah sudah cukup, dan apa konsekuensinya;
- membentuk linked list tunggal dari keadaan kosong;
- memahami hubungan antar node melalui `next`, dan arti `nullptr` di ujungnya;
- menelusuri seluruh daftar dari node pertama sampai node terakhir;
- menambahkan data di akhir daftar tanpa penanda ujung;
- menghitung posisi sebuah data di dalam daftar;
- menghapus data pada berbagai posisi sambil menjaga rantai tetap utuh;
- menangani daftar kosong, daftar satu node, dan daftar beberapa node; dan
- membebaskan seluruh node dengan benar.

---

## Materi

| Konsep | Yang perlu Anda kuasai |
|---|---|
| Node | satu satuan penyimpanan: sebuah data + alamat penyusulnya |
| `head` | penanda node pertama; sekaligus penanda daftar kosong |
| `next` | hubungan antar node; `nullptr` menandai node terakhir |
| Daftar kosong | keadaan sah yang harus ditangani setiap operasi |
| Penelusuran | mengunjungi node berurutan dari node pertama |
| Tambah di akhir | ujung belakang harus **dicari** dulu — tidak dipegang siapa pun |
| Posisi | menelusuri sambil menghitung, dengan penanda "tidak ada" |
| Penghapusan | node pertama, node tengah, node terakhir, satu-satunya node |
| Pembebasan | node yang dilepas tidak boleh ditinggalkan di memori |

---

## Untuk Mahasiswa

### File yang Harus Dikerjakan

**Satu-satunya file yang dinilai adalah:**

```
src/student.cpp
```

Di bagian paling bawah `src/student.cpp` ada `main()`. Bagian itu memeragakan
seluruh pagi di loket, sehingga Anda bisa langsung melihat hasil kerja Anda
berjalan sebagai satu cerita utuh. `main()` tersebut **tidak ikut dinilai** dan
**bebas Anda ubah** sesukanya.

Jangan mengubah file lain. Perubahan pada `src/student.h`, `tests/checker.cpp`,
`tests/report.h`, atau `.github/workflows/` tidak akan membuat nilai Anda naik
dan dapat menyebabkan penilaian gagal.

### Contract / API

Checker memanggil fungsi Anda secara langsung, jadi baris-baris berikut wajib
persis seperti ini (sudah dideklarasikan di `src/student.h`):

```cpp
struct Node {
    int data;
    Node* next;
};

bool tambahAkhir(Node*& head, int data);   // Soal 1
int  posisi(Node* head, int data);         // Soal 2
bool hapus(Node*& head, int data);         // Soal 3
void clear(Node*& head);                   // Soal 4

// Sudah disediakan, TIDAK dinilai
bool  tambahAwal(Node*& head, int data);
int   panjang(Node* head);
Node* cari(Node* head, int data);
```

Yang **wajib sama**: nama `struct Node` beserta kedua field-nya, nama fungsi,
tipe parameter, dan tipe kembalian.

Yang **bebas Anda tentukan**: seluruh isi fungsi, nama variabel, jenis loop, mau
menambah fungsi bantu atau tidak.

### Aturan yang berlaku untuk seluruh pekerjaan

- Nomor antrean boleh **negatif**, boleh **nol**, dan boleh **muncul lebih dari
  sekali**.
- `head` bernilai `nullptr` berarti antrean sedang **kosong**. Itu keadaan yang
  sah, bukan kesalahan.
- Parameter bertanda `&` berarti `head` milik pemanggil ikut berubah. Tanpa tanda
  `&`, fungsi hanya menerima **salinan** alamat orang terdepan — salinan itu
  boleh digeser-geser untuk menelusuri, dan `head` milik pemanggil tetap aman.
- Setiap orang dibuat di memori dinamis dengan `new`, dan yang keluar dari
  antrean harus dibuang dengan `delete`.
- Tidak ada satu pun fungsi yang mencetak ke layar.
- Anda boleh menambahkan fungsi bantu sendiri.

---

# Soal 1 — `tambahAkhir` (30 poin)

> Langkah 1 pada cerita · pasien baru mengantre di belakang

Tempatkan seorang pasien baru di posisi **paling belakang** antrean. Seluruh
pasien yang sudah ada tetap berada di depannya dengan urutan yang sama persis,
dan sesudah pasien baru itu tidak ada lagi siapa-siapa.

> **Perhatikan kesulitannya.** Yang Anda pegang cuma `head`, yaitu orang paling
> depan. Tidak ada penanda apa pun ke ujung belakang antrean. Jadi sebelum bisa
> menaruh orang baru di belakang, Anda harus **menemukan** dulu di mana ujung
> belakang itu — dan satu-satunya cara adalah berjalan dari depan.
>
> Bandingkan dengan `tambahAwal` yang sudah disediakan. Fungsi itu cuma tiga
> baris, karena tempat yang dituju sudah langsung dipegang oleh `head`.
> Perbedaan panjang kedua fungsi itu bukan kebetulan — itulah harga dari linked
> list yang cuma bisa berjalan satu arah.

| Parameter | Artinya |
|---|---|
| `head` | Alamat orang paling depan, milik pemanggil. Bertanda `&`. Boleh `nullptr` |
| `data` | Nomor antrean pasien yang baru datang |
| *kembalian* | `true` bila pasien baru berhasil masuk antrean |

| Sebelum | Operasi | Sesudah |
|---|---|---|
| `21 -> 47 -> 33` | `tambahAkhir(head, 58)` | `21 -> 47 -> 33 -> 58` |
| `(kosong)` | `tambahAkhir(head, 21)` | `21` |

**Yang perlu diingat.**
- Pada antrean yang tadinya **kosong**, pasien baru sekaligus menjadi orang
  paling depan, sehingga `head` milik pemanggil **harus** ikut berubah.
- Pada antrean yang **sudah berisi**, `head` **tidak boleh** berpindah sama
  sekali. Ini kesalahan yang paling sering terjadi: `head` ikut ditulis tanpa
  syarat, dan antrean jadi terbalik.
- Nomor-nomor lama tidak boleh hilang dan urutannya tidak boleh berubah.
- `next` milik pasien baru harus bernilai `nullptr`. Lupa ini membuat antrean
  tidak pernah berujung, dan penelusuran apa pun sesudahnya berjalan selamanya.
- Setiap pemanggilan menyediakan **tepat satu** node baru.

---

# Soal 2 — `posisi` (25 poin)

> Langkah 3 pada cerita · "masih berapa orang lagi di depan saya?"

Hitung ada **berapa orang** yang masih mengantre di depan pasien bernomor `data`.

Kalau nomor itu kebetulan berada paling depan, berarti tidak ada satu pun orang
di depannya — jawabannya `0`. Kalau ia berada di urutan kedua, ada 1 orang di
depannya. Begitu seterusnya.

Bisa juga nomor yang ditanyakan ternyata tidak ada di antrean, misalnya karena
orangnya sudah dipanggil dan pergi. Dalam keadaan itu pertanyaannya tidak punya
jawaban, jadi kembalikan **-1**.

| Parameter | Artinya |
|---|---|
| `head` | Alamat orang paling depan. **Tanpa** tanda `&`. Boleh `nullptr` |
| `data` | Nomor antrean yang sedang ditanyakan |
| *kembalian* | Banyaknya orang **di depan** nomor itu, atau `-1` bila tidak ada |

**Contoh.** Antrean `21 -> 47 -> 33 -> 58`:

```
   21    47    33    58
    ^     ^     ^     ^
    0     1     2     3      <- berapa orang yang ada di depannya
```

| Operasi | Hasil | Kenapa |
|---|---:|---|
| `posisi(head, 21)` | `0` | paling depan, tidak ada yang mendahului |
| `posisi(head, 47)` | `1` | ada 1 orang di depannya |
| `posisi(head, 33)` | `2` | ada 2 orang di depannya |
| `posisi(head, 58)` | `3` | paling belakang |
| `posisi(head, 99)` | `-1` | nomor 99 tidak ada di antrean ini |
| `posisi(nullptr, 21)` | `-1` | antreannya sedang kosong |

**Yang perlu diingat.**
- Orang **pertama** hasilnya `0`, bukan `1`. Yang dihitung adalah orang yang
  berada di **depan** nomor itu.
- Nomor yang tidak ada hasilnya `-1`. **Jangan** mengembalikan `0`, karena `0`
  sudah punya arti sendiri, yaitu "berada paling depan". Kedua keadaan itu sangat
  berbeda dan kembaliannya tidak boleh tertukar.
- Antrean kosong hasilnya `-1`, dan program tidak boleh berhenti tidak wajar.
- Bila nomor yang sama muncul lebih dari sekali, yang dihitung adalah kemunculan
  **pertama**. Pada `7 -> 3 -> 7 -> 9`, `posisi(head, 7)` bernilai `0`, bukan `2`.
- Melihat antrean tidak boleh mengubahnya sedikit pun.

---

# Soal 3 — `hapus` (30 poin)

> Langkah 4 pada cerita · pasien membatalkan antreannya

Keluarkan pasien bernomor `data` dari antrean, lalu buang datanya dari memori
supaya tidak menumpuk sia-sia.

Bayangkan antrean ini seperti rangkaian gerbong kereta yang saling disambung.
Mengeluarkan satu gerbong di tengah bukan cuma soal melepas gerbong itu saja.
Gerbong yang ada di depannya dan gerbong yang ada di belakangnya harus
**disambung kembali** satu sama lain. Kalau lupa disambung, rangkaiannya putus di
situ — dan seluruh gerbong sesudahnya ikut hilang dari antrean, walaupun
sebenarnya masih ada di memori.

| Parameter | Artinya |
|---|---|
| `head` | Alamat orang paling depan, milik pemanggil. Bertanda `&` |
| `data` | Nomor antrean orang yang membatalkan |
| *kembalian* | `true` bila memang ada yang dikeluarkan, `false` bila tidak ada |

| Sebelum | Operasi | Sesudah | Keterangan |
|---|---|---|---|
| `21 -> 47 -> 33` | hapus `47` | `21 -> 33` | di tengah |
| `21 -> 47 -> 33` | hapus `21` | `47 -> 33` | `head` berpindah |
| `21 -> 47 -> 33` | hapus `33` | `21 -> 47` | paling belakang |
| `21` | hapus `21` | `(kosong)` | `head` jadi `nullptr` |

**Yang perlu diingat.**
- Bila yang keluar adalah orang **paling depan**, `head` milik pemanggil harus
  berpindah ke orang sesudahnya.
- Bila antrean hanya berisi satu orang dan dialah yang keluar, `head` menjadi
  `nullptr`.
- Bila yang keluar adalah orang **paling belakang**, orang sebelum dia menjadi
  yang terakhir dan `next` miliknya harus bernilai `nullptr`.
- Bila nomornya muncul lebih dari sekali, yang keluar **hanya** kemunculan
  pertama. Pada `7 -> 3 -> 7`, `hapus(head, 7)` menyisakan `3 -> 7`.
- Bila nomornya tidak ada, kembaliannya `false` dan antrean **tidak boleh berubah
  sedikit pun** — termasuk tidak boleh ada node yang terbuang.
- Orang yang keluar harus dibuang dengan `delete`, **tepat satu** node per
  penghapusan yang berhasil.
- Hati-hati: isi sebuah node tidak boleh dibaca lagi setelah node itu di-`delete`,
  termasuk `next`-nya.

---

# Soal 4 — `clear` (15 poin)

> Langkah 6 pada cerita · loket tutup, antrean dibubarkan

Bubarkan seluruh antrean sekaligus, sampai benar-benar kosong seperti keadaan
sebelum loket dibuka.

Perhatikan baik-baik kata "dibubarkan". Memutus sambungannya saja tidak cukup.
Anda memang bisa langsung membuat `head` bernilai `nullptr`, dan sekilas
antreannya akan terlihat kosong — tetapi seluruh data orangnya masih menumpuk di
memori, dan sekarang tidak ada satu pun yang bisa mencapainya lagi karena alamat
orang terdepannya sudah hilang. Keadaan seperti itu disebut **kebocoran memori**,
dan itu ikut dinilai.

| Parameter | Artinya |
|---|---|
| `head` | Alamat orang paling depan, milik pemanggil. Bertanda `&` |
| *kembalian* | Tidak ada (`void`) |

**Yang perlu diingat.**
- Setelah selesai, `head` milik pemanggil harus bernilai `nullptr`.
- **Seluruh** orang harus dibuang dengan `delete`, bukan hanya yang paling depan.
  Banyaknya node yang dibuang ikut dihitung checker secara **tepat**.
- Alamat orang berikutnya harus sudah disimpan **sebelum** sebuah node
  di-`delete`.
- Memanggil `clear` pada antrean yang **sudah** kosong adalah sah, dan
  memanggilnya dua kali berturut-turut juga harus aman.

---

## Batasan

- Hanya **empat** fungsi di `src/student.cpp` yang dinilai: `tambahAkhir`,
  `posisi`, `hapus`, dan `clear`. Tiga fungsi lain sudah disediakan dan tidak
  dinilai. `main()` di bagian paling bawah file itu bebas Anda ubah.
- `cin` hanya boleh dipakai di dalam `main()` tersebut, tidak di dalam
  fungsi-fungsi yang dinilai.
- Jangan mengubah `struct Node` maupun signature fungsi di `src/student.h`.
- Materi pertemuan ini terbatas pada **linked list tunggal**. Tidak diperlukan
  doubly linked list, circular linked list, stack, queue, pohon, maupun graf.
- Tidak perlu memakai container pustaka standar (`list`, `vector`, dan
  sejenisnya) — node harus benar-benar dibuat sendiri di memori dinamis.

---

## Penilaian Otomatis

Penilaian sepenuhnya berdasarkan **perilaku** program: checker memanggil fungsi
Anda, lalu memeriksa isi dan urutan antrean sesudahnya, nilai yang dikembalikan,
dan apakah node yang dilepas benar-benar dibebaskan.

Antrean untuk pengujian dibangun sendiri oleh checker, bukan lewat fungsi Anda.
Karena itu Soal 1 yang belum benar **tidak** ikut menjatuhkan nilai soal lain.

Total **20 test case**, masing-masing bernilai **5 poin**:

| Soal | Fungsi | Test | Bobot |
|---|---|---:|---:|
| 1 | `tambahAkhir` | 6 | 30 |
| 2 | `posisi` | 5 | 25 |
| 3 | `hapus` | 6 | 30 |
| 4 | `clear` | 3 | 15 |
| | **Total** | **20** | **100** |

| Kondisi | Score |
|---|---|
| Gagal compile | 0 |
| Sebagian test lolos | jumlah test lolos × 5 |
| Semua test lolos | 100 |

Setiap soal diuji dengan antrean kosong, antrean satu orang, antrean beberapa
orang, dan antrean panjang — serta pada posisi depan, tengah, dan belakang.
Mengerjakan sebagian soal tetap mendapat nilai.

Program yang berhenti tidak wajar di tengah penilaian tidak menghanguskan nilai
yang sudah terkumpul: test yang sudah lolos tetap dihitung, sisanya dianggap
gagal.

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
setelannya, jadi tidak ada yang perlu Anda konfigurasi.

**Lewat terminal.**

```bash
g++ -std=c++17 src/student.cpp -o latihan
./latihan
```

`main()` bawaan menjalankan **pagi di loket secara berurutan**, dan menampilkan
hasil tiap langkah berdampingan dengan jawaban yang benar.

> **Saran urutan pengerjaan.** Kerjakan Soal 1 lebih dulu, karena seluruh
> percobaan di `main()` memerlukan antrean yang sudah terisi.

> **Penting: `cin` hanya di dalam `main()`.**
> Jangan pernah menaruh `cin` di dalam keempat fungsi yang dinilai. Saat menilai,
> checker memanggil fungsi-fungsi itu tanpa memberi masukan apa pun, sehingga
> `cin` di sana membaca sampah — dan nilai Anda berubah-ubah setiap kali dinilai,
> dari kode yang sama persis. Penilaian menolak lebih awal kode yang melanggar
> aturan ini.

> **Kalau program berhenti mendadak** dengan pesan seperti `Segmentation fault`,
> artinya kode Anda menyentuh memori yang bukan haknya — paling sering karena
> membaca node yang sudah di-`delete`, atau menelusuri `next` dari `nullptr`.
> Perintah ini menunjukkan baris persisnya:
>
> ```bash
> g++ -std=c++17 -g -fsanitize=address src/student.cpp -o latihan && ./latihan
> ```

### Memeriksa Kebocoran Memori (opsional, sangat disarankan)

```bash
g++ -std=c++17 -fsanitize=address,leak -g src/student.cpp -o latihan_periksa
./latihan_periksa
```

Bila ada node yang bocor, program melaporkannya di akhir dengan keterangan
`LeakSanitizer: detected memory leaks`.

---

## Cara Menjalankan Test di Komputer Sendiri

Butuh `g++` yang mendukung C++17:

```bash
chmod +x scripts/run_tests.sh
./scripts/run_tests.sh
```

Alurnya sama persis dengan yang dijalankan GitHub Actions, termasuk cara
menghitung score.

Pada starter code yang belum diisi, compiler memunculkan peringatan
*unused parameter*. Itu wajar dan **tidak** mengurangi nilai.

---

## Cara Mengumpulkan

Tidak ada tombol "submit". **Push adalah pengumpulan.**

```bash
git clone https://github.com/<ORG>/praktikum-03-<username>.git
cd praktikum-03-<username>
# edit src/student.cpp
git add src/student.cpp
git commit -m "Kerjakan pertemuan 3"
git push
```

Lalu buka tab **Actions** di GitHub, atau lihat nilainya di aplikasi praktikum.

Anda boleh push berkali-kali. **Setiap percobaan tersimpan**, misalnya
30 → 70 → 100.

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
