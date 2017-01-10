#include "../Cipher.h"

string globalkey = "";

long double monograms[] = {8.572943461540966,7.8463112887813535,8.141187709730083,8.228735262578752,8.723552014792169,7.979648765246908,7.960275610362052,8.335997124035698,8.505706139219495,6.98287746482747,7.548677590841689,8.264808688567578,8.043380136786297,8.49654295387987,8.514053065940553,7.956056705380062,6.658027240957975,8.442481087624394,8.468790571993626,8.592137996827502,8.069282387599914,7.665929421775836,7.902240458370373,6.922721047572901,7.876763340184817,6.696867017969479};

long double getScoreX(string x){
    long double score = 0;
    int val = 0;
    for(int i=0; i<x.size();i++){
        val = (int)x[i] - 'A';
        score += monograms[(int)x[i] - 'A'];
    }
    return score;
}

string getCeasarX(string text, int key){
    string out = "";
    int ch = 0;
    for(int i=0; i<text.size(); i++){
        ch = ((text[i]-'A') - key);
        if(ch >= 0){
            out = out + (char)((ch%26)+'A'); 
        }else{
            out = out + (char)((ch+26)+'A');
        }
    }
    
    return out;
}

char getCaesarKey(string encrypted){
  int bestkey = 0;
  long double bestscore = -INFINITY;
  for(int i=0; i<26; i++){
    if(getScoreX(getCeasarX(encrypted, i)) > bestscore){
      bestscore = getScoreX(getCeasarX(encrypted, i));
      bestkey = i;
    }
  }
  return (char)(bestkey + 'A');  
}

string getVigenereKey(){
    return globalkey;
}

string getVigenere(string text, string thiskey, int keylength){
    string out = "";
    char letter = 65;
    
    int x = 0;
    
    for(unsigned int i=0; i < text.size(); i++){
        x = (text[i]-'A') - (thiskey[i%keylength]-'A'); 
        if(x >= 0){
          out = out + (char)((x%26)+'A'); 
        }else{
          out = out + (char)((x+26)+'A');  
        }
    }
    
    return out;    
}

vector<int> factors(int num){
    vector<int> out;
    for (int i = 1; i <= num && i <= 20; i++){
        if (num % i == 0){
            out.push_back(i);
        }
    }
    return out;
}

string Vigenere(string encrypted){
    encrypted = uppercase(encrypted);
    string bestkey = "";
    long double bestscore = -INFINITY;
    vector<long double> scores;
    vector<string> keys;     
    
    string out;
    string key = "";
    string strings[20] = {"","","","","","","","","","","","","","","","","","","",""};
    for(int i=3; i<=20;  i++){
        string split[i];
        for(int x=0; x<encrypted.size(); x++){
            split[x%i] += encrypted[x];
        }
        for(int x=0; x<i; x++){
            key += getCaesarKey(split[x]);
        }
        scores.push_back(getScore(getVigenere(encrypted, key, key.size())));
        keys.push_back(key);
        key = "";
    }
    
    for(unsigned int i=0; i<scores.size(); i++){
        long double score = scores[i];
        if(score > bestscore){
            bestkey = keys[i];
            bestscore = scores[i];
        }
        
    }
       
    
    globalkey = bestkey;
    return "" + getVigenere(encrypted, bestkey, bestkey.size());    
}

string vigenerewithkey(string encrypted, string key){
    return "" + getVigenere(encrypted, key, key.size());    
}
