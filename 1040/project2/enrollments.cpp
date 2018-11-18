#include <string>
#include <iostream>
#include <fstream>
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
enrollments::enrollments() {
  enrollment_cnt = 0;
  enrollment_cap = CHUNKSIZE;
  enrollment_list = new enrollment[CHUNKSIZE];
  return;
}

//destructor
enrollments::~enrollments() {
  cout << "INFO: enrollments memory freed" << endl;
  delete[] enrollment_list;
  return;
}

//add enrollment object
void enrollments::addStudentToSection(students* studentss, courses* coursess) {
  string temp;
  int studentSelection;
  int courseSelection;

  //allocate new memory
  if (enrollment_cnt == enrollment_cap){
    cout << "INFO: New Enrollment Chunk Created" << endl;
    enrollment *temp;
    temp = new enrollment[enrollment_cap + CHUNKSIZE];
    for (int i=0; i<enrollment_cap; i++) temp[i] = enrollment_list[i];
    delete[] enrollment_list;
    enrollment_cap += CHUNKSIZE;
    enrollment_list = temp;
  }

  //get info from user -- TODO input validation
  studentss->printStudents();
  cout << "Select a student (use a number)> ";
  cin >> studentSelection; cin.ignore();

  if (studentss->student_list[studentSelection-1].numOfCourses > 4)
    cout << "ERROR: Student is already in 5 classes." << endl;
  else {

    coursess->printCourses();
    cout << "Select a course (use a number)> ";
    cin >> courseSelection; cin.ignore();

    if (coursess->course_list[courseSelection-1].numOfStudents > 47)
      cout << "ERROR: Course is full." << endl;
    else {


      //place student in course/enrollment object
      enrollment_list[enrollment_cnt].id = enrollment_cnt;
      enrollment_list[enrollment_cnt].studentId = studentss->student_list[studentSelection-1].id;
      enrollment_list[enrollment_cnt].courseId = coursess->course_list[courseSelection-1].id;
      enrollment_cnt += 1;
      coursess->course_list[courseSelection-1].numOfStudents++;
      studentss->student_list[studentSelection-1].numOfCourses++;
    }
  }
  return;
}

int enrollments::printStudentsInCourse(students* s, courses* c) {
  int courseSelection, studentId;

  c->printCourses();
  cout << "Select a course (use a number)> ";
  cin >> courseSelection; cin.ignore();

  for (int i=0; i < enrollment_cnt; i++) {
    if (enrollment_list[i].courseId == courseSelection) {

        for (int j=0; j < s->student_cnt; j++) {
          if (s->student_list[j].id == enrollment_list[i].studentId) {
            cout << s->student_list[j].id << ". " << setw(10) << s->student_list[j].firstName << " " << setw(10) << s->student_list[j].lastName << endl;
          }
        }
    }
  }
  cout << endl;
  return courseSelection;
}

void enrollments::addGrades(students* s, courses* c) {
  int input, courseId, studentId, enrollmentId, i=0;
  float num=0.00, average=-1.00, total=0.00;

  courseId = printStudentsInCourse(s, c);
  cout << endl;
  cout << "Select a Student to add grades (use a number)> ";
  cin >> studentId;

  for (int j=0; j < enrollment_cnt; j++) {
    if (enrollment_list[j].studentId == studentId) {
      enrollmentId = enrollment_list[j].id;
    }
  }


  cout << "Student: " << s->student_list[studentId-1].id << ". " << setw(10) << s->student_list[studentId-1].firstName << " " << setw(10) << s->student_list[studentId-1].lastName << endl;
  cout << "Class: " << c->course_list[courseId-1].name << endl;
  cout << endl;
  cout << "Enter up to 10 grades. Enter -1 to stop." << endl;
  while (input != -1 && i < 10){
    cout << "Grade " << i+1 << "> ";
    cin >> input; cin.ignore();
    enrollment_list[enrollmentId].grades[i] = input;
    i++;
  }
  for (int k=0; k<10; k++) {
    if (enrollment_list[enrollmentId].grades[k] != -1) {
      total += enrollment_list[enrollmentId].grades[k];
      num += 1.00;
    }
  }

  enrollment_list[enrollmentId].studentAvg = total / num;
  average = enrollment_list[enrollmentId].studentAvg;

  if (average < 59.49)
    enrollment_list[enrollmentId].letterGrade = "F";
  else if (average > 59.50 && average < 69.49)
    enrollment_list[enrollmentId].letterGrade = "D";
  else if (average > 69.50 && average < 79.49)
    enrollment_list[enrollmentId].letterGrade = "C";
  else if (average > 79.50 && average < 89.49)
    enrollment_list[enrollmentId].letterGrade = "B";
  else
    enrollment_list[enrollmentId].letterGrade = "A";
  return;
}

