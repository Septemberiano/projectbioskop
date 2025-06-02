#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


 
struct tanggal{
  int tanggal,bulan,tahun;
};
const int maks = 100;
struct biodata{
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
int jumlahpelanggan =0;

struct tayang
{
    int no_film[4] = {1,2,3,4};
     string judul[4] ={"Spiderman No Way Home","Guardian Galaxy","Kimetsu No Yaiba Mugen Train","Jujusu Kaisen Zero"};
     int harga = 35000;
}tayanganfilm;

const int baris = 10;
const int kolom = 4;
struct studio
{
    int nokursi;
    char posisikursi;
    bool terpesan;
};studio korsi[kolom][baris];


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
    cout<<"\t======== Daftar Film =========== \t\n";
    cout<<"\t1. Spiderman No Way Home \t\n";
    cout<<"\t2. Guardian Galaxy \t\n";
    cout<<"\t3. Kimetsu No Yaiba Mugen Train \t\n";
    cout<<"\t4. Jujusu Kaisen Zero \t\n";
    cout<<"harga tiket : Rp 35.000\t\n";
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
    
    cout << "Input Kolom kursi (A-D)  : "; cin >> kolomm;
    cout << "Input Baris kursi (1-10) : "; cin >> bariss;

    int kolomke = kolomm - 'A';
    int bariske = bariss - 1;

    if (korsi[kolomke][bariske].terpesan) {
        cout << "Kursi sudah dipesan, silakan pilih yang lain.\n";
        return kursi(index);  
    }

    korsi[kolomke][bariske].terpesan = true;

    pelanggan[index].baris_kursi = korsi[kolomke][bariske].posisikursi;
    pelanggan[index].nomor_kursi = korsi[kolomke][bariske].nokursi;
}

void inputpelanggan(){
film();
int pembelian;

cout<<"masukan jumlah pembelian : ";cin>>pembelian;
    for (int i = 0; i < pembelian; i++)
    {
        cout<<"Masukan Film (1-4) :"; cin>>pelanggan[jumlahpelanggan].judulfilm ;
        if (pelanggan[jumlahpelanggan].judulfilm == tayanganfilm.no_film[i] )
        {
            tayanganfilm.judul[i];
            pelanggan[jumlahpelanggan].pembayaran = pembelian * tayanganfilm.harga;
        }
       
        cout<<"Masukkan Nama pelanggan : ";getline(cin>>ws,pelanggan[jumlahpelanggan].namapelanggan);cout<<endl;
        cout<<"Pilih Studio : ";cin>>pelanggan[jumlahpelanggan].studio;cout<<endl;
        kursi(i);  
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
void bubblesortarc()
{

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
        
}cout<<"data berhasil di soritng\n";
binsec = true;
simpanDataKeFile();
}
void bubblesortdcs()
{
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
}cout<<"data berhasil di soritng\n";
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
    }cout<<"data berhasil di soritng\n";
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
    }cout<<"data berhasil di soritng\n";
    binsec = true;
simpanDataKeFile();
}


