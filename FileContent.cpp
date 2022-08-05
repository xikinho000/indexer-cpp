#include "../headers/FileContent.h"
#include <string>
using namespace std;
// string docNumber, author, biblio, title, text; 
void FileContent::CreateFileContent(string fileContents){
    this->setDocNumber (getStringBetweenDelimeters(fileContents, "<DOCNO>", "</DOCNO>") );
    this->setAuthor( getStringBetweenDelimeters(fileContents, "<AUTHOR>", "</AUTHOR>") );
    this->setBiblio( getStringBetweenDelimeters(fileContents, "<BIBLIO>", "</BIBLIO>") );
    this->setTitle( getStringBetweenDelimeters(fileContents, "<TITLE>", "</TITLE>") );
    this->setText(getStringBetweenDelimeters(fileContents, "<TEXT>", "</TEXT>"));
}
FileContent::FileContent(){}
FileContent::~FileContent(){}

void FileContent::setDocNumber(string docNumber){
    this->docNumber = docNumber;
}
string FileContent::getDocNumber(){
    return this->docNumber;
}

void FileContent::setAuthor(string author){
    this->author = author;
}
string FileContent::getAuthor(){
    return this->author;
}

void FileContent::setBiblio(string biblio){
    this->biblio = biblio;
}
string FileContent::getBiblio(){
    return this->biblio;
}

void FileContent::setTitle(string title){
    this->title = title;
}
string FileContent::getTitle(){
    return this->title;
}

void FileContent::setText(string text){
    this->text = text;
}
string FileContent::getText(){
    return this->text;
}

string FileContent::getStringBetweenDelimeters(const string &s, const string &start_delim, const string &stop_delim)
{
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find(stop_delim);

    return s.substr(end_pos_of_first_delim, last_delim_pos - end_pos_of_first_delim);
}