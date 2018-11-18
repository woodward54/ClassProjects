class student {
private:
  int id;
  float gpa;
  string name;
  string gender;
  string race;
  string major;
  string minor;

public:
  student();
  student(int resid, float resgpa, string resname, string resgender, string resrace, string resmajor, string resminor);
  void setId(int resid);
  void setGpa(float resgpa);
  void setName(string resname);
  void setGender(string resgender);
  void setRace(string resrace);
  void setMajor(string resmajor);
  void setMinor(string resminor);

  int getId();
  float getGpa();
  string getName();
  string getGender();
  string getRace();
  string getMajor();
  string getMinor();

  void printInfo();
};
