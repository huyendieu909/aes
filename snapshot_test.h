#include <bits/stdc++.h>
#include "test2.h"
using namespace std;
vector<int> state; // ma trận trạng thái
vector<unsigned char> in; // ma trận đầu vào
vector<unsigned char> out; // ma trận đầu ra
vector<unsigned char> Key;
vector<unsigned char> RoundKey; // lưu trữ các vòng khóa
int Nb = 4;
int Nr = 10; // số vòng
int Nk = 4; // số cọt của khóa gốc
int sz = 0;
char str[1024];

void InputStr(){
    fflush(stdin);
    // fgets(str,1024,stdin);
    gets(str);
}

void KeyNhapSan(){
    // Key[0]  = 0x6b;  Key[1]  = 0x6b;  Key[2]  = 0x6b;  Key[3]  = 0x6b;
    // Key[4]  = 0x65;  Key[5]  = 0x65;  Key[6]  = 0x65;  Key[7]  = 0x65;
    // Key[8]  = 0x79;  Key[9]  = 0x79;  Key[10] = 0x79;  Key[11] = 0x79;
    // Key[12] = 0x2e;  Key[13] = 0x2e;  Key[14] = 0x2e;  Key[15] = 0x2e;

    Key[0]  = 0x00;  Key[1]  = 0x00;  Key[2]  = 0x00;  Key[3]  = 0x00;
    Key[4]  = 0x00;  Key[5]  = 0x00;  Key[6]  = 0x00;  Key[7]  = 0x00;
    Key[8]  = 0x00;  Key[9]  = 0x00;  Key[10] = 0x00;  Key[11] = 0x00;
    Key[12] = 0x00;  Key[13] = 0x00;  Key[14] = 0x00;  Key[15] = 0x00;

    // Key[0]  = 0x6b;  Key[1]  = 0x65;  Key[2]  = 0x79;  Key[3]  = 0x2e;
    // Key[4]  = 0x6b;  Key[5]  = 0x65;  Key[6]  = 0x79;  Key[7]  = 0x2e;
    // Key[8]  = 0x6b;  Key[9]  = 0x65;  Key[10] = 0x79;  Key[11] = 0x2e;
    // Key[12] = 0x6b;  Key[13] = 0x65;  Key[14] = 0x79;  Key[15] = 0x2e;
}

void InputKey(){
    char key[100];
    do {
        cout << "Nhap key: ";
        fflush(stdin);
        gets(key);
    } while (strlen(key) > 16);
    if (strlen(key) < 16) {
        for (int i=strlen(key);i<16;i++) key[i] = 0; 
    }
    int k = 0; // con trỏ key nhập vào
    for (int i=0;i<Nk;i++){
        Key[i] = key[k++];
        Key[i+4] = key[k++];
        Key[i+8] = key[k++];
        Key[i+12] = key[k++];
    }
}

void KeyExpansion(){
    unsigned char temp[4],k;
    for (int i=0 ; i < Nk ; i++) {
        RoundKey[i*4+0] = Key[i*4+0];
        RoundKey[i*4+1] = Key[i*4+1];
        RoundKey[i*4+2] = Key[i*4+2];
        RoundKey[i*4+3] = Key[i*4+3];
    }
    int i = 4;
    while (i < (Nb * (Nr+1))){
        for (int j=0;j<4;j++){
            temp[j] = RoundKey[(i-1)*4+j];
        }
        if (i%Nk==0){
            // rotword
            k = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = k;
            // subword
            temp[0] = getSBoxValue(temp[0]);
            temp[1] = getSBoxValue(temp[1]);
            temp[2] = getSBoxValue(temp[2]);
            temp[3] = getSBoxValue(temp[3]);
            // rcon
            temp[0] = temp[0] ^ Rcon[i/Nk];
        }
        RoundKey[i*4+0] = RoundKey[(i-Nk)*4+0] ^ temp[0];
        RoundKey[i*4+1] = RoundKey[(i-Nk)*4+1] ^ temp[1];
        RoundKey[i*4+2] = RoundKey[(i-Nk)*4+2] ^ temp[2];
        RoundKey[i*4+3] = RoundKey[(i-Nk)*4+3] ^ temp[3];
        i++;
    }
}

void AddRoundKey(int round) {
   int i,j;
//    for (int i=0;i<16;i++){
//         state[i] = RoundKey[16*round+i];
//    }
   for (i=0 ; i < Nb ; i++) {
      for (j=0 ; j < 4 ; j++) {
	    state[j*4+i] ^= RoundKey[round * 16 + i * Nb + j];
      }
   }
}

