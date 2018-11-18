class crew {

private:
  int crew_cnt;
  bool error;


public:
  int getCrewCnt() {return crew_cnt;}
  vector <crew_member*> crew_list;

  crew() {crew_cnt = 0;}
  ~crew() {}

  void add();
  void edit();
  void deleteCrewMember();
  void search();
  void printCrewMember(int _id);
  bool printAllCrew();
  void printSingleCrewMember();
  void store();
  void load();
};
