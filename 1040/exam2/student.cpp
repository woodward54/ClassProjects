#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#include "student.h"

//constructor
student::student() {
  id = 0;
  gpa = 0.00;
  name = "none";
  gender = "none";
  race = "none";
  major = "none";
  minor = "none";
}

//constructor
student::student(int resid, float resgpa, string resname, string resgender, string resrace, string resmajor, string resminor) {
  id = resid;
  gpa = resgpa;
  name = resname;
  gender = resgender;
  race = resrace;
  major = resmajor;
  minor = resminor;
}

//printinfo function
void student::printInfo() {
  cout << endl;
  cout << endl;

  cout << "Name   : " << name << endl;
  cout << "ID     : " << id << endl;
  cout << "Gender : " << gender << endl;
  cout << "Race   : " << race << endl;
  cout << "Major  : " << major << endl;
  cout << "Minor  : " << minor << endl;
  cout << "GPA    : " << fixed <<  setprecision(2) << gpa << endl;

  cout << endl;
  cout << endl;
}

//mutators
void student::setId(int resid) {
  id = resid;
}
void student::setGpa(float resgpa) {
  gpa = resgpa;
}
void student::setName(string resname) {
  name = resname;
}
void student::setGender(string resgender) {
  gender = resgender;
}
void student::setRace(string resrace) {
  race = resrace;
}
void student::setMajor(string resmajor) {
  major = resmajor;
}
void student::setMinor(string resminor) {
  minor = resminor;
}

//accessors
int student::getId() {
  return id;
}
float student::getGpa() {
  return gpa;
}
string student::getName() {
  return name;
}
string student::getGender() {
  return gender;
}
string student::getRace() {
  return race;
}
string student::getMajor() {
  return major;
}
string student::getMinor() {
  return minor;
}
