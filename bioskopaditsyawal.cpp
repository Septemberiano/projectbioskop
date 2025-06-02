#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;

struct tanggal {
    int tanggal, bulan, tahun;
};

const int maks = 100;

struct biodata {
    string namapelanggan;
    string namafilm;
    int judulfilm;
    string studio;
    int pembayaran;
    float jam;
    char baris_kursi;
    int nomor_kursi;
};
biodata pelanggan[maks];
int jumlahpelanggan = 0;

struct tayang {
    int no_film[4] = {1, 2, 3, 4};
    string judul[4] = {"Spiderman No Way Home", "Guardian Galaxy", "Kimetsu No Yaiba Mugen Train", "Jujusu Kaisen Zero"};
    int harga = 35000;
} tayanganfilm;

const int baris = 10;
const int kolom = 4;

struct studio {
    int nokursi;
    char posisikursi;
    bool terpesan;
};
studio korsi[kolom][baris];

bool binsec = false;
int pilihan;

void simpanDataKeFile() {
    ofstream file("bioskop.txt", ios::app);
    if (!file) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    for (int i = 0; i < jumlahpelanggan; i++) {
        file << pelanggan[i].namapelanggan << " "
             << pelanggan[i].judulfilm << " "
             << pelanggan[i].studio << " "
             << pelanggan[i].pembayaran << " "
             << pelanggan[i].baris_kursi << " "
             << pelanggan[i].nomor_kursi << endl;
    }
    file.close();
    cout << "Data berhasil disimpan ke bioskop.txt!" << endl;
}

void bacaDataDariFile() {
    jumlahpelanggan = 0;
    ifstream file("bioskop.txt");
    if (!file) {
        cout << "Gagal membuka file atau file belum ada!" << endl;
        return;
    }
    string nama, studio;
    int judul, bayar;
    char baris;
    int nomor;
    while (file >> nama >> judul >> studio >> bayar >> baris >> nomor) {
        pelanggan[jumlahpelanggan].namapelanggan = nama;
        pelanggan[jumlahpelanggan].judulfilm = judul;
        pelanggan[jumlahpelanggan].studio = studio;
        pelanggan[jumlahpelanggan].pembayaran = bayar;
        pelanggan[jumlahpelanggan].baris_kursi = baris;
        pelanggan[jumlahpelanggan].nomor_kursi = nomor;
        jumlahpelanggan++;
    }
    file.close();
}

void film() {
    cout << "\t======== Daftar Film =========== \t\n";
    cout << "\t1. Spiderman No Way Home \t\n";
    cout << "\t2. Guardian Galaxy \t\n";
    cout << "\t3. Kimetsu No Yaiba Mugen Train \t\n";
    cout << "\t4. Jujusu Kaisen Zero \t\n";
    cout << "harga tiket : Rp 35.000\t\n";
}

void inisialisasikursi() {
    for (int i = 0; i < kolom; i++) {
        for (int j = 0; j < baris; j++) {
            korsi[i][j].posisikursi = 'A' + i;
            korsi[i][j].nokursi = j + 1;
            korsi[i][j].terpesan = false;
        }
    }
}

void tampilkanKursi() {
    cout << "\nTampilan Kursi Bioskop:\n";
    for (int i = 0; i < kolom; i++) {
        cout << korsi[i][0].posisikursi << " ";
        for (int j = 0; j < baris; j++) {
            cout << "[" << (korsi[i][j].terpesan ? 'X' : 'O') << "]";
        }
        cout << endl;
    }
    cout << "   ";
    for (int j = 0; j < baris; j++) {
        cout << setw(3) << j + 1;
    }
    cout << "\n\n";
}

