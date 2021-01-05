#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return word < wm1.getWord();
}

bool WordMeaning::operator ==(const WordMeaning &wm1) const {
    return word == wm1.getWord();
}

void Dictionary::readDictionary(ifstream &f)
{
    string word1,mean1;
    while (!f.eof())
    {
        getline(f,word1);
        getline(f,mean1);
        WordMeaning wm1(word1,mean1);
        words.insert(wm1);
    }
}

string Dictionary::searchFor(string word) const
{
    WordMeaning wm1(word,"");
    WordMeaning wmx = words.find(wm1);
    WordMeaning wmNotFound("","");

    if (wmx == wmNotFound)
    {
        BSTItrIn<WordMeaning> it(words);
        string wb = "", wa = "", mb = "", ma = "";

        while (!it.isAtEnd() && it.retrieve() < wm1)
        {
            wb = it.retrieve().getWord();
            mb = it.retrieve().getMeaning();
            it.advance();
        }
        if(!it.isAtEnd())
        {
            wa = it.retrieve().getWord();
            ma = it.retrieve().getMeaning();
        }
        throw WordInexistent(wb, mb, wa, ma);
    }
    else return wmx.getMeaning();
}

bool Dictionary::correct(string word, string newMeaning)
{
    WordMeaning w(word, "");
    string meaning;
    try{
        meaning = searchFor(word);
    } catch (WordInexistent) {
        words.insert(WordMeaning(word, newMeaning));
        return false;
    }
    words.remove(WordMeaning(word, ""));
    words.insert(WordMeaning(word, newMeaning));
    return true;
}

void Dictionary::print() const
{
    /// in-order iterator
    BSTItrIn<WordMeaning> it(words);
    while(!it.isAtEnd()){
        cout << it.retrieve().getWord() << endl << it.retrieve().getMeaning() << endl;
        it.advance();
    }

    /// another in-order iterator
    iteratorBST<WordMeaning> it1 = words.begin();
    while(it1 != words.end()){
        cout << (*it1).getWord() << endl << (*it1).getMeaning() << endl;
        it1++;
    }
}

