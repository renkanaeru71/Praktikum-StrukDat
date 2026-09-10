// =============================================================================
// runner_util.h — Penopang Runner Latihan (BUKAN bagian dari penilaian)
// =============================================================================
// Anda TIDAK perlu membaca atau mengubah file ini untuk mengerjakan praktikum.
// File ini hanya membuat src/main.cpp tahan banting.
//
// MASALAH YANG DISELESAIKAN
// -------------------------
// Runner memanggil fungsi-fungsi Anda satu per satu dalam satu proses. Kode
// yang masih setengah jadi bukan cuma memberi jawaban salah — ia bisa MEMBUNUH
// proses. Contoh yang paling sering terjadi:
//
//   - indeks array melewati batas             -> SIGSEGV (Segmentation fault)
//   - fungsi non-void selesai tanpa `return`  -> SIGILL
//   - pembagian dengan nol saat n == 0        -> SIGFPE
//   - loop yang syarat berhentinya tak pernah tercapai -> menggantung
//
// Tanpa penanganan, satu kejadian di atas menghentikan SELURUH runner. Bagian
// setelahnya tidak pernah tercetak, sehingga soal yang sudah Anda kerjakan
// dengan benar pun tidak bisa Anda lihat hasilnya. Soal yang macet berubah
// menjadi gerbang yang menutup semua soal sesudahnya.
//
// CARA KERJA
// ----------
// Setiap bagian runner dijalankan di PROSES ANAK tersendiri. Bila anak mati,
// yang mati hanya anak itu: runner mencetak penjelasan tentang kesalahan
// pemrograman yang menyebabkannya, lalu LANJUT ke bagian berikutnya.
//
// Penjelasan sinyalnya sengaja dibuat sama persis dengan yang dipakai checker
// di tests/report.h, supaya pesan yang Anda lihat saat latihan di laptop sama
// dengan yang Anda lihat di hasil penilaian.
// =============================================================================

#ifndef RUNNER_UTIL_H
#define RUNNER_UTIL_H

#include <cstdio>
#include <iostream>
#include <string>

// fork(), alarm(), dan waitpid() adalah POSIX. Di Windows fasilitas ini tidak
// ada, jadi runner jatuh ke mode tanpa isolasi: tetap bisa dikompilasi dan
// dijalankan, hanya kembali rapuh terhadap crash seperti sebelumnya.
#if defined(_WIN32)
#  define RUNNER_ISOLASI 0
#else
#  define RUNNER_ISOLASI 1
#  include <cerrno>
#  include <csignal>
#  include <sys/wait.h>
#  include <unistd.h>
#endif

// -----------------------------------------------------------------------------
// Menerjemahkan sebab kematian proses menjadi kalimat yang berguna
// -----------------------------------------------------------------------------
// Inti dari isolasi: Anda tidak lagi cuma melihat "Segmentation fault",
// melainkan penjelasan tentang kesalahan pemrograman yang menyebabkannya.

inline std::string runner_alasan_sinyal(int sinyal, int batas_detik) {
#if RUNNER_ISOLASI
    switch (sinyal) {
        case SIGILL:
            return "Program berhenti mendadak (SIGILL). Penyebab paling umum: "
                   "ada fungsi bertipe kembalian non-void yang selesai tanpa "
                   "menjalankan `return`. Periksa setiap cabang if/else dan "
                   "ujung setiap fungsi.";
        case SIGSEGV:
            return "Program mengakses memori yang bukan haknya (SIGSEGV). "
                   "Penyebab paling umum: indeks array di luar batas "
                   "(mis. data[n] atau data[-1]), atau pointer bernilai "
                   "nullptr yang tetap di-dereference.";
        case SIGFPE:
            return "Terjadi pembagian dengan nol (SIGFPE). Periksa kasus "
                   "n == 0: lakukan pembagian hanya setelah memastikan "
                   "pembaginya bukan nol.";
        case SIGABRT:
            return "Program dihentikan paksa (SIGABRT), mis. karena assert "
                   "gagal, exception yang tidak tertangkap, atau kerusakan "
                   "memori yang terdeteksi pustaka standar.";
        case SIGBUS:
            return "Akses memori tidak selaras / tidak sah (SIGBUS). Periksa "
                   "penggunaan pointer dan indeks array.";
        case SIGALRM:
            return "Melebihi batas waktu " + std::to_string(batas_detik) +
                   " detik. Penyebab paling umum: loop yang syarat berhentinya "
                   "tidak pernah tercapai (variabel penghitung lupa dinaikkan, "
                   "atau pointer `next` tidak pernah maju).";
        default:
            return "Program dihentikan oleh sinyal " + std::to_string(sinyal) +
                   ".";
    }
#else
    (void)sinyal;
    (void)batas_detik;
    return "Program berhenti tidak wajar.";
#endif
}