void kursi(int index) {
    char kolomm;
    int bariss;
    tampilkanKursi();
    cout << "Input Kolom kursi (A-D): ";
    cin >> kolomm;
    kolomm = toupper(kolomm);
    cout << "Input Baris kursi (1-10): ";
    while (!(cin >> bariss) || bariss < 1 || bariss > 10) {
        cout << "Baris cuma 1-10 bro! Coba lagi: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    int kolomke = kolomm - 'A';
    int bariske = bariss - 1;
    if (kolomke < 0 || kolomke >= kolom || bariske < 0 || bariske >= baris) {
        cout << "Kolom cuma A-D, baris 1-10! Coba lagi!\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return kursi(index);
    }
    if (korsi[kolomke][bariske].terpesan) {
        cout << "Kursi udah dipesen, pilih lain bro!\n";
        return kursi(index);
    }
    korsi[kolomke][bariske].terpesan = true;
    pelanggan[index].baris_kursi = korsi[kolomke][bariske].posisikursi;
    pelanggan[index].nomor_kursi = korsi[kolomke][bariske].nokursi;
}

void inputpelanggan() {
    film();
    int pembelian;
    cout << "Masukkan jumlah pembelian: ";
    while (!(cin >> pembelian) || pembelian <= 0 || pembelian > maks - jumlahpelanggan) {
        cout << "Jumlah gak valid (1-" << maks - jumlahpelanggan << ")! Coba lagi: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    for (int i = 0; i < pembelian; i++) {
        cout << "Masukkan Film (1-4): ";
        while (!(cin >> pelanggan[jumlahpelanggan].judulfilm) || pelanggan[jumlahpelanggan].judulfilm < 1 || pelanggan[jumlahpelanggan].judulfilm > 4) {
            cout << "Film cuma 1-4 bro! Coba lagi: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        if (pelanggan[jumlahpelanggan].judulfilm >= 1 && pelanggan[jumlahpelanggan].judulfilm <= 4) {
            pelanggan[jumlahpelanggan].namafilm = tayanganfilm.judul[pelanggan[jumlahpelanggan].judulfilm - 1];
            pelanggan[jumlahpelanggan].pembayaran = tayanganfilm.harga;
        }
        cout << "Masukkan Nama pelanggan: ";
        getline(cin >> ws, pelanggan[jumlahpelanggan].namapelanggan);
        cout << "Pilih Studio: ";
        getline(cin >> ws, pelanggan[jumlahpelanggan].studio);
        kursi(jumlahpelanggan);
        jumlahpelanggan++;
    }
    simpanDataKeFile();
}

void tampilkanData() {
    if (jumlahpelanggan == 0) {
        cout << "\nBelum ada data pelanggan yang tersimpan!\n";
        return;
    }
    for (int i = 0; i < jumlahpelanggan; i++) {
        if (pelanggan[i].judulfilm >= 1 && pelanggan[i].judulfilm <= 4) {
            pelanggan[i].namafilm = tayanganfilm.judul[pelanggan[i].judulfilm - 1];
        }
    }
    cout << "\n==========================================\n";
    cout << setw(15) << left << "Nama"
         << setw(25) << left << "Film"
         << setw(15) << left << "Studio"
         << setw(10) << left << "Kursi"
         << setw(15) << left << "Pembayaran"
         << endl;
    cout << "==========================================\n";
    for (int i = 0; i < jumlahpelanggan; i++) {
        cout << setw(15) << left << pelanggan[i].namapelanggan
             << setw(25) << left << pelanggan[i].namafilm
             << setw(15) << left << pelanggan[i].studio
             << pelanggan[i].baris_kursi << pelanggan[i].nomor_kursi << "    "
             << "Rp " << pelanggan[i].pembayaran << endl;
    }
    cout << "==========================================\n";
}

void bubbleSortNamaAscending() {
    for (int i = 0; i < jumlahpelanggan - 1; i++) {
        for (int j = 0; j < jumlahpelanggan - i - 1; j++) {
            if (pelanggan[j].namapelanggan > pelanggan[j + 1].namapelanggan) {
                swap(pelanggan[j], pelanggan[j + 1]);
            }
        }
    }
    cout << "Data berhasil disorting berdasarkan nama (A-Z).\n";
    simpanDataKeFile();
}

void bubbleSortNamaDescending() {
    for (int i = 0; i < jumlahpelanggan - 1; i++) {
        for (int j = 0; j < jumlahpelanggan - i - 1; j++) {
            if (pelanggan[j].namapelanggan < pelanggan[j + 1].namapelanggan) {
                swap(pelanggan[j], pelanggan[j + 1]);
            }
        }
    }
    cout << "Data berhasil disorting berdasarkan nama (Z-A).\n";
    binsec = true;
    simpanDataKeFile();
}

void selectionSortNamaAscending() {
    for (int i = 0; i < jumlahpelanggan - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < jumlahpelanggan; j++) {
            if (pelanggan[j].namapelanggan < pelanggan[minIndex].namapelanggan) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(pelanggan[i], pelanggan[minIndex]);
        }
    }
    cout << "Data berhasil disorting berdasarkan nama (A-Z).\n";
    simpanDataKeFile();
}

