#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct node {
  string name;
  bool isFile;
  node *next;
  node *parent;
};

class list {
private:
  node *root, *tail;

public:
  list() {
    root = NULL;
    tail = NULL;
  }
  node* getRoot() {return root;}

  void createNode(string name, node *parent, bool isFile);
  void removeNode(string name);
  void moveNode(string name, string dir);
  void printTree();
  void recursion(node *temp, vector<vector<string> > &components, int currentLevel);
  void getChildren(node *parent, vector<string> &child);
  string getChild(node *parent);
  node* search(string name);
  bool checkExists(string name);
  bool isFile(string name);
  bool isEmpty(node *parent);
  void display(node *parent);
};
