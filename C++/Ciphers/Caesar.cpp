#include "../Cipher.h"

string ceasarkey = "";

string getCeasarKey(){
    return ceasarkey;
}

string getCeasar(string in, int key){
  string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string alphabet2 = "abcdefghijklmnopqrstuvwxyz";
  string out;
  for(unsigned int i=0; i<in.size();i++){
    for(unsigned int x=0; x<alphabet.size();x++){
      if(in[i] == alphabet[x] || in[i] == alphabet2[x]){
        if(x + key > 25){
          out = out + alphabet[(x + key) - 26];
        }else{
          out = out + alphabet[x + key];
        }
      }
    }
  }
  return out;
}

string getCeasarFinal(string in, int key){
  string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string alphabet2 = "abcdefghijklmnopqrstuvwxyz";
  string out;
  bool done = false;
  for(unsigned int i=0; i<in.size();i++){
    done = false;
    for(unsigned int x=0; x<alphabet.size();x++){
      if(in[i] == alphabet[x] || in[i] == alphabet2[x]){
        if(x + key > 25){
          out = out + alphabet[(x + key) - 26];
        }else{
          out = out + alphabet[x + key];
        }
        done = true;
      }
    }
    if(!done){
      out = out + in[i];
    }
  }
  return out;
}

string Ceasar(string encrypted){
  int bestkey = 0;
  long double bestscore = -999999999999;
  for(int i=0; i<26; i++){
    if(getScore(getCeasar(encrypted, i)) > bestscore){
      bestscore = getScore(getCeasar(encrypted, i));
      bestkey = i;
    }
  }
  ceasarkey = IntToString(26 - bestkey);
  return getCeasarFinal(encrypted, bestkey);
}

string caesarwithkey(string encrypted, string key){
    string out = "";
    if(atof(key.c_str()) >= 0 && atof(key.c_str()) <= 26){
        out = getCeasarFinal(encrypted, 26 - atof(key.c_str()));
    } 
    return out;   
}