void SubBytes() {
    for (int i = 0; i < 16; i++)
        state[i] = getSBoxValue(state[i]);
}

void invSubBytes() {
    for (int i = 0; i < 16; i++)
        state[i] = getInvSBoxValue(state[i]);
}

void ShiftRows() {
   unsigned char temp;

   // Rotate first row 1 columns to left	
   temp = state[1*4+0];
   state[1*4+0] = state[1*4+1];
   state[1*4+1] = state[1*4+2];
   state[1*4+2] = state[1*4+3];
   state[1*4+3] = temp;

   // Rotate second row 2 columns to left	
   temp = state[2*4+0];
   state[2*4+0] = state[2*4+2];
   state[2*4+2] = temp;

   temp = state[2*4+1];
   state[2*4+1] = state[2*4+3];
   state[2*4+3] = temp;

   // Rotate third row 3 columns to left
   temp = state[3*4+0];
   state[3*4+0] = state[3*4+3];
   state[3*4+3] = state[3*4+2];
   state[3*4+2] = state[3*4+1];
   state[3*4+1] = temp;
}

void invShiftRows() {
   unsigned char temp;

   // Rotate first row 1 columns to right	
   temp = state[1*4+3];
   state[1*4+3] = state[1*4+2];
   state[1*4+2] = state[1*4+1];
   state[1*4+1] = state[1*4+0];
   state[1*4+0] = temp;

   // Rotate second row 2 columns to right	
   temp = state[2*4+0];
   state[2*4+0] = state[2*4+2];
   state[2*4+2] = temp;

   temp = state[2*4+1];
   state[2*4+1] = state[2*4+3];
   state[2*4+3] = temp;

   // Rotate third row 3 columns to right
   temp = state[3*4+0];
   state[3*4+0] = state[3*4+1];
   state[3*4+1] = state[3*4+2];
   state[3*4+2] = state[3*4+3];
   state[3*4+3] = temp;
}



void MixColumns() {
    int i;
   for (i=0 ; i < Nb ; i++) {	
      state[0*4+i] = galois_multiplication(state[0*4+i], 2) ^
                    galois_multiplication(state[3*4+i], 1) ^ 
                    galois_multiplication(state[2*4+i], 1) ^
                    galois_multiplication(state[1*4+i], 3);
      state[1*4+i] = galois_multiplication(state[1*4+i], 2) ^
                    galois_multiplication(state[0*4+i], 1) ^
                    galois_multiplication(state[3*4+i], 1) ^
                    galois_multiplication(state[2*4+i], 3);
      state[2*4+i] = galois_multiplication(state[2*4+i], 2) ^
                    galois_multiplication(state[1*4+i], 1) ^
                    galois_multiplication(state[0*4+i], 1) ^
                    galois_multiplication(state[3*4+i], 3);
      state[3*4+i] = galois_multiplication(state[3*4+i], 2) ^
                    galois_multiplication(state[2*4+i], 1) ^
                    galois_multiplication(state[1*4+i], 1) ^
                    galois_multiplication(state[0*4+i], 3);
   }
}

void invMixColumns()
{
   int i;
   for (i=0 ; i < Nb ; i++) {	
      state[0*4+i] = galois_multiplication(state[0*4+i], 14) ^
                    galois_multiplication(state[3*4+i], 9) ^ 
                    galois_multiplication(state[2*4+i], 13) ^
                    galois_multiplication(state[1*4+i], 11);
      state[1*4+i] = galois_multiplication(state[1*4+i], 14) ^
                    galois_multiplication(state[0*4+i], 9) ^
                    galois_multiplication(state[3*4+i], 13) ^
                    galois_multiplication(state[2*4+i], 11);
      state[2*4+i] = galois_multiplication(state[2*4+i], 14) ^
                    galois_multiplication(state[1*4+i], 9) ^
                    galois_multiplication(state[0*4+i], 13) ^
                    galois_multiplication(state[3*4+i], 11);
      state[3*4+i] = galois_multiplication(state[3*4+i], 14) ^
                    galois_multiplication(state[2*4+i], 9) ^
                    galois_multiplication(state[1*4+i], 13) ^
                    galois_multiplication(state[0*4+i], 11);
   }
}

