#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <stdio.h>
using namespace std;

#include "crew_member.h"
#include "crew.h"
#include "plane.h"
#include "planes.h"
#include "flight.h"
#include "flights.h"

//TODO input logic ie check if crew is available, plane is big enough
void flights::add(planes *p, crew *c) {
  bool error = false;
  int tempInt, planeId;
  string tempString;
  struct tm startTime, endTime;
  time_t tempTime, tempTime2;
  flight temp;

  //plane
  error = p->printAllPlanes();
  if (error) {return;}
  cout << "Select a plane                : ";
  cin >> planeId; cin.ignore();
  if (p->plane_list[planeId].getStatus().compare("in") != 0) {cout << "ERROR: This plane is " << p->plane_list[planeId].getStatus()<< "." << endl; return;}
  temp.setPlaneId(planeId);

  //start and end times
  //bug here! tempTime getting set to -1
  cout << "Months: 1-12, Days: 1-31, Hours: 0-23" << endl;
  cout << "Enter the start date MM DD YYYY : ";
  cin >> startTime.tm_mon >> startTime.tm_mday >> startTime.tm_year; cin.ignore();
  startTime.tm_year = startTime.tm_year-1900;
  startTime.tm_mon -=1;
  cout << "Enter the start time HH MM      : ";
  cin >> startTime.tm_hour >> startTime.tm_min; cin.ignore();
  tempTime = mktime(&startTime);
  temp.setStartTime(tempTime);

  cout << "Enter the end date MM DD YYYY   : ";
  cin >> endTime.tm_mon >> endTime.tm_mday >> endTime.tm_year; cin.ignore();
  endTime.tm_year = endTime.tm_year-1900;
  endTime.tm_mon -=1;
  cout << "Enter the end time HH MM        : ";
  cin >> endTime.tm_hour >> endTime.tm_min; cin.ignore();
  tempTime2 = mktime(&endTime);
  temp.setEndTime(tempTime2);

  //crew
 error = c->printAllCrew();
 if (error) {return;}
 cout << "Select '-1' for none." << endl;
 cout << "Select a pilot                  : ";
 cin >> tempInt; cin.ignore();
 if (c->crew_list[tempInt].getType().compare("pilot") != 0) {cout << "ERROR: This crew member is a "<<c->crew_list[tempInt].getType()<<"."<<endl; return;}
 if (c->crew_list[tempInt].getStatus().compare("available") != 0) {cout << "ERROR: This crew member is "<<c->crew_list[tempInt].getStatus()<<"."<<endl; return;}
 if (!(isAvailable(p, c, tempInt, temp.getStartTime(), temp.getEndTime()))) {return;}
 temp.setPiloitId(tempInt);

 cout << "Select a copilot                : ";
 cin >> tempInt; cin.ignore();
 if (c->crew_list[tempInt].getType().compare("copilot") != 0) {cout << "ERROR: This crew member is a "<<c->crew_list[tempInt].getType()<<"."<<endl; return;}
 if (c->crew_list[tempInt].getStatus().compare("available") != 0) {cout << "ERROR: This crew member is "<<c->crew_list[tempInt].getStatus()<<"."<<endl; return;}
 if (!(isAvailable(p, c, tempInt, temp.getStartTime(), temp.getEndTime()))) {return;}
 temp.setCoPiloitId(tempInt);

 cout << "Select cabin member 1           : ";
 cin >> tempInt; cin.ignore();
 if (c->crew_list[tempInt].getType().compare("cabin") != 0) {cout << "ERROR: This crew member is a "<<c->crew_list[tempInt].getType()<<"."<<endl; return;}
 if (c->crew_list[tempInt].getStatus().compare("available") != 0) {cout << "ERROR: This crew member is "<<c->crew_list[tempInt].getStatus()<<"."<<endl; return;}
 if (!(isAvailable(p,c, tempInt, temp.getStartTime(), temp.getEndTime()))) {return;}
 temp.setCrew1Id(tempInt);

 cout << "Select cabin member 2           : ";
 cin >> tempInt; cin.ignore();
 if (c->crew_list[tempInt].getType().compare("cabin") != 0) {cout << "ERROR: This crew member is a "<<c->crew_list[tempInt].getType()<<"."<<endl; return;}
 if (c->crew_list[tempInt].getStatus().compare("available") != 0) {cout << "ERROR: This crew member is "<<c->crew_list[tempInt].getStatus()<<"."<<endl; return;}
 if (!(isAvailable(p, c, tempInt, temp.getStartTime(), temp.getEndTime()))) {return;}
 temp.setCrew2Id(tempInt);

 cout << "Select cabin member 3           : ";
 cin >> tempInt; cin.ignore();
 if (c->crew_list[tempInt].getType().compare("cabin") != 0) {cout << "ERROR: This crew member is a "<<c->crew_list[tempInt].getType()<<"."<<endl; return;}
 if (c->crew_list[tempInt].getStatus().compare("available") != 0) {cout << "ERROR: This crew member is "<<c->crew_list[tempInt].getStatus()<<"."<<endl; return;}
 if (!(isAvailable(p, c, tempInt, temp.getStartTime(), temp.getEndTime()))) {return;}
 temp.setCrew3Id(tempInt);

 cout << "Enter the start airport code    : ";
 getline(cin, tempString);
 temp.setStartCode(tempString);

 cout << "Enter the end airport code      : ";
 getline(cin, tempString);
 temp.setEndCode(tempString);

 cout << "Enter the number of passengers  : ";
 cin >> tempInt; cin.ignore();
 if (p->plane_list[planeId].getNumOfSeats() < tempInt) {cout << "ERROR: This plane only seats " << p->plane_list[planeId].getNumOfSeats()<< "." << endl; return;}
 temp.setNumOfPass(tempInt);

 cout << "1. active  |  2. cancelled  |  3. completed" << endl;
 cout << "Select a status (num)           : ";
 cin >> tempInt; cin.ignore();
   if (tempInt == 1)
     tempString = "active";
   else if (tempInt == 2)
      tempString = "cancelled";
   else
     tempString = "completed";
  temp.setStatus(tempString);

  temp.setId(flight_cnt);

  flight_list.push_back(temp);
  flight_cnt++;
  return;
}

