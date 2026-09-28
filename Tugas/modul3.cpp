#include <iostream>
using namespace std;

struct Mahasiswa {
    char nim[20];
    char nama[100];
    double ipk;
};

struct Node {
    Mahasiswa data;
    Node* next;
};

bool samaNim(const char a[], const char b[]);
bool nimTersedia(const Node* head, const char nim[]);
bool tambahAkhir(Node*& head, const Mahasiswa& data);
Node* cariNim(Node* head, const char nim[]);
bool hapusNim(Node*& head, const char nim[]);
void tampilkan(const Node* head);
int jumlahData(const Node* head);
void clear(Node*& head);

int main() {
    Node* head = nullptr;
    int pilihan = 0;

    do {
        cout << "\n1. Tambah\n";
        cout << "2. Tampilkan\n";
        cout << "3. Cari\n";
        cout << "4. Hapus\n";
        cout << "5. Jumlah\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Pilihan tidak valid\n";
            pilihan = 0;
            continue;
        }

        switch (pilihan) {
            case 1: {
                Mahasiswa data;

                cout << "NIM: ";
                cin.width(20);
                cin >> data.nim;

                if (nimTersedia(head, data.nim)) {
                    cout << "NIM duplikat\n";
                    break;
                }

                cout << "Nama: ";
                cin >> ws;
                cin.getline(data.nama, 100);

                cout << "IPK: ";
                cin >> data.ipk;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Input IPK tidak valid\n";
                    break;
                }

                if (tambahAkhir(head, data))
                    cout << "Data berhasil ditambahkan\n";
                else
                    cout << "NIM duplikat\n";

                break;
            }

            case 2:
                tampilkan(head);
                break;

            case 3: {
                char nim[20];

                cout << "NIM: ";
                cin.width(20);
                cin >> nim;

                Node* hasil = cariNim(head, nim);

                if (hasil != nullptr) {
                    cout << "NIM  : " << hasil->data.nim << endl;
                    cout << "Nama : " << hasil->data.nama << endl;
                    cout << "IPK  : " << hasil->data.ipk << endl;
                } else {
                    cout << "Data tidak ditemukan\n";
                }

                break;
            }

            case 4: {
                char nim[20];

                cout << "NIM: ";
                cin.width(20);
                cin >> nim;

                if (hapusNim(head, nim))
                    cout << "Data berhasil dihapus\n";
                else
                    cout << "Data tidak ditemukan\n";

                break;
            }

            case 5:
                cout << "Jumlah mahasiswa: "
                     << jumlahData(head) << endl;
                break;

            case 6:
                cout << "Program selesai\n";
                break;

            default:
                cout << "Pilihan tidak valid\n";
        }

    } while (pilihan != 6);

    clear(head);

    return 0;
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

bool nimTersedia(const Node* head, const char nim[]) {
    const Node* bantu = head;

    while (bantu != nullptr) {
        if (samaNim(bantu->data.nim, nim))
            return true;

        bantu = bantu->next;
    }

    return false;
}

bool tambahAkhir(Node*& head, const Mahasiswa& data) {
    if (nimTersedia(head, data.nim))
        return false;

    Node* baru = new Node{data, nullptr};

    if (head == nullptr) {
        head = baru;
        return true;
    }

    Node* bantu = head;

    while (bantu->next != nullptr)
        bantu = bantu->next;

    bantu->next = baru;

    return true;
}

Node* cariNim(Node* head, const char nim[]) {
    Node* bantu = head;

    while (bantu != nullptr) {
        if (samaNim(bantu->data.nim, nim))
            return bantu;

        bantu = bantu->next;
    }

    return nullptr;
}

bool hapusNim(Node*& head, const char nim[]) {
    if (head == nullptr)
        return false;

    Node* target = head;
    Node* sebelum = nullptr;

    while (target != nullptr &&
           !samaNim(target->data.nim, nim)) {
        sebelum = target;
        target = target->next;
    }

    if (target == nullptr)
        return false;

    if (sebelum == nullptr)
        head = target->next;
    else
        sebelum->next = target->next;

    delete target;

    return true;
}

void tampilkan(const Node* head) {
    const Node* bantu = head;

    if (bantu == nullptr) {
        cout << "Data masih kosong\n";
        return;
    }

    while (bantu != nullptr) {
        cout << "NIM  : " << bantu->data.nim << endl;
        cout << "Nama : " << bantu->data.nama << endl;
        cout << "IPK  : " << bantu->data.ipk << endl;
        cout << endl;

        bantu = bantu->next;
    }
}

int jumlahData(const Node* head) {
    int jumlah = 0;
    const Node* bantu = head;

    while (bantu != nullptr) {
        jumlah++;
        bantu = bantu->next;
    }

    return jumlah;
}

void clear(Node*& head) {
    while (head != nullptr) {
        Node* hapus = head;
        head = head->next;
        delete hapus;
    }
}
