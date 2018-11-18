#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct fullName {
  vector<string> name;
  vector<string> shifts;
  string allShifts;
  string initials;
};

void parse(vector<fullName> &names, vector<vector<vector<bool> > > &weekDays);
void print2dMatrix(vector<vector<int> > &vectorName);
void print2dMatrixString(vector<vector<string> > &vectorName);

bool checkScc(vector<vector<int> > &testVector);
void checkRedNurse(vector<vector<vector<bool> > > weekDays, vector<fullName> names, vector<vector<string> > &mns);
void checkRedShift(vector<vector<vector<bool> > > weekDays, vector<fullName> names, vector<vector<string> > &mss);

void set_or(vector<vector<vector<bool> > > &weekDays, vector<vector<int> > &scc);
void set_and(vector<vector<vector<bool> > > &weekDays, vector<vector<int> > &scc, vector<vector<int> > &temp);
void set_not(vector<vector<int> > &nn, vector<vector<int> > &scc);
void set_symdiff(vector<vector<int> > &mt1, vector<vector<int> > &scc);

int main() {
  //variables
  vector<fullName> names;
  vector<vector<vector<bool> > > weekDays;
    //0 = monday
    //1 = tuesday
    //etc...
  //initalize all vectors/bit vectors to all 0's
  vector<vector<int> > scc(5, vector<int>(24)); //simple compleate coverage
  vector<vector<int> > mt1(5, vector<int>(24)); //more than 1
  vector<vector<int> > nn(5, vector<int>(24)); //no nurses
  vector<vector<int> > e1n(5, vector<int>(24)); //exactly 1 nurse
  vector<vector<int> > numOfNurses(5, vector<int>(24));
  vector<vector<string> > mns(5, vector<string>(24));  //minimal nurse schedule
  vector<vector<string> > mss(5, vector<string>(24));  //minimal shift schedule

  string simpleCoverage = "True";

  //initalize 5 days
  for (int d=0; d < 5; d++) {
    weekDays.push_back(vector<vector<bool> >());
  }

  //parse / populate vectors
  parse(names, weekDays);

  //create allShifts string
  for (int n = 0; n < names.size(); n++) {
    for (int s = 0; s < names[n].shifts.size(); s++) {
      names[n].allShifts = names[n].allShifts + names[n].shifts[s];
    }
  }

  //logic
  set_or(weekDays, scc);
  set_and(weekDays, mt1, numOfNurses);
  set_not(scc, nn);
  set_symdiff(e1n, numOfNurses);

  if (!checkScc(scc)) {
    simpleCoverage = "False";
  }

  //create minimal nurse and shift schedules
  checkRedNurse(weekDays, names, mns);
  checkRedShift(weekDays, names, mss);

  //output
  cout << endl; cout << endl;
  cout << "Simple Complete Coverage: " << simpleCoverage << endl;
  cout << endl; cout << endl;
  cout << "More than 1 Nurse: " << endl;
  print2dMatrix(mt1);
  cout << endl;
  cout << "No Nurses: " << endl;
  print2dMatrix(nn);
  cout << endl;
  cout << "Exactly 1 Nurse: " << endl;
  print2dMatrix(e1n);
  cout << endl;
  cout << "Minimal Nurses Schedule: " << endl;
  print2dMatrixString(mns);
  cout << endl;
  cout << "Minimal Shifts Schedule: " << endl;
  print2dMatrixString(mss);
  return 0;
}

