#include "../Cipher.h"

string getRailfence(string text, int key){
    string out = "";
    int y = 0;
    int x = 1;
    int column = ceil(text.size()/key);
    int lastcolumn = text.size() % column;
    
    for(unsigned int i=0; i<text.size(); i++){
        out = out + text[y];
        if(x<key){
            y += column;
        }else{
            y = ((y + lastcolumn)%(text.size()-1))+1;
            x = 0;
        }
        if(y >= text.size()){
            y = ((y+column)%(text.size()-1))+1;
            x = 0;
        }
        x += 1; 
    }
    return out;
}

string railfence(string encrypted){
    encrypted = uppercase(encrypted);
    int bestkey;
    long double bestscore = -INFINITY;
    long double score = 0;
    
    for(int i=1; i<=20; i++){
        score = getScore(getRailfence(encrypted, i));
        if(score > bestscore){
            bestscore = score;
            bestkey = i; 
        }

    }
    return "" + getRailfence(encrypted, bestkey);
}

vector<int> globaltranspositionkey = {};

vector<int> swap(vector<int> nums, int a, int b){
    bool generating = true;
    int pos1;
    int pos2;
    while(generating){
        pos1 = randbetween(a,b);
        pos2 = randbetween(a,b);
        if(pos1 != pos2){
            generating = false;
        }
    }
    int num1 = nums[pos1];
    int num2 = nums[pos2];
    nums[pos2] = num1;
    nums[pos1] = num2; 

    return nums;
}

// int randbetween(int minimum, int maximum){
//     return rand() % (maximum - minimum) + minimum;
// }

string getTransposition(vector<string> column, vector<int> key, int length, int keylength){
    string out;
    int a=0;
    int b=0;
    char letter;

    for(int i=0; i<length; i++){
        letter = column[key[a]][b];
        out += letter;
        a++;
        if(a >= keylength){
            a = 0;
            b += 1;
        }
        // if(!column[key[a]][b]){
        //     i--;
        // }
    }
    return out;
}

vector<int> randomTranspositionKey(int max){
    vector<int> nums;

    for(int i=0; i<max; i++){
        nums.push_back(i);
    }

    vector<int> outputkey;
    int randnum;

    for(int i=0; i<max; i++){
        if(i != max-1){
            randnum = randbetween(0, nums.size());
        }else{
            randnum = 0;
        }
        outputkey.push_back(nums[randnum]);
        nums.erase(nums.begin() + randnum);
    }

    return outputkey;
}

string Transposition(string encrypted){
    encrypted = uppercase(encrypted);
    vector<int> finalbestnums = {0};
    long double finalbestscore = -INFINITY;
    int finalbestlength = 1;
    if(encrypted.size() >= 20){
        for(int y=2; y<=20; y++){
            if(encrypted.size() % y == 0){
                int n = 0;
                while(n<ceil(y/4)){
                    vector<string> column = {};
                    vector<int> nums; 
                    nums = randomTranspositionKey(y); 
                    for(int x=0; x<y; x++){
                        column.push_back("");
                    }
                    int a = 0;
                    for(int i=0; i<encrypted.size(); i++){
                        column[a] += encrypted[i];
                        a++;
                        if(a >= y){
                            a = 0;
                        }
                    }
                    // if(y == 5){
                    //     // int nums[5] = {4,0,1,3,2};
                    //     nums[0] = 2;
                    //     nums[1] = 3;
                    //     nums[2] = 1;
                    //     nums[3] = 0;
                    //     nums[4] = 4;
                    // }

                    vector<int> bestnums;
                    bestnums = nums;
                    long double bestscore;
                    bestscore = getScore(getTransposition(column, bestnums, encrypted.size(), y)); 
                    
                    long double score;
                    string decrypted;

                    // for(int i=0; i<bestnums.size(); i++){
                    //     cout << bestnums[i] << ", ";
                    // }
                    // cout << endl;

                    for(int i=0; i<1000; i++){
                        nums = swap(nums, 0, y);
                        decrypted = getTransposition(column, nums, encrypted.size(), y);
                        score = getScore(decrypted);
                        if(score > bestscore){
                            bestscore = score;
                            bestnums = nums;
                            i=0;
                            if(score > finalbestscore){
                                finalbestscore = score;
                                finalbestnums = nums;
                                finalbestlength = y;
                                cout << "BESTSCORE CHANGED!!!\n";
                            }
                        }
                    }

                    // for(int i=0; i<bestnums.size(); i++){
                    //     cout << bestnums[i] << ", ";
                    // }

                    // cout << y << ": " << getTransposition(column, bestnums, encrypted.size(), y) << "\n\n";
                        n++;
                    }
                }
        }
    }else{
        return encrypted;
    }

    vector<string> column;
    for(int x=0; x<finalbestlength; x++){
        column.push_back("");
    }
    int a = 0;
    for(int i=0; i<encrypted.size(); i++){
        column[a] += encrypted[i];
        a++;
        if(a >= finalbestlength){
            a = 0;
        }
    }

    globaltranspositionkey = finalbestnums;
    return getTransposition(column, finalbestnums, encrypted.size(), finalbestlength);
}

string getTranspositionKey(){
    string out = "";
    for(int i=0; i<globaltranspositionkey.size(); i++){
        out += IntToString(globaltranspositionkey[i]) + " ";
    }
    return out;
}