void selectionSortNamaDescending() {
    for (int i = 0; i < jumlahpelanggan - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < jumlahpelanggan; j++) {
            if (pelanggan[j].namapelanggan > pelanggan[maxIndex].namapelanggan) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            swap(pelanggan[i], pelanggan[maxIndex]);
        }
    }
    cout << "Data berhasil disorting berdasarkan nama (Z-A).\n";
    binsec = true;
    simpanDataKeFile();
}

void bubblesortarc() {
    for (int i = 0; i < jumlahpelanggan - 1; i++) {
        for (int j = 0; j < jumlahpelanggan - i - 1; j++) {
            if (
                pelanggan[j].baris_kursi > pelanggan[j + 1].baris_kursi ||
                (pelanggan[j].baris_kursi == pelanggan[j + 1].baris_kursi &&
                 pelanggan[j].nomor_kursi > pelanggan[j + 1].nomor_kursi)
            ) {
                swap(pelanggan[j], pelanggan[j + 1]);
            }
        }
    }
    cout << "Data berhasil disortir berdasarkan kursi (ascending).\n";
    binsec = true;
    simpanDataKeFile();
}

void bubblesortdcs() {
    for (int i = 0; i < jumlahpelanggan - 1; i++) {
        for (int j = 0; j < jumlahpelanggan - i - 1; j++) {
            if (
                pelanggan[j].baris_kursi < pelanggan[j + 1].baris_kursi ||
                (pelanggan[j].baris_kursi == pelanggan[j + 1].baris_kursi &&
                 pelanggan[j].nomor_kursi < pelanggan[j + 1].nomor_kursi)
            ) {
                swap(pelanggan[j], pelanggan[j + 1]);
            }
        }
    }
    cout << "Data berhasil disortir berdasarkan kursi (descending).\n";
    simpanDataKeFile();
}

void selectionSortAscending() {
    for (int i = 0; i < jumlahpelanggan - 1; i++) {
        for (int j = i + 1; j < jumlahpelanggan; j++) {
            if (
                pelanggan[i].baris_kursi > pelanggan[j].baris_kursi ||
                (pelanggan[i].baris_kursi == pelanggan[j].baris_kursi &&
                 pelanggan[i].nomor_kursi > pelanggan[j].nomor_kursi)
            ) {
                swap(pelanggan[i], pelanggan[j]);
            }
        }
    }
    cout << "Data berhasil disortir berdasarkan kursi (ascending).\n";
    simpanDataKeFile();
}

void selectionSortDescending() {
    for (int i = 0; i < jumlahpelanggan - 1; i++) {
        for (int j = i + 1; j < jumlahpelanggan; j++) {
            if (
                pelanggan[i].baris_kursi < pelanggan[j].baris_kursi ||
                (pelanggan[i].baris_kursi == pelanggan[j].baris_kursi &&
                 pelanggan[i].nomor_kursi < pelanggan[j].nomor_kursi)
            ) {
                swap(pelanggan[i], pelanggan[j]);
            }
        }
    }
    cout << "Data berhasil disortir berdasarkan kursi (descending).\n";
    binsec = true;
    simpanDataKeFile();
}

