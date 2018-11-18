#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct person {
  string name;
  vector<bool> bitwise;
  vector<int> sets_cnt;
};

void parse(string inputFile, bool bonus, vector<string> &universal, vector<person> &people);
void scanPerson(int p_cnt, string s, vector<string> &universal, vector<person> &people);
void scanPersonAsUni(int p_cnt, string s, vector<string> &universal, vector<person> &people);

vector<bool> partyWhole(vector<bool> temp1, vector<bool> temp2);
vector<bool> partyWhole2(vector<bool> temp1, vector<bool> temp2);
vector<bool> duplicate1(vector<bool> temp1, vector<bool> temp2);
vector<bool> duplicate2(vector<bool> temp1, vector<bool> temp2);


int main() {
  int collumWidth = 15, collum1Width = 20;
  vector<string> universal;
  vector<person> people;
  vector<person> sets;
  string fileName, tempString;
  bool bonus;

  cout << "Enter the filename: ";
  getline(cin, fileName);
  cout << "Does this file contain a universal set?" << endl;
  cout << "yes/no: ";
  cin >> tempString; cin.ignore();
  if (tempString.compare("yes") == 0) {
    bonus = false;
  } else {
    bonus = true;
  }

  parse(fileName, bonus, universal, people);

  //call all set functions to get output data, they are stored in the sets vector
  //union / party whole
    struct person temp;
    temp.name = "Party Whole";
    sets.push_back(temp);
    sets[0].bitwise = partyWhole(people[0].bitwise, people[1].bitwise);
    for (int i=2; i<people.size(); i++)
      sets[0].bitwise = partyWhole(sets[0].bitwise, people[i].bitwise);

  //duplicate
    temp.name = "Duplicates";
    sets.push_back(temp);
    for (int i=0; i<universal.size(); i++) {
      sets[1].sets_cnt.push_back(0);
      sets[1].bitwise.push_back(0);
    }

    for (int i=0; i<people.size(); i++){
      //adds 1 for each item found
      for (int j=0; j<universal.size(); j++) {
          if (people[i].bitwise[j] == 1)
            sets[1].sets_cnt[j]++;
        }
    }
    for (int i=0; i<universal.size(); i++) {
      if (sets[1].sets_cnt[i] > 1)
        sets[1].bitwise[i] = 1;
    }
    cout << endl;

  //owned by only 1 part member
    temp.name = "Only One";
    sets.push_back(temp);
    for (int i=0; i<universal.size(); i++) {
      sets[2].sets_cnt.push_back(0);
      sets[2].bitwise.push_back(0);
    }
    for (int i=0; i<people.size(); i++){
      //gets the complment of the duplicates
      for (int j=0; j<universal.size(); j++) {
          if (sets[1].sets_cnt[j] > 0)
            sets[2].bitwise[j] = !sets[1].bitwise[j];
        }
    }

  //items party is lacking
    temp.name = "Party Lacking";
    sets.push_back(temp);
    for (int i=0; i<universal.size(); i++) {
      sets[3].sets_cnt.push_back(0);
      sets[3].bitwise.push_back(0);
    }
    for (int i=0; i<people.size(); i++){
      //gets the complment of the party whole
      for (int j=0; j<universal.size(); j++) {
            sets[3].bitwise[j] = !sets[0].bitwise[j];
        }
    }


  //output data in a table
    //row 1
    cout << left << setw(collum1Width) << " ";
    for (int i=0; i < people.size(); i++)
      cout << left << setw(collumWidth) << people[i].name;
    for (int i=0; i < sets.size(); i++)
      cout << left << setw(collumWidth) << sets[i].name;
    cout << endl;

    //row 2-n
    for (int i=0; i < universal.size(); i++) {
      cout << left << setw(collum1Width) << universal[i];
      for (int j=0; j < people.size(); j++)
        cout << left << setw(collumWidth) << people[j].bitwise[i];
      for (int j=0; j < sets.size(); j++)
        cout << left << setw(collumWidth) << sets[j].bitwise[i];
      cout << endl;
    }
    cout << endl;

  return 0;
}


