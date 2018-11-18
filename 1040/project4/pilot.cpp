#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;


#include "pilot.h"

void pilot::printInfo() {

  crew_member::printInfo();
  cout << "Type     : Pilot" << endl;
  cout << "Rating   : " << rating << endl;
  cout << "Hours    : " << hours << endl;
  return;
}
