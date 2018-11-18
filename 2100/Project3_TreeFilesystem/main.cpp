#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "list.h"

void mkdir(string name, node *currentDir);
void mkfile(string name, node *currentDir);
void mv(string name, string name2, node *currentDir);
void rm(string name, node *currentDir);
void cd(string name, node *&currentDir);
void ls(node *currentDir);

list fileSystem;

int main() {

  string file, s, el, del = " ";
  size_t pos=0;
  vector<string> words;
  node *currentDir; //cd will update this variable

  //create root node
  fileSystem.createNode("root", NULL, false);
  currentDir = fileSystem.getRoot();

  //parse file
   cout << "Enter file name: ";
   cin >> file; cin.ignore();
   ifstream fin;
   fin.open(file.c_str());

   while (!fin.eof()) {
     getline(fin, s);

     if (s.size() < 2) {
       break;
     }

     s += " ";
     while ((pos = s.find(del)) != string::npos) {
      	el = s.substr(0, pos);
      	words.push_back(el);
      	s.erase(0, pos + del.length());
     }
     if (words.size() == 1) {
    	 words.push_back("empty");
    	 words.push_back("empty");
     } else if (words.size() == 2) {
  	   words.push_back("empty");
    }



     //BUGFIX remove \r
     for (int i=0; i<3; i++) {
       if (words[i][words[i].size() - 1] == '\r') {
         words[i].erase(words[i].size() - 1);
       }
     }

     //excute functions
     if (words[0] == "mkdir") {
       mkdir(words[1], currentDir);
     } else if (words[0] == "mkfile") {
       mkfile(words[1], currentDir);
     } else if (words[0] == "mv") {
       mv(words[1], words[2], currentDir);
     } else if (words[0] == "rm") {
       rm(words[1], currentDir);
     } else if (words[0] == "cd") {
       cd(words[1], currentDir);
     } else if (words[0] == "ls") {
       ls(currentDir);
     } else {
       cout << "ERROR: Command " << words[0] << " not found." << endl;
     }
     words.clear();
   }
   fileSystem.printTree();
  return 0;
}


void mkdir(string name, node *currentDir) {

  if (fileSystem.checkExists(name)) {
    cout << "ERROR: Directory " << name << " already exists." << endl;
  } else {
    fileSystem.createNode(name, currentDir, false);
  }

  return;
}

void mkfile(string name, node *currentDir) {

  if (fileSystem.checkExists(name)) {
    cout << "ERROR: File " << name << " already exists." << endl;
  } else {
    fileSystem.createNode(name, currentDir, true);
  }

  return;
}

void mv(string name, string name2, node *currentDir) {

  fileSystem.moveNode(name, name2);
  return;
}

void rm(string name, node *currentDir) {

  fileSystem.removeNode(name);
  return;
}

void cd(string name, node *&currentDir) {

  if (!fileSystem.checkExists(name)) {
    cout << "ERROR: Directory " << name << " doesn't exist." << endl;
  } else if (fileSystem.isFile(name)) {
    cout << "ERROR: " << name << " is a file." << endl;
  } else {
    currentDir = fileSystem.search(name);
  }
  return;
}

void ls(node *currentDir) {
  fileSystem.display(currentDir);
  return;
}
