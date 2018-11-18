/*

Code by   : David Woodward
Assignment: exam2, problem 15
Date      : 03/09/2018

*/
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#include "student.h"
#define CHUNKSIZE 2

int main() {
  int userChoice = 0;
  int student_cnt = 0;
  int student_cap = 0;
  student *student_list = new student[CHUNKSIZE];

  while (userChoice != 3) {
    cout << "Menu:" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Print Student Info" << endl;
    cout << "3. Quit" << endl;
    cout << "Selection> ";
    cin >> userChoice; cin.ignore();

    if (userChoice == 1) {
      string temp;
      int id;
      float gpa;
      string name;
      string gender;
      string race;
      string major;
      string minor;
      //allocate new memory
      if (student_cnt == student_cap){
        cout << "INFO: New Student Chunk Created" << endl;
        student *temp;
        temp = new student[student_cap + CHUNKSIZE];
        for (int i=0; i<student_cap; i++) temp[i] = student_list[i];
        delete[] student_list;
        student_cap += CHUNKSIZE;
        student_list = temp;
      }

     cout << endl;
     cout << "Name   : ";
     getline(cin, name);
     student_list[student_cnt].setName(name);
     cout << "ID     : ";
     cin >> id; cin.ignore();
     student_list[student_cnt].setId(id);
     cout << "Gender : ";
     getline(cin, gender);
     student_list[student_cnt].setGender(gender);
     cout << "Race   : ";
     getline(cin, race);
     student_list[student_cnt].setRace(race);
     cout << "Major  : ";
     getline(cin, major);
     student_list[student_cnt].setMajor(major);
     cout << "Minor  : ";
     getline(cin, minor);
     student_list[student_cnt].setMinor(minor);
     cout << "GPA    : ";
     cin >> gpa;
     student_list[student_cnt].setGpa(gpa);


     student_cnt++;
   } else if (userChoice == 2) {
     int printChoice;
     //print all students
     for (int i=0; i < student_cnt; i++) {
       cout << i+1 << ". " << student_list[i].getName() << endl;
     }
     cout << "Selection> ";
     cin >> printChoice;
     student_list[printChoice-1].printInfo();

   } else if (userChoice == 3) {
     break;
   } else {
     cout << "ERROR: Invalid choice." << endl;
   }

  }

  cout << "INFO: Memory freed." << endl;
  delete[] student_list;
  return 0;
}