//not tested
void flights::update(planes *p, crew *c) {
  //updates crew and plane status based on current time
  time_t timer;
  time(&timer);

  for (int i=0; i<flight_cnt; i++) {
    time_t flightStart = flight_list[i].getStartTime();
    time_t flightEnd = flight_list[i].getEndTime();
    for (int j=0; j<c->getCrewCnt(); j++) {
      if (flight_list[i].getPiloitId() == c->crew_list[j].getId()) {
        if (flightStart < timer && timer < flightEnd && flight_list[i].getStatus()=="in") {
          c->crew_list[j].setStatus("out");
          cout << "INFO: " << c->crew_list[j].getName() << " is now out." << endl;
        } else if (flight_list[i].getStatus()=="out") {
          c->crew_list[j].setStatus("in");
          cout << "INFO: " << c->crew_list[j].getName() << " is now in." << endl;
        }
      } else if (flight_list[i].getCoPiloitId() == c->crew_list[j].getId()) {
        if (flightStart < timer && timer < flightEnd && flight_list[i].getStatus()=="in") {
          c->crew_list[j].setStatus("out");
          cout << "INFO: " << c->crew_list[j].getName() << " is now out." << endl;
        } else if (flight_list[i].getStatus()=="out") {
          c->crew_list[j].setStatus("in");
          cout << "INFO: " << c->crew_list[j].getName() << " is now in." << endl;
        }
      } else if (flight_list[i].getCrew1Id() == c->crew_list[j].getId()) {
        if (flightStart < timer && timer < flightEnd && flight_list[i].getStatus()=="in") {
          c->crew_list[j].setStatus("out");
          cout << "INFO: " << c->crew_list[j].getName() << " is now out." << endl;
        } else if (flight_list[i].getStatus()=="out") {
          c->crew_list[j].setStatus("in");
          cout << "INFO: " << c->crew_list[j].getName() << " is now in." << endl;
        }
      } else if (flight_list[i].getCrew2Id() == c->crew_list[j].getId()) {
        if (flightStart < timer && timer < flightEnd && flight_list[i].getStatus()=="in") {
          c->crew_list[j].setStatus("out");
          cout << "INFO: " << c->crew_list[j].getName() << " is now out." << endl;
        } else if (flight_list[i].getStatus()=="out") {
          c->crew_list[j].setStatus("in");
          cout << "INFO: " << c->crew_list[j].getName() << " is now in." << endl;
        }
      } else if (flight_list[i].getCrew3Id() == c->crew_list[j].getId()) {
       if (flightStart < timer && timer < flightEnd && flight_list[i].getStatus()=="in") {
        c->crew_list[j].setStatus("out");
        cout << "INFO: " << c->crew_list[j].getName() << " is now out." << endl;
      } else if (flight_list[i].getStatus()=="out") {
        c->crew_list[j].setStatus("in");
        cout << "INFO: " << c->crew_list[j].getName() << " is now in." << endl;
      }
    }
  }
}
  return;
}

