#include <iostream>

// mencari nilai min dan max menggunakan pointer
void cariMinMax(int arr[], int n, int *min, int *max)
{
    // inisialisasi min dan max dengan elemen pertama array
    *min = arr[0];
    *max = arr[0];

    // iterasi array untuk memperbarui nilai min dan max di alamat memori
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < *min)
        {
            *min = arr[i];
        }
        if (arr[i] > *max)
        {
            *max = arr[i];
        }
    }
}

int main()
{
    // inisialisasi variabel awal sesuai Hint
    int min = 0, max = 0;

    // deret angka
    int data[] = {12, 5, 45, 2, 89, 23};
    int n = sizeof(data) / sizeof(data[0]);

    // manggil fungsi dengan mengirimkan alamat memori
    cariMinMax(data, n, &min, &max);

    // tampilkan hasil setelah variabel diperbarui oleh fungsi
    std::cout << "Nilai Terkecil (Min): " << min << std::endl;
    std::cout << "Nilai Terbesar (Max): " << max << std::endl;

    return 0;
}