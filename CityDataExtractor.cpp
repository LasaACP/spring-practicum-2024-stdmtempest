#include "CityDataExtractor.h"
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
using namespace std;

CityDataExtractor::CityDataExtractor() {
  csv_array.clear();
  CityDataExtractor::populateArray();
  CityDataExtractor::CSVcleanup();
}

CityDataExtractor::~CityDataExtractor() {}

int CityDataExtractor::CSVlength() {
  string csv_file_name = "city-data/CityData.csv";
  ifstream csv_file(csv_file_name);
  if (!csv_file.is_open()) {
    cout << "Error opening file" << endl;
  } else {
    string line;
    int count = 0;
    while (getline(csv_file, line)) {
      count++;
    }
    csv_file.close();
    return (count - 1); // -1 because header
  }
  return -1;
}

void CityDataExtractor::populateArray() {
  csv_array.clear();
  string csv_file_name = "city-data/CityData.csv";
  int length = CSVlength();



  string line;
  ifstream csv_file(csv_file_name);
  getline(csv_file, line);
  int num_cols = 1; // starting with 1 because the final column doesn't have a
                    // comma after it
  for (int i = 0; i < line.length(); i++) {
    if (line[i] == ',') {
      num_cols++;
    }
  }

 

  csv_file.close();
  csv_file.open(csv_file_name);

  for (int i = 0; i < length + 1; i++) { // +1 because header
    if (i != 0) {
      vector<string> row;
      getline(csv_file, line);
      for (int j = 0; j < num_cols; j++) {
        if (line[0] != '\"') {
          row.push_back(line.substr(0, line.find(",")));
          line = line.substr(line.find(",") + 1);
        } else {
          line = line.substr(1);
          row.push_back(line.substr(0, line.find("\"")));
          line = line.substr(line.find("\"") + 2);
        }
      }
      csv_array.push_back(row);
    }
    else {
      getline(csv_file, line);
    }
  }
}

void CityDataExtractor::CSVcleanup() {
  for (int i = 0; i < csv_array.size(); i++) {
    csv_array[i][1].erase(
        std::remove(csv_array[i][1].begin(), csv_array[i][1].end(), ','),
        csv_array[i][1].end());
  }
}

/*
int main() {
   cout << "-------TESTING IN PROGRESS-------" << endl;
   CityDataExtractor cde;
   for (int j = 0; j < cde.CSVlength(); j++) {
     for (int i = 0; i < cde.csv_array[0].size(); i++) {
       cout << cde.csv_array[j][i] << "\t";
     }
     cout << endl;
   }
   cout << "-------TESTING COMPLETE-------" << endl;
}*/