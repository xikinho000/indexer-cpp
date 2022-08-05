/**
 * @file main.cpp
 * @author Kamel Assaf (kamelassaf1@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <chrono>
#include <set>
#include <map>
#include "src/FileManager.cpp"
#include "src/FileContent.cpp"
#include "src/Indexer.cpp"
#include "src/Query.cpp"
#include <atomic>

using namespace std;

void printQueriesSet(map<int, set<string>> &queriesSet)
{
    for(auto & q : queriesSet){
        for(set<string>::iterator it = begin(q.second); it != end(q.second); ++it)
            cout << *it << endl;
    }
}

void printDictionary(set<string> &dictionary)
{
    cout << "---------------------" << endl;
    cout << " Printing Dictionary " << endl;
    cout << "---------------------" << endl;
    for(set<string>::iterator i = begin(dictionary); i != end(dictionary); ++i)
        cout << *i << endl;
    cout << "---------------------" << endl;
}

void printPostings(map< string, map<string, int> > &postings)
{
    cout << "---------------------" << endl;
    cout << "  Printing Postings  " << endl;
    cout << "---------------------" << endl;
    for( const auto& posting : postings ) {
        string term = posting.first;
        cout << term << "|";
        for( const auto& postingList : posting.second )
            cout << postingList.first << "," << postingList.second << ";";
        cout << endl;
    }
    cout << "---------------------" << endl;
}

void printTestCollection(const map<string, FileContent> &TestCollection )
{
    cout << "---------------------" << endl;
    cout << "   Test Collection   " << endl;
    cout << "---------------------" << endl;
    for( const auto sm_pair : TestCollection ) { 
        std::cout << "Doc ID: " << sm_pair.first << "|" << endl;
        FileContent fc = sm_pair.second;
        string author    = fc.getAuthor(),
               title     = fc.getTitle(),
               text      = fc.getText(),
               biblio    = fc.getBiblio(),
               docNumber = fc.getDocNumber();
        
        cout << author;
        cout << title;
        cout << text;
        cout << biblio;
        cout << endl;
    }
}

int main( int argc, char ** argv )
{
    cout << "Version: " << __cplusplus << endl;
    map<string, FileContent> testCollection;
    map< string, map<string,int> > postings;
    set<string> dictionary;
    Indexer indexer;

    // ------------------------------------- //
    // ----- LOAD TEST COLLETION TO RAM ---- //
    // ------------------------------------- //
    auto start1 = chrono::steady_clock::now();
    indexer.loadCollection(testCollection);
    auto end1 = chrono::steady_clock::now();
    duration<double> time_span1 = duration_cast<duration<double>>(end1 - start1);
    cout << "[+] Time to load test collection: \t\t" <<
        time_span1.count() << " seconds." << endl;
        
    // ------------------------------------- //
    // --------- REMOVE PUNCTUATION -------- //
    // ------------------------------------- //
    auto start2 = chrono::steady_clock::now();
    indexer.startRemovePunctuation(testCollection);
    auto end2 = chrono::steady_clock::now();
    duration<double> time_span2 = duration_cast<duration<double>>(end2 - start2);
    cout << "[+] Time to remove punctuations: \t\t" <<
        time_span2.count() << " seconds." << endl;

    // ------------------------------------ //
    // ---------- REMOVE STOPWORDS -------- //
    // ------------------------------------ //
    auto start3 = chrono::steady_clock::now();
    indexer.removeStopwords(testCollection);
    auto end3 = chrono::steady_clock::now();
    duration<double> time_span3 = duration_cast<duration<double>>(end3 - start3);
    cout << "[+] Time to remove stopwords: \t\t\t" <<
        time_span3.count() << " seconds." << endl;
   
    // ------------------------------------- //
    // -------------- STEMMER -------------- //
    // ------------------------------------- //
    auto start5 = chrono::steady_clock::now();
    indexer.stemWords(testCollection);
    auto end5 = chrono::steady_clock::now();
    duration<double> time_span5 = duration_cast<duration<double>>(end5 - start5);
    cout << "[+] Time to stem terms: \t\t\t" <<
        time_span5.count() << " seconds." << endl;

    // ------------------------------------- //
    // --------- CREATE DICTIONARY --------- //
    // ------------------------------------- //
    indexer.createDictionary(dictionary, testCollection);

    // ------------------------------------- //
    // ----------- TERM FREQUENCY ---------- //
    // ------------------------------------- //
    auto start4 = chrono::steady_clock::now();
    indexer.setTermFrequency(testCollection, dictionary, postings);
    auto end4 = chrono::steady_clock::now();
    duration<double> time_span4 = duration_cast<duration<double>>(end4 - start4);
    cout << "[+] Time to count term frequency & create the postings: \t\t\t" <<
        time_span4.count() << " seconds." << endl;

    /* Researching -- Saving postings list to DIsk. */
    printPostings(postings);
    // indexer.writePostingsToDisk(postings);
    
    // printPostings(postings);
    // cout << "Total Time: " << (time_span1.count() + time_span2.count() + 
    //     time_span3.count() + time_span5.count()) << endl;
}