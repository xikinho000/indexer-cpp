#include <algorithm>
#include <iostream>
#include <string>
#include "stem.c"
#include "Common.cpp"
#include "../headers/Indexer.h"

using namespace std;

void 
Indexer::startRemovePunctuation(map<string, FileContent> &TestCollection)
{
    Common common;
    for(const auto& sm_pair : TestCollection){
        FileContent fc = sm_pair.second;
        string author = fc.getAuthor(),
               title  = fc.getTitle(),
               text   = fc.getText(),
               biblio = fc.getBiblio();
        
        common.removePunctuations( author, " " );
        common.removePunctuations( title , " " );
        common.removePunctuations( text  , " " );
        common.removePunctuations( biblio, " " );
        
        fc.setAuthor( author );
        fc.setTitle ( title  );
        fc.setBiblio( biblio );
        fc.setText  ( text   );
        TestCollection[sm_pair.first] = fc;
    }
}

void
Indexer::removeStopwords(map<string, FileContent> &TestCollection)
{
    Common common;
    string newAuthor, newTitle, newBiblio, newText;
    size_t pos = 0;
    string delimiter = " ";
    string token;
    set<string> stopwords;
    vector<string> contents;
    common.loadStopWords(stopwords);
    for(const auto sm_pair : TestCollection){
        string fileName = sm_pair.first;
        FileContent fc = sm_pair.second;
        istringstream author(fc.getAuthor());
        istringstream biblio(fc.getBiblio());
        istringstream text(fc.getText());
        istringstream title(fc.getTitle());

        string word, tempAuthor, tempBiblio, tempText, tempTitle;
        while(author >> word){
            set<string>::iterator it = stopwords.find(word);
            if(it == stopwords.end())
                tempAuthor += word + " ";
        }
        while(biblio >> word){
            set<string>::iterator it = stopwords.find(word);
            if(it == stopwords.end())
                tempBiblio += word + " ";
        }
        while(text >> word){
            set<string>::iterator it = stopwords.find(word);
            if(it == stopwords.end())
                tempText += word + " ";
        }
        while(title >> word){
            set<string>::iterator it = stopwords.find(word);
            if(it == stopwords.end())
                tempTitle += word + " ";
        }
        
        fc.setAuthor(tempAuthor);
        fc.setTitle(tempTitle);
        fc.setText(tempText);
        fc.setBiblio(tempBiblio);

        TestCollection[sm_pair.first] = fc;
    }
}

/*
 * map< string, map<string, int> > = Term(a), (Doc(x) -> TF(y))
*/
void
Indexer::setTermFrequency(map<string,FileContent> const &collection,
                          set<string> const &dictionary,
                          map<string, map<string,int>> &postings
){
    for(set<string>::iterator term = dictionary.begin(); term != dictionary.end(); term++){
        map<string,int> postingList;
        for(const auto data : collection){
            int tf = 0;
            string docName = data.first;
            FileContent fc = data.second;
            string author = fc.getAuthor();
            string biblio = fc.getBiblio();
            string text   = fc.getText();
            string title  = fc.getTitle();

            tf  = countTermOccurences(author, *term);
            tf += countTermOccurences(biblio, *term);
            tf += countTermOccurences(text,   *term);
            tf += countTermOccurences(title,  *term);
            if(tf>0)
                postingList.insert(pair<string,int>(docName, tf));
        }
        postings[*term] = postingList;
    }
}

void
Indexer::stemWords(map<string, FileContent> &TestCollection)
{
    Common common;
    for(const auto collection : TestCollection){
        string docName = collection.first;
        FileContent fc = collection.second;
        string author = fc.getAuthor();
        string biblio = fc.getBiblio();
        string text   = fc.getText();
        string title  = fc.getTitle();
        /* Should we really stem the author, biblio and title? */
        if(!author.empty())
            fc.setAuthor(common.SplitToStem(author, " "));
        
        if(!biblio.empty()) 
            fc.setBiblio(common.SplitToStem(biblio, " "));
        
        if(!text.empty()) 
            fc.setText(common.SplitToStem(text, " "));

        if(!title.empty())  
            fc.setTitle(common.SplitToStem(title, " "));

        TestCollection[collection.first] = fc;
    }
}

void 
Indexer::loadCollection(map<string, FileContent> &mapCollection)
{
    cout << "[+] Loading Test Collection \n";
    vector<string> files;
    FileManager fileManager;

    fileManager.readDirectory(files);

    for(string _filename : files) {
        if( _filename == "." || _filename == ".." )
            continue;
        else
            fileManager.readDocument( _filename, mapCollection );
    }
}

void 
Indexer::createDictionary(set<string> &dictionary, 
    map<string, FileContent> &TestCollection)
{
    Common common;
    for(const auto data : TestCollection){
        int tf = 0;
        string docName = data.first;
        FileContent fc = data.second;
        string author = fc.getAuthor();
        string biblio = fc.getBiblio();
        string text   = fc.getText();
        string title  = fc.getTitle();

        addToDictionary(author, dictionary);
        addToDictionary(biblio, dictionary);
        addToDictionary(text, dictionary);
        addToDictionary(title, dictionary);
        
    }
}

void
Indexer::addToDictionary(string content, set<string> &dictionary)
{
    string delimiter = " ";
    auto start = 0U;
    auto end = content.find(" ");
    while (end != std::string::npos){
        string term = content.substr(start, end - start);
        dictionary.insert(term);
        start = end + delimiter.length();
        end = content.find(delimiter, start);
    }
}