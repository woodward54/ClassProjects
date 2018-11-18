class flights {

private:
  int flight_cnt;
  bool error;
  vector <flight> flight_list;

public:
  int getFlightCnt() {return flight_cnt;}

  flights() {flight_cnt = 0;}
  ~flights() {}

  void add(planes *p, crew *c);
  void edit(planes *p, crew *c);
  void deleteFlight(planes *p, crew *c);
  void search(planes *p, crew *c);
  void printFlight(int _id);
  bool printAllFlights();
  void printSingleFlight();
  void printAssignmentSchdule(planes *p, crew *c);
  void printFlightsOnStatus(planes *p, crew *c);
  void update(planes *p, crew *c);
  bool isAvailable(planes *p, crew *c, int crewId, time_t testStart, time_t testEnd);

  void store();
  void load();
};
