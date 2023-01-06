uint32_t inputLen;     .input uzunluğu
uint32_t newSize;      .32 bit işaretsiz
uint32_t rounds; 	     .yuvarlama
bool decision;
string printFile = "";



  Bu işlev, TEA kullanarak 32 döngüde 64 bitlik bir bloğu şifrelemek için 128 bitlik bir anahtar kullanır.
 
  parametre values - 2 boyutlu uint32_t dizisi (64-bit block)
  parametre key -    4 boyutlu uint32_t dizisi (128-bit key)
 
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


 Bu işlev, TEA kullanarak 32 döngüde 64 bitlik bir bloğun şifresini çözmek için 128 bitlik bir anahtar kullanır.
 
  parametre values - 2 boyutlu uint32_t dizisi  (64-bit block)
  parametre key -    4 boyutlu uint32_t dizisi (128-bit key)

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


  Bu işlev, 8 boyutlu bir karakter dizisindeki her 4 karakteri bir 32 bit blokta birleştirir.
 
  parametre values - 2 boyutlu uint32_t dizisi  (64-bit block)
  parametre key -    4 boyutlu uint32_t dizisi (128-bit key)
 
void combine(unsigned char* str, uint32_t* values){
    .
	values[0] = str[0] | str[1] << 8 | str[2] << 16 | str[3] << 24;
    values[1] = str[4] | str[5] << 8 | str[6] << 16 | str[7] << 24;
}



 Bu işlev, 64 bit bloktan her 32 biti 4 karaktere böler
 
 parametre values - uint32_t dizisi (64-bit blok) bölünecek
 
 64 bit blokta saklanan eşdeğer 8 karakteri içeren bir dize döndürür
 
string split(uint32_t* values){
   

    string splitOut = "";

	// ilk 4 karakteri  değerleri[0] splitOut dizgisine bölüyoruz
    splitOut += (unsigned char)(values[0] & 0xFF);
    splitOut += (unsigned char)(values[0] >> 8);
    splitOut += (unsigned char)(values[0] >> 16);
    splitOut += (unsigned char)(values[0] >> 24);
uint32_t array (64-bit block) to be splitted
    // ikinci 4 karakterin  değerleri[1] splitOut dizesine bölünmesi
    splitOut += (unsigned char)(values[1] & 0xFF);
    splitOut += (unsigned char)(values[1] >> 8);
    splitOut += (unsigned char)(values[1] >> 16);
    splitOut += (unsigned char)(values[1] >> 24);

    return splitOut;
}



 Bu işlev, yinelenen kodu önlemek için diğer tüm işlevler için bir sürücü olarak çalışır.e
 Ayrıca, herhangi bir boyutta girişe izin vermek için diziyi 64 bitlik birden çok bloğa böler.
 Her bloğu şifrele veya şifresini çöz (karar bitine bağlı olarak)
 Şifrelenmiş metni veya şifresi çözülmüş metni görüntüleyin

 parametre str - kullanıcı input
 parametre key -    4 boyutlu uint32_t dizisi (128-bit key
 
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
            //cout<<' ';
            printFile+=' ';
        }
        else
        {
            //cout<<out[i];
            printFile+=out[i];
        }

    }

    //cout<<endl<<endl;

    return out;
}

#include "tea.hpp"
int main()
{
    fstream in("test_cases.txt");
    ofstream out("c++_out.txt");
    char string1[5000];
    while(!in.eof())
    {

        in.getline(string1,5000);

        string input = string1;

        decision = 0;
        string encrypted="";
        string decrypted="";
        uint32_t key[4] = {0,0,0,0};
        //cin.sync();



        inputLen = input.length();
        cout <<"Veri  Uzunlugu: "<<inputLen<<endl;

        newSize = inputLen;


        if (inputLen % 8 != 0)
            newSize = inputLen + (8 - inputLen % 8);

        for (uint32_t i = 0; i < newSize - inputLen; ++i)
        {
            char c = 0x0;
            input += c;
        }

        tur = kullanıcı tarafından girilen blok sayısı
        rounds = newSize/8;

        decision = 0;
        encrypted = TEA(input, key);
        out << printFile<<endl;


        decision = 1;
        decrypted = TEA(encrypted, key);
        out << printFile<<endl;
    }
    in.close();
    out.close();
    cout<<"çıktı basarılı şekilde yazıldı to: c++_out.txt"<<endl;
    return 0;
}




