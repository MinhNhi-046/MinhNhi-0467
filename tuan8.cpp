
#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>
#include <new>
using namespace std;
struct Product {
    int maSP;
    char tenSP[50];
    int soLuong;
    double donGia;
};

struct Node {
    Product data;
    Node* left;
    Node* right;
};

Node* taoNode(Product sp) {
    Node* p = new(nothrow) Node;

    if (p == NULL) {
        cout << "Khong du bo nho de tao Node!\n";
        return NULL;
    }

    p->data = sp;
    p->left = NULL;
    p->right = NULL;

    return p;
}

bool duLieuHopLe(Product sp) {
    if (sp.maSP <= 0) {
        cout << "Ma san pham phai la so nguyen duong!\n";
        return false;
    }

    if (sp.tenSP[0] == '\0') {
        cout << "Ten san pham khong duoc rong!\n";
        return false;
    }

    if (sp.soLuong < 0) {
        cout << "So luong khong duoc am!\n";
        return false;
    }

    if (sp.donGia < 0) {
        cout << "Don gia khong duoc am!\n";
        return false;
    }

    return true;
}

bool nhapSanPham(Product& sp) {
    cout << "Nhap ma san pham: ";
    if (!(cin >> sp.maSP)) {
        cout << "Ma san pham khong hop le!\n";
        cin.clear();
        cin.ignore();
        return false;
    }

    cin.ignore();

    cout << "Nhap ten san pham: ";
    cin.getline(sp.tenSP, 50);

    if (cin.fail()) {
        cout << "Ten san pham qua dai!\n";
        cin.clear();
        cin.ignore();
        return false;
    }

    cout << "Nhap so luong: ";
    if (!(cin >> sp.soLuong)) {
        cout << "So luong khong hop le!\n";
        cin.clear();
        cin.ignore();
        return false;
    }

    cout << "Nhap don gia: ";
    if (!(cin >> sp.donGia)) {
        cout << "Don gia khong hop le!\n";
        cin.clear();
        cin.ignore();
        return false;
    }

    cin.ignore();

    return duLieuHopLe(sp);
}

void inTieuDe() {
    cout << left
         << setw(10) << "Ma SP"
         << setw(22) << "Ten san pham"
         << setw(12) << "So luong"
         << setw(15) << "Don gia" << "\n";

    cout << "-----------------------------------------------------------\n";
}

void inSanPham(Product sp) {
    cout << left
         << setw(10) << sp.maSP
         << setw(22) << sp.tenSP
         << setw(12) << sp.soLuong
         << fixed << setprecision(2)
         << setw(15) << sp.donGia << "\n";
}

Node* timKiem(Node* root, int maSP) {
    if (root == NULL || root->data.maSP == maSP) {
        return root;
    }

    if (maSP < root->data.maSP) {
        return timKiem(root->left, maSP);
    }

    return timKiem(root->right, maSP);
}

bool chen(Node*& root, Product sp) {
    if (root == NULL) {
        Node* p = taoNode(sp);

        if (p == NULL) {
            return false;
        }

        root = p;
        return true;
    }

    if (sp.maSP < root->data.maSP) {
        return chen(root->left, sp);
    }

    if (sp.maSP > root->data.maSP) {
        return chen(root->right, sp);
    }

    cout << "Ma san pham da ton tai!\n";
    return false;
}

Node* timMin(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}

void xoa(Node*& root, int maSP) {
    if (root == NULL) {
        return;
    }

    if (maSP < root->data.maSP) {
        xoa(root->left, maSP);
    } else if (maSP > root->data.maSP) {
        xoa(root->right, maSP);
    } else {
        // Truong hop 1: Node la
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }

        // Truong hop 2: Node chi co con phai
        else if (root->left == NULL) {
            Node* p = root;
            root = root->right;
            delete p;
        }

        // Truong hop 3: Node chi co con trai
        else if (root->right == NULL) {
            Node* p = root;
            root = root->left;
            delete p;
        }

        // Truong hop 3: Node co hai con
        else {
            // Lay Node nho nhat cua cay con phai
            Node* p = timMin(root->right);

            // Sao chep toan bo thong tin san pham
            root->data = p->data;

            // Xoa Node ke tiep trung thu tu o vi tri cu
            xoa(root->right, p->data.maSP);
        }
    }
}