void Cipher() {
   int i,j,round=0;

   //Copy the input PlainText to state array.
//    for (i=0 ; i < Nb ; i++) {
//       for (j=0 ; j < 4 ; j++) {
// 	 state[j*4+i] = in[i*4 + j];
//       }
//    }
    for (i=0 ; i < Nb ; i++) {
      for (j=0 ; j < 4 ; j++) {
	 state[i*4+j] = in[i+4*j];
      }
   }

cout << "state: "; for (int i =0;i<16;i++) cout << (int) state[i] << " "; cout << "\n";
   // Add the First round key to the state before starting the rounds.
   AddRoundKey(0); 
	
   // There will be Nr rounds.
   // The first Nr-1 rounds are identical.
   // These Nr-1 rounds are executed in the loop below.
   for (round=1 ; round < Nr ; round++) {
      SubBytes();
      ShiftRows();
      MixColumns();
      AddRoundKey(round);
   }
	
   // The last round is given below.
   // The MixColumns function is not here in the last round.
   SubBytes();
   ShiftRows();
   AddRoundKey(Nr);
   
   // The encryption process is over.
   // Copy the state array to output array.
//    for (i=0 ; i < Nb ; i++) {
//       for (j=0 ; j < 4 ; j++) {
// 	 out[i*4+j]=state[j*4+i];
//       }
//    }
    for (i=0 ; i < Nb ; i++) {
      for (j=0 ; j < 4 ; j++) {
	 out[i+4*j]=state[i*4+j];
      }
   }
}

void Plain() {
   int i,j,round=9;

   //Copy the input CypherText to state array.
//    for (i=0 ; i < Nb ; i++) {
//       for (j=0 ; j < 4 ; j++) {
// 	    state[j*4+i] = in[i*4 + j];
//       }
//    }
    for (i=0 ; i < Nb ; i++) {
      for (j=0 ; j < 4 ; j++) {
	 state[i*4+j] = in[i+4*j];
      }
   }

   // Add the First round key to the state before starting the rounds.
   AddRoundKey(10); 
	
   // There will be Nr rounds.
   // The first Nr-1 rounds are identical.
   // These Nr-1 rounds are executed in the loop below.
   for (round=9 ; round >= 1 ; round--) {
      invShiftRows();
      invSubBytes();
      AddRoundKey(round);
      invMixColumns();
   }
	
   // The last round is given below.
   // The MixColumns function is not here in the last round.
   invShiftRows();
   invSubBytes();
   AddRoundKey(0);
   
   // Copy the state array to output array.
//    for (i=0 ; i < Nb ; i++) {
//       for (j=0 ; j < 4 ; j++) {
// 	      out[i*4+j]=state[j*4+i];
//       }
//    }
    for (i=0 ; i < Nb ; i++) {
      for (j=0 ; j < 4 ; j++) {
	 out[i+4*j]=state[i*4+j];
      }
   }
}

int fillBlock () {
   int j=0;
   while (sz < strlen(str)) {
      if (j >= Nb*4) break;
      in[j++] = str[sz];
      sz++;
   }
   // Pad the block with 0s, if necessary
   if (sz >= strlen(str)) for ( ; j < Nb*4 ; j++) in[j] = 0;
   return sz;   
}

void Initialize(){
    for (int i=0;i<16;i++) state.push_back(0);
    for (int i=0;i<16;i++) Key.push_back(0);
    for (int i=0;i<176;i++) RoundKey.push_back(0x61);
    for (int i=0;i<16;i++) in.push_back(0);
    for (int i=0;i<16;i++) out.push_back(0);
}

// #define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

// // MixColumns function mixes the columns of the state matrix
// void MixColumns() {
//    int i;
//    unsigned char Tmp,Tm,t;
//    for (i=0 ; i < Nb ; i++) {	
//       t = state[0*4+i];
//       Tmp = state[0*4+i] ^ state[1*4+i] ^ state[2*4+i] ^ state[3*4+i] ;
//       Tm = state[0*4+i] ^ state[1*4+i] ; 
//       Tm = xtime(Tm); 
//       state[0*4+i] ^= Tm ^ Tmp ;
      
//       Tm = state[1*4+i] ^ state[2*4+i] ; 
//       Tm = xtime(Tm); 
//       state[1*4+i] ^= Tm ^ Tmp ;

//       Tm = state[2*4+i] ^ state[3*4+i] ; 
//       Tm = xtime(Tm); 
//       state[2*4+i] ^= Tm ^ Tmp ;

//       Tm = state[3*4+i] ^ t ; 
//       Tm = xtime(Tm); 
//       state[3*4+i] ^= Tm ^ Tmp ;
//    }
// }