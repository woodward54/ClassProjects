class Snake {

private:
  string breed, name, gender, favFood, color, comment;
  int weight, length;

public:
  //setters
  void setBreed(string _breed) {breed = _breed; }
  void setName(string _name) {name = _name; }
  void setGender(string _gender) {gender = _gender; }
  void setFavFood(string _favFood) {favFood = _favFood; }
  void setColor(string _color) {color = _color; }
  void setComment(string _comment) {comment = _comment; }
  void setWeight(int _weight) {weight = _weight; }
  void setLength(int _length) {length = _length; }

  //getters
  string getBreed() {return breed; }
  string getName() {return name; }
  string getGender() {return gender; }
  string getFavFood() {return favFood; }
  string getColor() {return color; }
  string getComment() {return comment; }
  int getWeight() {return weight; }
  int getLength() {return length; }

  Snake();
  Snake(string _breed, string _name, string _gender, string _favFood, string _color, string _comment, int _weight, int _length);
  void printInfo();


};
