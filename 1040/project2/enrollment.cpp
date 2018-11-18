#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#include "global.h"
#include "student.h"
#include "students.h"
#include "course.h"
#include "courses.h"
#include "enrollment.h"
#include "enrollments.h"

//constructor
enrollment::enrollment() {
  id = -1;
  studentId = -1;
  courseId = -1;
  for (int i=0; i < 10; i++) {
    grades[i] = -1;
  }
  studentAvg = -1;
  letterGrade = "z";
  return;
}

//destructor
