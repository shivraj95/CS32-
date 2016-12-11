// WordLadderSolver.cpp

// This is an incomplete, and thus incorrect, implementation of WordLadderSolver
// functionality.  Your job is to change WordLadderSolverImpl to a correct,
// hopefully efficient, implementation.  You can change it any way you like,
// subject to restrictions in the spec (e.g., that the only C++ library
// containers you are allowed to use are vector, list, stack, and queue (and
// string); if you want anything fancier, implement it yourself).

#include "wordlist.h"
#include <string>
#include <vector>
#include <cctype>
#include <list>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

const int num_buck = 100000;

void removeNonLetters(string& s);

void insertToString(string* insertHere);


class Hashtable
{
public:
    
    Hashtable(int buckets) {
        
      m_words.resize(buckets);
    }
    
    bool search(const string& searchMe);
    void insert(const string& value);
    
    void deleteAll(){
        
        int size = m_words.size() - 1;
        
        for(int i = size; i > 0 ; i--){
        
            while(!m_words[i].empty()) {
                
                m_words[i].pop_back();
                
            }
            
            if(!m_words.empty()) {
                m_words.pop_back();
            }
        }
        
    }
    
    
private:
    
    vector<list<string> > m_words; //open hashtable
    
    
    int hashFunc(const string& word)
    {
        int totalvalue = 0;
        
        for(int i = 0; i < word.length(); i++) {
            
            totalvalue += totalvalue + (i+1) * word[i];
            
        }
        
        totalvalue = totalvalue % num_buck;
        
        return totalvalue;
    }
};

class tableofLadders{ //organized word Ladder that keeps track of words
public:
    void insert(const string& newValue) {
        
        orderedLadder.push_back(newValue);
        
    }
    
    bool search(const string& findMe) {
        
        list<string>::iterator findWord = orderedLadder.begin();
        
        for(findWord; findWord != orderedLadder.end(); findWord++) {
            
            if(*findWord == findMe) {
                return true;
            }
            
        }
        
        return false;
    }
    
    
    list<string>& getList() {
        return orderedLadder;
    }
    
    ~tableofLadders() {
        
        while(!orderedLadder.empty()) {
            
            orderedLadder.pop_back();
        }
        
    }

private:
    
    list<string> orderedLadder; //keeps track of ordering
    
};


class WordLadderSolverImpl
{
public:
    WordLadderSolverImpl(): container(num_buck) {}
    ~WordLadderSolverImpl() {}
    void createWordList(const vector<string>& words);
    int buildLadder(string start, string end, vector<string>& ladder);
    
    //4 ways to change a word in one step
    void substitute(tableofLadders addWords, const string& changeMe, queue<tableofLadders>& addLadders);
    void insertion(tableofLadders addWords, const string& changeMe, queue<tableofLadders>& addLadders);
    void deletion(tableofLadders addWords, const string& changeMe, queue<tableofLadders>& addLadders);
    void swap(tableofLadders addWords, const string& changeMe, queue<tableofLadders>& addLadders);
    
private:
    // You probably want something more sophisticated/efficient than this:
  
    Hashtable container;
};

bool Hashtable::search(const string& searchMe){
    
    int index = hashFunc(searchMe);
    const list<string>& findList = m_words[index];
    
    return find(findList.begin(), findList.end(), searchMe) != findList.end();
}

void Hashtable::insert(const string& value){
 
    int index = hashFunc(value);
    
   
    
    list<string> & findList = m_words[index];
    if(find(findList.begin(), findList.end(), value) != findList.end())
        return;
    
    findList.push_back(value);
    return;
}

void WordLadderSolverImpl::createWordList(const vector<string>& words)
{
    // You probably want something more sophisticated/efficient than this;
    // for one thing, it's horribly slow on a 60,000 word file.
    
    for (string word : words)
    {
        removeNonLetters(word);
        if (!word.empty())
            container.insert(word);
    }
}

