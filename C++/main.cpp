#include <fstream>
#include <iostream>
#include <windows.h>
#include "Cipher.h"

using namespace std;

enum ciphers {
    caesar = 0,
    monospace = 1,
    vigenere = 2,
    keyword = 3,
    transposition = 4
};

ciphers cipher = caesar;

int main(){

    loadQuadgrams();

    cout << "\nReady!\n";

    while(true){

        while(!(GetAsyncKeyState(VK_F24))){Sleep(10);}

        string xcipher = "";
        string key = "";
        string text = "";

        string line;

        ifstream cipherfile("data/cipher.txt");
        while(getline(cipherfile,line)){
            xcipher += line;
        }
        cipherfile.close();

        ifstream keyfile("data/key.txt");
        while(getline(keyfile,line)){
            key += line;
        }
        keyfile.close();

        ifstream textfile("data/text.txt");
        while(getline(textfile,line)){
            text += line;
        }
        textfile.close();

        if(xcipher == "caesar"){
            cipher = caesar;
        }else if(xcipher == "mono"){
            cipher = monospace;
        }else if(xcipher == "keyword"){
            cipher = keyword;
        }else if(xcipher == "vigenere"){
            cipher = vigenere;
        }else if(xcipher == "transposition"){
            cipher = transposition;
        }

        cout << "Chipher: " << cipher << endl;

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
                    ofstream errfile("data\\err.txt");
                    errfile << 2;
                    errfile.close();
                }else{
                  ofstream keyfile("data\\keyde.txt");
                  keyfile << key;
                  keyfile.close();
                }
            }else if(cipher == caesar && striptonumber(key) != ""){
                returnval = caesarwithkey(text, striptonumber(key));
                if(returnval == ""){
                    ofstream errfile("data\\err.txt");
                    errfile << 2;
                    errfile.close();
                }else{
                  ofstream keyfile("data\\keyde.txt");
                  keyfile << key;
                  keyfile.close();
                }
            }else{
                switch(cipher){
                    case monospace:{
                        returnval = Monospace(text);
                        ofstream keyfile("data\\keyde.txt");
                        keyfile << getMonospaceKey();
                        keyfile.close();
                        break;
                    }
                    case caesar:{
                        returnval = Ceasar(text);
                        ofstream keyfile("data\\keyde.txt");
                        keyfile << getCeasarKey();
                        keyfile.close();
                        break;
                    }
                    case vigenere:{
                        returnval = Vigenere(text);
                        ofstream keyfile("data\\keyde.txt");
                        keyfile << getVigenereKey();
                        keyfile.close();
                        break;
                    }
                    case keyword:{
                        ofstream errfile("data\\err.txt");
                        errfile << 3;
                        errfile.close();
                    }
                    case transposition:{
                        returnval = Transposition(text);
                        ofstream keyfile("data\\keyde.txt");
                        keyfile << getTranspositionKey();
                        keyfile.close();
                        break;
                    }
                    default:{
                      ofstream errfile("data\\err.txt");
                      errfile << 4;
                      errfile.close();
                    }
                }
            }
        }else{
            ofstream errfile("data\\err.txt");
            errfile << 1;
            errfile.close();
        }

        if(returnval != ""){
            ofstream decryptedfile("data\\decrypted.txt");
            decryptedfile << returnval;
            decryptedfile.close();
            cout << returnval;
        }

        system("data\\AutoHotKey.exe");
        
        Sleep(10);
    }

    return 0;
}
