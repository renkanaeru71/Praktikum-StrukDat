// #include <iostream>
// #include <string>

// // Struct untuk node
// struct Node {
//     std::string riwayatAksi;
//     Node* next;
// };

// // Fungsi membuat node baru
// Node* buatNode(std::string aksi) {
//     return new Node{aksi, nullptr};
// }

// // Tambah aksi baru di akhir (Insert Last)
// void tambahAksi(Node*& head, Node*& tail, std::string aksi) {
//     Node* baru = buatNode(aksi);
//     if (head == nullptr) {
//         head = baru;
//         tail = baru;
//     } else {
//         tail->next = baru;
//         tail = baru;
//     }
// }

// // Cetak seluruh riwayat dari awal (Traversal)
// void tampilkanRiwayat(const Node* head) {
//     const Node* temp = head;
//     std::cout << "Riwayat Aksi: ";
//     while (temp != nullptr) {
//         std::cout << "[" << temp->riwayatAksi << "] -> ";
//         temp = temp->next;
//     }
//     std::cout << "NULL\n";
// }

// int main() {
//     Node* head = nullptr;
//     Node* tail = nullptr;

//     // Simulasi pengguna mengetik
//     tambahAksi(head, tail, "Ketik: 'Halo'");
//     tambahAksi(head, tail, "Ketik: ' Dunia'");
//     tambahAksi(head, tail, "Format: Bold");

//     // Menampilkan riwayat
//     tampilkanRiwayat(head);

//     return 0;
// }

// another study case
// Antrean Pasien Berdasarkan Prioritas Umur
// Misal kita ingin memasukkan data umur pasien ke dalam linked list. 
// Pasien baru akan otomatis disisipkan secara urut (dari yang termuda ke tertua), dan jika pasien selesai dilayani, 
// datanya dihapus dari list.

#include <iostream>

struct Node {
    int umur;
    Node* next;
};

// Fungsi membuat node baru
Node* buatNode(int umur) {
    return new Node{umur, nullptr};
}

// Sisip Tengah (Sorted Insert) berdasarkan umur
void tambahPasienUrut(Node*& head, int umur) {
    Node* baru = buatNode(umur);

    // Jika list kosong atau umur baru paling kecil (sisip awal)
    if (head == nullptr || umur < head->umur) {
        baru->next = head;
        head = baru;
        return;
    }

    // Mencari posisi yang tepat untuk disisipkan
    Node* temp = head;
    while (temp->next != nullptr && temp->next->umur < umur) {
        temp = temp->next;
    }

    // Sambungkan pointer
    baru->next = temp->next;
    temp->next = baru;
}

// Hapus Data Pasien berdasarkan umur
bool hapusPasien(Node*& head, int umur) {
    if (head == nullptr) return false;

    Node* target = head;
    Node* sebelum = nullptr;

    // Mencari node target
    while (target != nullptr && target->umur != umur) {
        sebelum = target;
        target = target->next;
    }

    // Jika data tidak ditemukan
    if (target == nullptr) return false;

    // Jika data ada di head
    if (sebelum == nullptr) {
        head = target->next;
    } else {
        sebelum->next = target->next;
    }

    delete target;
    return true;
}

// Menampilkan seluruh data
void tampilkanDaftar(const Node* head) {
    const Node* temp = head;
    std::cout << "Daftar Pasien (Umur): ";
    while (temp != nullptr) {
        std::cout << temp->umur << " thn -> ";
        temp = temp->next;
    }
    std::cout << "NULL\n";
}

int main() {
    Node* head = nullptr;

    // Tambah pasien secara acak
    tambahPasienUrut(head, 45);
    tambahPasienUrut(head, 20);
    tambahPasienUrut(head, 35);
    tambahPasienUrut(head, 10);

    // Hasilnya otomatis urut dari termuda
    tampilkanDaftar(head); // Output: 10 thn -> 20 thn -> 35 thn -> 45 thn -> NULL

    // Hapus pasien umur 35 (Hapus tengah)
    std::cout << "\nMenghapus pasien umur 35...\n";
    hapusPasien(head, 35);

    tampilkanDaftar(head); // Output: 10 thn -> 20 thn -> 45 thn -> NULL

    return 0;
}