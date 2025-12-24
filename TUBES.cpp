#include "tubes.h"

void createListParent(ListParent &LP) {
    LP.first = nullptr;
}

void createListChild(ListChild &LC) {
    LC.first = nullptr;
}

adrParent newParent(InfoK data) {
    adrParent P = new ElmParent;

    P->info = data;
    P->next = nullptr;
    P->firstRelation = nullptr;
    return P;
}

adrChild newChild(InfoC data) {
    adrChild C = new ElmChild;

    C->info = data;
    C->next = nullptr;
    return C;
}

adrRelation newRelation(InfoP data, adrChild child) {
    adrRelation R = new ElmRelation;

    R->info = data;
    R->childPtr = child;
    R->next = nullptr;
    return R;
}

void insertParent(ListParent &LP, adrParent P) {
    if (LP.first == nullptr) {
        LP.first = P;
    } else {
        adrParent Q = LP.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void insertChild(ListChild &LC, adrChild C) {
    if (LC.first == nullptr) {
        LC.first = C;
    } else {
        adrChild Q = LC.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = C;
    }
}

void addRelation(adrParent parent, adrRelation R) {
    if (parent != nullptr && R != nullptr) {
        R->next = parent->firstRelation;
        parent->firstRelation = R;
    }
}

// FIND
adrParent findParent(ListParent LP, string idKereta) {
    adrParent P = LP.first;
    while (P != nullptr) {
        if (P->info.idKereta == idKereta) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

adrChild findChild(ListChild LC, string namaKelas) {
    adrChild C = LC.first;
    while (C != nullptr) {
        if (C->info.ekonomi == namaKelas) {
            return C;
        }
        C = C->next;
    }
    return nullptr;
}

bool isRelated(adrParent P, adrChild C) {
    if (P == nullptr || C == nullptr){
        return false;
    }

    adrRelation R = P->firstRelation;
    while (R != nullptr) {
        if (R->childPtr == C) {
            return true;
        }
        R = R->next;
    }
    return false;
}

adrRelation findRelation(adrParent P, string idPenumpang) {
    if (P == nullptr) {
        return nullptr;
    }

    adrRelation R = P->firstRelation;
    while (R != nullptr) {
        if (R->info.idPenumpang == idPenumpang) {
            return R;
        }
        R = R->next;
    }
    return nullptr;
}

// DELETE
void deleteRelation(adrParent P, string idPenumpang) {
    if (P == nullptr) {
        return;
    }

    adrRelation R = P->firstRelation;
    adrRelation prev = nullptr;
    while (R != nullptr && R->info.idPenumpang != idPenumpang) {
        prev = R;
        R = R->next;
    }
    if (R != nullptr) {
        if (R == P->firstRelation) {
            P->firstRelation = R->next;
        } else {
            prev->next = R->next;
        }
        delete R;
    }
}

void deleteParent(ListParent &LP, string idKereta) {
    adrParent P = findParent(LP, idKereta);
    if (P != nullptr) {
        while (P->firstRelation != nullptr) {
            adrRelation temp = P->firstRelation;
            P->firstRelation = temp->next;
            delete temp;
        }
        if (P == LP.first) {
            LP.first = P->next;
        } else {
            adrParent prev = LP.first;
            while (prev->next != P) {
                prev = prev->next;
            }
            prev->next = P->next;
        }
        delete P;
    }
}

void deleteChild(ListChild &LC, ListParent &LP, string namaKelas) {
    adrChild C = findChild(LC, namaKelas);
    if (C != nullptr) {
        adrParent P = LP.first;
        while (P != nullptr) {
            adrRelation R = P->firstRelation;
            while (R != nullptr) {
                if (R->childPtr == C) R->childPtr = nullptr;
                R = R->next;
            }
            P = P->next;
        }
        if (C == LC.first) {
            LC.first = C->next;
        } else {
            adrChild prev = LC.first;
            while (prev->next != C) {
                prev = prev->next;
            }
            prev->next = C->next;
        }
        delete C;
    }
}

// SHOW
void showAllParent(ListParent LP) {
    adrParent P = LP.first;
    while (P) {
        cout << "Kereta: " << P->info.namaKereta << " [" << P->info.idKereta << "]\n";
        P = P->next;
    }
}

void showAllChild(ListChild LC) {
    adrChild C = LC.first;
    while (C) {
        cout << "Kelas: " << C->info.ekonomi << endl;
        C = C->next;
    }
}

void showChildOfParent(adrParent P) {
    if (P) {
        adrRelation R = P->firstRelation;
        while (R) {
            if (R->childPtr) {
                cout << "- Kelas: " << R->childPtr->info.ekonomi << endl;
            }
            R = R->next;
        }
    }
}

void showParentOfChild(ListParent LP, adrChild C) {
    adrParent P = LP.first;
    while (P) {
        if (isRelated(P, C)) {
            cout << "- Kereta: " << P->info.namaKereta << endl;
        }
        P = P->next;
    }
}

void showData(ListParent LP) {
    adrParent P = LP.first;
    while (P) {
        cout << "Kereta: " << P->info.namaKereta << endl;
        adrRelation R = P->firstRelation;
        while (R) {
            cout << "  > Penumpang: " << R->info.nama;
            if (R->childPtr){
                cout << " | Kelas: " << R->childPtr->info.ekonomi;
            }
            cout << endl;
            R = R->next;
        }
        P = P->next;
    }
}

// COUNT
int countChildOfParent(adrParent P) {
    int total = 0;
    if (P) {
        adrRelation R = P->firstRelation;
        while (R) {
            total++; R = R->next;
        }
    }
    return total;
}

int countParentOfChild(ListParent LP, adrChild C) {
    int total = 0;
    adrParent P = LP.first;
    while (P) {
        if (isRelated(P, C)) {
            total++;
        }
        P = P->next;
    }
    return total;
}

int countOrphanChild(ListChild LC, ListParent LP) {
    int total = 0;
    adrChild C = LC.first;
    while (C) {
        bool used = false;
        adrParent P = LP.first;
        while (P && !used) {
            if (isRelated(P, C)) used = true;
            P = P->next;
        }
        if (!used) {
            total++;
        }
        C = C->next;
    }
    return total;
}

int countEmptyParent(ListParent LP) {
    int total = 0;
    adrParent P = LP.first;
    while (P) {
        if (P->firstRelation == nullptr) {
            total++;
        }
        P = P->next;
    }
    return total;
}

// === EDIT
void editRelasi(ListParent &LP, ListChild LC, string idPen, string newKeretaID, string newKelas) {
    adrParent pOld = nullptr, pNew = findParent(LP, newKeretaID);
    adrRelation rOld = nullptr;
    adrParent curr = LP.first;
    while (curr && !rOld) {
        rOld = findRelation(curr, idPen);
        if (rOld){
            pOld = curr;
        }
        curr = curr->next;
    }
    if (rOld && pNew) {
        InfoP infoTmp = rOld->info;
        deleteRelation(pOld, idPen);
        addRelation(pNew, newRelation(infoTmp, findChild(LC, newKelas)));
    }
}

void menuStatistik(ListParent LP, ListChild LC) {
    string kls;
    cout << "\n---------- STATISTIK ----------"  << endl;
    cout << "1. Jumlah Kereta Tanpa Penumpang (Empty Parent): " << countEmptyParent(LP) << endl;
    cout << "2. Jumlah Kelas Belum Pernah Dipakai (Orphan Child): " << countOrphanChild(LC, LP) << endl;
    cout << "Cek Kereta Tertentu: "; cin >> kls;
    adrParent P = findParent(LP, kls);
    if (P) {
        cout << "3. Jumlah Penumpang di Kereta " << kls << ": " << countChildOfParent(P) << endl;
    }
}
