// Aplikasi Perpus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Buku
{
    string ISBN;
    string Judul;
    int Stok;
    int Dipinjam;
    bool Dihapus;
};

vector<Buku> DaftarBuku;

struct FindResponse
{
    bool DataFound;
    int FoundIndex;
    Buku DataBuku;
};

static FindResponse CariBuku(string ISBN)
{
    FindResponse Response;

    for (int i = 0; i < size(DaftarBuku); i++)
    {
        if (DaftarBuku[i].ISBN == ISBN && !DaftarBuku[i].Dihapus)
        {
            Response.DataFound = true;
            Response.FoundIndex = i;
            Response.DataBuku = DaftarBuku[i];
        }
    }

    return Response;
}

static void AmbilDaftarBuku()
{
    if (size(DaftarBuku) < 1)
    {
        cout << "Belum ada buku di perpustakaan!\n";
        return;
    }

    cout << "================= DAFTAR BUKU =================\n";

    for (int i = 0; i < size(DaftarBuku); i++)
    {
        Buku dataBuku = DaftarBuku[i];

        if (!dataBuku.Dihapus)
        {
            cout << i + 1 << ". " << dataBuku.ISBN << " - " << dataBuku.Judul << ". Stok: " << (dataBuku.Stok - dataBuku.Dipinjam) << "\n";
        }
    }
    
    cout << "===============================================\n";
}

static void TambahBuku()
{
    Buku DataBuku;
    string ISBN;
    string Judul;
    bool FoundSameISBN = false;
    int Stok;

    cout << "================== INPUT BUKU =================\n";
    cout << "ISBN: ";
    cin.ignore();
    getline(cin, ISBN);
    cout << "Judul: ";
    getline(cin, Judul);
    cout << "Stok: ";
    cin >> Stok;

    for (int i = 0; i < size(DaftarBuku); i++)
    {
        if (DaftarBuku[i].ISBN == ISBN) {
            FoundSameISBN = true;
        }
    }

    if (FoundSameISBN)
    {
        cout << "Tidak dapat menambahkan: buku telah terdaftar sebelumnya!\n";
        cout << "===============================================\n";
        return;
    }

    DataBuku.ISBN = ISBN;
    DataBuku.Judul = Judul;
    DataBuku.Stok = Stok;
    DataBuku.Dipinjam = 0;
    DataBuku.Dihapus = false;

    DaftarBuku.push_back(DataBuku);
    cout << "===============================================\n";
}

static void PinjamBuku()
{
    string ISBN;
    cout << "============== PEMINJAMAN BUKU ================\n";
    cout << "Masukkan ISBN: ";
    cin.ignore();
    getline(cin, ISBN);
    
    FindResponse FoundBook = CariBuku(ISBN);

    // Jika buku tidak ketemu
    if (!FoundBook.DataFound)
    {
        cout << "Buku tidak tersedia!\n";
        cout << "===============================================\n";
        return;
    }

    // Jika buku yang dipinjam habis
    if (FoundBook.DataBuku.Stok - FoundBook.DataBuku.Dipinjam < 1)
    {
        cout << "Stock tidak tersedia!\n";
        cout << "===============================================\n";
        return;
    }

    DaftarBuku[FoundBook.FoundIndex].Dipinjam++;

    // Beritahu user jika buku berhasil dipinjam!
    cout << "Buku " << FoundBook.DataBuku.Judul << " berhasil dipinjam!\n";
    cout << "===============================================\n";
}

static void KembalikanBuku()
{
    string ISBN;

    cout << "============== KEMBALIKAN BUKU ==============\n";
    cout << "Masukkan ISBN: ";
    cin.ignore();
    getline(cin, ISBN);

    FindResponse BookResult = CariBuku(ISBN);

    // Jika buku tidak ketemu
    if (!BookResult.DataFound)
    {
        cout << "Buku tidak tersedia!\n";
        cout << "===============================================\n";
        return;
    }

    DaftarBuku[BookResult.FoundIndex].Dipinjam--;
    // Beritahu user jika buku berhasil dikembalikan!
    cout << "Buku " << BookResult.DataBuku.Judul << " berhasil dikembalikan!\n";
    cout << "===============================================\n";
}

static void HapusBuku()
{
    string ISBN;
    cout << "================= HAPUS BUKU ==================\n";
    cout << "Masukkan ISBN: ";
    cin.ignore();
    getline(cin, ISBN);

    FindResponse BookResult = CariBuku(ISBN);

    if (!BookResult.DataFound)
    {
        cout << "Buku tidak tersedia!\n";
        cout << "===============================================\n";
        return;
    }

    DaftarBuku[BookResult.FoundIndex].Dihapus = true;
    cout << "Buku " << BookResult.DataBuku.Judul << " berhasil dihapus!\n";
    cout << "===============================================\n";
}

int main()
{
    int Action;

    cout << "============ PROGRAM PERPUSTAKAAN ============\n";
    cout << "Pilih menu:\n";
    cout << "1. Daftar buku\n";
    cout << "2. Tambah buku\n";
    cout << "3. Pinjam buku\n";
    cout << "4. Kembalikan buku\n";
    cout << "5. Hapus buku\n";
    cout << "0. Keluar aplikasi.\n";
    cout << "Masukkan pilihan: ";
    cin >> Action;

    switch (Action)
    {
    case 1:
        system("cls");
        AmbilDaftarBuku();
        main();
        break;

    case 2:
        system("cls");
        TambahBuku();
        main();
        break;

    case 3:
        system("cls");
        PinjamBuku();
        main();
        break;

    case 4:
        system("cls");
        KembalikanBuku();
        main();
        break;

    case 5:
        system("cls");
        HapusBuku();
        main();
        break;

    case 0:
        exit(0);
        break;

    default:
        system("cls");
        cout << "Input tidak valid!\n";
        main();
    }
}
