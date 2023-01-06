#include "tea.hpp"
int main()
{
    fstream in("veri.txt");
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
    cout<<"Cikti Basarili Sekilde Yazildi to: c++_out.txt"<<endl;
    return 0;
}
