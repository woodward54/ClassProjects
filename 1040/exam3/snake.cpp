#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

#include "snake.h"

Snake::Snake() {
  breed = "empty";
  name =  "empty";
  gender =  "empty";
  favFood =  "empty";
  color =  "empty";
  comment =  "empty";

  weight = 0;
  length = 0;
}

Snake::Snake(string _breed, string _name, string _gender, string _favFood, string _color, string _comment, int _weight, int _length) {

  breed = _breed;
  name = _name;
  gender = _gender;
  favFood = _favFood;
  color = _color;
  comment = _comment;

  weight = _weight;
  length = _length;
}

void Snake::printInfo() {

 cout << "Name          : " << name << endl;
 cout << "Breed         : " << breed << endl;
 cout << "Gender        : " << gender << endl;
 cout << "Favorite Food : " << favFood << endl;
 cout << "Color         : " << color << endl;
 cout << "comment       : " << comment << endl;
 cout << "Weight        : " << weight << endl;
 cout << "Length        : " << length << endl;

}
