/**
 * @file Common.cpp
 * @author Kamel Assaf kamelassaf1@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Kamel Assaf (c) 1998 - 2022
 */
#include <iostream>
#include <string>
#include <set>
#include <map>
#include "../headers/Common.h"

void Common::removePunctuations(string &str, string replaceChar)
{
    unsigned int i = 0;
    char punctuations [] = { '!', '?', '.', ',', '#', '%', '^', '&', '*', 
        '(', ')', '_', '-', '+', '=', '[', ']', '{', '}', '/', '\'',
        };
    for( char punctuation : punctuations ) {
        for( i = 0 ; i < str.size(); i++ )
            if( str.at(i) == punctuation )
                str.replace( i, 1, replaceChar );
    }
}

void Common::loadStopWords(set<string> &stopwords)
{
    // ===================================== //
    // =========== LOAD STOPWORDS ========== //
    // ===================================== //
    string path = "stopwords/stopwordlist.txt";
    string stopword = "";
    ifstream fileReader( path );
    if( fileReader.is_open() ) {
        while ( getline( fileReader, stopword ) )
            stopwords.insert( stopword );
    }
    fileReader.close();
}

void
Common::stem(string &term)
{
    size_t tokenSize = term.size();
    char tokenToStem[ term.size() ];
    strcpy(tokenToStem, term.c_str());
    startStemTerm(tokenToStem, tokenSize);
    term = tokenToStem;
};

string Common::SplitToStem(string &phrase, string delimiter)
{
    string stemmedPhrase = "";
    auto start = 0U;
    auto end = phrase.find(delimiter);
     
    while (end != std::string::npos){
        string term = phrase.substr(start, end - start);
        stem( term );
        stemmedPhrase += term + " ";
        start = end + delimiter.length();
        end = phrase.find(delimiter, start);
    }
    return stemmedPhrase;
}

vector<string> Common::SplitToVector(string &phrase, string delimiter)
{
    vector<string> data;
    auto start = 0U;
    auto end = phrase.find(delimiter);
     
    while (end != std::string::npos){
        string term = phrase.substr(start, end - start);
        data.push_back(term);
        start = end + delimiter.length();
        end = phrase.find(delimiter, start);
    }
    return data;
}

// Returns a set (unique values). // for dictionary use.
set<string> Common::SplitToSet(string &phrase, string delimiter)
{
    set<string> data;
    auto start = 0U;
    auto end = phrase.find(delimiter);
     
    while (end != std::string::npos){
        string term = phrase.substr(start, end - start);
        data.insert(term);
        start = end + delimiter.length();
        end = phrase.find(delimiter, start);
    }
    return data;
}

void
Common::SplitToDictionary(string &phrase, string delimiter, set<string> &dictionary)
{
    set<string> data;
    auto start = 0U;
    auto end = phrase.find(delimiter);
     
    while (end != std::string::npos){
        string term = phrase.substr(start, end - start);
        dictionary.insert(term);
        start = end + delimiter.length();
        end = phrase.find(delimiter, start);
    }
}

// Occurences per phrase / text.
int countTermOccurences(string &phrase, string term)
{
    int tf = 0;
    for (int i = 0; (i = phrase.find(term, i)) != std::string::npos; i++)
        tf++;
    return tf;
}