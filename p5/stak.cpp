#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct LinkedStack {
    Node* top;
};

LinkedStack stack;

// Membuat stack kosong
void buatStack() {
    stack.top = nullptr;
}

// Mengecek stack kosong
bool isEmpty(LinkedStack stack) {
    return stack.top == nullptr;
}

// Mengecek apakah memori masih tersedia
bool isFull() {
    Node* temp = new Node;

    if (temp == nullptr) {
        return true;
    }

    delete temp;
    return false;
}

// PUSH
bool push(LinkedStack& s, int nilai) {
    Node* newNode = new Node;

    if (newNode == nullptr)
        return false;

    newNode->data = nilai;
    newNode->next = s.top;
    s.top = newNode;

    return true;
}

// POP
bool pop(LinkedStack& s, int& nilai) {
    if (s.top == nullptr)
        return false;

    Node* temp = s.top;

    nilai = temp->data;
    s.top = s.top->next;

    delete temp;

    return true;
}

// PEEK
bool peek(LinkedStack& s, int& nilai) {
    if (s.top == nullptr)
        return false;

    nilai = s.top->data;

    return true;
}

// Menampilkan isi stack
void tampilStack(LinkedStack stack) {
    Node* current = stack.top;

    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }

    cout << endl;
}

// Menghapus seluruh stack
void clearStack(LinkedStack& stack) {
    while (stack.top != nullptr) {
        Node* temp = stack.top;
        stack.top = stack.top->next;
        delete temp;
    }
}

int main() {
    buatStack();

    cout << "=== PUSH ===" << endl;

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    cout << "Isi Stack : ";
    tampilStack(stack);

    int nilai;

    cout << "\n=== PEEK ===" << endl;

    if (peek(stack, nilai)) {
        cout << "Data teratas: " << nilai << endl;
    }

    cout << "\n=== POP ===" << endl;

    if (pop(stack, nilai)) {
        cout << "Data yang keluar: " << nilai << endl;
    }

    cout << "Isi Stack : ";
    tampilStack(stack);

    cout << "\n=== CLEAR STACK ===" << endl;

    clearStack(stack);

    if (isEmpty(stack)) {
        cout << "Stack sekarang kosong" << endl;
    }

    return 0;
}