void duyetLNR(Node* root) {
    if (root == NULL) {
        return;
    }

    duyetLNR(root->left);
    inSanPham(root->data);
    duyetLNR(root->right);
}

int demNode(Node* root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + demNode(root->left)
             + demNode(root->right);
}

int chieuCao(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int trai = chieuCao(root->left);
    int phai = chieuCao(root->right);

    return 1 + (trai > phai ? trai : phai);
}


void giaiPhong(Node*& root) {
    if (root == NULL) {
        return;
    }

    giaiPhong(root->left);
    giaiPhong(root->right);

    delete root;
    root = NULL;
}

void taoDuLieuMau(Node*& root) {
    Product ds[7] = {
        {50, "But bi",      120,  5000},
        {30, "Vo o ly",      80, 12000},
        {70, "Bia ho so",    35, 15000},
        {20, "Thuoc ke",     40,  8000},
        {40, "Tay",          65,  4000},
        {60, "So tay",       25, 25000},
        {80, "But chi",     110,  3000}
    };

    for (int i = 0; i < 7; i++) {
        if (!chen(root, ds[i])) {
            cout << "Khong the nap du lieu mau tai ma "
                 << ds[i].maSP << "!\n";
            return;
        }
    }

    cout << "Da nap 7 san pham mau.\n";
}

int main() {
    Node* root = NULL;
    int chon, maSP;

    do {
        cout << "\n========== QUAN LY SAN PHAM BST ==========\n";
        cout << "1. Them san pham\n";
        cout << "2. Tim kiem san pham\n";
        cout << "3. Xoa san pham\n";
        cout << "4. In danh sach tang dan theo ma\n";
        cout << "5. Dem so nut va chieu cao cay\n";
        cout << "6. Nap 7 san pham mau\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";

        if (!(cin >> chon)) {
            cout << "Lua chon khong hop le!\n";
            cin.clear();
            cin.ignore();
            continue;
        }

        cin.ignore();

        switch (chon) {
            case 1: {
                Product sp;

                if (nhapSanPham(sp)) {
                    chen(root, sp);
                }
                break;
            }

            case 2: {
                cout << "Nhap ma san pham can tim: ";

                if (!(cin >> maSP)) {
                    cout << "Ma san pham khong hop le!\n";
                    cin.clear();
                    cin.ignore();
                    break;
                }

                cin.ignore();

                Node* p = timKiem(root, maSP);

                if (p == NULL) {
                    cout << "Khong tim thay san pham!\n";
                } else {
                    inTieuDe();
                    inSanPham(p->data);
                }
                break;
            }

            case 3: {
                cout << "Nhap ma san pham can xoa: ";

                if (!(cin >> maSP)) {
                    cout << "Ma san pham khong hop le!\n";
                    cin.clear();
                    cin.ignore();
                    break;
                }

                cin.ignore();

                if (timKiem(root, maSP) == NULL) {
                    cout << "Khong tim thay san pham!\n";
                } else {
                    xoa(root, maSP);
                    cout << "Da xoa san pham co ma "
                         << maSP << ".\n";
                }
                break;
            }

            case 4:
                if (root == NULL) {
                    cout << "Danh sach san pham rong!\n";
                } else {
                    cout << "\nDANH SACH SAN PHAM THEO MA TANG DAN\n";
                    inTieuDe();
                    duyetLNR(root);
                }
                break;

            case 5:
                cout << "So nut trong cay: " << demNode(root) << "\n";
                cout << "Chieu cao cay: " << chieuCao(root) << "\n";
                break;

            case 6:
                if (root != NULL) {
                    cout << "Cay dang co du lieu. "
                         << "Hay thoat va chay lai de nap cay mau.\n";
                } else {
                    taoDuLieuMau(root);
                }
                break;

            case 0:
                giaiPhong(root);
                cout << "Da giai phong bo nho. Ket thuc chuong trinh!\n";
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (chon != 0);

    return 0;
}