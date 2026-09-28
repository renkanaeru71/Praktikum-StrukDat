#include <iostream>
using namespace std;

struct Lagu {
    char judul[100];
    char penyanyi[100];
};

struct Node {
    Lagu data;
    Node* prev;
    Node* next;
};

bool samaJudul(const char a[], const char b[]);
bool judulTersedia(const Node* head, const char judul[]);
bool tambahAkhir(Node*& head, Node*& tail, const Lagu& data);
Node* cariJudul(Node* head, const char judul[]);
bool hapusJudul(Node*& head, Node*& tail, const char judul[]);
void tampilMaju(const Node* head);
void tampilMundur(const Node* tail);
int jumlahData(const Node* head);
void clear(Node*& head, Node*& tail);

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;
    int pilihan = 0;

    do {
        cout << "\n1. Tambah lagu\n";
        cout << "2. Tampilkan maju\n";
        cout << "3. Tampilkan mundur\n";
        cout << "4. Cari lagu\n";
        cout << "5. Hapus lagu\n";
        cout << "6. Jumlah lagu\n";
        cout << "7. Keluar\n";
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
                Lagu data;

                cout << "Judul lagu: ";
                cin >> ws;
                cin.getline(data.judul, 100);

                if (judulTersedia(head, data.judul)) {
                    cout << "Judul udah ada\n";
                    break;
                }

                cout << "Penyanyi: ";
                cin.getline(data.penyanyi, 100);

                if (tambahAkhir(head, tail, data))
                    cout << "Lagu berhasil ditambahkan\n";
                else
                    cout << "Judul udah tersedia\n";
                break;
            }

            case 2:
                tampilMaju(head);
                break;

            case 3:
                tampilMundur(tail);
                break;

            case 4: {
                char judul[100];

                cout << "Judul lagu: ";
                cin >> ws;
                cin.getline(judul, 100);

                Node* hasil = cariJudul(head, judul);

                if (hasil != nullptr) {
                    cout << "Judul    : " << hasil->data.judul << endl;
                    cout << "Penyanyi : " << hasil->data.penyanyi << endl;
                } else {
                    cout << "Lagu ga ditemukan\n";
                }

                break;
            }

            case 5: {
                char judul[100];

                cout << "Judul lagu: ";
                cin >> ws;
                cin.getline(judul, 100);

                if (hapusJudul(head, tail, judul))
                    cout << "Lagu berhasil dihapus\n";
                else
                    cout << "Lagu ga ditemukan\n";

                break;
            }

            case 6:
                cout << "Jumlah lagu: " << jumlahData(head) << endl;
                break;

            case 7:
                cout << "Program selesai\n";
                break;

            default:
                cout << "Pilihan tidak valid\n";
        }

    } while (pilihan != 7);

    clear(head, tail);

    return 0;
}

bool samaJudul(const char a[], const char b[]) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return false;

        i++;
    }

    return a[i] == b[i];
}

bool judulTersedia(const Node* head, const char judul[]) {
    const Node* bantu = head;

    while (bantu != nullptr) {
        if (samaJudul(bantu->data.judul, judul))
            return true;

        bantu = bantu->next;
    }

    return false;
}

bool tambahAkhir(Node*& head, Node*& tail, const Lagu& data) {
    if (judulTersedia(head, data.judul))
        return false;

    Node* baru = new Node{data, nullptr, nullptr};

    if (head == nullptr) {
        head = tail = baru;
    } else {
        baru->prev = tail;
        tail->next = baru;
        tail = baru;
    }

    return true;
}

Node* cariJudul(Node* head, const char judul[]) {
    Node* bantu = head;

    while (bantu != nullptr) {
        if (samaJudul(bantu->data.judul, judul))
            return bantu;

        bantu = bantu->next;
    }

    return nullptr;
}

bool hapusJudul(Node*& head, Node*& tail, const char judul[]) {
    Node* target = cariJudul(head, judul);

    if (target == nullptr)
        return false;

    if (target == head)
        head = target->next;
    else
        target->prev->next = target->next;

    if (target == tail)
        tail = target->prev;
    else
        target->next->prev = target->prev;

    delete target;

    return true;
}

void tampilMaju(const Node* head) {
    if (head == nullptr) {
        cout << "Playlist kosong\n";
        return;
    }

    const Node* bantu = head;

    while (bantu != nullptr) {
        cout << "Judul    : " << bantu->data.judul << endl;
        cout << "Penyanyi : " << bantu->data.penyanyi << endl;
        cout << endl;

        bantu = bantu->next;
    }
}

void tampilMundur(const Node* tail) {
    if (tail == nullptr) {
        cout << "Playlist kosong\n";
        return;
    }

    const Node* bantu = tail;

    while (bantu != nullptr) {
        cout << "Judul    : " << bantu->data.judul << endl;
        cout << "Penyanyi : " << bantu->data.penyanyi << endl;
        cout << endl;

        bantu = bantu->prev;
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

void clear(Node*& head, Node*& tail) {
    while (head != nullptr) {
        Node* hapus = head;
        head = head->next;
        delete hapus;
    }

    tail = nullptr;
}