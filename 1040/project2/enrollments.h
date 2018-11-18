class enrollments {
private:
  int enrollment_cnt;
  int enrollment_cap;
  enrollment *enrollment_list;
public:
  enrollments();
  ~enrollments();
  void addStudentToSection(students* studentss, courses* classess);
  int printStudentsInCourse(students* s, courses* c);
  void addGrades(students* s, courses* c);
  void printGrades(students* s, courses* c);
  void studentAverage(students* s, courses* c);
  void courseAverage(students* s, courses* c);
  void store(students* s, courses* c);
  void load(students* s, courses* c);
};
