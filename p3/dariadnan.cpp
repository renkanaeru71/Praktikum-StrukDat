#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

Node* buatNode(int data, Node *next) {
    return new Node{data, next};
}

void cetakList(Node *head) {
    Node *temp = head;
    while (temp != nullptr) {
        cout << temp->data << "";
        temp = temp->next;
    }
    cout << endl;
}

void tambahAwal(Node*& head, Node*& tail, int data) {
    Node* baru = new Node{data, head};
    head = baru;

    if (tail == nullptr) {
        tail = baru;
    }
}

// void tambahAkhir(Node*& head, Node*& tail, int data) { 
//     Node* baru = new Node{data, nullptr};
    
//     if (head == nullptr) {
//         head = baru;
//         tail = baru;
//         return;
//     }

//     tail->next = baru;
//     tail = baru;
// }

// void tambahTengah(Node*& head, int data) {
//     Node* baru = new Node{data, nullptr};
    
//     if (head == nullptr) {
//         head = baru;
//         return;
//     }

//     Node *temp = head;
    
//     while(temp != NULL && baru->data > temp->next->data) {
//         temp = temp->next;
//     }        
//     baru->next = temp->next;
//     temp->next = baru;
// }

int main() {
    Node *pertama = buatNode(100, nullptr);

    Node *head = pertama;
    Node *tail = pertama;

    cetakList(head);

    return 0;
}