#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int nilai;
    Node *next;
};

Node *head = nullptr;
Node *tail = nullptr;
Node *temp = nullptr;
Node *hapus = nullptr;

void sisipNode(int data)
{
    Node *baru = new Node{data, nullptr};

    if (head == nullptr)
    {
        head = tail = baru; // list kosong
        baru->next = head;
    }
    else if (data < head->nilai)
    {
        baru->next = head; // node baru < nilai head
        head = baru;
        tail->next = head;
    }
    else if (data >= tail->nilai)
    {
        tail->next = baru;
        tail = baru;
        tail->next = head;
    }
    else
    {
        temp = head;
        while (temp->next != head && temp->next->nilai <= data)
        {
            temp = temp->next;
        }
        baru->next = temp->next;
        temp->next = baru;
    }
};

void cetak()
{
    if (head == nullptr)
    {
        cout << " List masih kosong \n";
        return;
    }
    temp = head;
    cout << "Cetak isi list \n";
    do
    {
        cout << temp->nilai << " ,";
        temp = temp->next;
    } while (temp != head);
    cout << endl;
}
void hapusNode(int info_hapus)
{
    if (head == nullptr)
    {
        cout << " List masih kosong \n";
        return;
    }

    temp = tail, hapus = head;
    do
    {
        if (hapus->nilai == info_hapus)
        {
            if (head == tail)
            {
                head = tail = nullptr;
            }
            else
            {
                temp->next = hapus->next;
                if (hapus == head)
                {
                    head = hapus->next;
                }
                if (hapus == tail)
                {
                    tail = temp;
                }
            }
            delete hapus;
            cout<<" Node berhasil dihapus \n";
            return;
        }
        temp = hapus;
        hapus = hapus->next;
    } while (hapus != head);
    cout<<"data "<<info_hapus<<" tidak ditemukan \n";
};

int main(){
    sisipNode(78);
    sisipNode(46);
    sisipNode(99);
    cout<<" Isi list \n ";
    cetak();
    
    hapusNode(46);
    hapusNode(100);
    cout<<"Isi list setelah dihapus \n";
    cetak();
    return 0;
}