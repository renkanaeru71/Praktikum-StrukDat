# 📚 Arsip Praktikum Struktur Data

Selamat datang di repositori **Arsip Praktikum Struktur Data**! 🚀

Dokumen dan repositori ini dibuat sebagai wadah dokumentasi, penyimpanan kode program, serta arsip pribadi selama mengikuti seluruh rangkaian praktikum mata kuliah **Struktur Data**. 

 Seluruh modul, tugas mingguan, proyek akhir, dan catatan teknis akan diorganisasi secara rapi di dalam repositori ini agar dapat diakses kembali dengan mudah di masa mendatang.

---

## 🎯 Tujuan Repositori

- 📂 **Arsip Digital:** Menyimpan semua tugas dan modul praktikum Struktur Data secara terstruktur.
- 💡 **Pemahaman Konsep:** Melatih dan mendalami implementasi struktur data (Array, Linked List, Stack, Queue, Tree, Graph, Sorting, Searching).
- 🛠️ **Version Control:** Menerapkan alur kerja Git dan GitHub secara konsisten selama perkuliahan.

---

## 💻 Panduan Penggunaan Git & GitHub via VS Code

Berikut adalah panduan praktis untuk mengambil repositori (clone) ke VS Code serta mengunggah perubahan (push) kembali ke GitHub.

---

### 📥 1. Cara Ambil Repo dari GitHub ke VS Code (Clone)

Metode ini digunakan saat Anda ingin mengunduh repositori dari GitHub ke komputer lokal untuk pertama kali.

#### Langkah-langkah:
1. **Salin URL Repositori:**
   - Buka repositori Anda di situs GitHub.
   - Klik tombol hijau **`Code`**.
   - Salin tautan HTTPS (contoh: `https://github.com/username/praktikum-struktur-data.git`).

2. **Kloning via VS Code:**
   - Buka aplikasi **Visual Studio Code**.
   - Tekan tombol `Ctrl + Shift + P` (atau `Cmd + Shift + P` di Mac) untuk membuka Command Palette.
   - Ketik `Git: Clone` lalu tekan **Enter**.
   - Tempel (paste) URL repositori yang sudah disalin, lalu tekan **Enter**.
   - Pilih folder penyimpanan di komputer Anda untuk menyimpan repositori tersebut.
   - Klik **Open** saat VS Code menanyakan apakah ingin membuka repositori yang baru dikloning.

---

### 📤 2. Cara Push Perubahan dari VS Code ke GitHub

Metode ini digunakan setelah Anda membuat, mengubah, atau menambahkan kode baru di VS Code dan ingin menyimpannya ke GitHub.

#### Langkah-langkah via Terminal (Command Line):

1. **Buka Terminal di VS Code:**
   - Tekan `Ctrl + \`` (atau menu **Terminal** > **New Terminal**).

2. **Cek Status Perubahan:**
   ```bash
   git status
   ```
   *Langkah ini untuk melihat berkas mana saja yang telah diubah atau ditambahkan.*

3. **Tambahkan Berkas ke Staging Area:**
   ```bash
   git add .
   ```
   *(Tanda titik `.` berarti menyertakan seluruh berkas yang baru atau mengalami perubahan).*

4. **Simpan Perubahan dengan Pesan Commit:**
   ```bash
   git commit -m "Menambahkan tugas modul 1 struktur data"
   ```
   *Sesuaikan pesan commit dengan perubahan yang Anda lakukan.*

5. **Kirim Perubahan ke GitHub (Push):**
   ```bash
   git push origin main
   ```
   *(Jika cabang utama Anda bernama `master`, gunakan `git push origin master`).*

---

#### Langkah-langkah via Antarmuka Visual (GUI) VS Code:

1. Klik ikon **Source Control** di bilah samping kiri (atau tekan `Ctrl + Shift + G`).
2. Masukkan pesan commit pada kolom teks di bagian atas (contoh: `Update modul praktikum`).
3. Klik tombol **Commit** (atau ikon centang `✓`).
4. Klik tombol **Publish Branch** atau **Sync Changes** untuk melakukan *push* ke GitHub.

---

## 🛠️ Alat dan Teknologi
- **Bahasa Pemrograman:** C++
- **Editor Teks:** Visual Studio Code
- **Version Control:** Git & GitHub

---
