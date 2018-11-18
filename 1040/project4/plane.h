class plane {

private:
  int id, num_of_seats, range;
  string tail_num, model, make, status;

public:
  //setters / getters
  void setId(int _id) {id = _id;}
  int getId() {return id;}
  void setNumOfSeats(int _num) {num_of_seats = _num;}
  int getNumOfSeats() {return num_of_seats;}
  void setRange(int _range) {range = _range;}
  int getRange() {return range;}
  void setTailNum(string _tail_num) {tail_num = _tail_num;}
  string getTailNum() {return tail_num;}
  void setModel(string _model) {model = _model;}
  string getModel() {return model;}
  void setMake(string _make) {make = _make;}
  string getMake() {return make;}
  void setStatus(string _status) {status = _status;}
  string getStatus() {return status;}

};
