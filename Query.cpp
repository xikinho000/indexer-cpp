/**
 * @file Query.cpp
 * @author Kamel Assaf kamelassaf1@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Kamel Assaf (c) 1998 - 2022
 */
#include <iostream>
#include <string>
#include <map>

#include "../headers/Common.h"
#include "../headers/Query.h"

void Query::loadQueries(map<int, string> &queries)
{
    string path = "queries/Queries.txt";
    ifstream fileReader( path );
    int queryCounter = 0;
    string query = "";
    if( fileReader.is_open() ){
        while( getline(fileReader, query) )
            queries.insert( make_pair( ++queryCounter, query ) );
    }
    fileReader.close();
}

void Query::createQuerySet(map<int,string> &queries, map<int,set<string>> &queriesSet)
{
    for( auto& query : queries) {
        int pos = 0;
        string delimiter = " ";
        set<string> querySet;
        string q = query.second;
        while( ( pos = q.find(delimiter) ) != string::npos ) {
            string queryToken = q.substr(0, pos);
            querySet.insert(queryToken);
            q.erase(0, pos + delimiter.length());
        }
        queriesSet[query.first] = querySet;
    }
}

void Query::beginRemovePunctations(map<int, string> &queries)
{
    Common common;
    for(auto & query : queries) {
        common.removePunctuations(query.second, "");
        queries[query.first] = query.second;
    }
}

void Query::removeStopwords(map<int, string> &queries)
{
    Common common;
    set<string> stopwords;
    common.loadStopWords(stopwords);
    
    for( auto& query : queries ) {
        int pos = 0;
        int queryIndex = query.first;
        string delimiter = " ", q = query.second, newQuery = "";
        while( ( pos = q.find( delimiter ) ) != string::npos ) {
            string queryToken = q.substr( 0, pos );
            set<string>::iterator it = stopwords.find(queryToken);
            if( it == end(stopwords) )
                newQuery += " " + queryToken;
                
            q.erase(0, pos+delimiter.length());
        }
        queries[ queryIndex ] = newQuery;
    }
}

void Query::startExecuteQueries(map<int,set<string>> &queriesSet,
    map< string, map<string, int> > &postings,
    int numberOfDocs, int a)
{
    for( const auto & q : queriesSet ) {
        int queryIndex = q.first;
        cout << "Query[" << queryIndex << "]";
        set<string> qSet = q.second;
        set<string>::iterator it;
        for( it = begin(qSet); it != end(qSet); ++it ) {
            string qToken = *it;
            cout << qToken << " ";
        }
        cout << endl;
    }
}