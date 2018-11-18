#include "list.h"


void list::printTree() {
  vector<vector<string> > components;
  int currentLevel = 1;
  vector<string> temp1;
  temp1.push_back("root");
  components.push_back(temp1);

  recursion(root, components, currentLevel);
  components.pop_back();

  //print
  int maxScreen = 75;
  for(int i=0; i<components.size(); i++) {
    for (int j=0; j<components[i].size(); j++) {
      cout << setw(maxScreen/(components[i].size()+1)) << components[i][j];
    }


    for (int k=0; k<10; k++) {
      cout << endl;
    }
  }

  cout << endl;
  return;
}

void list::recursion(node *temp, vector<vector<string> > &components, int currentLevel) {
  vector <string> child;
  node *childP;

  if (components.size() < (currentLevel+1)) {
    vector<string> temp;
    components.push_back(temp);
  }

  if(!isEmpty(temp)) {
    getChildren(temp, child);

    for (int i=0; i<child.size(); i++) {
      childP = search(child[i]);
      components[currentLevel].push_back(childP->name);
      currentLevel++;
      recursion(childP, components, currentLevel);
      currentLevel--;
    }
  }


  return;
}

void list::getChildren(node *parent, vector<string> &child) {

  node *temp = new node;
  temp = root;
  while (temp != NULL) {
    if (temp->parent == parent) {
      //found child
      child.push_back(temp->name);
    }
    temp=temp->next;
  }
  return;
}

void list::createNode(string name, node *parent, bool isFile) {

  node *temp = new node;
  temp->name = name;
  temp->parent = parent;
  if (isFile) {
    temp->isFile = true;
  } else {
    temp->isFile = false;
  }
  temp->next = NULL;
  if (root==NULL) {
    //root node
    root = temp;
    tail = temp;
    temp->parent = NULL;
    temp = NULL;
  } else {
    tail->next=temp;
    tail=temp;
  }
}

void list::moveNode(string name, string dir) {

  node *temp = new node;
  node *newParent;
  temp = root;
  while (temp != NULL) {
    if (temp->name == name) {

      newParent = search(dir);
      temp->parent = newParent;
      return;
    }
    temp=temp->next;
  }
  cout << "ERROR: Directory " << dir << " doesn't exist." << endl;
  return;
}

void list::display(node *parent) {

    node *temp = new node;
    temp = root;
    while (temp != NULL) {
      if (temp->parent == parent) {
        cout << temp->name << "\t";
      }
      temp=temp->next;
    }
    cout << endl;
    return;
}

void list::removeNode(string name) {
  node *temp = new node;
  int pos = 1;
  bool done = false;
  string childName;
  temp = root;

  while (temp != NULL) {

    if (temp->name == name) {
      //will the address of temp change?
      while (!isEmpty(temp)) {
          //recursion
          childName = getChild(temp);
          cout << temp->name << endl;
          cout << childName << endl;
          string dummy;
          cin >> dummy; cin.ignore();
          removeNode(childName);
      }
        node *current = new node;
        node *previous = new node;
        current = root;
        for (int i=1; i < pos; i++) {
          previous = current;
          current = current->next;
        }
        previous->next=current->next;
        return;
    }
    temp=temp->next;
    pos++;
  }
  cout << "ERROR: Directory/File " << name << " doesn't exist." << endl;
  return;
}

string list::getChild(node *parent) {

  node *temp = new node;
  temp = root;
  while (temp != NULL) {
    if (temp->parent == parent) {
      //found child
      return temp->name;
    }
    temp=temp->next;
  }
  return "empty";
}

bool list::isEmpty(node *parent) {
  node *temp = new node;
  temp = root;
  while (temp != NULL) {
    if (temp->parent == parent) {
      //found child
      return false;
    }
    temp=temp->next;
  }
  return true;
}

node* list::search(string name) {

  node *temp = new node;
  temp = root;
  while (temp != NULL) {
    if (temp->name == name) {
      return temp;
    }
    temp=temp->next;
  }
  return NULL;
}

bool list::isFile(string name) {
  node *temp = new node;
  temp = root;
  while (temp != NULL) {
    if (temp->name == name) {
      if (temp->isFile) {
        return true;
      } else {
        return false;
      }
    }
    temp=temp->next;
  }
}

bool list::checkExists(string name) {
  node *temp = new node;
  temp = root;
  while (temp != NULL) {
    if (temp->name == name) {
      return true;
    }
    temp=temp->next;
  }
  return false;
}