bool flights::isAvailable(planes *p, crew *c, int crewId, time_t testStart, time_t testEnd) {
  for (int i=0; i<flight_cnt; i++) {
    for (int j=0; j<c->getCrewCnt(); j++) {
      if (flight_list[i].getPiloitId()==crewId || flight_list[i].getCoPiloitId()==crewId || flight_list[i].getCrew1Id()==crewId || flight_list[i].getCrew2Id()==crewId || flight_list[i].getCrew3Id()==crewId) {
        if (flight_list[i].getStartTime() < testStart && testStart < flight_list[i].getEndTime()) { //check start time
          cout << "ERROR: This crew member is out on flight "<< i <<" at this time."<<endl;
          return false;
        } else if (flight_list[i].getStartTime() < testEnd && testEnd < flight_list[i].getEndTime()) { //check end time
          cout << "ERROR: This crew member is out on flight "<< i <<" at this time."<<endl;
          return false;
        }
      }
    }
  }
  return true;
}

void flights::edit(planes *p, crew *c) {
  int planeId, tempInt, editSel, id;
  string tempString;
  struct tm startTime, endTime;
  time_t tempTime, tempTime2;

  error = printAllFlights();
  if (error) {return;}

  cout << "Select a flight to edit: ";
  cin >> id; cin.ignore();

  for (int i=0; i < flight_cnt; i++) {
    if (id == flight_list[i].getId()) {
      cout << "What would you like to edit?" << endl;
      cout << "1. Plane, 2. Pilot, 3. CoPilot, 4. Cabin 1, 5. Cabin 2, 6. Cabin 3, 7. Start Time, 8. End Time, 9. Start Airport, 10. End Airport, 11. Num of passengers, 12. Status" << endl;
      cout << "Selection: ";
      cin >> editSel; cin.ignore();

      switch (editSel) {
        case 1:
          error = p->printAllPlanes();
          if (error) {return;}
          cout << "Select a plane                : ";
          cin >> planeId; cin.ignore();
          if (p->plane_list[planeId].getStatus().compare("in") != 0) {cout << "ERROR: This plane is " << p->plane_list[planeId].getStatus()<< "." << endl; return;}
          flight_list[id].setPlaneId(planeId); break;
        case 2:
          error = c->printAllCrew();
          if (error) {return;}
          cout << "Select '-1' for none." << endl;
          cout << "Select a pilot                  : ";
          cin >> tempInt; cin.ignore();
          if (c->crew_list[tempInt].getType().compare("pilot") != 0) {cout << "ERROR: This crew member is a "<<c->crew_list[tempInt].getType()<<"."<<endl; return;}
          if (c->crew_list[tempInt].getStatus().compare("available") != 0) {cout << "ERROR: This crew member is "<<c->crew_list[tempInt].getStatus()<<"."<<endl; return;}
          if (!(isAvailable(p, c, tempInt, flight_list[id].getStartTime(), flight_list[id].getEndTime()))) {return;}
          flight_list[id].setPiloitId(tempInt); break;
        case 3:
          error = c->printAllCrew();
          if (error) {return;}
          cout << "Select a copilot                : ";
          cin >> tempInt; cin.ignore();
          if (c->crew_list[tempInt].getType().compare("copilot") != 0) {cout << "ERROR: This crew member is a "<<c->crew_list[tempInt].getType()<<"."<<endl; return;}
          if (c->crew_list[tempInt].getStatus().compare("available") != 0) {cout << "ERROR: This crew member is "<<c->crew_list[tempInt].getStatus()<<"."<<endl; return;}
          if (!(isAvailable(p, c, tempInt, flight_list[id].getStartTime(), flight_list[id].getEndTime()))) {return;}
          flight_list[id].setCoPiloitId(tempInt); break;
        case 4:
          error = c->printAllCrew();
          if (error) {return;}
          cout << "Select cabin member 1           : ";
          cin >> tempInt; cin.ignore();
          if (c->crew_list[tempInt].getType().compare("cabin") != 0) {cout << "ERROR: This crew member is a "<<c->crew_list[tempInt].getType()<<"."<<endl; return;}
          if (c->crew_list[tempInt].getStatus().compare("available") != 0) {cout << "ERROR: This crew member is "<<c->crew_list[tempInt].getStatus()<<"."<<endl; return;}
          if (!(isAvailable(p,c, tempInt, flight_list[id].getStartTime(), flight_list[id].getEndTime()))) {return;}
          flight_list[id].setCrew1Id(tempInt);
        case 5:
          error = c->printAllCrew();
          if (error) {return;}
          cout << "Select cabin member 2           : ";
          cin >> tempInt; cin.ignore();
          if (c->crew_list[tempInt].getType().compare("cabin") != 0) {cout << "ERROR: This crew member is a "<<c->crew_list[tempInt].getType()<<"."<<endl; return;}
          if (c->crew_list[tempInt].getStatus().compare("available") != 0) {cout << "ERROR: This crew member is "<<c->crew_list[tempInt].getStatus()<<"."<<endl; return;}
          if (!(isAvailable(p, c, tempInt, flight_list[id].getStartTime(), flight_list[id].getEndTime()))) {return;}
          flight_list[id].setCrew2Id(tempInt); break;
        case 6:
          error = c->printAllCrew();
          if (error) {return;}
          cout << "Select cabin member 3           : ";
          cin >> tempInt; cin.ignore();
          if (c->crew_list[tempInt].getType().compare("cabin") != 0) {cout << "ERROR: This crew member is a "<<c->crew_list[tempInt].getType()<<"."<<endl; return;}
          if (c->crew_list[tempInt].getStatus().compare("available") != 0) {cout << "ERROR: This crew member is "<<c->crew_list[tempInt].getStatus()<<"."<<endl; return;}
          if (!(isAvailable(p, c, tempInt, flight_list[id].getStartTime(), flight_list[id].getEndTime()))) {return;}
          flight_list[id].setCrew3Id(tempInt); break;
        case 7:
          //bug here! tempTime getting set to -1
          cout << "Months: 1-12, Days: 1-31, Hours: 0-23" << endl;
          cout << "Enter the start date MM DD YYYY : ";
          cin >> startTime.tm_mon >> startTime.tm_mday >> startTime.tm_year; cin.ignore();
          startTime.tm_year = startTime.tm_year-1900;
          startTime.tm_mon -=1;
          cout << "Enter the start time HH MM      : ";
          cin >> startTime.tm_hour >> startTime.tm_min; cin.ignore();
          tempTime = mktime(&startTime);
          flight_list[id].setStartTime(tempTime);
        case 8:
          cout << "Enter the end date MM DD YYYY   : ";
          cin >> endTime.tm_mon >> endTime.tm_mday >> endTime.tm_year; cin.ignore();
          endTime.tm_year = endTime.tm_year-1900;
          endTime.tm_mon -=1;
          cout << "Enter the end time HH MM        : ";
          cin >> endTime.tm_hour >> endTime.tm_min; cin.ignore();
          tempTime2 = mktime(&endTime);
          flight_list[id].setEndTime(tempTime2);
        case 9:
          cout << "Enter the start airport code    : ";
          getline(cin, tempString);
          flight_list[id].setStartCode(tempString);
        case 11:
          cout << "Enter the number of passengers  : ";
          cin >> tempInt; cin.ignore();
          if (p->plane_list[planeId].getNumOfSeats() < tempInt) {cout << "ERROR: This plane only seats " << p->plane_list[planeId].getNumOfSeats()<< "." << endl; return;}
          flight_list[id].setNumOfPass(tempInt);
        case 12:
          cout << "1. active  |  2. cancelled  |  3. completed" << endl;
          cout << "Select a status (num)           : ";
          cin >> tempInt; cin.ignore();
            if (tempInt == 1)
              tempString = "active";
            else if (tempInt == 2)
               tempString = "cancelled";
            else
              tempString = "completed";
           flight_list[id].setStatus(tempString);
          case 10:
          cout << "Enter the end airport code      : ";
          getline(cin, tempString);
          flight_list[id].setEndCode(tempString);
        default: cout << "ERROR: Not a valid selection." << endl;
      }
    }
  }
  return;
}