void sentinelSearchNama() {
    string namaCari;
    cout << "\nMasukkan nama pelanggan yang mau dicari: ";
    getline(cin >> ws, namaCari);
    bool ketemu = false;
    for (int i = 0; i < jumlahpelanggan; i++) {
        if (pelanggan[i].namapelanggan == namaCari) {
            ketemu = true;
            cout << "\n==========================================\n";
            cout << setw(20) << left << "Data Ditemukan!" << endl;
            cout << "==========================================\n";
            cout << setw(15) << left << "Nama" << ": " << pelanggan[i].namapelanggan << endl;
            cout << setw(15) << left << "Film" << ": " << pelanggan[i].namafilm << endl;
            cout << setw(15) << left << "Studio" << ": " << pelanggan[i].studio << endl;
            cout << setw(15) << left << "Kursi" << ": " << pelanggan[i].baris_kursi << pelanggan[i].nomor_kursi << endl;
            cout << setw(15) << left << "Pembayaran" << ": Rp " << pelanggan[i].pembayaran << endl;
            cout << "==========================================\n";
            break;
        }
    }
    if (!ketemu) {
        cout << "\n==========================================\n";
        cout << setw(20) << left << "Data pelanggan gak ketemu!" << endl;
        cout << "==========================================\n";
    }
}

void sequentialSearchNama() {
    bool ditemukan = false;
    string namaCari;
    cout << "\nMasukkan nama pelanggan yang ingin dicari: ";
    getline(cin >> ws, namaCari);
    for (int i = 0; i < jumlahpelanggan; i++) {
        if (pelanggan[i].namapelanggan == namaCari) {
            ditemukan = true;
            cout << "\n==========================================\n";
            cout << setw(20) << left << "Data Ditemukan!" << endl;
            cout << "==========================================\n";
            cout << setw(15) << left << "Nama" << ": " << pelanggan[i].namapelanggan << endl;
            cout << setw(15) << left << "Film" << ": " << pelanggan[i].namafilm << endl;
            cout << setw(15) << left << "Studio" << ": " << pelanggan[i].studio << endl;
            cout << setw(15) << left << "Kursi" << ": " << pelanggan[i].baris_kursi << pelanggan[i].nomor_kursi << endl;
            cout << setw(15) << left << "Pembayaran" << ": Rp " << pelanggan[i].pembayaran << endl;
            cout << "==========================================\n";
            break;
        }
    }
    if (!ditemukan) {
        cout << "\n==========================================\n";
        cout << setw(20) << left << "Data pelanggan tidak ditemukan!" << endl;
        cout << "==========================================\n";
    }
}

void binarysearch() {
    if (!binsec) {
        cout << "Data harus disortir dulu buat binary search bro!\n";
        return;
    }
    string namaDicari;
    cout << "Masukkan nama pelanggan yang mau dicari: ";
    getline(cin >> ws, namaDicari);
    int kiri = 0;
    int kanan = jumlahpelanggan - 1;
    bool ketemu = false;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        if (pelanggan[tengah].namapelanggan == namaDicari) {
            cout << "\nData Ditemukan:\n";
            cout << "Nama       : " << pelanggan[tengah].namapelanggan << endl;
            cout << "Judul Film : " << pelanggan[tengah].namafilm << endl;
            cout << "Studio     : " << pelanggan[tengah].studio << endl;
            cout << "Kursi      : " << pelanggan[tengah].baris_kursi << pelanggan[tengah].nomor_kursi << endl;
            cout << "Pembayaran : Rp " << pelanggan[tengah].pembayaran << endl;
            ketemu = true;
            break;
        } else if (pelanggan[tengah].namapelanggan < namaDicari) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    if (!ketemu) {
        cout << "\nData pelanggan gak ketemu.\n";
    }
}

