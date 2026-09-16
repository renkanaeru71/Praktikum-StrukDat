#include <iostream>
#include <string>

// Struct Data Mahasiswa (Modul Bab 5.1)
struct Mahasiswa {
    std::string nim;
    std::string nama;
    double ipk;
};

// Struct Node Singly Linked List
struct Node {
    Mahasiswa data;
    Node* next;
};

// Cek ketersediaan NIM
bool nimTersedia(const Node* head, const std::string& nim) {
    const Node* bantu = head;
    while (bantu != nullptr) {
        if (bantu->data.nim == nim) return true; // NIM Ditemukan
        bantu = bantu->next;
    }
    return false;
}

// Tambah Mahasiswa di akhir (dengan validasi NIM Duplikat)
bool tambahAkhir(Node*& head, const Mahasiswa& data) {
    // Tolak NIM Duplikat
    if (nimTersedia(head, data.nim)) {
        std::cout << "[ERROR] NIM sudah terdaftar! Penambahan ditolak.\n";
        return false;
    }

    Node* baru = new Node{data, nullptr};
    if (head == nullptr) {
        head = baru;
        return true;
    }

    Node* bantu = head;
    while (bantu->next != nullptr) {
        bantu = bantu->next;
    }
    bantu->next = baru;
    return true;
}

// Cari Mahasiswa berdasarkan NIM
Node* cariNim(Node* head, const std::string& nim) {
    Node* bantu = head;
    while (bantu != nullptr) {
        if (bantu->data.nim == nim) return bantu;
        bantu = bantu->next;
    }
    return nullptr;
}

// Hapus Mahasiswa berdasarkan NIM
bool hapusNim(Node*& head, const std::string& nim) {
    if (head == nullptr) return false;

    Node* target = head;
    Node* sebelum = nullptr;

    while (target != nullptr && target->data.nim != nim) {
        sebelum = target;
        target = target->next;
    }

    if (target == nullptr) return false; // Data tidak ditemukan

    if (sebelum == nullptr) {
        head = target->next; // Hapus node pertama
    } else {
        sebelum->next = target->next; // Hapus node tengah/akhir
    }

    delete target;
    return true;
}

// Tampilkan seluruh Mahasiswa
void tampilkan(const Node* head) {
    if (head == nullptr) {
        std::cout << "Daftar mahasiswa kosong.\n";
        return;
    }

    const Node* bantu = head;
    std::cout << "\n--- DAFTAR MAHASISWA ---\n";
    while (bantu != nullptr) {
        std::cout << "NIM  : " << bantu->data.nim << "\n";
        std::cout << "Nama : " << bantu->data.nama << "\n";
        std::cout << "IPK  : " << bantu->data.ipk << "\n";
        std::cout << "------------------------\n";
        bantu = bantu->next;
    }
}

// Hitung Jumlah Mahasiswa
int jumlahData(const Node* head) {
    int count = 0;
    const Node* bantu = head;
    while (bantu != nullptr) {
        count++;
        bantu = bantu->next;
    }
    return count;
}

// Bebaskan seluruh memori
void clear(Node*& head) {
    while (head != nullptr) {
        Node* hapus = head;
        head = head->next;
        delete hapus;
    }
}

int main() {
    Node* head = nullptr;
    int pilihan;

    do {
        std::cout << "\n=== MENU DATA MAHASISWA ===\n";
        std::cout << "1. Tambah Mahasiswa\n";
        std::cout << "2. Tampilkan Semua\n";
        std::cout << "3. Cari Mahasiswa (NIM)\n";
        std::cout << "4. Hapus Mahasiswa (NIM)\n";
        std::cout << "5. Jumlah Mahasiswa\n";
        std::cout << "6. Keluar\n";
        std::cout << "Pilihan: ";
        std::cin >> pilihan;

        if (pilihan == 1) {
            Mahasiswa m;
            std::cout << "Masukkan NIM  : "; std::cin >> m.nim;
            std::cout << "Masukkan Nama : "; std::cin.ignore(); std::getline(std::cin, m.nama);
            std::cout << "Masukkan IPK  : "; std::cin >> m.ipk;
            
            if (tambahAkhir(head, m)) {
                std::cout << "Data mahasiswa berhasil ditambahkan.\n";
            }
        } else if (pilihan == 2) {
            tampilkan(head);
        } else if (pilihan == 3) {
            std::string nim;
            std::cout << "Masukkan NIM yang dicari: "; std::cin >> nim;
            Node* res = cariNim(head, nim);
            if (res != nullptr) {
                std::cout << "[Ditemukan] Nama: " << res->data.nama << ", IPK: " << res->data.ipk << "\n";
            } else {
                std::cout << "[Tidak Ditemukan] NIM tidak terdaftar.\n";
            }
        } else if (pilihan == 4) {
            std::string nim;
            std::cout << "Masukkan NIM yang akan dihapus: "; std::cin >> nim;
            if (hapusNim(head, nim)) {
                std::cout << "Data berhasil dihapus.\n";
            } else {
                std::cout << "Data tidak ditemukan / Gagal dihapus.\n";
            }
        } else if (pilihan == 5) {
            std::cout << "Jumlah Mahasiswa: " << jumlahData(head) << " orang.\n";
        }

    } while (pilihan != 6);

    clear(head); // Membebaskan memori sebelum program selesai[cite: 2]
    std::cout << "Memori dibebaskan. Program selesai.\n";
    return 0;
}