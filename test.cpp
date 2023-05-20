#include "test.h"
#include "base64.hpp"
using namespace base64;
fstream f;
fstream f64;
fstream if64;
void startApp();
void cypher();
void plain();
void menu();
int main(){
    startApp();
    menu();
    cypher();
    plain();
}
void menu(){
    cout << "\n============================================\n";
    cout <<   "|-----------------Menu---------------------|\n";
    cout <<   "|    1. Ma hoa                             |\n";
    cout <<   "|    2. Giai ma                            |\n";
    cout <<   "|   Nhap lua chon:                         |\n";
}
void cypher(){
    InputKey();
    KeyExpansion();
    cout << "Nhap xau ki tu can ma hoa: ";
    InputStr();
    while (sz < str.size()) {
        sz = fillBlock();
        Cipher();
        string s = "";
        for (int i=0;i<16;i++) f << (int) out[i] << " ";f << "\n";
        for (int i=0 ; i < Nb*4 ; i++) f << out[i], s+= out[i];
        
        
        f << "\n";
        s = to_base64(s);
        f64 << s;
    }
}
void plain(){
    InputKey();
    KeyExpansion();
    cout << "Nhap do dai xau ki tu da ma hoa: ";
    int k;
    cin >> k;
    int numberOfBlock = k/16;
    if (k%16!=0) numberOfBlock++;
    f64.seekg(-(24*numberOfBlock),ios::end);
    // f.seekg(-(16*numberOfBlock),ios::end);
    cout << f64.tellg() << "\n";
    // cout << f.tellg() << "\n";
    string s,ss;
    f64 >> ss;
    // f >> ss;
    cout << ss << "\n";
    // ss = from_base64(ss);

    int pos = 0;
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

    // for (int i=0;i<16*numberOfBlock;i++) str[i] = ss[i];
    sz = 0;
    while (sz < str.size()) {
        sz = fillBlock();
        Plain();
        for (int i=0;i<16;i++) cout << out[i];
        for (int i=0;i<16;i++) if64 << out[i];
        // cout << "\n";
    }
}
void startApp(){
    Initialize();
    // InputKey();
    // KeyNhapSan();
    // KeyExpansion();
    f.open("o.ou",ios::in|ios::out|ios::app);
    f64.open("o64.ou",ios::in|ios::out|ios::app);
    if64.open("o.ou",ios::app);
}

// cout << "Key: ";for (int x=0;x<16;x++) cout <<hex<< (int)Key[x] << " ";cout << "\n";
// cout << "in: "; for (int i =0;i<16;i++) cout << (int) in[i] << " "; cout << "\n";
// for (int i=0 ; i < Nb*4 ; i++) cout << out[i] << " ";


// for (int i = 0; i<strlen(str);i++) in[i] = str[i];
    // cout << "in: "; for (int i =0;i<16;i++) cout << hex <<(int) in[i] << " "; cout << "\n";
    // Cipher();
    // cout << "out cy: ";for (int i=0 ; i < Nb*4 ; i++) cout << out[i];
    // in = out;
    // vector<unsigned char>out64 = out;
    // string s;
    // for (int i=0;i<16;i++) s+= out[i];
    // s = to_base64(s);
    // cout << "\nout cy2: " << s;
    // s = from_base64(s);
    // cout << "\nout cyb64: " << s;
    // cout << "\nin cy: ";for (int i=0 ; i < Nb*4 ; i++) cout << hex << (int)in[i] << " ";
    // cout << "\n";
    // Plain();
    // cout << "out pl: ";for (int i=0 ; i < Nb*4 ; i++) cout << out[i];
    //system("pause");