void menuutama() {
    int pilihan;
    do {
        cout << "===Selamat Datang Di Bioskop Sigma===\n";
        cout << "1. Beli Tiket Film\n";
        cout << "2. Liat Data Pembelian\n";
        cout << "3. Cari Data Pembeli\n";
        cout << "4. Sortir Data Pembeli\n";
        cout << "5. Keluar\n";
        cout << "Pilih (1-5): ";
        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 5) {
            cout << "Pilih cuma 1-5 bro! Coba lagi: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        switch (pilihan) {
            case 1:
                inputpelanggan();
                break;
            case 2:
                bacaDataDariFile();
                tampilkanData();
                break;
            case 3: {
                int cari;
                do {
                    cout << "\n=== Pencarian Data ===\n";
                    cout << "1. Sequential Non-Sentinel\n";
                    cout << "2. Sequential Sentinel\n";
                    cout << "3. Binary Search\n";
                    cout << "4. Kembali\n";
                    cout << "Pilih (1-4): ";
                    while (!(cin >> cari) || cari < 1 || cari > 4) {
                        cout << "Pilih cuma 1-4 bro! Coba lagi: ";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    switch (cari) {
                        case 1:
                            sequentialSearchNama();
                            break;
                        case 2:
                            sentinelSearchNama();
                            break;
                        case 3:
                            binarysearch();
                            break;
                        case 4:
                            break;
                    }
                } while (cari != 4);
                break;
            }
            case 4: {
                int sort;
                do {
                    cout << "\n=== Sorting Data ===\n";
                    cout << "1. Sortir Kursi\n";
                    cout << "2. Sortir Nama\n";
                    cout << "3. Kembali\n";
                    cout << "Pilih (1-3): ";
                    while (!(cin >> sort) || sort < 1 || sort > 3) {
                        cout << "Pilih cuma 1-3 bro! Coba lagi: ";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    if (sort == 1) {
                        int metode;
                        do {
                            cout << "\n=== Sorting Kursi ===\n";
                            cout << "1. Bubble Sort Ascending\n";
                            cout << "2. Bubble Sort Descending\n";
                            cout << "3. Selection Sort Ascending\n";
                            cout << "4. Selection Sort Descending\n";
                            cout << "5. Kembali\n";
                            cout << "Pilih (1-5): ";
                            while (!(cin >> metode) || metode < 1 || metode > 5) {
                                cout << "Pilih cuma 1-5 bro! Coba lagi: ";
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            switch (metode) {
                                case 1:
                                    bubblesortarc();
                                    break;
                                case 2:
                                    bubblesortdcs();
                                    break;
                                case 3:
                                    selectionSortAscending();
                                    break;
                                case 4:
                                    selectionSortDescending();
                                    break;
                                case 5:
                                    break;
                            }
                        } while (metode != 5);
                    } else if (sort == 2) {
                        int metode;
                        do {
                            cout << "\n=== Sorting Nama ===\n";
                            cout << "1. Bubble Sort Ascending\n";
                            cout << "2. Bubble Sort Descending\n";
                            cout << "3. Selection Sort Ascending\n";
                            cout << "4. Selection Sort Descending\n";
                            cout << "5. Kembali\n";
                            cout << "Pilih (1-5): ";
                            while (!(cin >> metode) || metode < 1 || metode > 5) {
                                cout << "Pilih cuma 1-5 bro! Coba lagi: ";
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            switch (metode) {
                                case 1:
                                    bubbleSortNamaAscending();
                                    break;
                                case 2:
                                    bubbleSortNamaDescending();
                                    break;
                                case 3:
                                    selectionSortNamaAscending();
                                    break;
                                case 4:
                                    selectionSortNamaDescending();
                                    break;
                                case 5:
                                    break;
                            }
                        } while (metode != 5);
                    }
                } while (sort != 3);
                break;
            }
            case 5:
                cout << "Bye bro, thanks pake Bioskop Sigma!\n";
                return;
        }
    } while (pilihan != 5);
}

void login(int coba = 0) {
    if (coba > 3) {
        cout << "Terlalu banyak percobaan! Program keluar.\n";
        return;
    }
    string user, pass;
    cout << "Masukan Username: ";
    cin >> user;
    cout << "Masukan Password: ";
    cin >> pass;
    if (user == "admin" && pass == "123") {
        cout << "Login berhasil!\n";
        menuutama();
    } else {
        cout << "Login gagal, coba lagi.\n";
        login(coba + 1);
    }
}

int main() {
    inisialisasikursi();
    bacaDataDariFile();
    login();
}