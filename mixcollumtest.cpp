#include "test.h"

int main(){
    Initialize();

    // InputKey();
    KeyNhapSan();
    KeyExpansion();
    state = {0xd4,0xe0,0xb8,0x1e,0xbf,0xb4,0x41,0x27,0x5d,0x52,0x11,0x98,0x30,0xae,0xf1,0xe5};
    MixColumns();
    cout << "state: ";for (int x=0;x<16;x++) cout <<hex<< (int)state[x] << " ";
    cout << "\n";
    
}
