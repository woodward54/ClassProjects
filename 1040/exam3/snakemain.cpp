/*
David Woodward
CSCE 1040
Lab Exam 3
3/30/2018
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

#include "snake.h"

int main() {

  vector <Snake> snake_list(5);

  for (int i=0; i < snake_list.size(); i++) {
    string temp;
    int tempInt;
    cout << endl;
    cout << "SNAKE " << i+1 << endl;

    cout << "Name          : ";
    getline(cin, temp); snake_list[i].setName(temp);
    cout << "Breed         : ";
    getline(cin, temp); snake_list[i].setBreed(temp);
    cout << "Gender        : ";
    getline(cin, temp); snake_list[i].setGender(temp);
    cout << "Favorite Food : ";
    getline(cin, temp); snake_list[i].setFavFood(temp);
    cout << "Color         : ";
    getline(cin, temp); snake_list[i].setColor(temp);
    cout << "comment       : ";
    getline(cin, temp); snake_list[i].setComment(temp);
    cout << "Weight        : ";
    cin >> tempInt; cin.ignore(); snake_list[i].setWeight(tempInt);
    cout << "Length        : ";
    cin >> tempInt; cin.ignore(); snake_list[i].setLength(tempInt);
  }

  cout << endl;
  cout << "Printing..." << endl;
  for (int i=0; i < snake_list.size(); i++) {
    cout << "SNAKE " << i+1 << endl;
    snake_list[i].printInfo();
  }


  return 0;
}
