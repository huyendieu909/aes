#include "test.h"

int main(){
    Initialize();

    // InputKey();
    KeyNhapSan();
    KeyExpansion();

    cout << "Key: ";for (int x=0;x<16;x++) cout << (int)Key[x] << " ";
    cout << "\n";
    for (int i = 0;i<11;i++){
        for (int j = 0;j<16;j++){
            cout << hex << (int) RoundKey[16*i+j] << " ";
        }
        cout << "\n";
    }
    
}
//for (auto i: RoundKey) cout<<(int)i << " ";