#ifndef CREW_MEMBER_H
#define CREW_MEMBER_H

//base class
class crew_member {

protected:
  int id;
  string name, status;

public:
  //setters and getters
  void setId(int _id) {id = _id;}
  int getId() {return id;}

  void setName(string _name) {name = _name;}
  string getName() {return name;}
  void setStatus(string _status) {status = _status;}
  string getStatus() {return status;}

  virtual void printInfo();
};

#endif
