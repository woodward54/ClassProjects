class flight {

private:
  int id, planeId, piloitId, coPiloitId, crew1Id, crew2Id, crew3Id, numOfPassengers;
  string startCode, endCode, status;
  time_t startTime, endTime;

public:
  //setters and getters
  void setId(int _id) {id = _id;}
  int getId() {return id;}
  void setPlaneId(int _planeid) {planeId = _planeid;}
  int getPlaneId() {return planeId;}
  void setPiloitId(int _piloitId) {piloitId = _piloitId;}
  int getPiloitId() {return piloitId;}
  void setCoPiloitId(int _id) {coPiloitId = _id;}
  int getCoPiloitId() {return coPiloitId;}
  void setCrew1Id(int _id) {crew1Id = _id;}
  int getCrew1Id() {return crew1Id;}
  void setCrew2Id(int _id) {crew2Id = _id;}
  int getCrew2Id() {return crew2Id;}
  void setCrew3Id(int _id) {crew3Id = _id;}
  int getCrew3Id() {return crew3Id;}
  void setNumOfPass(int _num) {numOfPassengers = _num;}
  int getNumOfPass() {return numOfPassengers;}

  void setStartCode(string _name) {startCode = _name;}
  string getStartCode() {return startCode;}
  void setEndCode(string _type) {endCode = _type;}
  string getEndCode() {return endCode;}
  void setStatus(string _status) {status = _status;}
  string getStatus() {return status;}

  void setStartTime(time_t _time) {startTime = _time;}
  time_t getStartTime() {return startTime;}
  void setEndTime(time_t _time) {endTime = _time;}
   time_t getEndTime() {return endTime;}
};
