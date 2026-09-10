// =============================================================================
// student.h — Interface Praktikum
// Pertemuan 2: Pointer
// =============================================================================
// INSTRUKSI UNTUK MAHASISWA:
//   - JANGAN mengubah file ini.
//   - Kerjakan seluruh fungsi berikut di dalam src/student.cpp.
//   - Nama fungsi, tipe parameter, dan tipe kembalian adalah KONTRAK: checker
//     memanggilnya langsung, jadi tidak boleh diubah.
//   - Cara Anda memenuhi kontrak sepenuhnya bebas. Penilaian hanya melihat
//     akibat yang teramati oleh pemanggil.
//
// Penjelasan soal yang lengkap beserta contohnya ada di src/student.cpp, tepat
// di atas masing-masing fungsi. File ini hanya ringkasan kontraknya.
//
// -----------------------------------------------------------------------------
// KONVENSI UMUM
// -----------------------------------------------------------------------------
//   - `n` adalah banyaknya angka pada sebuah deret. Di pertemuan ini nilainya
//     selalu minimal 1, jadi deretnya tidak pernah kosong.
//
//   - SELURUH parameter bertipe pointer di pertemuan ini SELALU berisi alamat
//     yang sah. Tidak ada satu pun yang bisa bernilai `nullptr`, jadi Anda
//     tidak perlu memeriksanya.
// =============================================================================

#ifndef STUDENT_H
#define STUDENT_H

// =============================================================================
// SOAL 1 — tukarNilai
// =============================================================================
/**
 * Pemanggil punya dua variabel dan menyerahkan alamat keduanya.
 *
 * Setelah pemanggilan selesai, isi kedua variabel itu harus sudah bertukar, dan
 * perubahan tersebut terlihat oleh pemanggil pada data aslinya — bukan hanya
 * pada salinan sementara di dalam fungsi.
 *
 * `a` dan `b` selalu alamat yang sah, dan selalu menunjuk ke dua variabel yang
 * berbeda.
 */
void tukarNilai(int* a, int* b);

// =============================================================================
// SOAL 2 — cariElemen
// =============================================================================
/**
 * Pemanggil ingin menemukan sebuah angka di dalam deret, lalu MENGUBAH angka
 * itu langsung di tempatnya. Karena itu yang ia butuhkan bukan nilai angkanya,
 * melainkan alamatnya.
 *
 * Kontrak:
 *   - Yang dikembalikan adalah alamat elemen PERTAMA yang isinya sama dengan
 *     `target`, sehingga penulisan pemanggil ke alamat itu langsung mengubah
 *     deret aslinya.
 *   - `target` dijamin ada di dalam `data`, dan `n` dijamin minimal 1.
 *   - `data` selalu alamat yang sah.
 */
int* cariElemen(int* data, int n, int target);

// =============================================================================
// SOAL 3 — perbaruiSensor
// =============================================================================
/**
 * Satu rekaman sensor menyimpan riwayat ringkas dari pembacaan-pembacaan yang
 * pernah masuk.
 *
 * Rekaman ini milik pemanggil; setelah sebuah pembacaan baru diproses, rekaman
 * milik pemanggil itulah yang harus sudah mencerminkan keadaan terbaru.
 */
struct Sensor {
    int suhuTerakhir;     // suhu dari pembacaan paling akhir
    int suhuTertinggi;    // suhu tertinggi sepanjang riwayat pembacaan
    int totalPembacaan;   // banyaknya pembacaan yang sudah diproses
};

/**
 * Memproses satu pembacaan suhu baru untuk sebuah rekaman sensor.
 *
 * Kontrak:
 *   - Setelah pemanggilan, `suhuTerakhir` bernilai suhu pembacaan baru dan
 *     `totalPembacaan` bertambah satu.
 *   - `suhuTertinggi` mencerminkan suhu tertinggi dari seluruh pembacaan yang
 *     sudah diproses.
 *   - Rekaman selalu diserahkan dalam keadaan awal {0, 0, 0}, yaitu belum
 *     pernah menerima pembacaan sama sekali.
 *   - `suhuBaru` tidak pernah negatif.
 *   - `sensor` selalu alamat yang sah.
 */
void perbaruiSensor(Sensor* sensor, int suhuBaru);

#endif // STUDENT_H
