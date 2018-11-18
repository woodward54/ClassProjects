#include <iostream>
#include <string>
using namespace std;

class animal {

protected:
  int weight;
  string name, gender, color;

public:
  animal() {weight = 0; name = "blank"; gender = "blank"; color = "blank";}
  animal(int _weight, string _name, string _gender, string _color) {weight = _weight; name = _name; gender = _gender; color = _color;}
  virtual void printInfo();

  //accessors and mutators
  void setWeight(int _weight) {weight = _weight;}
  int getWeight() {return weight;}
  void setName(string _name) {name = _name;}
  string getName() {return name;}
  void setGender(string _gender) {gender = _gender;}
  string getGender() {return gender;}
  void setColor(string _color) {color = _color;}
  string getColor() {return color;}

};