void enrollments::printGrades(students* s, courses* c) {
  int courseId, studentId;

  courseId = printStudentsInCourse(s, c);
  cout << "Select a Student to add grades (use a number)> ";
  cin >> studentId;

  cout << "Student: " << s->student_list[studentId-1].id << ". " << setw(10) << s->student_list[studentId-1].firstName << " " << setw(10) << s->student_list[studentId-1].lastName << endl;
  cout << "Class: " << c->course_list[courseId-1].name << endl;
  cout << "Grades: ";

  for (int j=0; j < enrollment_cnt; j++) {
    if (enrollment_list[j].studentId == studentId && enrollment_list[j].courseId == courseId) {
      for (int k=0; k < 10; k++){
        cout << enrollment_list[j].grades[k] << " ";
      }
    }
  }

  cout << endl;
  cout << endl;
  return;
}

void enrollments::studentAverage(students* s, courses* c) {
  int studentId, enrollmentId, courseId;

  courseId = printStudentsInCourse(s, c);
  cout << endl;
  cout << "Select a Student to add grades (use a number)> ";
  cin >> studentId;

  for (int j=0; j < enrollment_cnt; j++) {
    if (enrollment_list[j].studentId == studentId && enrollment_list[j].courseId == courseId) {
      enrollmentId = enrollment_list[j].id;
    }
  }

  cout << fixed;
  cout << "Average      : " << setprecision(2) << enrollment_list[enrollmentId].studentAvg << endl;
  cout << "Letter Grade : " << enrollment_list[enrollmentId].letterGrade << endl;
  cout << endl;
}

void enrollments::courseAverage(students* s, courses* c) {
  int courseSelection, enrollmentId;
  float num=0.00, total=0.00;

  c->printCourses();
  cout << "Select a course (use a number)> ";
  cin >> courseSelection; cin.ignore();

  for (int i=0; i < enrollment_cnt; i++) {
    if (enrollment_list[i].courseId == courseSelection) {
      total += enrollment_list[i].studentAvg;
      num += 1.00;
    }
  }
  c->course_list[courseSelection-1].courseAvg = total / num;

  cout << fixed;
  cout << "Average: " << setprecision(2) << c->course_list[courseSelection-1].courseAvg << endl;
  cout << endl;
  return;
}

void enrollments::store(students* s, courses* c) {
  string fileNameString;

  cout << "What would you like to name the file? (one word)> ";
  cin >> fileNameString; cin.ignore();

  ofstream outFile;
  outFile.open(fileNameString.c_str());

  outFile << "Students: " << s->student_cnt << endl;
  outFile << left;
  for (int i=0; i < s->student_cnt; i++)
    outFile << s->student_list[i].id << ". " << setw(10) << s->student_list[i].firstName << " " << setw(10) << s->student_list[i].lastName << " " << setw(2) << s->student_list[i].classification << endl;

  outFile << "Courses: " << c->course_cnt << endl;
  outFile << left;
  for (int i=0; i < c->course_cnt; i++)
    outFile << c->course_list[i].id << ". " << setw(10) << c->course_list[i].name << " " << setw(10) << c->course_list[i].location << " " << setw(10) << c->course_list[i].time <<endl;

  outFile << "Enrollment: " << enrollment_cnt << endl;
  for (int i=0; i<enrollment_cnt; i++){
    outFile << enrollment_list[i].id << ". " << enrollment_list[i].studentId << " " << enrollment_list[i].courseId << " ";
    for (int j=0; j < 10; j++)
      outFile << enrollment_list[i].grades[j] << " ";
    outFile << enrollment_list[i].studentAvg << " " << enrollment_list[i].letterGrade << endl;
  }
  outFile.close();
  return;
}

