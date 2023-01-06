#include<stdint.h>
#include <string>
#include<iostream>
using namespace std;

uint32_t inputLen;
uint32_t newSize;
uint32_t rounds;
bool decision;

/**
 * Bu işlev, TEA kullanarak 32 döngüde 64 bitlik bir bloğu şifrelemek için 128 bitlik bir anahtar kullanır.
 *
 * @param values - 2 boyutlu uint32_t  dizisi (64 bit blok)
 * @param key - 4 boyutlu uint32_t dizisi (128 bit anahtar)
 */
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



/**
 * Bu işlev, TEA kullanarak 32 döngüde 64 bitlik bir bloğun şifresini çözmek için 128 bitlik bir anahtar kullanır.
 *
 * @param values - 
 * @param key 
 */
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



/**
 *Bu işlev, 8 boyutlu bir karakter dizisindeki her 4 karakteri bir 32 bit blokta birleştirir.
 *
 * @param str - 8 boyutunda imzasız karakter dizisi
 * @param values - uint32_t boyut 2 dizisi (64 bit blok)
 */
void combine(unsigned char* str, uint32_t* values){
  
	values[0] = str[0] | str[1] << 8 | str[2] << 16 | str[3] << 24;
    values[1] = str[4] | str[5] << 8 | str[6] << 16 | str[7] << 24;
}




/**
 * 
 *
 * @param values - uint32_t dizisi (64-bit blok) bölünecek
 *
 * @return bir dize, 64 bit blokta saklanan eşdeğer 8 karakteri içerir
 */
string split(uint32_t* values){
   

    string splitOut = "";

	// ilk 4 karakteri [0] değerlerinden splitOut dizgisine bölüyoruz
    splitOut += (unsigned char)(values[0] & 0xFF);
    splitOut += (unsigned char)(values[0] >> 8);
    splitOut += (unsigned char)(values[0] >> 16);
    splitOut += (unsigned char)(values[0] >> 24);

    // value[1]'den ikinci 4 karakter splitOut string'e bölünüyor
    splitOut += (unsigned char)(values[1] & 0xFF);
    splitOut += (unsigned char)(values[1] >> 8);
    splitOut += (unsigned char)(values[1] >> 16);
    splitOut += (unsigned char)(values[1] >> 24);

    return splitOut;
}



/**

  * Bu işlev, yinelenen kodu önlemek için diğer tüm işlevler için bir sürücü olarak çalışır.
  * Ayrıca, herhangi bir boyutta girişe izin vermek için diziyi 64 bitlik birden çok bloğa böler.
  * Her bloğu şifrele veya şifresini çöz (karar bitine bağlı olarak)
  * Şifrelenmiş metni veya şifresi çözülmüş metni görüntüleyin
 

  @param str - kullanıcı input
  @param key 
 */
string TEA(string in, uint32_t* key){

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
        cout<<out[i];
    }
    cout<<endl<<endl;

    return out;
}



/**
  *Kullanıcıdan herhangi bir boyutta bir dizi okuyun
  * Kullanıcıdan 4 tamsayı anahtarı okuyun
  *
  * 4 tamsayı anahtarını kullanarak tüm diziyi şifreleyin
  * Şifreli mesajı göster
  *
  * Kullanıcıya şifresini çözmek mi yoksa başka bir dizi girmek mi istediğini sorun.
  *
  * Şifresi çözülmüş mesajı göster
  * veya programın başına tekrar gidin
 */