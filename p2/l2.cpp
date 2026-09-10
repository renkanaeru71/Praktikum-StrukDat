#include <iostream>
using namespace std;

int main() {
    int angka = 50;       // Variabel biasa
    int* ptr = &angka;    // Pointer yang menyimpan ALAMAT dari variabel 'angka'

    // 1. NILAI
    cout << "Nilai angka                : " << angka << endl; // Output: 50

    // 2. ALAMAT
    cout << "Alamat angka (&angka)      : " << &angka << endl; // Contoh: 0x61ff08
    cout << "Alamat disimpannya ptr     : " << ptr << endl;    // Sama dengan &angka: 0x61ff08

    // 3. DEREFERENCE
    cout << "Nilai lewat ptr (*ptr)     : " << *ptr << endl;   // Output: 50

    // Mengubah nilai lewat dereference
    *ptr = 100;
    cout << "Nilai angka setelah diubah : " << angka << endl;  // Output: 100

    return 0;
}