// Nama pendek sinyal, dicetak sebagai judul supaya mudah dicari di internet.
inline std::string runner_nama_sinyal(int sinyal) {
#if RUNNER_ISOLASI
    switch (sinyal) {
        case SIGILL:  return "SIGILL";
        case SIGSEGV: return "SIGSEGV";
        case SIGFPE:  return "SIGFPE";
        case SIGABRT: return "SIGABRT";
        case SIGBUS:  return "SIGBUS";
        case SIGALRM: return "SIGALRM (kehabisan waktu)";
        default:      return "sinyal " + std::to_string(sinyal);
    }
#else
    (void)sinyal;
    return "tidak diketahui";
#endif
}

// -----------------------------------------------------------------------------
// Mencetak kalimat panjang sebagai beberapa baris menjorok
// -----------------------------------------------------------------------------
inline void runner_cetak_terbungkus(const std::string& teks,
                                    const std::string& jorok,
                                    std::size_t lebar) {
    std::size_t mulai = 0;
    while (mulai < teks.size()) {
        std::size_t sisa = teks.size() - mulai;
        if (sisa <= lebar) {
            std::cout << jorok << teks.substr(mulai) << "\n";
            return;
        }
        // Mundur ke spasi terakhir supaya kata tidak terpotong di tengah.
        std::size_t potong = teks.rfind(' ', mulai + lebar);
        if (potong == std::string::npos || potong <= mulai) {
            potong = mulai + lebar;
        }
        std::cout << jorok << teks.substr(mulai, potong - mulai) << "\n";
        mulai = potong;
        while (mulai < teks.size() && teks[mulai] == ' ') mulai++;
    }
}

// -----------------------------------------------------------------------------
// Menjalankan satu bagian runner di proses terpisah
// -----------------------------------------------------------------------------
/**
 * Menjalankan `bagian` di proses anak. Keluaran anak langsung tercetak ke
 * layar seperti biasa; yang berbeda hanyalah apa yang terjadi saat anak mati.
 *
 * @param bagian       fungsi yang mencetak satu bagian runner
 * @param batas_detik  batas waktu; bagian yang melewatinya dibunuh SIGALRM
 * @return             true bila bagian selesai normal, false bila mati
 */
inline bool jalankan_bagian(void (*bagian)(), int batas_detik) {
#if !RUNNER_ISOLASI
    (void)batas_detik;
    bagian();
    return true;
#else
    // Kosongkan buffer keluaran SEBELUM fork, supaya isi buffer induk tidak
    // ikut tersalin ke anak lalu tercetak dua kali.
    std::cout.flush();
    fflush(nullptr);

    pid_t pid = fork();
    if (pid < 0) {
        bagian();     // fasilitas OS tidak tersedia: jalankan apa adanya
        return true;
    }

    if (pid == 0) {
        // ---- proses anak ----
        // unitbuf membuat setiap operasi keluaran langsung dikirim keluar.
        // Tanpa ini, isi buffer yang belum sempat dikosongkan akan HILANG saat
        // anak mati — sehingga baris terakhir yang Anda lihat bukan baris
        // tempat program benar-benar berhenti. Ini terutama terjadi saat
        // keluaran runner dialihkan ke berkas, mis. `./latihan > hasil.txt`.
        std::cout << std::unitbuf;
        alarm(static_cast<unsigned>(batas_detik));
        bagian();
        std::cout.flush();
        fflush(nullptr);
        _exit(0);
    }

    // ---- proses induk ----
    int status_anak = 0;
    while (waitpid(pid, &status_anak, 0) < 0 && errno == EINTR) {
        // waitpid diinterupsi sinyal: ulangi.
    }

    std::string alasan;
    std::string judul;
    if (WIFSIGNALED(status_anak)) {
        const int sinyal = WTERMSIG(status_anak);
        judul  = runner_nama_sinyal(sinyal);
        alasan = runner_alasan_sinyal(sinyal, batas_detik);
    } else if (WIFEXITED(status_anak) && WEXITSTATUS(status_anak) != 0) {
        judul  = "keluar dengan exit code " +
                 std::to_string(WEXITSTATUS(status_anak));
        alasan = "Program keluar lebih awal. Fungsi yang Anda tulis sebaiknya "
                 "tidak memanggil exit().";
    } else {
        return true;
    }

    // Anak bisa mati setelah label tercetak tapi sebelum nilainya, jadi
    // barisnya menggantung. Baris baru ini menutup baris tanggung itu.
    std::cout << "\n    [BERHENTI MENDADAK] " << judul << "\n";
    runner_cetak_terbungkus(alasan, "      ", 64);
    std::cout << "      Bagian ini dilewati, lanjut ke bagian berikutnya.\n";
    return false;
#endif
}

#endif  // RUNNER_UTIL_H
