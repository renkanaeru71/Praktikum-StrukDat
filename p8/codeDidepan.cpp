#include <iostream>
using namespace std;

struct Node { 
    int data;
    Node* left;
    Node* right;
};
// Inorder --> left --> root -- >  right

void inorder(Node* node){
    if(node == nullptr){
        return;
    }
    inorder(node->left);//untuk menulusuri ke kiri
    cout << node->data << " "; // untuk mencetak node data
    inorder(node->right);   // untuk menulusuri ke kanan
}

bool insert(Node*& node, int nilai){
    //ketika nodenya itu kosong atau nullptr
    if(node == nullptr){
    node = new Node {nilai, nullptr, nullptr};// buat node baru alias buat root
    return true; // berhasil ngeinsert data
}
 // ketika nilai kurang dari node/root
    if (nilai < node->data){
        return insert(node->left, nilai); // data bakal menelusuri ke kiri
    }
    //ketika nilai lebih dari node/root
    if (nilai >  node->data){
        return insert(node->right, nilai); // data bakal menelusuri ke kanan
    }
    return false;
}

void gambarTree(Node* node, int depth = 0, char cabang = ' '){
        if(node == nullptr){
            return;
        }
        gambarTree(node->right, depth + 1, '/');
        for(int i = 0;i<depth; i++){
            cout << "       "; //cout 7 spasi
        }
        if(cabang!=' '){
            cout << cabang <<"---";
        }
        cout << "[" << node->data<< "]/n";
        gambarTree(node->left, depth + 1, '\\');//dianggap sbg satu 
}

Node* cari(Node* node, int target){
    //kondisi ketemu
        if(node == nullptr || target == node->data){
            return node;// mereturn isi dari node, karena node itu variable pointer, maka dia mereturn alamat   
        }
        //kondisi ketika yang mau dicari itu kurang dari node 
        if (target < node-> data){
            return cari(node->left, target);
        }
        return cari(node->right, target );
    }

    // fungsi untuk mencari nilai yang paling kecil di pohon kita, alias nilai minimum
    Node* minimum(Node* node){
        if(node == nullptr){
            return nullptr;// artinya dia ngasih tau kalo nodenya itu kosong
        }
        while(node->left!= nullptr){ 
            node = node->left;// bakal geser ke kiri
        }
        return node;
    }
    bool hapus(Node* node, int nilaiHapus){
    if(node == nullptr){
        return false;
    }
    if(nilaiHapus< node ->data){
        return hapus( node->left,nilaiHapus);
    }else if(nilaiHapus>node->data){
        return hapus( node->right,nilaiHapus);
    }else{
        // ada beberapa kasus
        //childnya 0 
        if(node->left == nullptr && node->right==nullptr){
            delete node;
            node = nullptr;
        }
        //childnya itu ada 1, satu yng ada di kiri atau kanan
        //child 1 tapi yang sebelah kanan
        else if(node->left==nullptr){
            Node* alatBantu = node; // membantu nyimpen node
            node = node->right;
            delete alatBantu;
        }
        //child 1 tapi yang sebelah kanan
        else if (node->right == nullptr){
        Node* alatBantu = node;
            node = node->left;
            delete alatBantu;
        //chilldnya itu ada 2
    }
    else { 
        Node* successor = minimum(node->right);//nilai paling kecil dari subtree kanannnya root
        node-> data= successor->data;
        hapus(node->right, successor->data);
    }
    }
}
int main(){
    Node* node = nullptr; // awal awal kosogn atau nullptr
    int angka[] = {50, 55, 40, 30, 60, 65, 35, 40, 10, 70};
    for (int x : angka){
        insert(node, x);
    }

    gambarTree(node);

}