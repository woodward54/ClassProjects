/*
Name:     David Woodward
Email:    davidwoodward@my.unt.edu

*This program is a basic grade book. Use the program to enter students, courses, and then you can assign students to courses and give them grades*

*/

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

#include "global.h"
#include "student.h"
#include "students.h"
#include "course.h"
#include "courses.h"
#include "enrollment.h"
#include "enrollments.h"

int CHUNKSIZE = 2;
students studentss;
courses coursess;
enrollments enrollmentss;

int main() {
  cout << endl;
  cout << endl;
  cout << "Name:       David Woodward" << endl;
  cout << "Class:      CSCE 1040" << endl;
  cout << "Assignment: HW2" << endl;
  cout << "Email:      davidwoodward@my.unt.edu" << endl;

  cout << endl;
  cout << endl;

  int userChoice = 0;
  while (userChoice != 13){
    cout << "1. Add a new course" << endl;
    cout << "2. Add a new student" << endl;
    cout << "3. Add a student to a class" << endl;
    cout << "4. Add grades for a student in a course" << endl;
    cout << "5. Print a list of all grades for a student in a course" << endl;
    cout << "6. Print a list of all students in a course" << endl;
    cout << "7. Compute the average for a student in a course" << endl;
    cout << "8. Print a list of all courses" << endl;
    cout << "9. Print a list of all students" << endl;
    cout << "10. Compute the average for a course" << endl;
    cout << "11. Store Grade book" << endl;
    cout << "12. Load Grade book" << endl;
    cout << "13. quit" << endl;
    cout << endl;
    cout << "Selection> ";
    cin >> userChoice; cin.ignore();

    switch (userChoice){
      case 1: coursess.addCourse(); break; //add a new course
      case 2: studentss.addStudent(); break;
      case 3: enrollmentss.addStudentToSection(&studentss, &coursess); break;
      case 4: enrollmentss.addGrades(&studentss, &coursess); break;
      case 5: enrollmentss.printGrades(&studentss, &coursess); break;
      case 6: enrollmentss.printStudentsInCourse(&studentss, &coursess); break;
      case 7: enrollmentss.studentAverage(&studentss, &coursess); break;
      case 8: coursess.printCourses(); break;
      case 9: studentss.printStudents(); break;
      case 10: enrollmentss.courseAverage(&studentss, &coursess); break;
      case 11: enrollmentss.store(&studentss, &coursess); break;
      case 12: enrollmentss.load(&studentss, &coursess); break;
      case 13: cout << "Quitting..." << endl; break;
      default:
        cout << "ERROR: Invalid choice" << endl;
        cout << endl;
    }
  }

  return 0;
}
