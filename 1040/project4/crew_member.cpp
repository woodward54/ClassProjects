#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

#include "crew_member.h"


void crew_member::printInfo() {
  cout << "Name     : " << name << endl;
  cout << "Id       : " << id << endl;
  cout << "Status   : " << status << endl;
  return;
}
