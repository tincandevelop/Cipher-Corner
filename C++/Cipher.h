#ifndef CIPHER_H
#define CIPHER_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <math.h> 
#include <iostream>

using namespace std;
    void loadQuadgrams();
    void loadWords();
    string Ceasar(string encrypted);
    string caesarwithkey(string encrypted, string key);
    string Monospace(string encrypted);
    string monospacewithkey(string encrypted, string key);
    string Vigenere(string encrypted);
    string vigenerewithkey(string encrypted, string key);
    string railfence(string encrypted);
    string Transposition(string encrypted);
    string Keyword(string encrypted, string keyword);
    string getMonospaceKey();
    string getVigenereKey();
    string getCeasarKey();
    string getTranspositionKey();
    string uppercase(string text);
    string IntToString(double a);
    string addSpaces(string in);
    string striptonumber(string in);
    long double getScore(string text);
    int randbetween(int min, int max);

#endif
