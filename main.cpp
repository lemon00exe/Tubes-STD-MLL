#include <iostream>
#include <string>
#include "tubes.h"

using namespace std;

int main() {
    ListParent LP; ListChild LC;
    createListParent(LP); createListChild(LC);

    insertChild(LC, newChild({"ekonomi", "Gerbong Ekonomi", "50rb", "100"}));
    insertChild(LC, newChild({"bisnis", "Gerbong Bisnis", "100rb", "60"}));
    insertChild(LC, newChild({"eksekutif", "Gerbong Eksekutif", "200rb", "40"}));

    int pilihan;
    string kID, kNama, kAsal, kTujuan, pID, pNama, kls, kID2;

    do {
        cout << "\n========== SISTEM PEMBELIAN TIKET KERETA  ==========" << endl;
        cout << "1.  Tambah Kereta " << endl;
        cout << "2.  Tambah Penumpang & Pilih Kelas " << endl;
        cout << "3.  Hapus Kereta " << endl;
        cout << "4.  Hapus Penumpang " << endl;
        cout << "5.  Hapus Kelas Total" << endl;
        cout << "6.  Tampilkan Semua Data " << endl;
        cout << "7.  Cek Relasi Kereta & Kelas " << endl;
        cout << "8.  Daftar Kereta Berdasarkan Kelas " << endl;
        cout << "9.  Edit Tiket/Pindah Perjalanan " << endl;
        cout << "10. Statistik & Hitung Data" << endl;
        cout << "0.  Keluar" << endl;
        cout << "Pilihan: "; cin >> pilihan;

        switch (pilihan) {
            case 1: // Poin A
                cout << "ID, Nama, Asal, Tujuan: "; cin >> kID >> kNama >> kAsal >> kTujuan;
                insertParent(LP, newParent({kID, kNama, kTujuan, kAsal}));
                break;
            case 2: // Poin C & H
                cout << "ID Kereta & Nama Kelas: "; cin >> kID >> kls;
                if (findParent(LP, kID) && findChild(LC, kls)) {
                    cout << "ID Penumpang & Nama: "; cin >> pID >> pNama;
                    addRelation(findParent(LP, kID), newRelation({pID, pNama}, findChild(LC, kls)));
                } else cout << "Data tidak ditemukan!" << endl;
                break;
            case 3: // Poin D
                cout << "ID Kereta dihapus: "; cin >> kID;
                deleteParent(LP, kID);
                break;
            case 4: // Poin F
                cout << "ID Kereta & ID Penumpang: "; cin >> kID >> pID;
                deleteRelation(findParent(LP, kID), pID);
                break;
            case 5: // Poin E
                cout << "Nama Kelas dihapus: "; cin >> kls;
                deleteChild(LC, LP, kls);
                break;
            case 6: // Poin J, K, O
                showData(LP);
                break;
            case 7: // Poin I
                cout << "ID Kereta & Nama Kelas: "; cin >> kID >> kls;
                if (isRelated(findParent(LP, kID), findChild(LC, kls)))
                    cout << "RELASI DITEMUKAN." << endl;
                else cout << "TIDAK ADA RELASI." << endl;
                break;
            case 8: // Poin N
                cout << "Nama Kelas: "; cin >> kls;
                showParentOfChild(LP, findChild(LC, kls));
                break;
            case 9: // Poin T
                cout << "ID Pen, ID Kereta Baru, Kelas Baru: "; cin >> pID >> kID2 >> kls;
                editRelasi(LP, LC, pID, kID2, kls);
                break;
            case 10: // Poin P, Q, R, S
                menuStatistik(LP, LC);
                break;
        }
    } while (pilihan != 0);
    return 0;
}
