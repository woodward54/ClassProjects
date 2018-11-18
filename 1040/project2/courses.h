class courses {
private:



public:
  int course_cap;
  course *course_list;
  int course_cnt;
  courses();
  ~courses();
  void addCourse();
  void printCourses();
};
