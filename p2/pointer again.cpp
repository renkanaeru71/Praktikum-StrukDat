#include <iostream>
using namespace std;

struct mhs {
    string nama;
    string nim;
    float ipk;
};

void inputData(mhs *mahasiswa, int jumlah);
void tampilData(const mhs *mahasiswa, int jumlah);
int cariNIM(const mhs *mahasiswa, int jumlah, string NIM);

int main() {
    int jumlah;
    cout << "masukkan jumlah data yang mau di input: ";
    cin >> jumlah;
    if (jumlah <= 0) {
        return 0;
    }

    mhs *mahasiswa = new mhs[jumlah];
    inputData(mahasiswa, jumlah);
    tampilData(mahasiswa, jumlah);

    string NIM;
    cout << "cari nim: "; cin >> NIM;
    int posisi = cariNIM(mahasiswa, jumlah, NIM);
    cout << posisi << endl;

}


void inputData(mhs *mahasiswa, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        cout << "masukkan nama: "; cin >> mahasiswa->nama;
        cout << "masukkan nim: "; cin >> mahasiswa->nim;
        cout << "masukkan ipk: "; cin >> mahasiswa->ipk;
    }
}

void tampilData(const mhs *mahasiswa, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        cout << "nama: " << mahasiswa->nama << endl;
        cout << "nim: " << mahasiswa->nim << endl;
        cout << "ipk: " << mahasiswa->ipk << endl;
    }
}

int cariNIM(const mhs *mahasiswa, int jumlah, string NIM) {
    for (int i = 0; i < jumlah; i++) {
        if (mahasiswa->nim == NIM) {
            return i;
        }
    }
    return -1;
}