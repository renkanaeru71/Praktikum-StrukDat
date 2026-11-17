#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

// INSERT
bool insert(Node*& root, int nilai) {
    if (root == nullptr) {
        root = new Node{nilai, nullptr, nullptr};
        return true;
    }
    if (nilai < root->data) return insert(root->left, nilai);
    if (nilai > root->data) return insert(root->right, nilai);
    return false; // duplikat
}

// SEARCH
const Node* cari(const Node* root, int nilai) {
    if (root == nullptr) return nullptr;
    if (nilai == root->data) return root;
    if (nilai < root->data) return cari(root->left, nilai);
    return cari(root->right, nilai);
}

// MINIMUM 
const Node* minimum(const Node* root) {
    if (root == nullptr) return nullptr;
    while (root->left != nullptr) root = root->left;
    return root;
}

// DELETE
bool hapus(Node*& root, int nilai) {
    if (root == nullptr) return false;

    if (nilai < root->data) return hapus(root->left, nilai);
    if (nilai > root->data) return hapus(root->right, nilai);

    if (root->left == nullptr && root->right == nullptr) {
        delete root;
        root = nullptr;
    } else if (root->left == nullptr) {
        Node* target = root;
        root = root->right;
        delete target;
    } else if (root->right == nullptr) {
        Node* target = root;
        root = root->left;
        delete target;
    } else {
        const Node* pengganti = minimum(root->right);
        root->data = pengganti->data;
        hapus(root->right, pengganti->data);
    }
    return true;
}

// INORDER
void inorder(const Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << ' ';
    inorder(root->right);
}

// CLEAR
void clear(Node*& root) {
    if (root == nullptr) return;
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
}

int main() {
    Node* root = nullptr;
    int pilihan, nilai;

    do {
        cout << "\n===== PENGELOLAAN BST =====\n";
        cout << "1. Tambah nilai\n";
        cout << "2. Cari nilai\n";
        cout << "3. Hapus nilai\n";
        cout << "4. Tampilkan inorder\n";
        cout << "5. Tampilkan minimum\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan nilai: "; cin >> nilai;
                if (insert(root, nilai)) cout << "Berhasil ditambahkan.\n";
                else cout << "Gagal: nilai sudah ada (duplikat ditolak).\n";
                break;
            case 2:
                cout << "Masukkan nilai: "; cin >> nilai;
                if (cari(root, nilai) != nullptr) cout << "Ditemukan.\n";
                else cout << "Tidak ditemukan.\n";
                break;
            case 3:
                cout << "Masukkan nilai: "; cin >> nilai;
                if (hapus(root, nilai)) cout << "Berhasil dihapus.\n";
                else cout << "Gagal: nilai tidak ada.\n";
                break;
            case 4:
                cout << "Inorder: ";
                if (root == nullptr) cout << "(kosong)";
                inorder(root);
                cout << "\n";
                break;
            case 5:
                if (root == nullptr) cout << "Tree kosong.\n";
                else cout << "Minimum: " << minimum(root)->data << "\n";
                break;
            case 6:
                clear(root);
                cout << "Memori dibebaskan. Keluar.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}