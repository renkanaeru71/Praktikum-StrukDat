#include <iostream>
using namespace std;

int main(){
    int nilai = 90;
    cout << "Nilai: " << nilai << endl;
    cout << "Alamat memori dari nilai: " << &nilai << endl;

    int *ptr = &nilai;
    cout << "isi pointer: " << *ptr << endl;
    cout << "isi alamat memori dari pointer: " << ptr << endl;
    
    *ptr = 80;
    cout << "isi pointer setelah diubah nilainya: " << *ptr << endl;
    cout << "isi nilai setelah diubah melalui pointer: " << nilai << endl;


    // pointer kosong (null)

    int *ptrnull = nullptr;
    if (ptrnull != nullptr) {
        cout << *ptrnull << endl;
    } else {
        cout << "pointer kosong" << endl;
    }

}   