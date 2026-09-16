#include <iostream>
using namespace std;

// bikin struct node
struct node{
    int data;
    node *next;
};

void bacamaju(node *&head);
void sisipnode(node *&head, int nilai);
void sisidepan(node *&head, int nilai);
void hapusnote(node *&head, int nilai);

int main() {
    node *head = nullptr;

    sisipnode(head, 67);
    sisipnode(head, 89);
    sisipnode(head, 45);
    sisipnode(head, 99);

    cout << "tampilan list: ";
    bacamaju(head);
    sisidepan(head, 15);
    hapusnote(head, 45);
    
    cout << "setelah di hapus dan disisipkan: ";
    bacamaju(head);
}


void bacamaju(node *&head) {
    node *bantu = head;
    while (bantu != nullptr){
        cout << bantu->data << ", ";
        bantu = bantu->next;
    }
    cout << endl;
    
}

void sisipnode(node *&head, int nilai) {
    node *baru = new node;
    baru->data = nilai;
    baru->next = nullptr;

    if (head == nullptr){
        head = baru;
        return;
    }
    
    node *bantu = head;
    while (bantu->next != nullptr){
        bantu = bantu->next;
    }
    bantu->next = baru;
}

void sisidepan(node *&head, int nilai){
    node *baru = new node;
    baru->data = nilai;
    baru->next = head;

    head = baru;
}

void hapusnote(node *&head, int nilai) {
    if (head == nullptr){
        return;
    }

    if (head->data == nilai)
    {
        node *hapus = head;
        head = head->next;
        delete hapus;
        return;
    }

    node *bantu = head;
    if (bantu->next == nullptr) { // data ga ditemuin
        return;
    }
    
    while (bantu->next != nullptr && bantu->next->data != nilai) {
        bantu = bantu->next;
    }
    node *hapus = bantu->next;
    bantu->next = hapus->next;
    delete hapus;
} 