void enrollments::load(students* s, courses* c) {
  string fileNameString, tempString, temp, dot;
  int num;
  ifstream inFile;
  cout << "Enter the file name (one word)> ";
  cin >> fileNameString;


  //check for error
  inFile.open(fileNameString.c_str());
  if (inFile.fail())
    cerr << "ERROR: File open failure" << endl;

  inFile >> tempString;
  inFile >> num;
  cout << tempString << endl;
  cout << "Num of Students: " << num << endl;

    for(int i=0; i < num; i++) {
      //STUDENTS
      //allocate new memory
      if (s->student_cnt == s->student_cap){
        student *temp;
        temp = new student[s->student_cap + CHUNKSIZE];
        for (int j=0; j<s->student_cap; j++) temp[j] = s->student_list[j];
        delete[] s->student_list;
        s->student_cap += CHUNKSIZE;
        s->student_list = temp;
      }

      inFile >> s->student_list[s->student_cnt].id;
      inFile >> dot;
      inFile >> s->student_list[s->student_cnt].firstName;
      inFile >> s->student_list[s->student_cnt].lastName;
      inFile >> s->student_list[s->student_cnt].classification;

      s->student_cnt += 1;
    }

    inFile >> tempString;
    inFile >> num;
    cout << "Num of courses: " << num << endl;
    for (int i=0; i < num; i++){
      //COURSES
      //allocate new memory
      if (c->course_cnt == c->course_cap){
        course *temp;
        temp = new course[c->course_cap + CHUNKSIZE];
        for (int j=0; j<c->course_cap; j++) temp[j] = c->course_list[j];
        delete[] c->course_list;
        c->course_cap += CHUNKSIZE;
        c->course_list = temp;
      }

      inFile >> c->course_list[c->course_cnt].id;
      inFile >> dot;
      inFile >> c->course_list[c->course_cnt].name;
      inFile >> c->course_list[c->course_cnt].location;
      inFile >> c->course_list[c->course_cnt].time;

      c->course_cnt += 1;
    }

    inFile >> tempString;
    inFile >> num;
    cout << "Num of Enrollments: " << num << endl;
    for (int i=0; i < num; i++){
      //ENROLLMENT
      //allocate new memory
      if (enrollment_cnt == enrollment_cap){
        cout << "INFO: New Enrollment Chunk Created" << endl;
        enrollment *temp;
        temp = new enrollment[enrollment_cap + CHUNKSIZE];
        for (int j=0; j<enrollment_cap; j++) temp[j] = enrollment_list[j];
        delete[] enrollment_list;
        enrollment_cap += CHUNKSIZE;
        enrollment_list = temp;
      }

      inFile >> enrollment_list[enrollment_cnt].id;
      inFile >> dot;
      inFile >> enrollment_list[enrollment_cnt].studentId;
      inFile >> enrollment_list[enrollment_cnt].courseId;
      for (int j=0; j < 10; j++) {
        inFile >>  enrollment_list[enrollment_cnt].grades[j];
      }
      inFile >> enrollment_list[enrollment_cnt].studentAvg;
      inFile >> enrollment_list[enrollment_cnt].letterGrade;
      enrollment_cnt += 1;
      //c->course_list[courseSelection-1].numOfStudents++;
      //s->student_list[studentSelection-1].numOfCourses++;
    }
  inFile.close();
  return;
}
