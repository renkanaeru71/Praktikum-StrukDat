#include <iostream>
using namespace std;

void cetakNilai(const int* ptr) {
    // Validasi keamanan pointer
    if (ptr != nullptr) {
        cout << "Nilai: " << *ptr << endl;
    } else {
        cout << "Error: Pointer bernilai null!" << endl;
    }
}

int main() {
    int data = 42;
    int* ptrValid = &data;
    int* ptrKosong = nullptr;

    cetakNilai(ptrValid);  // Aman
    cetakNilai(ptrKosong); // Aman, terhindar dari crash

    return 0;
}