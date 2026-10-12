#include <iostream>
#include <string>
using namespace std;

struct Node {
    int id;
    string nd;
    Node *trai;
    Node *phai;
};

// Tao mot nut moi
Node* taoNut(int id, string nd) {
    Node* p = new Node;
    p->id = id;
    p->nd = nd;
    p->trai = nullptr;
    p->phai = nullptr;
    return p;
}

// Tao cay nhi phan
Node* taoCay() {
    Node* goc = taoNut(1, "DTB < 2.0 ?");
    
    goc->trai = taoNut(2, "No >= 12 tin chi ?");
    goc->phai = taoNut(3, "DTB >= 3.2 ?");

    goc->trai->trai = taoNut(4, "Canh bao hoc vu muc 2");
    goc->trai->phai = taoNut(5, "Canh bao hoc vu muc 1");

    goc->phai->trai = taoNut(6, "De xuat khen thuong");
    goc->phai->phai = taoNut(7, "Theo doi binh thuong");

    return goc;
}

// Hien thi cay
void hienThi(Node* goc) {
    if (goc == nullptr)
        return;

    cout << "\nID\tNoi dung\t\t\tTrai\tPhai\n";

    // Duyet cac nut theo thu tu tien tu
    Node* q[7];
    int dau = 0, cuoi = 0;
    q[cuoi++] = goc;

    while (dau < cuoi) {
        Node* p = q[dau++];

        cout << p->id << "\t"
             << p->nd << "\t"
             << (p->trai ? p->trai->id : 0) << "\t"
             << (p->phai ? p->phai->id : 0) << endl;

        if (p->trai != nullptr)
            q[cuoi++] = p->trai;

        if (p->phai != nullptr)
            q[cuoi++] = p->phai;
    }
}

// Duyet tien tu: Goc - Trai - Phai
void tienTu(Node* goc) {
    if (goc == nullptr)
        return;

    cout << goc->id << " ";
    tienTu(goc->trai);
    tienTu(goc->phai);
}

// Duyet trung tu: Trai - Goc - Phai
void trungTu(Node* goc) {
    if (goc == nullptr)
        return;

    trungTu(goc->trai);
    cout << goc->id << " ";
    trungTu(goc->phai);
}

// Duyet hau tu: Trai - Phai - Goc
void hauTu(Node* goc) {
    if (goc == nullptr)
        return;

    hauTu(goc->trai);
    hauTu(goc->phai);
    cout << goc->id << " ";
}

// Tinh chieu cao cay
int chieuCao(Node* goc) {
    if (goc == nullptr)
        return 0;

    int t = chieuCao(goc->trai);
    int p = chieuCao(goc->phai);

    return (t > p ? t : p) + 1;
}

// Dem nut la
int demLa(Node* goc) {
    if (goc == nullptr)
        return 0;

    if (goc->trai == nullptr && goc->phai == nullptr)
        return 1;

    return demLa(goc->trai) + demLa(goc->phai);
}

// Tim nut va in duong di
bool timDuong(Node* goc, int canTim, string& duong) {
    if (goc == nullptr)
        return false;

    if (!duong.empty())
        duong += " -> ";

    duong += to_string(goc->id);

    if (goc->id == canTim)
        return true;

    if (timDuong(goc->trai, canTim, duong))
        return true;

    if (timDuong(goc->phai, canTim, duong))
        return true;

    // Bo nut cuoi neu khong tim thay
    size_t viTri = duong.rfind(" -> ");
    if (viTri != string::npos)
        duong.erase(viTri);
    else
        duong.clear();

    return false;
}

void timNut(Node* goc) {
    int id;
    cout << "Nhap ID can tim: ";
    cin >> id;

    string duong = "";

    if (timDuong(goc, id, duong))
        cout << "Duong di: " << duong << endl;
    else
        cout << "Khong tim thay\n";
}

// Tu van hoc vu
void tuVan(Node* goc) {
    Node* p = goc;
    char tl;

    while (p != nullptr &&
          (p->trai != nullptr || p->phai != nullptr)) {
        cout << p->nd << " (y/n): ";
        cin >> tl;

        if (tl == 'y' || tl == 'Y')
            p = p->trai;
        else
            p = p->phai;
    }

    if (p != nullptr)
        cout << "Ket qua: " << p->nd << endl;
}

// Giai phong bo nho
void giaiPhong(Node* goc) {
    if (goc == nullptr)
        return;

    giaiPhong(goc->trai);
    giaiPhong(goc->phai);
    delete goc;
}

int main() {
    Node* goc = taoCay();
    int chon;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Hien thi cay\n";
        cout << "2. Duyet tien tu\n";
        cout << "3. Duyet trung tu\n";
        cout << "4. Duyet hau tu\n";
        cout << "5. Tim nut va in duong di\n";
        cout << "6. Chieu cao cay\n";
        cout << "7. Dem nut la\n";
        cout << "8. Tu van hoc vu\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        switch (chon) {
            case 1:
                hienThi(goc);
                break;

            case 2:
                cout << "Tien tu: ";
                tienTu(goc);
                cout << endl;
                break;

            case 3:
                cout << "Trung tu: ";
                trungTu(goc);
                cout << endl;
                break;

            case 4:
                cout << "Hau tu: ";
                hauTu(goc);
                cout << endl;
                break;

            case 5:
                timNut(goc);
                break;

            case 6:
                cout << "Chieu cao cay: "
                     << chieuCao(goc) << endl;
                break;

            case 7:
                cout << "So nut la: "
                     << demLa(goc) << endl;
                break;

            case 8:
                tuVan(goc);
                break;

            case 0:
                cout << "Ket thuc chuong trinh\n";
                break;

            default:
                cout << "Nhap sai\n";
        }
    } while (chon != 0);

    giaiPhong(goc);
    return 0;
}