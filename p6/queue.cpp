#include <iostream>
using namespace std;

const int KAPASITAS = 5;

struct queue {
    int data[KAPASITAS];
    int depan;
    int belakang;
    int jumlah;
};

void init(queue& q){
    q.depan = 0;
    q.belakang = -1;
    q.jumlah = 0;
}

bool isempty(queue& q) {
    return q.jumlah == 0;
}

bool isfull(queue& q) {
    return q.jumlah == KAPASITAS;
}

bool enqueue(queue& q, int nilai) {
    if (isfull(q)) {
        cout << "antrian penuh! " << endl;
        return false;
    }
    q.belakang = (q.belakang + 1) % KAPASITAS;
    q.data[q.belakang] = nilai;
    q.jumlah++;
    return true;
}

bool dequeue(queue& q, int& nilai) {
    if (isempty(q)) {
        cout << "antrian kosong! " << endl;
        return false;
    }
    nilai = q.data[q.depan];
    q.depan = (q.depan + 1) % KAPASITAS;
    --q.jumlah;
    return true;
}

void tampilan(queue& q) {
    if (isempty(q)) {
        cout << "antrian kosong! " << endl;
        return;
    }
    cout << "Isi antrian: ";
    for (int i = 0; i < q.jumlah; i++) {
        int index = (q.depan + i) % KAPASITAS;
        cout << q.data[index] << " ";
    }
    cout << endl;
}

int main() {
    queue q;
    init(q);

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    tampilan(q);

    int diambil;
    if (dequeue(q, diambil)) {
        cout << "Nilai yang dikeluarkan: " << diambil << endl;
    }
    tampilan(q);

    enqueue(q, 40);
    enqueue(q, 50);
    enqueue(q, 60);
    tampilan(q);
    return 0;
}