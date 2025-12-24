#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

struct InfoP {
    string idPenumpang;
    string nama;
};

struct InfoK {
    string idKereta;
    string namaKereta;
    string tujuan;
    string asal;
};

struct InfoC {
    string ekonomi;
    string deskripsi;
    string harga;
    string fasilitas;
};

typedef struct ElmParent* adrParent;
typedef struct ElmChild* adrChild;
typedef struct ElmRelation* adrRelation;

struct ElmChild {
    InfoC info;
    adrChild next;
};

struct ElmRelation {
    InfoP info;
    adrChild childPtr;
    adrRelation next;
};

struct ElmParent {
    InfoK info;
    adrParent next;
    adrRelation firstRelation;
};
struct ListParent { adrParent first; };
struct ListChild { adrChild first; };


void createListParent(ListParent &LP);
void createListChild(ListChild &LC);
adrParent newParent(InfoK data);
adrChild newChild(InfoC data);
adrRelation newRelation(InfoP data, adrChild child);

// --- INSERT (Poin A, B, C) ---
void insertParent(ListParent &LP, adrParent P);
void insertChild(ListChild &LC, adrChild C);
void addRelation(adrParent parent, adrRelation R);

// --- DELETE (Poin D, E, F) ---
void deleteParent(ListParent &LP, string idKereta);
void deleteChild(ListChild &LC, ListParent &LP, string namaKelas);
void deleteRelation(adrParent P, string idPenumpang);

// --- FIND (Poin G, H, I) ---
adrParent findParent(ListParent LP, string idKereta);
adrChild findChild(ListChild LC, string namaKelas);
bool isRelated(adrParent P, adrChild C);

// --- SHOW (Poin J, K, L, M, N, O) ---
void showAllParent(ListParent LP);
void showAllChild(ListChild LC);
void showChildOfParent(adrParent P);
void showParentOfChild(ListParent LP, adrChild C);
void showData(ListParent LP);
void showChildWithParents(ListChild LC, ListParent LP);

// --- COUNT (Poin P, Q, R, S) ---
int countChildOfParent(adrParent P);
int countParentOfChild(ListParent LP, adrChild C);
int countOrphanChild(ListChild LC, ListParent LP);
int countEmptyParent(ListParent LP);

// --- EDIT (Poin T) ---
void editRelasi(ListParent &LP, ListChild LC, string idPen, string newKeretaID, string newKelas);

// --- MENU STATISTIK ---
void menuStatistik(ListParent LP, ListChild LC);

#endif