void flights::deleteFlight(planes *p, crew *c) {
  int id;
  printAllFlights();
  if (error) {return;}

  cout << "Selection: ";
  cin >> id; cin.ignore();
  cout << "INFO: Flight " << flight_list[id].getId() << " deleted." << endl;
  flight_list.erase(flight_list.begin() + id);
  return;
}

void flights::search(planes *p, crew *c) {
  string search;
  cout << "Enter a starting airport code : ";
  cin.ignore(); getline(cin, search);

  for (int i=0; i<flight_cnt; i++){
    if (search.compare(flight_list[i].getStartCode()) == 0) {
      cout << "Flight found! Printing flight details with starting airport: " << search << endl;
      printFlight(i);
    } else if (i == flight_cnt-1)
      cout << "ERROR: No flights found with starting airport: " << search << endl;
  }
  return;
}

void flights::printFlight(int _id) {
  for (int i=0; i < flight_cnt; i++) {
    if (flight_list[i].getId() == _id) {
      char buffer[80];
      time_t temp = flight_list[i].getStartTime();
      struct tm *time1 = localtime(&temp);
      strftime(buffer,80, "%Y %B %e %R", time1);

      cout << "Id               : " << flight_list[i].getId() << endl;
      cout << "Plane ID         : " << flight_list[i].getPlaneId() << endl;
      cout << "Piloit ID        : " << flight_list[i].getPiloitId() << endl;
      cout << "CoPiloit ID      : " << flight_list[i].getCoPiloitId() << endl;
      cout << "Crew IDs         : " << flight_list[i].getCrew1Id() << ", " << flight_list[i].getCrew2Id() << ", " << flight_list[i].getCrew3Id() << endl;
      cout << "Start Time       : "; puts(buffer);
      char buffer2[80]; time_t temp2 = flight_list[i].getEndTime(); struct tm *time2 = localtime(&temp2); strftime(buffer2,80, "%Y %B %e %R", time2);
      cout << "End Time         : "; puts(buffer2);
      cout << "Destination      : " << flight_list[i].getStartCode() << " -> " << flight_list[i].getEndCode() << endl;
      cout << "Num of passengers: " << flight_list[i].getNumOfPass() << endl;
      cout << "Status           : " << flight_list[i].getStatus() << endl;
    } else if (i == flight_list.size())
      cout << "ERROR: Flight not found" << endl;
  }
  return;
}

