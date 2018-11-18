class planes {

private:
  int plane_cnt;
  bool error;

public:
  int getPlaneCnt() {return plane_cnt;}
  vector <plane> plane_list;

  planes() {plane_cnt = 0;}
  ~planes() {}

  void addPlane();
  void editPlane();
  void deletePlane();
  void searchPlanes();
  void printPlane(int _id);
  bool printAllPlanes();
  void printSinglePlane();
  void store();
  void load();
};
