//Hoang Xuan Quy                                  -git\huyendieu909-
#include "test.h"
#include "base64.hpp"
using namespace base64;
void cypher();
void plain();
void menu();

int main(){
    int choice = 0;
    Initialize();
    menu();
    do{
        cout << "\n___Nhap lua chon: ";
        cin >> choice;
        switch (choice){
            case 1: 
                system("cls");
                cypher();
                cout << "======================Da ma hoa====================\n\n\n\n";
                system("pause");
                menu();
                choice = 0;
                break;
            case 2:
                system("cls");
                plain();
                cout << "\n=========================ok=====================\n\n\n\n";
                system("pause");
                menu();
                choice = 0;
                break;
            case 3:
                system("cls");
                MakeKey();
                choice = 0;
                cout << "\n==================Da thay doi key=================\n\n\n\n";
                system("pause");
                menu();
                break;
            case 4: 
                system("cls");
                InputPath();
                cout << "\n=================Da thay doi anh==================\n\n\n\n";
                system("pause");
                choice = 0;
                break;
            case 5:
                system("cls");
                menu();
                choice = 0;
                break;
            case 6:
                cout << "\nKet thuc chuong trinh\n";
                f64.close();
                system("exit");
                break;
        }
    } while (choice <1 || choice > 7);
}

void menu(){
    cout << "\n=======================================================================\n";
    cout <<   "|------------------------------Menu-----------------------------------|\n";
    cout <<   "|            1. Ma hoa                                                |\n";
    cout <<   "|            2. Giai ma                                               |\n";
    cout <<   "|            3. Thay doi key                                          |\n";
    cout <<   "|            4. Thay doi anh                                          |\n";
    cout <<   "|            5. Xoa man hinh                                          |\n";
    cout <<   "|            6. Ket thuc chuong trinh                                 |\n";
    cout <<   "| Key: " << key << ""; xd; 
    cout <<   "| Path: " << path<< ""; xd;
    cout <<   "|---------------------------------------------------------------------|\n";
    cout <<   "=======================================================================\n";
}
void cypher(){
    if (strlen(key)==0) MakeKey();
    if (path.size()<=1) InputPath();
    cout << "Nhap xau ki tu can ma hoa: ";
    InputStr();
    sz = 0;
    while (sz < str.size()) {
        sz = fillBlock();
        Cipher();
        string s = "";
        for (int i=0 ; i < Nb*4 ; i++) s+= out[i];
        s = to_base64(s);
        f64 << s;
    }
    f64 << " ";
    f64 << str.size() << " ";
    int a = scs(str.size());
    f64 << a << " ";
    int b = scs(a);
    f64 << b;
}
void plain(){
    if (strlen(key)==0) MakeKey();
    if (path.size()<=1) InputPath();
    // dịch chuyển con trỏ file để tìm độ dài thông điệp
    int k,a,b,pos=0;
    f64.seekg(-1,ios::end); pos++;
    f64>>b; b++; pos+=b;
    f64.seekg(-pos,ios::end);
    f64>>a; a++; pos+=a;
    f64.seekg(-pos,ios::end);
    f64 >> k; pos++;
    // độ dài thông điệp đã lưu vào biến k, phép toán dưới đây sẽ tìm số khối mã aes cần giải
    int numberOfBlock = k/16;
    if (k%16!=0) numberOfBlock++;
    string s,ss;
    f64.seekg(-(24*numberOfBlock)-pos,ios::end); 
    // cout << f64.tellg() << "\n"; for debug;
    f64 >> ss;
    cout << ss << "\n";
    s = "";
    str = "";
    for (int i=0;i<ss.size();i++){
        s+=ss[i];
        if (i%24==23){
            s = from_base64(s);
            for (int i=0;i<s.size();i++) str += s[i];
            s = "";
        }
    }
    cout << "_____Key: " << key; xd;
    cout << "----------------Thong diep giai ma---------------\n";
    sz = 0;
    while (sz < str.size()) {
        sz = fillBlock();
        Plain();
        for (int i=0;i<16;i++) cout << out[i];
        if64 << "\n";
        for (int i=0;i<16;i++) if64 << out[i];
    }
}