void parse(string inputFile, bool bonus, vector<string> &universal, vector<person> &people) {
  string name, s, element, delimiter = ",";
  size_t pos=0;
  int p_cnt=0;

  ifstream fin;
  fin.open(inputFile.c_str());

  getline(fin, s);
  s += ",";

  if (bonus) {
    //no universal set
    //scan the first person as the universal

    struct person temp;
    people.push_back(temp);

    scanPersonAsUni(p_cnt, s, universal, people);

    p_cnt++;

  } else {
    //scan universal set

    while ((pos = s.find(delimiter)) != string::npos) {
      element = s.substr(0, pos);
      universal.push_back(element);
      s.erase(0, pos + delimiter.length());
    }
    cout << "INFO: Universal set loaded." << endl;
  }

  //scan all of the people
  while (!fin.eof()) {

    getline(fin, s);
    s += ",";

    //bug fix
    if (s.compare(",") == 0)
      break;
    //cout << "TEST: " << s << endl;
    struct person temp;
    people.push_back(temp);

    scanPerson(p_cnt, s, universal, people);

    p_cnt++;
  }
  cout << endl; cout << endl;
  return;
}

void scanPerson(int p_cnt, string s, vector<string> &universal, vector<person> &people) {
  string element, delimiter;
  size_t pos=0;
  bool foundItem;

  //get name
  delimiter = ":";
  pos = s.find(delimiter);
  people[p_cnt].name = s.substr(0, pos);
  s.erase(0, pos + delimiter.length());

  //set bitwise vector to 0s
  for (int i=0; i < universal.size(); i++) {
    people[p_cnt].bitwise.push_back(0);
  }

  //get elements
  delimiter = ",";
  while ((pos = s.find(delimiter)) != string::npos) {
    element = s.substr(0, pos);
    foundItem = false;

    for (int i=0; i < universal.size(); i++) {
      if (universal[i].compare(element) == 0) {
        //element found in universal set
        people[p_cnt].bitwise[i] = 1;
        foundItem = true;
      }
    }
    if (!foundItem) {
      //item not found in universal set
      cout << "ALERT: Item " << element << " not in universal set. Adding it..." << endl;
      universal.push_back(element);
      //update everyone's bitwise vectors
      for (int i=0; i<people.size(); i++) {
        people[i].bitwise.push_back(0);
      }
      people[p_cnt].bitwise[universal.size()-1] = 1;
    }
    s.erase(0, pos + delimiter.length());
  }
  cout << "INFO: Person " << people[p_cnt].name << " loaded." << endl;

  return;
}

void scanPersonAsUni(int p_cnt, string s, vector<string> &universal, vector<person> &people) {

  string element, delimiter;
  size_t pos=0;

  //get name
  delimiter = ":";
  pos = s.find(delimiter);
  people[p_cnt].name = s.substr(0, pos);
  s.erase(0, pos + delimiter.length());

  //get elements
  delimiter = ",";
  while ((pos = s.find(delimiter)) != string::npos) {
      element = s.substr(0, pos);
      universal.push_back(element);
      people[p_cnt].bitwise.push_back(1);
      s.erase(0, pos + delimiter.length());
    }

  cout << "INFO: Person " << people[p_cnt].name << " loaded." << endl;
  return;
}



//set functions

//party whole / union
vector<bool> partyWhole(vector<bool> temp1, vector<bool> temp2) {
   vector<bool> unionn(temp1.size());

   for (int i = 0; i < temp1.size(); i++) {
      if (temp1.at(i) == true || temp2.at(i) == true)
        unionn.at(i) = true;
      else
        unionn.at(i) = false;
   }
   return unionn;
}

vector<bool> partyWhole2(vector<bool> temp1, vector<bool> temp2) {
   vector<bool> unionn(temp1.size());

   for (int i = 0; i < temp1.size(); i++)
      if (temp1.at(i) == true || temp2.at(i) == true)
        unionn.at(i) = true;
   return unionn;
}

//duplicate / intersect
vector<bool> duplicate1(vector<bool> temp1, vector<bool> temp2) {
   vector<bool> intersect(temp1.size());

   for (int i = 0; i < temp1.size(); i++) {
      if (temp1.at(i) == 1 && temp2.at(i) == 1)
        intersect.at(i) = 1;
      else
        intersect.at(i) = 0;
   }
   return intersect;
}

vector<bool> duplicate2(vector<bool> temp1, vector<bool> temp2) {
   vector<bool> intersect(temp1.size());

   for (int i = 0; i < temp1.size(); i++) {
      if (temp1.at(i) == 1 && temp2.at(i) == 1)
        intersect.at(i) = 1;
   }
   return intersect;
}
