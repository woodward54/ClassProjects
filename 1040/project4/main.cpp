/*
Name:     David Woodward
Email:    davidwoodward@my.unt.edu
Program:  HW4

This program is a basic flight mangment system with crew, planes, and flights.
*/

#include <fstream>
#include <string>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

#include "plane.h"
#include "planes.h"
#include "pilot.h"
#include "crew_member.h"
#include "crew.h"
#include "flight.h"
#include "flights.h"

planes p;
crew c;
flights f;
void load();
void store();
void update();


int main() {
  //header
  cout << endl;
  cout << endl;
  cout << "Name:       David Woodward" << endl;
  cout << "Class:      CSCE 1040" << endl;
  cout << "Assignment: HW4" << endl;
  cout << "Email:      davidwoodward@my.unt.edu" << endl;
  cout << endl; cout << endl;
  cout << "Deleting cancelled/completed Flights happens automatically" << endl;
  cout << "Updating flight status happens automatically" << endl;
  cout << "There is test data, press 23 to load it. Storing before loading the data will erase the test data." << endl;

  cout << endl;

  int userChoice = 0;
  while (userChoice != 25) {
    f.update(&p, &c);
    cout << endl;
    cout << "<======PLANES======>" << endl;
    cout << "1. Add" << endl;
    cout << "2. Edit" << endl;
    cout << "3. Delete" << endl;
    cout << "4. Search" << endl;
    cout << "5. Print all Planes" << endl;
    cout << "6. Print single Plane detailes" << endl;

    cout << "<=======CREW=======>" << endl;
    cout << "7. Add" << endl;
    cout << "8. Edit" << endl;
    cout << "9. Delete" << endl;
    cout << "10. Search" << endl;
    cout << "11. Print all Crew" << endl;
    cout << "12. Print single Crew Member detailes" << endl;

    cout << "<======FLIGHTS======>" << endl;
    cout << "13. Add" << endl;
    cout << "14. Edit" << endl;
    cout << "15. Delete" << endl;
    cout << "16. Search" << endl;
    cout << "17. Print all Flights" << endl;
    cout << "18. Print single Flight detailes" << endl;
    cout << "19. Print assignments schedule" << endl;
    cout << "20. Print Flights based on status" << endl;
    //cout << "21. " << endl; //automatic??
    //cout << "22. " << endl; //automatic??
    cout << "<======OTHER======>" << endl;
    cout << "23. Load" << endl; //automatic??
    cout << "24. Store" << endl;
    cout << "25. Quit" << endl;
    cout << endl;


    //input validation
    for (;;) {
     cout << "Enter a selection: ";
     if (cin >> userChoice) {
         break;
     } else {
         cout << "ERROR: Please enter a valid integer" << endl;
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
     }
    }


   switch (userChoice) {
     case 1: p.addPlane(); break;
     case 2: p.editPlane(); break;
     case 3: p.deletePlane(); break;
     case 4: p.searchPlanes(); break;
     case 5: p.printAllPlanes(); break;
     case 6: p.printSinglePlane(); break;
     case 7: c.add(); break;
     case 8: c.edit(); break;
     case 9: c.deleteCrewMember(); break;
     case 10: c.search(); break;
     case 11: c.printAllCrew(); break;
     case 12: c.printSingleCrewMember(); break;
     case 13: f.add(&p, &c); break;
     case 14: f.edit(&p, &c); break;
     case 15: f.deleteFlight(&p, &c); break;
     case 16: f.search(&p, &c); break;
     case 17: f.printAllFlights(); break;
     case 18: f.printSingleFlight(); break;
     case 19: f.printAssignmentSchdule(&p, &c); break;
     case 20: f.printFlightsOnStatus(&p, &c); break;
     //case 21: f.update(&p, &c); break;
     //case 22: f.update(&p, &c); break;
     case 23: load(); break;
     case 24: store(); break;
     case 25: cout<<"INFO: Quitting..."<< endl; break;
     default:
       cout << "ERROR: Invalid choice" << endl;
   }
  } // end while
  return 0;
}

void load() {
  p.load();
  c.load();
  f.load();
  return;
}

void store() {
  p.store();
  c.store();
  f.store();
  return;
}
