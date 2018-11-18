#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#include "global.h"
#include "course.h"
#include "courses.h"

//constructor
courses::courses() {
  course_cnt = 0;
  course_cap = CHUNKSIZE;
  course_list = new course[CHUNKSIZE];
  return;
}

//destructor
courses::~courses() {
  cout << "INFO: Courses memory freed" << endl;
  delete[] course_list;
  return;
}

//add course object
void courses::addCourse() {
  string temp;
  //allocate new memory
  if (course_cnt == course_cap){
    cout << "INFO: New Course Chunk Created" << endl;
    course *temp;
    temp = new course[course_cap + CHUNKSIZE];
    for (int i=0; i<course_cap; i++) temp[i] = course_list[i];
    delete[] course_list;
    course_cap += CHUNKSIZE;
    course_list = temp;
  }

  cout << endl;
  cout << "Course Name: ";
  getline(cin, course_list[course_cnt].name);
  cout << "Course Location: ";
  getline(cin, course_list[course_cnt].location);
  cout << "Course Time: ";
  getline(cin, course_list[course_cnt].time);
  cout << endl;

  course_list[course_cnt].id = course_cnt+1;
  course_cnt += 1;
  return;
}

//print courses function
void courses::printCourses() {
  cout << endl;
  cout << "Courses:" << endl;
  cout << left;
  for (int i=0; i < course_cnt; i++) {
    cout << course_list[i].id << ". " << setw(10) << course_list[i].name << " " << setw(10) << course_list[i].location << " " << setw(10) << course_list[i].time <<endl;
  }
  cout << endl;
  return;
}
