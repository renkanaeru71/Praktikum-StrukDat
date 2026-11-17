#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

struct queue{
    Node* front;
    Node* rear;
    int count;
};

void init(queue& q){
    q.front = nullptr;
    q.rear = nullptr;
    q.count = 0;
}

bool isEmpety(queue& q){
    return q.front == nullptr; // 0x0 == nullptr return true jik antrian nol

}

void enqueue(queue& q, int nilai){
    Node* baru = new Node();
    baru->data = nilai;
    baru->next = nullptr;
    if (isEmpety(q)) {
        q.front = baru;
        q.rear = baru;
    }else{
        q.rear->next = baru;//belakang sambungin ke node baru
        q.rear = baru;
    }

    q.count++;
    return;
}

void dequeue(queue& q){ // Hapus parameter int& nilaiKeluar
    if (isEmpety(q)) {
        cout<<"Masih Kosong \n";
        return;
    }
    Node* bantu = q.front;
    q.front = q.front->next; // q front dipindah ke belakang (next)

    if (q.front == nullptr) {
        q.rear = nullptr;
    }
    delete bantu;
    q.count--;
    return;
}

void peek(queue& q){
    if (isEmpety(q)) {
        cout<<"masih kosong queuenya ...\n";
        return;
    }
    cout<<"antrian paling depan adalah : "<<q.front->data<<endl;
}

void printAntrian(queue& q){
    if (isEmpety(q)) {
        cout<<"masih kosong queuenya ...\n";
        return;
    }

    cout<<"Isi Queue: ";
    Node* current = q.front;
    while (current != nullptr) {
       cout<<current->data<<", ";
       current = current->next; //untuk pindah pindah
    }
    cout<<"\nJumlah antrian: "<<q.count<<endl;
}

void clear(queue& q){
    Node* current = q.front;
    while (current != nullptr) {
        Node* bantu = current;
        current = current->next;//pindah node dan hapus
        delete bantu;
    }
    init(q);
    // q.front = nullptr;
    // q.rear = nullptr;
    // q.count = 0;

}

int main(){
    queue q;
    init(q);
    enqueue(q, 100);
    enqueue(q, 155);
    enqueue(q, 600);
    printAntrian(q);

    dequeue(q);
    dequeue(q);
    printAntrian(q);
}