//utitilty functions
void parse(vector<fullName> &names, vector<vector<vector<bool> > > &weekDays) {
  string file, s, el, el2, del = " ";
  size_t pos=0;
  int ppl_cnt = 0;
  bool moveOn = true;
  vector<int> ntimes;
  //parse file
   cout << "Enter file name: ";
   cin >> file; cin.ignore();
   ifstream fin;
   fin.open(file.c_str());

   while (!fin.eof()) {

     del = " ";
     struct fullName tmp;

     //get first and last name
     getline(fin, s);
     s += " ";
     while ((pos = s.find(del)) != string::npos) {
      	el = s.substr(0, pos);
      	tmp.name.push_back(el);
      	s.erase(0, pos + del.length());
     }

     // was here
     ppl_cnt += 1;
     for (int d = 0; d < 5; d++) {
       weekDays[d].push_back(vector<bool>());
       for (int h=0; h < 24; h++) {
         weekDays[d][ppl_cnt-1].push_back(false);
       }
     }

    //get days and hours
    while(moveOn) {
     getline(fin, s);
     tmp.shifts.push_back(s);
     s += "-";
     //get day of the week
     del = " ";
     while ((pos = s.find(del)) != string::npos) {
       el = s.substr(0, pos);
       s.erase(0, pos + del.length());
     }

     //get numbers
     del = "-";
     while ((pos = s.find(del)) != string::npos) {
       el2 = s.substr(0, pos);
         if (el2[0] == '0') {
           el2.erase(0, 1);
         }
       //check if el2 is empty
       if (el2.length() > 0) {
         cout << "TEST: " << el2 << endl;
         ntimes.push_back((int)stof(el2));

       } else {
         cout << "INFO: " << tmp.name[0] << " " << tmp.name[1] << " loaded." << endl;
         moveOn = false;
         ntimes.clear();
       }
       s.erase(0, pos + del.length());
     }

     //cout << el << endl;
     //cout << ntimes[0] << " " << ntimes[1] << endl;
   for(int i=0 + ntimes[0]; i<=ntimes[1]; i++){

      if (el == "Monday")
        weekDays[0][ppl_cnt-1][i] = true;
      else if (el == "Tuesday")
        weekDays[1][ppl_cnt-1][i] = true;
      else if (el == "Wednesday")
        weekDays[2][ppl_cnt-1][i] = true;
      else if (el == "Thursday")
        weekDays[3][ppl_cnt-1][i] = true;
      else if (el == "Friday")
        weekDays[4][ppl_cnt-1][i] = true;

      ntimes.clear();
    }
  }
  names.push_back(tmp);
  moveOn = true;
  }
  string name1, name2, f, l;
  for (int i=0; i < ppl_cnt; i++) {
    name1=names[i].name[0];
    name2=names[i].name[1];
    f=name1[0];
    l=name2[0];
    names[i].initials = f + l;
  }
  return;
}

void print2dMatrix(vector<vector<int> > &vectorName) {

  int colW1 = 7, colW2 = 3;
  //print hours
  cout << setw(colW1) << " ";
  for (int i = 0; i < 24; i++) {
    cout << setw(colW2) << i;
  }
  cout << endl;
  //rows
  for (int i = 0; i < vectorName.size(); i++) {

    if (i == 0)
      cout << setw(colW1) << "Mon";
    else if (i == 1)
      cout << setw(colW1) << "Tues";
    else if (i == 2)
      cout << setw(colW1) << "Wed";
    else if (i == 3)
      cout << setw(colW1) << "Thur";
    else
      cout << setw(colW1) << "Fri";
    //cols
    for (int j = 0; j < 24; j++) {
      if (vectorName[i][j] == 1)
        cout << setw(colW2) << "1";
      else
        cout << setw(colW2) << "0";
    }
    cout << endl;
  }
  cout << endl;
  return;
}

void print2dMatrixString(vector<vector<string> > &vectorName) {

  //find longest string
  //for (int i=0; i < vectorName.size(); i++) {
  //  for (int j=0; j < vectorName.size())   vectorName[i][j].size() + 2
  //}
  int colW1 = 7, colW2 = 9;
  //print hours
  cout << setw(colW1) << " ";
  for (int i = 0; i < 24; i++) {
    cout << left << setw(colW2) << i;
  }
  cout << endl;
  //rows
  for (int i = 0; i < vectorName.size(); i++) {

    if (i == 0)
      cout << setw(colW1) << "Mon";
    else if (i == 1)
      cout << setw(colW1) << "Tues";
    else if (i == 2)
      cout << setw(colW1) << "Wed";
    else if (i == 3)
      cout << setw(colW1) << "Thur";
    else
      cout << setw(colW1) << "Fri";
    //cols
    for (int j = 0; j < 24; j++) {
      cout << setw(colW2) << vectorName[i][j];
    }
    cout << endl;
  }
  cout << endl;
  return;
}

