#include <iostream>
#include <string>
using namespace std;

#include "animal.h"

class cow : public animal {

public:
  //constructors
  cow() {breed = "blank"; neutered = "blank"; id = "blank"; comments = "blank";}
  cow(string _breed, string _neutered, string _id, string _comments) {breed = _breed; neutered = _neutered; id = _id; comments = _comments;}

  //functions
  void printInfo();

  //accessors and mutators
  void setBreed(string _breed) {breed = _breed;}
  string getBreed() {return breed;}
  void setNeutered(string _n) {neutered = _n;}
  string getNeutered() {return neutered;}
  void setId(string _id) {id = _id;}
  string getId() {return id;}
  void setComments(string _comments) {comments = _comments;}
  string getComments() {return comments;}
  
private:
  string breed, neutered, id, comments;



};