int WordLadderSolverImpl::buildLadder(string start, string end, vector<string>& ladder)
{
    ladder.clear();
    removeNonLetters(start);
    removeNonLetters(end);
    
    
    if (!container.search(start))
        return 1;

    if (container.search(start) && !container.search(end))
        return 2;
    if (container.search(start) && start == end) {
        return 3;
    }
    
    else { //both words are in the wordlist and now it's time to check if there is a ladder
        
        queue<tableofLadders> allLadders;
        
        tableofLadders firstLadder;
        
        firstLadder.insert(start); //start off with start word
        
        allLadders.push(firstLadder);
        
        int distance = 1;
    
        while(!allLadders.empty())
        {
            tableofLadders currentLadder = allLadders.front();
            allLadders.pop();
            
            if(currentLadder.getList().back() == end) { //if the ladder leads to the end word
                
                for(list<string>::iterator addMe = currentLadder.getList().begin(); addMe != currentLadder.getList().end(); addMe++) { //copy the contents into the ladder
                    
                    ladder.push_back(*addMe);
                    
                }
                return 0; //and return the number of steps taken
                
            }
            
            //Now do the 4 types of changes to the last word of the ladder
            
            substitute(currentLadder, currentLadder.getList().back(), allLadders);
            
            insertion(currentLadder, currentLadder.getList().back(), allLadders);
            
            deletion(currentLadder, currentLadder.getList().back(), allLadders);
            
            swap(currentLadder, currentLadder.getList().back(), allLadders);
            
            
            
        }
        
        
        return -1;
        
    }
    
}

void WordLadderSolverImpl::substitute(tableofLadders addWords, const string& changeMe, queue<tableofLadders>& addLadders) {
    
    string temp = changeMe;
  
    for(int i=0;i<temp.size();i++)
    {
        
        for(char m='a';m<='z';m++)
        {
            temp[i] = m;
            
            if(container.search(temp) && !addWords.search(temp)) {
                //if word is in list and not in current ladder
                
                tableofLadders newLadder = addWords;
                newLadder.insert(temp); //make a new ladder
                
                addLadders.push(newLadder);
                
            }
            
        }
        temp = changeMe;
    }
    
}


    
void WordLadderSolverImpl::insertion(tableofLadders addWords, const string& changeMe, queue<tableofLadders>& addLadders) {
    
    
    string temp = changeMe;
    
    for(int i=0;i<changeMe.size();i++)
    {
        
        for(char m='a';m<='z';m++)
        {
            if(i == changeMe.size() - 1) {
                temp.insert(temp.end(), 1, m);
            }
            else {
            temp.insert(i, 1, m);
            }
            
            if(container.search(temp) && !addWords.search(temp)) {
                //if word is in list and not in current ladder
                
                tableofLadders newLadder = addWords;
                newLadder.insert(temp); //make a new ladder
                
                addLadders.push(newLadder);
                
            }
            
            temp = changeMe;
            
        }
    }
    
}

void WordLadderSolverImpl::deletion(tableofLadders addWords, const string& changeMe, queue<tableofLadders>& addLadders) {
    
    
    string temp = changeMe;
    
    for(int i=0;i<changeMe.size();i++)
    {
        
        temp.erase(i, 1);
            
            
        if(container.search(temp) && !addWords.search(temp)) {
            //if word is in list and not in current ladder
                
            tableofLadders newLadder = addWords;
            newLadder.insert(temp); //make a new ladder
                
            addLadders.push(newLadder);
                
        }
            
        temp = changeMe;
            
        
    }
    
}

void WordLadderSolverImpl::swap(tableofLadders addWords, const string& changeMe, queue<tableofLadders>& addLadders) {
    
    
    string temp = changeMe;
    
    for(int i=0;i<changeMe.size()-1;i++)
    {
        
        ::swap(temp[i], temp[i+1]);
        
        
        if(container.search(temp) && !addWords.search(temp)) {
            //if word is in list and not in current ladder
            
            tableofLadders newLadder = addWords;
            newLadder.insert(temp); //make a new ladder
            
            addLadders.push(newLadder);
            
        }
        
        temp = changeMe;
        
    }
    
}


void removeNonLetters(string& s){
    
    string::iterator to = s.begin();
    for (char ch : s)
    {
        if (isalpha(ch))
        {
            *to = tolower(ch);
            to++;
        }
    }
    s.erase(to, s.end());  // chop off everything from "to" to end.
}

//******************** WordLadderSolver functions **********************************

// These functions simply delegate to WordLadderSolverImpl's functions.
// You probably don't want to change any of this code.

WordLadderSolver::WordLadderSolver()
{
    m_impl = new WordLadderSolverImpl;
}

WordLadderSolver::~WordLadderSolver()
{
    delete m_impl;
}

void WordLadderSolver::createWordList(const vector<string>& words)
{
    m_impl->createWordList(words);
}

int WordLadderSolver::buildLadder(string start, string end, vector<string>& ladder)
{
    return m_impl->buildLadder(start, end, ladder);
}