void sentinelSearchNama() {
    string namaCari;
    cout << "\nMasukkan nama pelanggan yang ingin dicari: ";
    getline(cin >> ws, namaCari);

    pelanggan[jumlahpelanggan].namapelanggan = namaCari;

    int i = 0;
    while (pelanggan[i].namapelanggan != namaCari) {
        i++;
    }

    if (i < jumlahpelanggan) {
        cout << "\n==========================================\n";
        cout << setw(20) << left << "Data Ditemukan!" << endl;
        cout << "==========================================\n";
        cout << setw(15) << left << "Nama" << ": " << pelanggan[i].namapelanggan << endl;
        cout << setw(15) << left << "Film" << ": " << pelanggan[i].namafilm << endl;
        cout << setw(15) << left << "Studio" << ": " << pelanggan[i].studio << endl;
        cout << setw(15) << left << "Kursi" << ": " << pelanggan[i].baris_kursi << pelanggan[i].nomor_kursi << endl;
        cout << setw(15) << left << "Pembayaran" << ": Rp " << pelanggan[i].pembayaran << endl;
        cout << "==========================================\n";
    } else {
        cout << "\n==========================================\n";
        cout << setw(20) << left << "Data pelanggan tidak ditemukan!" << endl;
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


void binarysearch(){

    string namaDicari;
    if (binsec == true)
    {
        cout << "Masukkan nama pelanggan yang ingin dicari: ";
cin >> ws;
getline(cin, namaDicari);


for (int i = 0; i < jumlahpelanggan - 1; i++) {
    for (int j = 0; j < jumlahpelanggan - i - 1; j++) {
        if (pelanggan[j].namapelanggan > pelanggan[j + 1].namapelanggan) {
            swap(pelanggan[j], pelanggan[j + 1]);
        }
    }
}

int kiri = 0;
int kanan = jumlahpelanggan - 1;
bool ditemukan = false;

while (kiri <= kanan) {
    int tengah = (kiri + kanan) / 2;
    if (pelanggan[tengah].namapelanggan == namaDicari) {
        cout << "\nData Ditemukan:\n";
        cout << "Nama       : " << pelanggan[tengah].namapelanggan << endl;
        cout << "Judul Film : " << pelanggan[tengah].namafilm << endl;
        cout << "Studio     : " << pelanggan[tengah].studio << endl;
        cout << "Kursi      : " << pelanggan[tengah].baris_kursi << pelanggan[tengah].nomor_kursi << endl;
        cout << "Pembayaran : Rp " << pelanggan[tengah].pembayaran << endl;
        ditemukan = true;
        break;
    } else if (pelanggan[tengah].namapelanggan < namaDicari) {
        kiri = tengah + 1;
    } else {
        kanan = tengah - 1;
    }
}

if (!ditemukan) {
    cout << "\nData pelanggan tidak ditemukan.\n";
}
    }
  if (binsec == false)
  {
    cout<<"sorting biner dulu yah\n\t";
  }
  


}





 void menuutama(){
    int pilihan2;
    do
    {
            cout<<"===Selamat Datang Di Bioskop Sigma===\n";
    cout<<"1. Pembelian Tiket Film\n";
    cout<<"2. Data Pembelian Tiket Film\n";
    cout<<"3. Pencarian Data Pembeli\n";
    cout<<"4. Sorting Data Pembeli\n";
    cout<<"5.keluar\n";

    cout<<"masukan pilihan anda :";cin>>pilihan;
    switch (pilihan)
    {
    case 1:
        inputpelanggan();
        break;
    case 2:
    bacaDataDariFile();
    tampilkanData();
        break; 
    case 3 :do
    {
        cout<<"==== Pencarian Data ===\n\t";
    cout<<"Pilih metodi Pencarian \n\t";
    cout<<"1. Sequential non sentinel\n\t";
    cout<<"2. Squiential Sentinel\n\t";
    cout<<"3. Binary Search\n\t";
    cout<<"masukan pilihan anda :"; cin>>pilihan2;
    switch (pilihan2)
    {
    case 1:
        sequentialSearchNama();
        break;
    case 2 :
    sentinelSearchNama();
    case 3 : binarysearch();
   
    break;
    default:
        break;
    }
    } while (pilihan2 > 0 || pilihan2 == 3);
    
    
    break;
    case  4: int sorting,metode;
    do
    {  
         cout<<"==Sorting Data==\t\n";
      cout<<"1.Berdasarkan Kursi \n\t";
      cout<<"2.berdasarkan nama\n\t";
      cout<<"3.keluar\t\n";
      switch (sorting)
      {
      case 1 : do
      {
          cout<<"====sorting berdasarkan kursi===\n\t";
              cout<<"1. bubble sort ascending\n\t";
              cout<<"2. bubble sort descending\n\t";
              cout<<"3. bubble selection ascending\n\t";
              cout<<"4. bubble selection descending\n\t";
              cout<<"5. keluar\n\t";
              switch (metode)
              {
              case 1:
                bubblesortarc;
                break;
              case 2 : 
              bubblesortdcs;
              break;
              case 3 :
              selectionSortAscending;
              break;
              case 4: 
              selectionSortDescending;
              case 5 :
              return;
              break;
              default:
                break;
              }
      } while (metode > 0 || metode == 5);
      
            
        break;
      case 2:do
      {
           cout<<"====sorting berdasarkan nama===\n\t";
              cout<<"1. bubble sort ascending\n\t";
              cout<<"2. bubble sort descending\n\t";
              cout<<"3. bubble selection ascending\n\t";
              cout<<"4. bubble selection descending\n\t";
              cout<<"5. binery sort ascending\n\t";
              cout<<"6. binery sort descending\n\t";
              cout<<"7. keluar\n\t";
              switch (metode)
              {
              case 1:
                bubbleSortNamaAscending();
                break;
              case 2 : 
              bubbleSortNamaDescending();
              break;
              case 3 :
              selectionSortNamaAscending();
              break;
              case 4: 
              selectionSortNamaDescending();
              case 5 :
              bubblesortarc();
              break;
              case 6: 
              bubblesortdcs();
              case 7:
              break;
              default:
                break;
              }
      } while (sorting > 0 || sorting == 7);
      
         
      break;
      default:
        break;
      }

    } while (sorting);
    
     
    break;
    case 5 :
    break;
    default:
        break;
    }
    
    }  while (pilihan > 0 || pilihan == 5);
  
  
    
 }
 void login(int coba =0) {
    if (coba > 3) {
        cout << "Terlalu banyak percobaan! Program keluar.\n";
        return;
    }

    string user, pass;
    cout << "Masukan Username: "; cin >> user;
    cout << "Masukan Password: "; cin >> pass;

    if (user == "admin" && pass == "123") {
        cout << "Login berhasil!\n";
        menuutama();
    } else {
        cout << "Login gagal, coba lagi.\n";
        login(coba + 1); 
    }
}

int main(){
inisialisasikursi();
   bacaDataDariFile();
   login();
    
    }
   
    
    
 
    

