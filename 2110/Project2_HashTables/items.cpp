#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "items.h"

//utility functions
int items::hashF(string key) {
  int pos = 0;
  int mult = 7;
  if (key == "LABEL") {
    pos = 0;
  } else {
    for (int i=0; i < key.length(); i++) {
      char c = key[i];
      pos = (pos*mult) + (int)c;
    }
  }

  return (pos % p.size());
}

void items::updateTableSizes() {
  //initalize columnWidths if it is uninitalised
  if (columnWidths[0] == 0) {
    columnWidths[0] = p[0].data[0].length()+columnSpace;
    for (int i=1; i<p[0].data.size(); i++) {
      //add column
      columnWidths.push_back(p[0].data[i].length()+columnSpace);
    }
  }

  //if data string is longer than exisiting, update new largest length
  for (int i=0; i<columnWidths.size(); i++) {
    for (int d=0; d<p.size(); d++) {
      if (!p[d].data.empty()) {
        if (p[d].data[i].length() > columnWidths[i]) {
          columnWidths[i] = p[d].data[i].length()+columnSpace;
        }
      }
    }
  }
  return;
}

vector<string> items::query(vector<string> query) {
  vector<string> keyVals;
  bool pass;
  //find all elements that match search params
  for (int i=0; i < p.size(); i++) {
    pass = true;
    //search params
    if (!p[i].data.empty()) {
      for (int j=0; j < query.size(); j++) {
        if (query[j] != "*" && p[i].data[j] != query[j]) {
          //incorrect combindation
          pass = false;
        }
      }
      if (pass) {
        //this element is a match
        keyVals.push_back(p[i].key);
      }
    }
  }
  return keyVals;
}

//Hash table functions
bool items::insert(vector<string> data, string key) {
  //get position
  int ogPos = hashF(key);
  int pos = ogPos;

  //linear probing
  int probed = 0;
  while (probed < p.size()) {
    //check for unique key value
    if (p[pos].key == key) {
      cout << "ERROR: (items.cpp) 10: Duplicate key, key: " << key << endl;
      return false;
    }
    if (p[pos].data == emptyVector) {
      //spot is empty, add data
      p[pos].data = data;
      p[pos].key = key;
      updateTableSizes();
      cout << "INFO: Successful insertion. Table: " << tableType << ", Key: "<< setw(10) << key << ", Table Pos: " << pos << endl;
      return true;
    }
    pos = (pos + 1) % p.size();
    probed++;
  }
  cout << "ERROR: (items.cpp) 1: Linear Probing Failed." << endl;
  return false;
}

bool items::update(vector<string> data, string key) {
  int pos = hashF(key);
  //linear probing
  int probed = 0;
  while (probed < p.size()) {
    if (p[pos].key == key) {
      p[pos].data = data;
      updateTableSizes();
      cout << "INFO: Successful update, Key: " << key << endl;
      return true;
    }
    pos = (pos + 1) % p.size();
    probed++;
  }
  cout << "ERROR: (items.cpp) 2: update Failed, No key value found. Key: " << key << endl;
  return false;
}


bool items::delete_(vector<string> query_) {
  //get all matching key values
  vector<string> keyVals = query(query_);
  if (keyVals.size() == 0) {
    cout << "ERROR: (items.cpp) 3: Delete failed, no elements match query." << endl;
    return false;
  }

  for (int k=0; k < keyVals.size(); k++) {
    int pos = hashF(keyVals[k]);
    //linear probing
    int probed = 0;
    while (probed < p.size()) {
      if (p[pos].key == keyVals[k]) {
        cout << "INFO: Successful delete. Table: " << tableType << ", Key: "<< setw(10) << keyVals[k] << endl;
        p[pos].data = emptyVector;
        p[pos].key = "";
        updateTableSizes();
      }
      pos = (pos + 1) % p.size();
      probed++;
    }
  }
  return true;
}

void items::select(vector<string> query_) {
  //get all matching key values
  vector<string> keyVals = query(query_);
  if (keyVals.size() == 0) {
    cout << "ERROR: (items.cpp) 4: Select failed, no elements match query." << endl;
    return;
  }
  for (int k=0; k < keyVals.size(); k++) {
    //get position
    int pos = hashF(keyVals[k]);
    //linear probing
    int probed = 0;
    while (probed < p.size()) {
      if (p[pos].key == keyVals[k]) {
        display(keyVals[k]);
      }
      pos = (pos + 1) % p.size();
      probed++;
    }
  }
  return;
}

