#include <iostream>
#include <string>
using namespace std;

#include "cow.h"

void cow::printInfo() {
  animal::printInfo();
  cout << "Breed    : " << breed << endl;
  cout << "Neutered : " << neutered << endl;
  cout << "ID       : " << id << endl;
  cout << "Comments : " << comments << endl;
  return;
}
