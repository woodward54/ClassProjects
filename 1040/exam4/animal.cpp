#include "animal.h"

#include <iostream>
#include <string>
using namespace std;

void animal::printInfo() {
  cout << "Name     : " << name << endl;
  cout << "Gender   : " << gender << endl;
  cout << "Weight   : " << weight << endl;
  cout << "Color    : " << color << endl;
  return;
}