//check minimal nurse and shift functions
bool checkScc(vector<vector<int> > &scc) {
  for (int i=0; i < scc.size(); i++) {
    for (int j=0; j < scc[i].size(); j++) {
      if (scc[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

void checkRedNurse(vector<vector<vector<bool> > > weekDays, vector<fullName> names, vector<vector<string> > &mns) {
  //create temp vector to edit values
  vector<vector<vector<bool> > > weekDaysTemp(5, vector<vector<bool>>(weekDays[0].size(), vector<bool>(24)));

  //create test scc vector
  vector<vector<int> > testScc(5, vector<int>(24));
  vector<vector<int> > testSccZero(5, vector<int>(24));

  //create a copy of names
  vector<fullName> testNames;
  weekDaysTemp = weekDays;
  testNames = names;

  //delete duplicate nurses from weekDays and names
  for (int n = 0; n < names.size(); n++) {
    for (int n1 = n+1; n1 < names.size(); n1++) {
      if (names[n].allShifts == names[n1].allShifts) {
        //nurse n and n1 have the same exact schedule, delete n1 from names and weekDays
        //cout << "Deleting: " << names[n1].name[0] << endl;
        names.erase(names.begin() + n1);
        for (int d = 0; d < weekDays.size(); d++) {
          weekDays[d].erase(weekDays[d].begin() + n1);
        }
      }
    }
  }

  for (int n = 0; n < names.size(); n++) {
    //reset test vectors
    testNames = names;
    weekDaysTemp = weekDays;
    testScc = testSccZero;

    for (int d = 0; d < weekDays.size(); d++) {
      //remove nurse from schedule
      weekDaysTemp[d].erase(weekDaysTemp[d].begin() + n);
    }
    for (int d = 0; d < weekDays.size(); d++) {
      //populate testScc vector
      set_or(weekDaysTemp, testScc);
    }
    //remove selected nurse from names vector
    testNames.erase(testNames.begin() + n);

    //check is simple complete coverage is still true
    if (!checkScc(testScc)) {
      //nurse is unique
      for (int d = 0; d < weekDays.size(); d++) {
        for (int h = 0; h < 24; h++) {
          if (weekDays[d][n][h] == 1) {
            if (mns[d][h].size() < 1) {
              mns[d][h] = names[n].initials;
            } else {
              mns[d][h] = mns[d][h] + "," + names[n].initials;
            }
          }
        }
      }
    }
  }

  return;
}

void checkRedShift(vector<vector<vector<bool> > > weekDays, vector<fullName> names, vector<vector<string> > &mss) {
  //create temp vector to edit values
  vector<vector<vector<bool> > > weekDaysTemp(5, vector<vector<bool>>(weekDays[0].size(), vector<bool>(24)));

  //create test scc vector
  vector<vector<int> > testScc(5, vector<int>(24));
  vector<vector<int> > testSccZero(5, vector<int>(24));

  //create a copy of names
  vector<fullName> testNames;
  weekDaysTemp = weekDays;
  testNames = names;

  //delete duplicate nurses from weekDays and names
  for (int n = 0; n < names.size(); n++) {
    for (int n1 = n+1; n1 < names.size(); n1++) {
      if (names[n].allShifts == names[n1].allShifts) {
        //nurse n and n1 have the same exact schedule, delete n1 from names and weekDays
        //cout << "Deleting: " << names[n1].name[0] << endl;
        names.erase(names.begin() + n1);
        for (int d = 0; d < weekDays.size(); d++) {
          weekDays[d].erase(weekDays[d].begin() + n1);
        }
      }
    }
  }

  //delete duplicate shifts from weekDays
  for (int n1 = 0; n1 < names.size(); n1++) {
    for (int n2 = n1+1; n2 < names.size(); n2++) {
      for (int s1 = 0; s1 < names[n1].shifts.size(); s1++) {
        for (int s2 = 0; s2 < names[n2].shifts.size(); s2++) {
          if (names[n1].shifts[s1] == names[n2].shifts[s2] && names[n2].shifts[s2].size() > 2) {
            //nurse n1 and n2 have the same shift s1 and s2, deleting s2 from weekDays and names.shifts
            //cout << "TEST: " << names[n2].name[0] << " " << s2 << endl;
            //cout << "Deleting shift: " << names[n2].shifts[s2] << endl;
            //get the day of s2
            int d;
            if (names[n2].shifts[s2][0] == 'M')
              d = 0;
            else if (names[n2].shifts[s2][1] == 'u')
              d = 1;
            else if (names[n2].shifts[s2][0] == 'W')
              d = 2;
            else if (names[n2].shifts[s2][1] == 'h')
              d = 3;
            else if (names[n2].shifts[s2][0] == 'F')
              d = 4;
            else
              cout << "ERROR 1: " << names[n2].shifts[s2] << " not recognised." << endl;
            //remove shift from schedule by setting every hour of the shift day to 0
            for (int h = 0; h < 24; h++) {
              weekDays[d][n2][h] = 0;
            }
            names[n2].shifts.erase(names[n2].shifts.begin() + s2);
          }
        }
      }
    }
  }

  //remove shift and check is scc is still true
  for (int n = 0; n < names.size(); n++) {
    for (int s = 0; s < names[n].shifts.size()-1; s++) {
      //reset test vectors
      testNames = names;
      weekDaysTemp = weekDays;
      testScc = testSccZero;

      //get day d of shift s
      int d;
      if (names[n].shifts[s][0] == 'M')
        d = 0;
      else if (names[n].shifts[s][1] == 'u')
        d = 1;
      else if (names[n].shifts[s][0] == 'W')
        d = 2;
      else if (names[n].shifts[s][1] == 'h')
        d = 3;
      else if (names[n].shifts[s][0] == 'F')
        d = 4;
      else
        cout << "ERROR 2: " << names[n].shifts[s] << " not recognised." << endl;

      //remove nurse schedule from weekDaysTemp
      for (int h = 0; h < 24; h++) {
        weekDaysTemp[d][n][h] = 0;
      }

      //populate testScc vector
      set_or(weekDaysTemp, testScc);


      //check is simple complete coverage is still true
      if (!checkScc(testScc)) {
        //shift is unique, add nurse n shift s to minimal shift schedule
        for (int h = 0; h < 24; h++) {
          if (weekDays[d][n][h] == 1) {
            if (mss[d][h].size() < 1) {
              mss[d][h] = names[n].initials;
            } else {
              mss[d][h] = mss[d][h] + "," + names[n].initials;
            }
          }
        }
      }
    }
  }

  return;
}

//set operations
void set_or(vector<vector<vector<bool> > > &weekDays, vector<vector<int> > &scc) {
  for (int d = 0; d < 5; d++) {
    for (int n = 0; n < weekDays[d].size(); n++) {
      for (int h = 0; h < 24; h++) {
        if (weekDays[d][n][h] == true) {
          scc[d][h] = 1;
        }
      }
    }
  }
  return;
}

void set_and(vector<vector<vector<bool> > > &weekDays, vector<vector<int> > &mt1, vector<vector<int> > &numOfNurses) {
  for (int d = 0; d < 5; d++) {
    for (int n = 0; n < weekDays[d].size(); n++) {
      for (int h = 0; h < 24; h++) {
        if (weekDays[d][n][h] == true) {
          numOfNurses[d][h]++;
          if (numOfNurses[d][h] > 1)
            mt1[d][h] = 1;
        }
      }
    }
  }
  return;
}

void set_not(vector<vector<int> > &scc, vector<vector<int> > &nn) {
  for (int d = 0; d < scc.size(); d++) {
    for (int h = 0; h < scc[d].size(); h++) {
      if (scc[d][h] != 0)
        nn[d][h] = 0;
      else
        nn[d][h] = 1;
    }
  }
  return;
}

void set_symdiff(vector<vector<int> > &e1n, vector<vector<int> > &numOfNurses) {
  for (int d = 0; d < numOfNurses.size(); d++) {
    for (int h = 0; h < numOfNurses[d].size(); h++) {
      if (numOfNurses[d][h] == 1) {
        e1n[d][h] = 1;
      }
    }
  }
  return;
}
