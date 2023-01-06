#include<stdint.h>
#include <string>
#include<iostream>
#include<fstream>
using namespace std;

uint32_t inputLen;
uint32_t newSize;
uint32_t rounds;
bool decision;
string printFile = "";




 
void encrypt(uint32_t* values, uint32_t* key) {
   

    uint32_t sum = 0, i, v0 = values[0], v1 = values[1];
    uint32_t delta = 0x9e3779b9;

    for (i = 0; i < 32; i++) {
        sum += delta;
        v0 += ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        v1 += ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
    }
    values[0] = v0; values[1] = v1;

}




void decrypt(uint32_t* values, uint32_t* key) {
  

    uint32_t delta = 0x9e3779b9;
    uint32_t v0 = values[0], v1 = values[1],
    		sum = delta<<5, i;

    for (i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
        v0 -= ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        sum -= delta;
    }

    values[0] = v0; values[1] = v1;

}



void combine(unsigned char* str, uint32_t* values){
 
	values[0] = str[0] | str[1] << 8 | str[2] << 16 | str[3] << 24;
    values[1] = str[4] | str[5] << 8 | str[6] << 16 | str[7] << 24;
}



string split(uint32_t* values){
  

    string splitOut = "";

	
    splitOut += (unsigned char)(values[0] & 0xFF);
    splitOut += (unsigned char)(values[0] >> 8);
    splitOut += (unsigned char)(values[0] >> 16);
    splitOut += (unsigned char)(values[0] >> 24);

    
    splitOut += (unsigned char)(values[1] & 0xFF);
    splitOut += (unsigned char)(values[1] >> 8);
    splitOut += (unsigned char)(values[1] >> 16);
    splitOut += (unsigned char)(values[1] >> 24);

    return splitOut;
}




string TEA(string in, uint32_t* key){
    printFile="";
    string out = "";
    uint32_t values[2];
    unsigned char turn[9]= "";

    for(uint32_t i = 0 ; i < rounds ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            turn[j] = in[i*8 + j];
        }

        combine(turn, values);

        if(decision == 0)
            encrypt(values, key);
        else
            decrypt(values, key);

        out+=split(values);
    }
    
    cout<<endl;
    if(decision == 0)
    {
        cout<<"Encrypted: ";
    }
    else
        cout<<"Decrypted: ";
    
    for(uint32_t i = 0 ; i < inputLen ; i++)
    {
        if(out[i] == 0x0)
        {
            cout<<' ';
            printFile+=' ';
        }
        else
        {
            cout<<out[i];
            printFile+=out[i];
        }

    }

    cout<<endl<<endl;

    return out;
}



