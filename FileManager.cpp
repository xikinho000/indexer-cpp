/**
 * @file FileManager.cpp
 * @author Kamel Assaf (kamelassaf1@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright (c) 2022
 */

#include "../headers/FileContent.h"
#include "../headers/FileManager.h"

using namespace std::chrono;
using namespace std;

void 
FileManager::readDocument(string fileName, map<string, FileContent> &mapCollection)
{
    /**
     * 1 - Read vectors with the collection files.
     * 2 - open each file individually.
     * 3 - populate vector with each file content.
     */
    string contents = "";
    string line = "";
    string filePath = "collection/"+fileName;
    ifstream fileReader(filePath);
    // opening file 
    if(fileReader.is_open()){
        while(getline(fileReader, line)){
            line += " ";
            contents += line;
        }
        FileContent fileContent;
        fileContent.CreateFileContent(contents);
        mapCollection.insert(pair<string,FileContent>(fileName, fileContent));
        // mapCollection.insert(pair<string,string>(fileName, contents)); 
        filePath = "";
        fileReader.close();
    } else {
        cout << "Could not read file" << endl;
        exit(0);
    }
    fileReader.close();
}

void 
FileManager::readDirectory(vector<string> &files){
    DIR *dir;
    struct dirent *dp;

    char cwd[1024];

    getcwd(cwd, sizeof(cwd));

    if((dir  = opendir("collection")) == NULL) {
        perror("\nUnable to open directory.");
        exit(0);
    }
    while ((dp=readdir(dir)) != NULL){
        files.push_back(dp->d_name);
    }
    closedir(dir);
}  