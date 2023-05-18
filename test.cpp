#include "test.h"
#include "base64.hpp"
using namespace base64;
int main(){
    Initialize();
    InputStr();
    InputKey();
    // KeyNhapSan();
    KeyExpansion();

    cout << "Key: ";for (int x=0;x<16;x++) cout <<hex<< (int)Key[x] << " ";
    cout << "\n";
    
    for (int i = 0; i<strlen(str);i++) in[i] = str[i];
    cout << "in: "; for (int i =0;i<16;i++) cout << hex <<(int) in[i] << " "; cout << "\n";
    Cipher();
    cout << "out cy: ";for (int i=0 ; i < Nb*4 ; i++) cout << out[i];
    in = out;
    vector<unsigned char>out64 = out;
    string s;
    for (int i=0;i<16;i++) s+= out[i];
    s = to_base64(s);
    cout << "\nout cy2: " << s;
    s = from_base64(s);
    cout << "\nout cyb64: " << s;
    cout << "\nin cy: ";for (int i=0 ; i < Nb*4 ; i++) cout << hex << (int)in[i] << " ";
    cout << "\n";
    Plain();
    cout << "out pl: ";for (int i=0 ; i < Nb*4 ; i++) cout << out[i];
    
    // while (sz < strlen(str)) {
    //     sz = fillBlock();
    //     cout << "in: "; for (int i =0;i<16;i++) cout << (int) in[i] << " "; cout << "\n";
    //     Cipher();
    //     for (int i=0 ; i < Nb*4 ; i++) cout << out[i] << " ";
    //     in = out;
    //     cout << "\n";
    //     Plain();
    //     for (int i=0 ; i < Nb*4 ; i++) cout << out[i] << " ";
    // }
    // cout << strlen(str);
}
//for (auto i: RoundKey) cout<<(int)i << " ";