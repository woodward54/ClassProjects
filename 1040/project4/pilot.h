#include <iostream>
#include <string>
using namespace std;

#include "crew_member.h"

class pilot : public crew_member {

private:
  string rating;
  int hours;

public:
  //setters and getters
  void setHours(int _hours) {hours = _hours;}
  int getHours() {return hours;}

  void setRating(string _rating) {rating = _rating;}
  string getRating() {return rating;}

  void printInfo();

};
