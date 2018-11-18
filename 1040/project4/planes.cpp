#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


#include "crew_member.h"
#include "crew.h"
#include "plane.h"
#include "planes.h"
#include "flight.h"
#include "flights.h"

//add plane object
void planes::addPlane() {

  int range, num_of_seats, status_num;
  string make, model, tail_num, status;
  plane temp;

  cout << "Make         : ";
  cin.ignore();
  getline(cin, make);
  cout << "Model        : ";
  getline(cin, model);
  cout << "Tail Number  : ";
  getline(cin, tail_num);

  cout << "1. in  |  2. out  |  3. in repair" << endl;
  cout << "Status(num)  : ";
  cin >> status_num; cin.ignore();
  if (status_num == 1)
    status = "in";
  else if (status_num == 2)
    status = "out";
  else
    status = "in repair";
  cout << "Num of Seats : ";
  cin >> num_of_seats; cin.ignore();
  cout << "Range(miles) : ";
  cin >> range; cin.ignore();

  temp.setMake(make);
  temp.setModel(model);
  temp.setTailNum(tail_num);
  temp.setStatus(status);
  temp.setNumOfSeats(num_of_seats);
  temp.setRange(range);
  temp.setId(plane_cnt);

  plane_list.push_back(temp);
  plane_cnt += 1;
  return;
}

void planes::editPlane(){
  int id, editSel, tempInt, error;
  string tempString, status;

  if (plane_cnt == 0) {
    cout << "ERROR: 0 Planes in system." << endl;
  } else {
  printAllPlanes();
  cout << "Select a plane to edit: ";
  cin >> id; cin.ignore();

  for (int i=0; i < plane_cnt; i++) {
    if (id == plane_list[i].getId()) {
      cout << "What would you like to edit?" << endl;
      cout << "1. Make, 2. Model, 3. Tail Number, 4. Status, 5. Number of Seats, 6. Range" << endl;
      cout << "Selection: ";
      cin >> editSel; cin.ignore();

      switch (editSel) {
        case 1: cout << "New Make: "; getline(cin, tempString); plane_list[id].setMake(tempString); break;
        case 2: cout << "New Model: "; getline(cin, tempString); plane_list[id].setModel(tempString); break;
        case 3: cout << "New Tail Number: "; getline(cin, tempString); plane_list[id].setTailNum(tempString); break;
        case 4: cout << "1. in  |  2. out  |  3. in repair" << endl; cout << "New Status (num): ";
        cin >> tempInt; cin.ignore();
        if (tempInt == 1)
          status = "in";
        else if (tempInt == 2)
          status = "out";
        else
          status = "in repair";
        plane_list[id].setStatus(status); break;
        case 5: cout << "New Number of Seats: "; cin >> tempInt; cin.ignore(); plane_list[id].setNumOfSeats(tempInt); break;
        case 6: cout << "New Range: "; cin >> tempInt; cin.ignore(); plane_list[id].setRange(tempInt); break;
        default: cout << "ERROR: Not a valid selection." << endl;
      }
    }
  }
 }
  return;
}
void planes::deletePlane() {
  int id;
  if (plane_cnt == 0) {
    cout << "ERROR: 0 Planes in system." << endl;
  } else {
  printAllPlanes();
  cout << "Selection: ";
  cin >> id; cin.ignore();
  cout << "INFO: Plane " << plane_list[id].getTailNum() << " deleted." << endl;
  plane_list.erase(plane_list.begin() + id);
 }
  return;
}
void planes::searchPlanes() {
  string search;

  if (plane_cnt == 0) {
    cout << "ERROR: 0 Planes in system." << endl;
  } else {
  cout << "Enter a TailNumber to search: ";
  cin.ignore(); getline(cin, search);

  for (int i=0; i<plane_cnt; i++){
    if (search.compare(plane_list[i].getTailNum()) == 0) {
      cout << "Plane found! Printing plane details with Tail number: " << search << endl;
      printPlane(i);
    } else if (i == plane_cnt-1)
      cout << "ERROR: No plane found with Tail number: " << search << endl;
  }
}
  return;
}

void planes::printPlane(int _id) {

  for (int i=0; i < plane_list.size(); i++) {
    if (plane_list[i].getId() == _id) {
      cout << "Make         : " << plane_list[i].getMake() << endl;
      cout << "Model        : " << plane_list[i].getModel() << endl;
      cout << "Tail Number  : " << plane_list[i].getTailNum() << endl;
      cout << "Status       : " << plane_list[i].getStatus() << endl;
      cout << "Num of Seats : " << plane_list[i].getNumOfSeats() << endl;
      cout << "Range(miles) : " << plane_list[i].getRange() << endl;
    } else if (i == plane_list.size())
      cout << "ERROR: Plane not found" << endl;
  }
  return;
}

bool planes::printAllPlanes() {
  if (plane_cnt == 0) {
    cout << "ERROR: 0 Planes in system." << endl;
    return true;
  } else {
  for (int i=0; i < plane_list.size(); i++) {
    cout << left << plane_list[i].getId() << ". " << setw(7) << plane_list[i].getTailNum() << ", " << setw(7) << plane_list[i].getMake() << ", " << setw(7) << plane_list[i].getModel() << endl;
  }
 }
  return false;
}

void planes::printSinglePlane() {
  int id;
  if (plane_cnt == 0) {
    cout << "ERROR: 0 Planes in system." << endl;
  } else {
  printAllPlanes();
  cout << "Selection: ";
  cin >> id; cin.ignore();
  printPlane(id);
 }
  return;
}

void planes::store() {
 
  error = printAllPlanes();
  if (error) {return;}

  ofstream fout;
  fout.open("planes.dat");
  fout << plane_cnt << endl;
  for (int i=0; i < plane_cnt; i++) {
    fout << plane_list[i].getId() << endl;
    fout << plane_list[i].getTailNum() << endl;
    fout << plane_list[i].getMake() << endl;
    fout << plane_list[i].getModel() << endl;
    fout << plane_list[i].getStatus() << endl;
    fout << plane_list[i].getNumOfSeats() << " " << plane_list[i].getRange() << endl;
  }
  fout.close();
  cout << "INFO: " << plane_cnt << " Planes stored." << endl;
  return;
}

void planes::load() {

  int id, num_of_seats, range;
  string tail_num, model, make, status;
  ifstream fin;
  plane temp;
  fin.open("planes.dat");
  fin >> plane_cnt; fin.ignore();

  for (int i=0; i < plane_cnt; i++) {

    fin >> id; fin.ignore();
    getline(fin, tail_num);

    getline(fin, make);
    getline(fin, model);
    getline(fin, status);
    fin >> num_of_seats >> range; fin.ignore();
    temp.setId(id); temp.setTailNum(tail_num); temp.setMake(make); temp.setModel(model);
    temp.setStatus(status); temp.setNumOfSeats(num_of_seats); temp.setRange(range);

    plane_list.push_back(temp);
  }
  cout << "INFO: " << plane_cnt << " Planes loaded." << endl;
  return;
}