bool flights::printAllFlights() {
  if (flight_cnt == 0) {
    cout << "ERROR: 0 Flights in system." << endl;
    return true;
  }
  for (int i=0; i<flight_cnt; i++)
    cout << left << flight_list[i].getId() << ". " << flight_list[i].getStartCode() << " -> " << flight_list[i].getEndCode() << endl;
  return false;
}

void flights::printSingleFlight() {
  int selection;
  bool error = false;
  error = printAllFlights();
  if (error) {return;}

  cout << "Selection: ";
  cin >> selection; cin.ignore();
  printFlight(selection);
  return;
}

void flights::printAssignmentSchdule(planes *p, crew *c) {
  int crewId;

  error = c->printAllCrew();
  if (error) {return;}
  cout << "Select a crew member     : ";
  cin >> crewId; cin.ignore();
  for (int i=0; i<flight_cnt; i++) {
    if (flight_list[i].getPiloitId()==crewId || flight_list[i].getCoPiloitId()==crewId || flight_list[i].getCrew1Id()==crewId || flight_list[i].getCrew2Id()==crewId || flight_list[i].getCrew3Id()==crewId) {
      cout << i+1 << ". " << flight_list[i].getStartCode() << " -> " << flight_list[i].getEndCode() << endl;
    }
  }
  return;
}
void flights::printFlightsOnStatus(planes *p, crew *c) {
  int tempInt;
  string tempString;
  cout << "1. active  |  2. cancelled  |  3. completed" << endl;
  cout << "Select a status to print (num)           : ";
  cin >> tempInt; cin.ignore();
    if (tempInt == 1)
      tempString = "active";
    else if (tempInt == 2)
       tempString = "cancelled";
    else
      tempString = "completed";
  for (int i=0; i<flight_cnt; i++) {
    if (tempString.compare(flight_list[i].getStatus()) == 0) {
      printFlight(i);
    }
  }
  return;
}

