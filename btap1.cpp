#include <iostream>

using namespace std;

struct Node{

    int id;

    string nd;

    int trai;

    int phai;

};

Node a[100];

void taoCay(){

    a[1] = {1,"DTB < 2.0 ?",2,3};

    a[2] = {2,"No >= 12 tin chi ?",4,5};

    a[3] = {3,"DTB >= 3.2 ?",6,7};

    a[4] = {4,"Canh bao hoc vu muc 2",0,0};

    a[5] = {5,"Canh bao hoc vu muc 1",0,0};

    a[6] = {6,"De xuat khen thuong",0,0};

    a[7] = {7,"Theo doi binh thuong",0,0};

}

void hienThi()

{

    cout << "\nID\tNoi dung\t\t\tTrai\tPhai\n";

    for(int i = 1; i <= 7; i++)

    {

        cout << a[i].id << "\t"
<< a[i].nd << "\t"
<< a[i].trai << "\t"
<< a[i].phai << endl;

    }

}

void tienTu(int x)

{

    if(x == 0)

        return;

    cout << a[x].id << " ";

    tienTu(a[x].trai);

    tienTu(a[x].phai);

}

void trungTu(int x)

{

    if(x == 0)

        return;

    trungTu(a[x].trai);

    cout << a[x].id << " ";

    trungTu(a[x].phai);

}

void hauTu(int x)

{

    if(x == 0)

        return;

    hauTu(a[x].trai);

    hauTu(a[x].phai);

    cout << a[x].id << " ";

}

int chieuCao(int x)

{

    if(x == 0)

        return 0;

    int t = chieuCao(a[x].trai);

    int p = chieuCao(a[x].phai);

    if(t > p)

        return t + 1;

    return p + 1;

}

int demLa(int x)

{

    if(x == 0)

        return 0;

    if(a[x].trai == 0 && a[x].phai == 0)

        return 1;

    return demLa(a[x].trai) + demLa(a[x].phai);

}

int duong[100];

int n;

bool timDuong(int x, int canTim)

{

    if(x == 0)

        return false;

    duong[n] = x;

    n++;

    if(a[x].id == canTim)

        return true;

    if(timDuong(a[x].trai, canTim))

        return true;

    if(timDuong(a[x].phai, canTim))

        return true;

    n--;

    return false;

}

void timNut()

{

    int id;

    cout << "Nhap ID can tim: ";

    cin >> id;

    n = 0;

    if(timDuong(1, id))

    {

        cout << "Duong di: ";

        for(int i = 0; i < n; i++)

        {

            cout << duong[i];

            if(i < n - 1)

                cout << " -> ";

        }

        cout << endl;

    }

    else

    {

        cout << "Khong tim thay\n";

    }

}

void tuVan()

{

    int x = 1;

    char tl;

    while(a[x].trai != 0 || a[x].phai != 0)

    {

        cout << a[x].nd << " (y/n): ";

        cin >> tl;

        if(tl == 'y' || tl == 'Y')

            x = a[x].trai;

        else

            x = a[x].phai;

    }

    cout << "Ket qua: " << a[x].nd << endl;

}

int main()

{

    taoCay();

    int chon;

    do

    {

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

        switch(chon)

        {

            case 1:

                hienThi();

                break;

            case 2:

                cout << "Tien tu: ";

                tienTu(1);

                cout << endl;

                break;

            case 3:

                cout << "Trung tu: ";

                trungTu(1);

                cout << endl;

                break;

            case 4:

                cout << "Hau tu: ";

                hauTu(1);

                cout << endl;

                break;

            case 5:

                timNut();

                break;

            case 6:

                cout << "Chieu cao cay: "
<< chieuCao(1) << endl;

                break;

            case 7:

                cout << "So nut la: "
<< demLa(1) << endl;

                break;

            case 8:

                tuVan();

                break;

            case 0:

                cout << "Ket thuc chuong trinh\n";

                break;

            default:

                cout << "Nhap sai\n";

        }

    } while(chon != 0);

    return 0;
 