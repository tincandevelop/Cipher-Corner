#include "../Cipher.h"

string monospacekey = "";
string encryptedanalysis;

int randbetween(int minimum, int maximum){
    return rand() % (maximum - minimum) + minimum;
}

string getMonoAnalysis(string key){
    string out = "";
    string letter;
    int z;
    for(unsigned int s = 0; s < encryptedanalysis.size(); s++){
        z = (int)encryptedanalysis[s];    
        out = out + "" + key[z - 65]; 
    }
    return out;
}

string getMonoFinal(string text, string key){
    string out = "";
    string letter;
    int z;
    for(unsigned int s = 0; s < text.size(); s++){
        z = (int)text[s];
        if(z >= 65 && z <= 90){
            out = out + "" + key[z - 65]; 
        }else if(z >= 97 && z <= 122){
            out = out + "" + key[z - 97];
        }else{
            out = out + text[s];    
        }    
    }
    return out;
}

string randomMonoKey(){
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string out = "";
    int num;
    string letter;
    bool good = false;

    for(int i = 0; i < 26; i++){
        while(!good){
            num = randbetween(0,alphabet.size());
            letter = alphabet[num];
            if(letter != "_"){
                out = out + alphabet[num];
                alphabet[num] = '_';
                good = true;
            }
        }
        good = false;
    }
    return out;
}

string swapMonoKey(string in, int num1, int num2){
    if(num1 != num2){
        char swap1 = in[num1];
        char swap2 = in[num2];
        in[num1] = swap2;
        in[num2] = swap1;
    }
    return in;
}

string reversekey(string key){
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string out = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(unsigned int i=0; i < alphabet.size(); i++){
        out[(int)key[i] - 65] = alphabet[i];
    }
    return out;
}

string Monospace(string encrypted){
    encryptedanalysis = uppercase(encrypted);
    if(encryptedanalysis.size() > 500){
        string x = "";
        for(int i=0; i<500; i++){
            x += encryptedanalysis[i];
        }
        encryptedanalysis = x;
    }
    long double firstscore = -INFINITY;
    string firstkey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string bestkey;
    double b = 0.0;
    int ticks = 0;
    int start;
    
    for(int y=0; y < 5; y++){
        string key = randomMonoKey();
        if(y == 0){
            bestkey = key;
        }
        long double score;
        long double bestscore = getScore(getMonoAnalysis(key));
        string text;
        int a;
        int b;
        for(int i=0; i<25; i++){
            if(i+1 < 26){
                for(int x=i+1; x<26; x++){
                    key = swapMonoKey(bestkey, i, x);
                    text = getMonoAnalysis(key);
                    score = getScore(text);
                    if(score > bestscore){
                        bestkey = key;
                        bestscore = score;
                        i = 0;
                    }
               }
            }
        }
        if(bestscore > firstscore){
            firstscore = bestscore;
            firstkey = bestkey;
        }
    }
    monospacekey = reversekey(firstkey);
    return getMonoFinal(encrypted, firstkey);
}

string getMonospaceKey(){
    return monospacekey;
}

string Keyword(string encrypted, string keyword){
    keyword = uppercase(keyword);
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string key = "";
    
    for(int i=0; i<keyword.size(); i++){
        if(alphabet[keyword[i] - 'A'] != '_'){
            key += keyword[i];
            alphabet[keyword[i] - 'A'] = '_';
        }
    }
    
    int keysize = key.size();
    int x = key[keysize-1] - 'A';
    
    for(int i=keysize; i < alphabet.size(); i+=0){
        if(x > 25){
            x = 0;
        }
        if(alphabet[x] != '_'){
            key += alphabet[x];
            alphabet[x] = '_';
            i++;
        }
        x++;
    }
    
    key = reversekey(key);
    
    return getMonoFinal(encrypted, key);    
}

string monospacewithkey(string encrypted, string key){
    string out = ""; 
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    bool iskey = true;
    if(key.size() == 26){
        for(int i=0; i <= 25; i++){
            if(alphabet[key[i] - 'A'] != '_'){
                alphabet[key[i] - 'A'] = '_';     
            }else{
                iskey = false;    
            }
        }
        if(iskey){
            out = getMonoFinal(encrypted, reversekey(key));
        }
    }
    return out;    
}
