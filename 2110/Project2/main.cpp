#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "items.h"

items P("Potions"), I("Ingredients");                //items manager class

void parse();
void parsePotions(vector<string> &elV, int &pKeyP);
void parseIngredients(vector<string> &elV, int &iKeyP);

int main() {

  cout << left;
  parse();

  return 0;
}

void parse() {
  string file, s, el, com, vec, typ, del = " ";
  vector<string> elV, items, proC;
  int iKeyP, pKeyP;
  size_t pos = 0;
//  vector<string> items;

  //get main parse file
  cout << "Enter input file: ";
  cin >> file; cin.ignore();
  ifstream fin;
  fin.open(file.c_str());

    del = " ";
    for (int i = 0; i < 2; i++) {                     //get first two lines of input text
      getline(fin, s);
      s += " ";
      while ((pos = s.find(del)) != string::npos) {   //save two strings of line into vector to read later
        el = s.substr(0, pos);
        elV.push_back(el);
        s.erase(0, pos + del.length());
      }
      if (elV[1] == "potions") {                      //if second word is potions go to potions parse function
        parsePotions(elV, pKeyP);                     // pass parse function string of what text file to open
      }                                               //if not go to ingredients parse function
      else parseIngredients(elV, iKeyP);

      elV.clear();                                    //clear vector for second line
    }
    getline(fin, s);                                  //get empty line and move on with life
  while (!fin.eof()) {                                //while loop for all remaining lines
    string proj;
    getline(fin, s);                                  //read in line
    if (s.length() < 3) break;                        //fix seg fault bug
    del = "(";
    pos = s.find(del);
    com = s.substr(0, pos);                           //extract querie string
    s.erase(0, pos + del.length() + 1);               //erase what i've saved
    if (com == "PROJECT") {                           //if querie was project erase extra querie select
      proj = com;
      del = "(";
      pos = s.find(del);
      com = s.substr(0, pos);
      s.erase(0, pos + del.length() + 1);
      com = proj;
    }
    del = ")";
    pos = s.find(del);
    vec = s.substr(0, pos);                           //extract tuple string
    s.erase(0, pos + del.length() + 1);               //erase what i've saved
    pos = s.find(del);
    typ = s.substr(0, pos);                           //extract string of table
        vec += "|";
    pos = 0;
    del = "|";
    while ((pos = vec.find(del)) != string::npos) {   //save each part of tuple into string vector
      el = vec.substr(0, pos);
      items.push_back(el);
      vec.erase(0, pos + del.length());
    }

    if (com == "INSERT") {                            //if insert query call insert function
      if (typ == "ingredients") I.insert(items, items[iKeyP]);
      else P.insert(items, items[pKeyP]);
    }
    else if (com == "UPDATE") {                       //if update query call update function
      if (typ == "ingredients") I.update(items, items[iKeyP]);
      else P.update(items, items[pKeyP]);
    }
    else if (com == "DELETE") {                       //if delete query call delete function
      if (typ == "ingredients") I.delete_(items);
      else P.delete_(items);
    }
    else if (com == "SELECT") {                       //if select query call select function
      if (typ == "ingredients") I.select(items);
      else P.select(items);
    }
    else if (com == "DISPLAY") {                      //if display query call display function
      I.display();
      P.display();
    }
    else if (com == "WRITE") {                        //if write query call write function
      I.write(iKeyP, "i");
      P.write(pKeyP, "p");
    }
    else if (com == "PROJECT") {                      //if project query call project function after more steps
      del = ")";
      pos = s.find(del);
      s.erase(0, pos + del.length() + 1);             //project query has more info so erase what we already saved
      pos = s.find(del);
      vec = s.substr(0, pos);                         //extract list of columns
      vec += "|";
      pos = 0;
      del = "|";
      while ((pos = vec.find(del)) != string::npos) { //save list of columns into vector
        el = vec.substr(0, pos);
        proC.push_back(el);
        vec.erase(0, pos + del.length());
      }
      if (typ == "ingredients") I.project(items, proC);//finally call project function depending on table type
      else P.project(items, proC);
      proC.clear();                                   //clear vector for next line
    }
    else cout << "ERROR: Incorrect command" << endl;  //if query doesn't match error
    items.clear();                                    //clear vector for next line
  }
  return;
}

void parsePotions(vector<string> &elV, int &pKeyP) {
  string file, s, el, key, del = ",";
  size_t pos = 0;
  vector<string> items;
  file = elV[0];
  ifstream fin;
  fin.open(file.c_str());
  getline(fin, s);
  key = s;                                            //save key as string
  getline(fin, s);
  s += ",";
  while ((pos = s.find(del)) != string::npos) {       //save table scheme
    el = s.substr(0, pos);
    items.push_back(el);
    s.erase(0, pos + del.length());
  }
  for (int i = 0; i < items.size(); i++) {            //find key pos in scheme
    if (key == items[i]) pKeyP = i;
  }
  P.insert(items, "LABEL");                           //insert table scheme into table
  items.clear();
  del = "|";
  while (!fin.eof()) {                                //remainder lines get all attributes
    getline(fin, s);
    if (s.length() < 3) break;
    s += "|";
    while ((pos = s.find(del)) != string::npos) {
      el = s.substr(0, pos);
      items.push_back(el);
      s.erase(0, pos + del.length());
    }
    P.insert(items, items[pKeyP]);
    items.clear();
  }

  return;
}

void parseIngredients(vector<string> &elV, int &iKeyP) {

  string file, s, el, key, del = ",";
  size_t pos = 0;
  vector<string> items;
  file = elV[0];
  ifstream fin;
  fin.open(file.c_str());
  getline(fin, s);
  key = s;                                            //save key as string
  getline(fin, s);
  s += ",";
  while ((pos = s.find(del)) != string::npos) {       //save table scheme
    el = s.substr(0, pos);
    items.push_back(el);
    s.erase(0, pos + del.length());
  }
  for (int i = 0; i < items.size(); i++) {            //find key pos in scheme
    if (key == items[i]) iKeyP = i;
  }
  I.insert(items, "LABEL");                           //insert table scheme into table
  items.clear();
  del = "|";
  while (!fin.eof()) {                                //remainder lines get all attributes
    getline(fin, s);
    if (s.length() < 3) break;
    s += "|";
    while ((pos = s.find(del)) != string::npos) {
      el = s.substr(0, pos);
      items.push_back(el);
      s.erase(0, pos + del.length());
    }
    I.insert(items, items[iKeyP]);
    items.clear();
  }
  return;
}
