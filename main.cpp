//
//  main.cpp
//  project4
//
//  Created by Shivraj Gill on 8/9/15.
//  Copyright (c) 2015 Shivraj Gill. All rights reserved.
//
#include "wordlist.h" 
#include <string>
#include <vector>
#include <cctype>
#include <list>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;


const char* filename = "/Users/shivrajgill/Downloads/wordladder/wordlist.txt";
// A Windows user might have the path be "C:/CS32/P4/wordlist.txt"
// A Mac user might have it be "/Users/fred/CS32/P4/wordlist.txt"

int main()
{
    ifstream wordlistfile(filename);
    if (!wordlistfile)
    {
        cerr << "Cannot open " << filename << "!" << endl;
        return 1;
    }
    vector<string> words;
    vector<string> result;
    
    string w;
    while (wordlistfile >> w)
        words.push_back(w);
    
    WordLadderSolver wls;
    wls.createWordList(words);
    
    assert(wls.buildLadder("b", "a", result) == 1  &&  result.empty());
    assert(wls.buildLadder("a", "b", result) == 2  &&  result.empty());
    
    assert(wls.buildLadder("abandoned", "abandoned", result) == 3  &&  result.empty());
    assert(wls.buildLadder("abandoned", "abandoning", result) == -1  && result.empty());
    
    
    assert(wls.buildLadder("a", "aah", result) == 0  && result.size() == 3);
    
    int i = 0;
    while(i < 3) {
        
        cout << result[i] << " " ;
        i++;
    }
    cout << endl;
    
    
    assert(wls.buildLadder("love", "hate", result) == 0  && result.size() == 4);
    
    int j = 0;
    while(j < 4) {
        
        cout << result[j] << " " ;
        j++;
    }
    cout << endl;
    
    assert(wls.buildLadder("bed", "big", result) == 0  && result.size() == 3);
    
    int x = 0;
    while(x < 3) {
        
        cout << result[x] << " " ;
        x++;
    }
    cout << endl;

}