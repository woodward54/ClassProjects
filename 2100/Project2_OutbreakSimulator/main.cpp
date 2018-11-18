//Authors: David Woodward and Luis Garcia



#include "colormod.h" // namespace Color class from user Joel Sjögren on https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
#include <unistd.h> //library for time

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <random>
using namespace std;

void fifo(vector<string> &grid, string newVal);
int random(int min, int max);

void parse(string file, vector<vector<vector<string> > > &grid, vector<string> &uni, vector<float> &ints, vector<string> &nums, int &xSize, bool bonus);
void getNums(vector<vector<vector<string> > > &grid, int &numOfI, int &numOfV, int &numOfR, int &numOfS);
void printNums(int num1, int num2, int num3, int num4, string box, int day);
void updateGrid(vector<vector<vector<string> > > &grid, int searchSize, int infection, int recover, float probility, bool bonus);
void printGrid(vector<vector<vector<string> > > &grid, string box);

Color::Modifier white(Color::FG_WHITE);       //susceptible
Color::Modifier green(Color::FG_GREEN);       //infected
Color::Modifier blue(Color::FG_LIGHT_BLUE);   //vaccinated
Color::Modifier pink(Color::FG_MAGENTA);        //recovered
Color::Modifier def(Color::FG_DEFAULT);

int main() {
  vector<vector<vector<string> > > grid;
  int infection, recover, display, reach, numOfI, numOfV, numOfR, numOfS;
  string tempString, fileName;
  float probility;

  vector<string> uni, nums;
  vector<float> ints;
  int xSize, ySize;

  //Program Variables
  string box = "■ ";
  int day_cnt = 0, peakI = 0, peakDay = 0;
  bool bonus = false;

  //color legend
/*  cout << endl; cout << endl; cout << endl;
  cout << white << box << def << setw(15) << left << " : Susceptible";
  cout << green << box << def << " : Infected";
  cout << endl;
  cout << blue << box << def << setw(15) << left << " : Vaccinated";
  cout << pink << box << def << " : Recovered";
  cout << endl;
  cout << endl; */


  //user input

  //get file name
  cout << "Enter the file name: ";
  getline(cin, fileName);
  cout << "Is this a bonus file? " << endl;
  cout << "yes/no: ";
  getline(cin, tempString);
  if (tempString == "yes") {
    bonus = true;
  }
  else if (tempString == "no") {
    reach = 1;
    bonus = false;
  }
  else {
    cout << "ERROR 4: Invalid input, quitting..." << endl;
    return 0;
  }

  //parse
  parse(fileName, grid, uni, ints, nums, xSize, bonus);
  ySize = uni.size() / xSize;
  if (bonus) {
    recover = ints[0];
    display = ints[1];
    reach = ints[2];
    probility = ints[3];
  } else {
    infection = ints[0];
    recover = ints[1];
    display = ints[2];
  }


  for (int y = 0; y < ySize; y++) {

     grid.push_back(vector<vector<string> >());
     for (int x = 0; x < xSize; x++) {
          grid[y].push_back(vector<string>()); //add couts
          grid[y][x].push_back(uni[xSize*y + x]);

          //add extra day/days
          for (int i=1; i<recover; i++) {
            grid[y][x].push_back("e");
          }
     }
  }

  cout << endl; cout << endl;

  while (numOfI != 0) {
    getNums(grid, numOfI, numOfV, numOfR, numOfS);
    if (day_cnt%display == 0 || numOfI == 0) {
      printGrid(grid, box);
      if (numOfI != 0)
        printNums(numOfI, numOfV, numOfR, numOfS, box, day_cnt); cout << endl; cout << endl;
    }

    updateGrid(grid, reach, infection, recover, probility, bonus);

    if (numOfI > peakI) {
      peakI = numOfI;
      peakDay = day_cnt;
    }
    day_cnt++;
    usleep(350000);
    //cout << def << "Press enter to continue: ";
    //cin >> tempString; cin.ignore(); cout << endl;
  }

  //stats output
  cout << def << "Final Values - " << endl;
  cout << "Final Day          : " << day_cnt-1 << endl;
  cout << "Peak Infection Day : " << peakDay << endl;
  printNums(numOfI, numOfV, numOfR, numOfS, box, day_cnt);

  cout << endl; cout << endl;
  cout << def << endl;


  return 0;
}

//utility functions
//fifo = first in first out
void fifo(vector<string> &status, string newVal) {

  for (int i=status.size()-1; i>0; i--) {
    status[i] = status[i-1];
  }

  status[0] = newVal;
  return;
}

int random(int min, int max) //range : [min, max)
{
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}


