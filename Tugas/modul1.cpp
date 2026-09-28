
#include <iostream>
using namespace std;

const int kapasitas = 10;

struct Mahasiswa {
    char nim[20];
    char nama[100];
    double ipk;
};

struct DataMahasiswa {
    Mahasiswa data[kapasitas];
    int jumlah;
};

void init(DataMahasiswa& daftar);
bool samaNim(const char a[], const char b[]);
int cariNim(const DataMahasiswa& daftar, const char nim[]);
bool tambahMahasiswa(DataMahasiswa& daftar, const Mahasiswa& mhs);
bool ubahIpk(DataMahasiswa& daftar, const char nim[], double ipkBaru);
void tampilkan(const DataMahasiswa& daftar);

int main() {
    DataMahasiswa daftar;
    init(daftar);

    int pilihan;

    do {
        cout << "\n===== DATA MAHASISWA =====\n";
        cout << "1. Tambah Mahasiswa\n";
        cout << "2. Tampilkan Mahasiswa\n";
        cout << "3. Cari Mahasiswa\n";
        cout << "4. Ubah IPK\n";
        cout << "5. Jumlah Mahasiswa\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                Mahasiswa mhs;

                if (daftar.jumlah >= kapasitas) {
                    cout << "Array penuh!\n";
                    break;
                }

                cout << "NIM: ";
                cin >> mhs.nim;

                cout << "Nama: ";
                cin >> ws;
                cin.getline(mhs.nama, 100);

                cout << "IPK: ";
                cin >> mhs.ipk;

                if (tambahMahasiswa(daftar, mhs))
                    cout << "Data berhasil ditambahkan!\n";
                else
                    cout << "Gagal! NIM duplikat atau IPK tidak valid.\n";

                break;
            }

            case 2:
                tampilkan(daftar);
                break;

            case 3: {
                char nim[20];

                cout << "Masukkan NIM: ";
                cin >> nim;

                int posisi = cariNim(daftar, nim);

                if (posisi == -1) {
                    cout << "Mahasiswa tidak ditemukan!\n";
                } else {
                    cout << "NIM  : " << daftar.data[posisi].nim << endl;
                    cout << "Nama : " << daftar.data[posisi].nama << endl;
                    cout << "IPK  : " << daftar.data[posisi].ipk << endl;
                }
                break;
            }

            case 4: {
                char nim[20];
                double ipkBaru;

                cout << "Masukkan NIM: ";
                cin >> nim;

                cout << "IPK baru: ";
                cin >> ipkBaru;

                if (ubahIpk(daftar, nim, ipkBaru))
                    cout << "IPK berhasil diubah!\n";
                else
                    cout << "Gagal! NIM tidak ditemukan atau IPK tidak valid.\n";

                break;
            }

            case 5:
                cout << "Jumlah mahasiswa: " << daftar.jumlah << endl;
                break;

            case 6:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 6);

    return 0;
}

void init(DataMahasiswa& daftar) {
    daftar.jumlah = 0;
}

bool samaNim(const char a[], const char b[]) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return false;

        i++;
    }

    return a[i] == b[i];
}

int cariNim(const DataMahasiswa& daftar, const char nim[]) {
    for (int i = 0; i < daftar.jumlah; i++) {
        if (samaNim(daftar.data[i].nim, nim))
            return i;
    }

    return -1;
}

bool tambahMahasiswa(DataMahasiswa& daftar, const Mahasiswa& mhs) {
    if (daftar.jumlah >= kapasitas)
        return false;

    if (cariNim(daftar, mhs.nim) != -1)
        return false;

    if (mhs.ipk < 0.0 || mhs.ipk > 4.0)
        return false;

    daftar.data[daftar.jumlah] = mhs;
    daftar.jumlah++;

    return true;
}

bool ubahIpk(DataMahasiswa& daftar, const char nim[], double ipkBaru) {
    if (ipkBaru < 0.0 || ipkBaru > 4.0)
        return false;

    int posisi = cariNim(daftar, nim);

    if (posisi == -1)
        return false;

    daftar.data[posisi].ipk = ipkBaru;

    return true;
}

void tampilkan(const DataMahasiswa& daftar) {
    if (daftar.jumlah == 0) {
        cout << "Data masih kosong!\n";
        return;
    }

    for (int i = 0; i < daftar.jumlah; i++) {
        cout << "\nMahasiswa ke-" << i + 1 << endl;
        cout << "NIM  : " << daftar.data[i].nim << endl;
        cout << "Nama : " << daftar.data[i].nama << endl;
        cout << "IPK  : " << daftar.data[i].ipk << endl;
    }
}