void items::display() {
  cout << endl; cout << endl;
  cout << "Table: " << tableType << endl;
  for (int i=0; i<columnWidths.size(); i++) {
    cout << setw(columnWidths[i]) << p[0].data[i];
  }
  cout << endl;
  for (int i=0; i<columnWidths.size(); i++) {
    for (int d=0; d<columnWidths[i]; d++) {
      cout << "-";
    }
  }
  cout << endl;
  for (int j=1; j<p.size(); j++) {
    for (int i=0; i<columnWidths.size(); i++) {
      if (!p[j].data.empty()) {
        cout << setw(columnWidths[i]) << p[j].data[i];
        if (i == columnWidths.size()-1) {
          cout << endl;
        }
      }
    }
  }
  cout << endl; cout << endl;
  return;
}

void items::display(string key) {
  //get position
  int pos = hashF(key);
  //linear probing
  int probed = 0;
  cout << endl; cout << endl;
  cout << "SELECT" << endl;
  cout << "Table: " << tableType << endl;
  cout << "Key: " << key << endl;
  while (probed < p.size()) {
    if (p[pos].key == key) {
      for (int i=0; i<columnWidths.size(); i++) {
        cout << setw(columnWidths[i]) << p[0].data[i];
      }
      cout << endl;
      for (int i=0; i<columnWidths.size(); i++) {
        for (int d=0; d<columnWidths[i]; d++) {
          cout << "-";
        }
      }
      cout << endl;
      for (int i=0; i<columnWidths.size(); i++) {
        if (p[pos].data.empty()) {
          cout << "ERROR: (items.cpp) 6: Key value not found. Key: " << key << endl;
        } else {
          cout << setw(columnWidths[i]) << p[pos].data[i];
        }
      }
      cout << endl; cout << endl;
      return;
    }
    pos = (pos + 1) % p.size();
    probed++;
  }
  cout << "ERROR: (items.cpp) 5: No data at key value to print. Key: " << key << endl;
  return;
}

void items::write(int keyP, string t) {

  ofstream fout;
  if (t == "p") fout.open("potionsWrite.txt");
  else fout.open("ingredientsWrite.txt");
  fout << p[0].data[keyP] << endl;
  fout << p[0].data[0];
  for (int i=1; i<columnWidths.size(); i++) {
    fout << "," << p[0].data[i];
  }
  fout << endl;
  for (int j=1; j<p.size(); j++) {
    if (!p[j].data.empty()) {
      fout << p[j].data[0];
    }
    for (int i=1; i<columnWidths.size(); i++) {
      if (!p[j].data.empty()) {
        fout << "|" << p[j].data[i];
        if (i == columnWidths.size()-1) {
          fout << endl;
        }
      }
    }
  }
  fout.close();
  return;
}

void items::project(vector<string> query_, vector<string> selCol) {
  //vector of the positions of the columns we want
  vector<int> colPos;

  //get all matching key values
  vector<string> keyVals = query(query_);
  if (keyVals.size() == 0) {
    cout << "ERROR: (items.cpp) 4: Project failed, no elements match query." << endl;
    return;
  }

  //get select columns
  for (int i=0; i<selCol.size(); i++) {
    for (int j=0; j<p[0].data.size(); j++) {
      if (p[0].data[j] == selCol[i]) {
        colPos.push_back(j);
      }
    }
  }

  cout << endl; cout << endl;
  cout << "PROJECT" << endl;
  cout << "Table: " << tableType << endl;
  for (int i=0; i<colPos.size(); i++) {
    cout << setw(columnWidths[colPos[i]]) << p[0].data[colPos[i]];
  }
  cout << endl;
  for (int i=0; i<colPos.size(); i++) {
    for (int d=0; d<columnWidths[colPos[i]]; d++) {
      cout << "-";
    }
  }
  cout << endl;
  for (int j=1; j<p.size(); j++) {
    for (int k=0; k<keyVals.size(); k++) {
      for (int i=0; i<colPos.size(); i++) {
        if (!p[j].data.empty() && p[j].key == keyVals[k]) {
          cout << setw(columnWidths[colPos[i]]) << p[j].data[colPos[i]];
          if (i == colPos.size()-1) {
            cout << endl;
          }
        }
      }
    }
  }
  cout << endl; cout << endl;

  return;
}
