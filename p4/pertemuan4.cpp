#include <iostream>
using namespace std;

struct node
{
    int nilai;
    node *prev;
    node *next;
};

node* newnode = nullptr;
node* head = nullptr;
node* tail = nullptr;
node* temp = nullptr;

// sisip depan, blkng, traversal

void sisipdepan(int data);
void sisipbelakang(int data);
void traversal();

int main (){
    sisipdepan(67);
    sisipbelakang(92);
    sisipbelakang(71);
    sisipbelakang(61);
    
    cout << "isi list: ";
    traversal();

    sisipdepan(2);
    sisipdepan(13);

    cout << "isi list setelah di sisip depan: ";
    traversal()
}

void sisipdepan(int data){
    newnode = new node();
    newnode ->nilai = data;
    newnode ->prev = nullptr;
    newnode ->next = nullptr;

    if (head == nullptr){
        head = newnode;
        tail = newnode;
    }
    else {
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
}

void sisipbelakang(int data){
    newnode = new node();
    newnode->nilai = data;
    newnode->next = nullptr;
    newnode->prev = nullptr;

    if (head == nullptr){
        head = newnode;
        tail = newnode;
    } else{
        newnode->prev = tail;
        tail->next = newnode;
        tail = newnode;
    }
}

void traversal(){
    if (head == nullptr){
        cout << "kosong jir\n";
    }
    else {
        temp = head;
        while (temp != nullptr) {
            cout << temp->nilai << ", ";
            temp = temp->next;
        }
        
    }
}
