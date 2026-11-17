#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

// Fungsi membuat node baru
Node* createNode(int nilai) {
    Node* baru = new Node{nilai, nullptr, nullptr};
    return baru;
}

// Traversal Inorder (Left -> Root -> Right)
void inorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Traversal Postorder (Left -> Right -> Root)
void postorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Traversal Preorder (Root -> Left -> Right)
void preorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Menghitung total node
int jumlahNode(Node* root) {
    if (root == nullptr) {
        return 0; // Harus return integer 0
    }
    return 1 + jumlahNode(root->left) + jumlahNode(root->right);
}

// Membebaskan seluruh memori tree (pola postorder)
void clear(Node* root) {
    if (root == nullptr) {
        return;
    }
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
}

// Fungsi mencari nilai di dalam binary tree
bool carinilai(Node* root, int cari) {
    if (root == nullptr) {
        return false;
    }
    if (root->data == cari) {
        return true;
    }
    // Cari di subtree kiri atau subtree kanan
    return carinilai(root->left, cari) || carinilai(root->right, cari);
}

int main() {
    Node* root = nullptr;

    // Membentuk tree sesuai contoh modul (Kegiatan 6.1)
    root = createNode(50);
    root->left = createNode(80);
    root->right = createNode(20);
    root->left->left = createNode(10);
    root->left->right = createNode(70);
    root->right->right = createNode(90);
    root->left->right->left = createNode(30);

    // Menampilkan hasil traversal
    cout << "Preorder : ";
    preorder(root);
    cout << endl;

    cout << "Inorder  : ";
    inorder(root);
    cout << endl;

    cout << "Postorder: ";
    postorder(root);
    cout << endl;

    // Menampilkan jumlah node
    cout << "Jumlah Node: " << jumlahNode(root) << endl;

    // Uji fungsi pencarian
    int cari = 70;
    if (carinilai(root, cari)) {
        cout << "Nilai " << cari << " ditemukan dalam tree." << endl;
    } else {
        cout << "Nilai " << cari << " tidak ditemukan dalam tree." << endl;
    }

    // Membebaskan memori
    clear(root);

    return 0;
}