void flights::store() {
  error = printAllFlights();
  if (error) {return;}
  ofstream fout;
  fout.open("flights.dat");
  fout << flight_cnt << endl;
  for (int i=0; i < flight_cnt; i++) {
    fout << flight_list[i].getId() << endl;
    fout << flight_list[i].getPlaneId()<<" "<<flight_list[i].getPiloitId()<<" "<<flight_list[i].getCoPiloitId()<<" "<<flight_list[i].getCrew1Id()<<" "<<flight_list[i].getCrew2Id()<<" "<<flight_list[i].getCrew3Id()<<endl;
    fout << flight_list[i].getStartTime()<<" "<<flight_list[i].getEndTime()<<endl;
    fout << flight_list[i].getStartCode()<< endl;
    fout << flight_list[i].getEndCode()<<endl;
    fout << flight_list[i].getNumOfPass()<<endl;
    fout << flight_list[i].getStatus() << endl;
  }
  fout.close();
  cout << "INFO: " << flight_cnt << " flights stored." << endl;
  return;
}

void flights::load() {
  int id, planeId, piloitId, coPiloitId, crew1Id, crew2Id, crew3Id, num;
  string startCode, endCode, status;
  time_t startTime, endTime;
  ifstream fin;
  flight temp;
  fin.open("flights.dat");
  fin >> flight_cnt; fin.ignore();

  for (int i=0; i < flight_cnt; i++) {

    fin >> id; fin.ignore();
    fin >> planeId >> piloitId >> coPiloitId >> crew1Id >> crew2Id >> crew3Id; fin.ignore();
    fin >> startTime >> endTime; fin.ignore();
    getline(fin, startCode); getline(fin, endCode);
    fin >> num; fin.ignore();
    getline(fin, status);

    temp.setId(id); temp.setPlaneId(planeId); temp.setPiloitId(piloitId); temp.setCoPiloitId(coPiloitId); temp.setCrew1Id(crew1Id);
    temp.setCrew2Id(crew2Id); temp.setCrew3Id(crew3Id); temp.setStartTime(startTime); temp.setEndTime(endTime);
    temp.setStartCode(startCode); temp.setEndCode(endCode); temp.setNumOfPass(num); temp.setStatus(status);

    flight_list.push_back(temp);
  }
  cout << "INFO: " << flight_cnt << " Flights loaded." << endl;
  return;
}
