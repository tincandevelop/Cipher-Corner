#include <fstream>
#include <iostream>
#include "Cipher.h"

using namespace std;

enum ciphers {
    caesar,
    monospace,
    vigenere,
    keyword,
    transposition
};

ciphers cipher = caesar;

int main(){

    loadQuadgrams();

    while(true){

        

        string xcipher = "";
        string key = "";
        string text = "";
        int err = 0;

        cout << "Ciphertext: ";
        fflush(stdin);
        cin >> text;
        cout << endl << "Cipher: ";
        cin >> xcipher;
        cout << endl << "Encryption key (if unknown type '0'): ";
        cin >> key;

        if(key == "0"){
            key = "";
        }

        if(xcipher == "caesar"){
            cipher = caesar;
        }else if(xcipher == "mono-alphabetic"){
            cipher = monospace;
        }else if(xcipher == "keyword"){
            cipher = keyword;
        }else if(xcipher == "vigenere"){
            cipher = vigenere;
        }

        string returnval = "";

        if(text.size() > 4){
            if(uppercase(key) != "" && cipher != caesar){
                switch(cipher){
                  case monospace:
                    returnval = monospacewithkey(text, uppercase(key));
                    break;
                  case vigenere:
                    returnval = vigenerewithkey(uppercase(text), uppercase(key));
                    break;
                  case keyword:
                    returnval = Keyword(text, uppercase(key));
                    break;
                  default:
                    break;
                }
                if(returnval == ""){
                    err = 2;
                }else{
                }
            }else if(cipher == caesar && striptonumber(key) != ""){
                returnval = caesarwithkey(text, striptonumber(key));
                if(returnval == ""){
                    err = 2;
                }else{
                }
            }else{
                switch(cipher){
                    case monospace:{
                        returnval = Monospace(text);
                        key = getMonospaceKey();
                        break;
                    }
                    case caesar:{
                        returnval = Ceasar(text);
                        key = getCeasarKey();
                        break;
                    }
                    case vigenere:{
                        returnval = Vigenere(text);
                        key = getVigenereKey();
                        break;
                    }
                    case keyword:{
                        err = 3; //cannot guess keyword
                    }
                    default:{
                        err = 4; //invalid cipher
                    }
                }
            }
        }else{
            err = 1; //Invalid chiphertext
        }

        if(returnval != ""){
            cout << endl << "Key: " << key;
            cout << endl << "Plaintext: " << returnval << endl;
        }
    }

    return 0;
}
