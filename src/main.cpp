#include "tea.hpp"
int main()
{
    while(1)
    {
        string input="";
        decision = 0;
        string encrypted="";
        string decrypted="";
        uint32_t key[4] = {0,0,0,0};
        cin.sync();

        cout<<"Enter a String: ";
        getline(cin,input);

        inputLen = input.length();

        newSize = inputLen;

        cout<<"Enter a 4 digits key: ";
        for(int i = 0 ; i < 4 ; i++)
        {
            cin>>key[i];
        }

        if (inputLen % 8 != 0)
            newSize = inputLen + (8 - inputLen % 8);

        for (uint32_t i = 0; i < newSize - inputLen; ++i)
        {
            char c = 0x0;
            input += c;
        }

        //rounds = how many blocks have been entered by user
        rounds = newSize/8;

        decision = 0;
        encrypted = TEA(input, key);

        cout<<"Enter (1) to Decrypt, or (0) to Enter another sentence: ";
        cin>>decision;

        if(decision)
        {
            decision = 1;
            decrypted = TEA(encrypted, key);
            return 0;
        }
    }
}
