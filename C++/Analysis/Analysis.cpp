#include <sstream>
#include <time.h>
#include <stdlib.h>
#include "../Cipher.h"

using namespace std;

vector<long double> quads;

string IntToString (double a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}

void loadQuadgrams(){
    srand(time(NULL));    
    ifstream infile("data/quads.txt");

    string line;

    while(getline(infile, line)){

        string val = "";

        for(unsigned int i=0; i<line.size(); i++){
            val = val + line[i];
        }
        long double newVal = atof(val.c_str());
        quads.push_back(newVal);
    }
    infile.close();
}

string uppercase(string text){
    string out;
    string key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int z;
    
    for(unsigned int s = 0; s < text.size(); s++){
        z = (int)text[s];    
        if(z >= 65 && z <= 90){
            out = out + "" + key[z - 65]; 
        }else if(z >= 97 && z <= 122){
            out = out + "" + key[z - 97];
        }
    }
    
    return out;
}

string striptonumber(string in){
    string out = "";
    
    for(unsigned int i=0; i<in.size(); i++){
        if(in[i] >= '0' && in[i] <= '9'){
            out += in[i];
        }
    }
        
    return out;
}

long double getScore(string text){
    int val = 0;
    long double score = 0;
    for(unsigned int i=0; i<text.size()-3; i++){
        val = (((int)text[i]-65)*26*26*26) + (((int)text[i+1]-65)*26*26) + (((int)text[i+2]-65)*26) + ((int)text[i+3]-65);
        score += quads[val];
        val = 0;
    }
    return score;
}
