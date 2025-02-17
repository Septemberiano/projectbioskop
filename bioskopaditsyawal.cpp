#include <iostream>
using namespace std;


struct tanggal{
  int tanggal,bulan,tahun;
};
struct biodata{
    tanggal datatanggal;
    string nama;
    string namafilm;
    string studio;
    string kursi;
    int jam [2];
};
biodata pelanggan[100];



void film() {
    cout<<"\t======== Daftar Film =========== \t\n";
    cout<<"\t1. Spiderman No Way Home \t\n";
    cout<<"\t2. Guardian Galaxy \t\n";
    cout<<"\t3. Kimetsu No Yaiba Mugen Train \t\n";
    cout<<"\t4. Jujusu Kaisen Zero \t\n";
    
}
 

int main(){
    int pilihan;
    cout<<"Selamat Data Di Bioskop Ambarowo\n"; 
    cout<<"1.Daftar Film Tayang\n";
    cout<<"2.Pembelian tiket\n";
    cout<<"3.Riwayat pembelian tiket\n";
    cout<<"Pilihan Anda : ";cin>>pilihan;
    if ( pilihan == 1)
    {
        film();
    }
    

}