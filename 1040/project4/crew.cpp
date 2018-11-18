#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//#include "crew_member.h"
#include "pilot.h"
#include "crew.h"
#include "plane.h"
#include "planes.h"
#include "flight.h"
#include "flights.h"

void crew::add() {
  string name, type, status, rating;
  int status_num, type_num, hours;
  pilot* tempP = 0;
  tempP = new pilot;

  cout << "Name        : ";
  cin.ignore(); getline(cin, name);
  cout << "1. available  |  2. on leave  |  3. sick" << endl; //4th is "out" set by system
  cout << "Status(num)    : ";
  cin >> status_num; cin.ignore();
  if (status_num == 1)
    status = "available";
  else if (status_num == 2)
    status = "on leave";
  else
    status = "sick";

    cout << "1. pilot  |  2. copilot  |  3. cabin" << endl;
    cout << "Type(num)   : ";
    cin >> type_num; cin.ignore();
    if (type_num == 1) {

      cout << "Rating     : ";
      getline(cin, rating);
      cout << "Hours      : ";
      cin >> hours; cin.ignore();
      tempP->setRating(rating);
      tempP->setHours(hours);
      tempP->setName(name);
      tempP->setStatus(status);
      tempP->setId(crew_cnt);
      crew_list.push_back(tempP);
    }
    else if (type_num == 2) {
            cout << endl;
    }
    else {
      cout << endl;
      //type = "cabin";
    }

  crew_cnt++;
  return;
}

void crew::edit() {
  int id, editSel, tempInt, status_num, type_num;
  string tempString, status, type;


  error = printAllCrew();
  if (error) {return;}

  cout << "Select a crew member to edit: ";
  cin >> id; cin.ignore();

  for (int i=0; i < crew_cnt; i++) {
    if (id == crew_list[i]->getId()) {

      cout << "What would you like to edit?" << endl;
      cout << "1. Name, 2. Status, 3. Rating(pilots), 4. Hours (pilots), 5. Position (cabin only)" << endl;
      cout << "Selection: ";
      cin >> editSel; cin.ignore();

      switch (editSel) {
        case 1: cout << "New Name   : "; getline(cin, tempString); crew_list[id]->setName(tempString); break;

        case 2:
        cout << "1. available  |  2. on leave  |  3. sick" << endl;
        cout << "New Status(num)   : ";
        cin >> status_num; cin.ignore();
        if (status_num == 1)
          status = "available";
        else if (status_num == 2)
          status = "on leave";
        else
          status = "sick";
        crew_list[id]->setStatus(status); break;
//static_cast<p*>(
        case 3: cout << "New Rating     : "; //getline(cin, tempString); crew_list[id]->setRating(tempString); break;
        case 4: cout << "New Hours      : "; //cin >> tempInt; cin.ignore(); crew_list[id]->setHours(tempInt); break;
        case 5: cout << "New Position   : "; //getline(cin, tempString); crew_list[id]->setPosition(tempString); break;
        default: cout << "ERROR: Not a valid selection." << endl;
      }
    }
  }
  return;
}

void crew::deleteCrewMember() {
  int id;
  printAllCrew();
  if (error) {return;}

  cout << "Selection: ";
  cin >> id; cin.ignore();
  cout << "INFO: Crew Member " << crew_list[id]->getName() << " deleted." << endl;
  crew_list.erase(crew_list.begin() + id);
  return;
}

void crew::search() {
  string search;
  cout << "Enter a Name to search: ";
  cin.ignore(); getline(cin, search);

  for (int i=0; i<crew_cnt; i++){
    if (search.compare(crew_list[i]->getName()) == 0) {
      cout << "Crew Member found! Printing crew member details with name: " << search << endl;
      printCrewMember(i);
    } else if (i == crew_cnt-1)
      cout << "ERROR: No crew member found with name: " << search << endl;
  }
  return;
}

void crew::printCrewMember(int _id) {
  for (int i=0; i < crew_cnt; i++) {
    if (crew_list[i]->getId() == _id) {
      crew_list[i]->printInfo();
    } else if (i == crew_list.size())
      cout << "ERROR: Crew member not found" << endl;
  }
  return;
}

bool crew::printAllCrew() {
  if (crew_cnt == 0) {
    cout << "ERROR: 0 Crew members in system." << endl;
    return true;
  }
  for (int i=0; i<crew_cnt; i++)
    cout << left << crew_list[i]->getId() << ". " << left << setw(20) <<crew_list[i]->getName() << endl;
  return false;
}

void crew::printSingleCrewMember() {
  int selection;
  error = printAllCrew();
  if (error) {return;}

  cout << "Selection: ";
  cin >> selection; cin.ignore();
  printCrewMember(selection);
  return;
}

void crew::store() {
  error = printAllCrew();
  if (error) {return;}

  ofstream fout;
  fout.open("crew.dat");
  fout << crew_cnt << endl;
  for (int i=0; i < crew_cnt; i++) {
    fout << crew_list[i]->getId() << endl;
    fout << crew_list[i]->getName() << endl;
    //fout << crew_list[i]->getType() << endl;
    fout << crew_list[i]->getStatus() << endl;
  }
  fout.close();
  cout << "INFO: " << crew_cnt << " crew members stored." << endl;
  return;
}

void crew::load() {
  int id;
  string name, type, status;
  ifstream fin;
  crew_member temp;
  fin.open("crew.dat");
  fin >> crew_cnt; fin.ignore();

  for (int i=0; i < crew_cnt; i++) {

    fin >> id; fin.ignore(); getline(fin, name); getline(fin, type); getline(fin, status);

    temp.setId(id); temp.setName(name); temp.setStatus(status);

    //crew_list.push_back(temp);
  }
  cout << "INFO: " << crew_cnt << " Crew Members loaded." << endl;
  return;
}
