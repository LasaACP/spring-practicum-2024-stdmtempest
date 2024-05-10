#include <iostream>
#include <fstream>
#include <string>
#include "WeatherLinkedList.h"
using namespace std;

void CSVtoLinkedList(string csv_file_name, 
WeatherLinkedList& list) {
  ifstream csv_file(csv_file_name);
  if (!csv_file.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return;
  }
  
  int month, day;
  string place;
  cout << "Enter month:";
  cin >> month;
  cout << "Enter day:";
  cin >> day;
  cout << "Enter place:";
  getline(cin, place);
  
  string line;
  while (getline(csv_file, line)) {
    
      size_t pos = 0;
      int commaCount = 0;
      while (pos != string::npos && commaCount < 8) {
          pos = line.find(',', pos + 1);
          commaCount++;
      }

      if (pos != string::npos) {
        
          string temperature;
          string remainder;
          split(line.substr(pos + 1), ',', temperature, remainder);

          cout << "Temperature: " << temperature << endl;
      } else {
          cerr << "Row does not contain enough values." << endl;
      }
  }


  csv_file.close();
}