#include <iostream>
using namespace std;


struct node{
    int data;
    node* next;
};

struct linkedStack{
    node* top;
};

void buatStack(linkedStack& s){
    s.top = nullptr;
}

bool isEmpty(linkedStack& s){
    return s.top == nullptr;
}

bool isFull(){
    node* temp = new node;
    if(temp == nullptr){
        return true;
    }
    delete temp;
    return false;
}

void push(linkedStack& s, int nilai){
    if(isFull()){
        cout << "[OVERFLOW] push gagal = memori penuh"  << endl;
        return;
    }
    node* newNode = new node;
    newNode->data = nilai;
    newNode->next= s.top;
    s.top = newNode;
}

int pop(linkedStack& s){
    if(isEmpty(s)){
        cout << "[UNDERFLOW] pop ditolak : stack masih kosong" << endl;
        return -1;
    }
    node* temp = s.top;
    int nilai = temp->data;
    s.top = s.top->next;
    delete temp; // menghapus s.top
    return nilai;
}

int peek(linkedStack& s){
    if(isEmpty(s)){
        cout << "[UNDERFLOW] peek ditolak : stack masih kosong" << endl;
        return -1;
    }
    return s.top->data;
}

void tampilStack(linkedStack& s){
    if(isEmpty(s)){
        cout << "[UNDERFLOW] pop ditolak : stack masih kosong" << endl;
        return;
    }
    node* temp = s.top;
    cout << "ISI LINKED STACK DARI TOP KE BOTTOM \n";
    while(temp != nullptr){
        cout << "[ " << temp->data << " ] -> ";
        temp = temp->next; 
    }
}

void clearstack(linkedStack& s) {
    while (s.top != nullptr)
    {
        node* temp = s.top;
        s.top =s.top->next;
        delete temp;
    }
    cout << "\nseluruh node dalam stak linkedlis berhasil dibebaskan!!\n";
    
}

int main(){ 
    linkedStack st;

    buatStack(st);

    cout << "PUSH 3 elemen" << endl;
    push(st, 40);
    push(st, 5);
    push(st, 100);

    cout << endl;
    tampilStack(st);

    clearstack(st);
    tampilStack(st);

    return 0;
}