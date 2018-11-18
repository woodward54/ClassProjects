#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#include "global.h"
#include "student.h"
#include "students.h"

//constructor
students::students() {
  student_cnt = 0;
  student_cap = CHUNKSIZE;
  student_list = new student[CHUNKSIZE];
  return;
}

//destructor
students::~students() {
  cout << "INFO: Students memory freed" << endl;
  cout << endl;
  cout << endl;
  delete[] student_list;
  return;
}

//add student object
void students::addStudent() {
  string temp;
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
  cout << "Student First Name: ";
  cin >> student_list[student_cnt].firstName; cin.ignore();
  cout << "Student Last Name: ";
  cin >> student_list[student_cnt].lastName; cin.ignore();
  cout << "Student classification (1-5): ";
  cin >> student_list[student_cnt].classification; cin.ignore();
  cout << endl;

  student_list[student_cnt].id = student_cnt+1;
  student_cnt += 1;
  return;
}

void students::printStudents() {
  cout << endl;
  cout << "Students:" << endl;
  cout << left;
  for (int i=0; i < student_cnt; i++) {
    cout << student_list[i].id << ". " << setw(10) << student_list[i].firstName << " " << setw(10) << student_list[i].lastName << " " << setw(2) << student_list[i].classification << endl;
  }
  cout << endl;
  return;
}
