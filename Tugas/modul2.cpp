
#include <iostream>
using namespace std;

struct Mahasiswa {
    int nim;
    char nama[100];
    double ipk;
};

void inputData(Mahasiswa* data, int jumlah);
void tampilkanData(const Mahasiswa* data, int jumlah);
int cariNim(const Mahasiswa* data, int jumlah, int nim);

int main() {
    int jumlah;

    cout << "Masukkan jumlah mahasiswa: ";
    cin >> jumlah;

    if (jumlah <= 0) {
        cout << "Jumlah mahasiswa harus lebih dari 0!" << endl;
        return 0;
    }

    Mahasiswa* data = new Mahasiswa[jumlah];

    inputData(data, jumlah);

    tampilkanData(data, jumlah);

    int nim;
    cout << "\nMasukkan NIM yang dicari: ";
    cin >> nim;

    int posisi = cariNim(data, jumlah, nim);

    if (posisi == -1) {
        cout << "Mahasiswa tidak ditemukan!" << endl;
    } else {
        cout << "\nMahasiswa ditemukan pada indeks "
             << posisi << endl;

        cout << "NIM  : " << data[posisi].nim << endl;
        cout << "Nama : " << data[posisi].nama << endl;
        cout << "IPK  : " << data[posisi].ipk << endl;
    }

    delete[] data;
    data = nullptr;

    return 0;
}

void inputData(Mahasiswa* data, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        cout << "\nMahasiswa ke-" << i + 1 << endl;

        cout << "NIM  : ";
        cin >> data[i].nim;

        cout << "Nama : ";
        cin >> ws;
        cin.getline(data[i].nama, 100);

        cout << "IPK  : ";
        cin >> data[i].ipk;
    }
}

void tampilkanData(const Mahasiswa* data, int jumlah) {
    cout << "\n===== DATA MAHASISWA =====" << endl;

    for (int i = 0; i < jumlah; i++) {
        cout << "\nMahasiswa ke-" << i + 1 << endl;
        cout << "NIM  : " << data[i].nim << endl;
        cout << "Nama : " << data[i].nama << endl;
        cout << "IPK  : " << data[i].ipk << endl;
    }
}

int cariNim(const Mahasiswa* data, int jumlah, int nim) {
    for (int i = 0; i < jumlah; i++) {
        if (data[i].nim == nim) {
            return i;
        }
    }

    return -1;
}