#include "../Cipher.h"
#include <map>
#include <algorithm>

//map<string,long double> words;
//string xyz = "";

//void loadWords(){
//    ifstream file("dictionary.txt");
//    
//    string line;
//    string key;
//    string value;
//    vector<string> s;
//    int i = 0;
//    while (getline(file, key) && getline(file, value) && i < 63570){
//        words[uppercase(key)] = log10(atof(value.c_str()) / 1024908267229.0);
//        xyz = key;
//    }    
//}

string addSpaces(string in){
    in = uppercase(in);
/*    string out = xyz + ";";
    string word = "";
    long double biggest;
    string bstring = "";
    //vector<string> words;
    bool done = false;
    
    for(int i=0; i<in.length(); i++){
        done = false;
        biggest = -999999999999;
        bstring = "";
        for(int length = 1; length <= 29; length++){
            word = "";
            for(int x=0; x<length; x++){
                word = word + in[i + x];
            }
            if(words[word] != 0){
                if(words[word] > biggest){
                    done = true;
                    biggest = words[word];
                    bstring = word;
                }
            }
        }
        if(!done){
            out = out + "" + in[i];
        }else{
            out = out + bstring + " ";
            i = i + bstring.size() - 1;
        } 
    }*/
    
    return in;
}
