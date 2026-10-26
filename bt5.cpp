
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct SanPham {
    string maSP;
    string tenSP;
    int donGia;
    int soLuong;
};

int docTep(SanPham ds[]) {
    ifstream file("san_pham.txt");

    if (!file.is_open()) {
        cout << "Khong mo duoc tep san_pham.txt!\n";
        return 0;
    }

    int n;
    file >> n;
    file.ignore();

    if (n <= 0 || n > 1000) {
        cout << "So luong san pham khong hop le!\n";
        file.close();
        return 0;
    }

    for (int i = 0; i < n; i++) {
        string dong;
        getline(file, dong);

        int p1 = dong.find('|');
        int p2 = dong.find('|', p1 + 1);
        int p3 = dong.find('|', p2 + 1);

        if (p1 == -1 || p2 == -1 || p3 == -1) {
            cout << "Du lieu khong hop le!\n";
            file.close();
            return 0;
        }

        ds[i].maSP = dong.substr(0, p1);
        ds[i].tenSP = dong.substr(p1 + 1, p2 - p1 - 1);
        ds[i].donGia = stoi(dong.substr(p2 + 1, p3 - p2 - 1));
        ds[i].soLuong = stoi(dong.substr(p3 + 1));

        for (int j = 0; j < i; j++) {
            if (ds[i].maSP == ds[j].maSP) {
                cout << "Ma san pham bi trung!\n";
                file.close();
                return 0;
            }
        }
    }

    file.close();
    return n;
}

void inDanhSach(SanPham ds[], int n) {
    cout << "\nDANH SACH SAN PHAM\n";
    cout << "MaSP\tTenSP\t\tDonGia\tSoLuong\n";

    for (int i = 0; i < n; i++) {
        cout << ds[i].maSP << "\t"
            << ds[i].tenSP << "\t"
            << ds[i].donGia << "\t"
            << ds[i].soLuong << "\n";
    }
}

void saoChepVaSapXep(SanPham ds[], SanPham dsSapXep[], int n) {
    for (int i = 0; i < n; i++) {
        dsSapXep[i] = ds[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dsSapXep[i].maSP > dsSapXep[j].maSP) {
                SanPham tam = dsSapXep[i];
                dsSapXep[i] = dsSapXep[j];
                dsSapXep[j] = tam;
            }
        }
    }
}

void timKiemTuanTu(SanPham ds[], int n, string ma) {
    int viTri = -1;
    int soLan = 0;

    for (int i = 0; i < n; i++) {
        soLan++;

        if (ds[i].maSP == ma) {
            viTri = i;
            break;
        }
    }

    cout << "\nKET QUA TIM KIEM TUAN TU\n";

    if (viTri != -1) {
        cout << "Ma SP: " << ds[viTri].maSP << "\n";
        cout << "Ten SP: " << ds[viTri].tenSP << "\n";
        cout << "Don gia: " << ds[viTri].donGia << "\n";
        cout << "So luong: " << ds[viTri].soLuong << "\n";
        cout << "Vi tri trong mang goc: " << viTri + 1 << "\n";
    } else {
        cout << "Khong tim thay san pham!\n";
    }

    cout << "So lan so sanh: " << soLan << "\n";
}

void timKiemNhiPhan(SanPham ds[], int n, string ma) {
    int trai = 0;
    int phai = n - 1;
    int viTri = -1;
    int soLan = 0;

    while (trai <= phai) {
        int giua = (trai + phai) / 2;
        soLan++;

        if (ds[giua].maSP == ma) {
            viTri = giua;
            break;
        } else if (ds[giua].maSP < ma) {
            trai = giua + 1;
        } else {
            phai = giua - 1;
        }
    }

    cout << "\nKET QUA TIM KIEM NHI PHAN\n";

    if (viTri != -1) {
        cout << "Ma SP: " << ds[viTri].maSP << "\n";
        cout << "Ten SP: " << ds[viTri].tenSP << "\n";
        cout << "Don gia: " << ds[viTri].donGia << "\n";
        cout << "So luong: " << ds[viTri].soLuong << "\n";
        cout << "Vi tri trong mang da sap xep: " << viTri + 1 << "\n";
    } else {
        cout << "Khong tim thay san pham!\n";
    }

    cout << "So lan so sanh: " << soLan << "\n";
}

int main() {
    SanPham ds[1000], dsSapXep[1000];
    int n = 0;
    int daDoc = 0;
    int chon;
    string ma;

    do {
        cout << "\n===== MENU CHINH =====\n";
        cout << "1. Doc tep TXT va in danh sach\n";
        cout << "2. Tim kiem tuan tu\n";
        cout << "3. Sap xep va tim kiem nhi phan\n";
        cout << "4. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> chon;

        if (chon == 1) {
            n = docTep(ds);

            if (n > 0) {
                inDanhSach(ds, n);
                daDoc = 1;
            } else {
                daDoc = 0;
            }
        }
        else if (chon == 2) {
            if (daDoc == 0) {
                cout << "Hay doc tep truoc!\n";
            } else {
                cout << "Nhap ma san pham can tim: ";
                cin >> ma;

                timKiemTuanTu(ds, n, ma);
            }
        }
        else if (chon == 3) {
            if (daDoc == 0) {
                cout << "Hay doc tep truoc!\n";
            } else {
                saoChepVaSapXep(ds, dsSapXep, n);

                cout << "\nDANH SACH DA SAP XEP\n";
                inDanhSach(dsSapXep, n);

                cout << "Nhap ma san pham can tim: ";
                cin >> ma;

                timKiemNhiPhan(dsSapXep, n, ma);
            }
        }
        else if (chon != 4) {
            cout << "Lua chon khong hop le!\n";
        }

    } while (chon != 4);

    return 0;
}