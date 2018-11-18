#include <iostream>
#include <string>
#include <vector>
using namespace std;


#include "cow.h"

int main() {
  cout << endl; cout << endl;
  cout << "David Woodward" << endl;
  cout << "11126094" << endl;
  cout << "Exam 4" << endl;
  cout << endl; cout << endl;

  //vector of animal (base class) pointers
  vector <animal*> animal_list;

  //declaring temp as a cow pointer
  cow* temp = 0;

  for (int i=0; i<5; i++) {

    temp = new cow;
    string name, gender, color, breed, neutered, comments, id;
    int weight;

    //get user input
    cout << "Name     : "; getline(cin, name);
    cout << "Gender   : "; getline(cin, gender);
    cout << "Weight   : "; cin >> weight; cin.ignore();
    cout << "Color    : "; getline(cin, color);
    cout << "Breed    : "; getline(cin, breed);
    cout << "Neutered : "; getline(cin, neutered);
    cout << "ID       : "; getline(cin, id);
    cout << "Comments : "; getline(cin, comments);

    temp->setName(name);
    temp->setGender(gender);
    temp->setWeight(weight);
    temp->setColor(color);
    temp->setBreed(breed);
    temp->setNeutered(neutered);
    temp->setId(id);
    temp->setComments(comments);
    animal_list.push_back(temp);
  }
  cout << endl;

  //print all cows
  cout << "Printing " << animal_list.size() << " cows." << endl;
  for (int i=0; i<animal_list.size(); i++) {
    animal_list[i]->printInfo();
  }

  //free allocated memory
  delete temp;

  return 0;
}
