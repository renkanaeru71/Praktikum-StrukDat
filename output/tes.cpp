#include <iostream>
using namespace std;
int main(){
    // cout << "hello world!" << endl;

    // ngerjain soal di modul
    // 1. bikin array nilai berisi 5 elemen
    int nilai[]={80, 75, 90, 80, 70};
    int jumlah = sizeof(nilai) / sizeof(nilai[0]);

    // 2. tampilin seluruh nilai
    cout << "Seluruh nilai: ";
    for (int i = 0; i < jumlah; i++) {
        cout << nilai[i] << " ";
    }
    cout << endl;

    // 3. hitung jumlah nilai dan nilai terbesar
    int total = 0;
    int terbesar = nilai[0];

    for (int i = 0; i < jumlah; i++) {
        total += nilai[i];

        if (nilai[i] > terbesar) {
            terbesar = nilai[i];
        }
    }
    cout << "Jumlah nilai: " << total << endl;
    cout << "Nilai terbesar: " << terbesar << endl;

    // 4. cek indeks pertama dan terakhir
    cout << "elemen index pertama (index 0): " << nilai[0] << endl;
    cout << "elemen index terakhir (index " << jumlah - 1 << "): " << nilai[jumlah - 1] << endl;

    // 5. perulangan yang menggunakan i <= jumlah
  cout << "\nMenampilkan indeks & elemen dengan perulangan yang benar:" << endl;
    for (int i = 0; i < jumlah; i++) { // Menggunakan i < jumlah
        cout << "Indeks ke-" << i << " = " << nilai[i] << endl;
    }
    cout << endl;

}