//grid functions
void updateGrid(vector<vector<vector<string> > > &grid, int reach, int infection, int recover, float probility, bool bonus) {
  int i_cnt = 0, num_i_found = 0, tempInt;
  vector<vector<vector<string> > > statusCopy;
  statusCopy = grid;

  for (int y=0; y<grid.size(); y++) {
    for (int x=0; x<grid[y].size(); x++) {
      //cout << y << " " << x << endl; test debug statment
      if (statusCopy[y][x][0] == "s") {
        num_i_found = 0;
        //find num of i's around y,x
        for (int i=(-1*reach); i<=reach; i++) {
          for (int j=(-1*reach); j<=reach; j++) {
            //Check if current spot is out of bounds
            if (!(y+i < 0 || y+i > grid.size()-1 || x+j < 0 || x+j > grid[y].size()-1)) {
              if (statusCopy[y+i][x+j][0] == "i") {
                num_i_found++;
              }
            }
          }
        }

        if (bonus) {
          //bonus probility code
          tempInt = (num_i_found*probility)*100;
          if (random(1,100) < tempInt) {
            fifo(grid[y][x], "i");
          } else {
            fifo(grid[y][x], "s");
          }
        } else {
        //not bonus
          if (num_i_found >= infection) {
            fifo(grid[y][x], "i");
          }
        }

      } else if (statusCopy[y][x][0] == "i") {
        i_cnt = 0;
        for (int i=0; i<grid[y][x].size(); i++) {
          if (grid[y][x][i] == "i") {
            i_cnt++;
          }
          if (i_cnt == recover) {
            fifo(grid[y][x], "r");
          } else if (i == grid[y][x].size()-1){
            fifo(grid[y][x], "i");
          }
        }
      } else if (statusCopy[y][x][0] == "v") {
        fifo(grid[y][x], "v");
      }  else if (statusCopy[y][x][0] == "r") {
        fifo(grid[y][x], "r");
      } else {
        cout << "ERROR 1: Invalid value[" << grid[y][x][0] <<  "] in string vector." << endl;
      }
    }
  }
  return;
}

void printGrid(vector<vector<vector<string> > > &grid, string box) {


  for (int y=0; y<grid.size(); y++) {
    for (int x=0; x<grid[y].size(); x++) {

      if (grid[y][x][0] == "s")
        cout << white << box;
      else if (grid[y][x][0] == "i")
        cout << green << box;
      else if (grid[y][x][0] == "v")
        cout << blue << box;
      else if (grid[y][x][0] == "r")
        cout << pink << box;
      else
        cout << "ERROR 2: Invalid value[" << grid[y][x][0] <<  "] in string vector." << endl;

    }
    cout << endl;
  }
  return;
}

void printNums(int numOfI, int numOfV, int numOfR, int numOfS, string box, int day_cnt) {

  if (numOfI != 0)
    cout << def << "Day: " << day_cnt << endl;
  cout << green << box << def << setw(15) << left << " Infected " << numOfI << endl;
  cout << white << box << def << setw(15) << left << " Susceptible " << numOfS << endl;
  cout << blue << box << def << setw(15) << left << " Vaccinated " << numOfV << endl;
  cout << pink << box << def << setw(15) << left << " Recovered " << numOfR << endl;


  return;
}

void getNums(vector<vector<vector<string> > > &grid, int &numOfI, int &numOfV, int &numOfR, int &numOfS) {

  numOfS = 0;
  numOfI = 0;
  numOfR = 0;
  numOfV = 0;

  for (int y=0; y<grid.size(); y++) {
    for (int x=0; x<grid[y].size(); x++) {
      if (grid[y][x][0] == "s")
        numOfS++;
      else if (grid[y][x][0] == "r")
        numOfR++;
      else if (grid[y][x][0] == "v")
        numOfV++;
      else if (grid[y][x][0] == "i")
        numOfI++;
      else
        cout << "ERROR 3: Invalid value[" << grid[y][x][0] <<  "] in string vector." << endl;
    }
  }

  return;
}

void parse(string file, vector<vector<vector<string> > > &grid, vector<string> &uni, vector<float> &ints, vector<string> &nums, int &xSize, bool bonus) {
   string s, el, del = ":";
   int bonusInt;
   size_t pos=0;

   ifstream fin;
   fin.open(file.c_str());

   if (bonus)
    bonusInt = 4;
   else
    bonusInt = 3;

   for (int i = 0; i < bonusInt; i++) {
      getline(fin, s);
      s += ":";
      while ((pos = s.find(del)) != string::npos) {
         el = s.substr(0, pos);
         s.erase(0, pos + del.length());
         el = s.substr(0, pos);
         nums.push_back(el);
         s.erase(0, pos + del.length());
      }
   }

   del = ",";

   getline(fin, s);
   s += ",";

   while ((pos = s.find(del)) != string::npos) {
      el = s.substr(0, pos);
      uni.push_back(el);
      s.erase(0, pos + del.length());
   }

   xSize = uni.size();

   while (!fin.eof()) {
      getline(fin, s);
      s += ",";
      if (s.compare(",") == 0) break;
      while ((pos = s.find(del)) != string::npos) {
        el = s.substr(0, pos);
        uni.push_back(el);
        s.erase(0, pos + del.length());
      }
   }

  for (int i=0; i<bonusInt; i++) {
    float a = stof(nums[i]);
    ints.push_back(a);
  }

}
