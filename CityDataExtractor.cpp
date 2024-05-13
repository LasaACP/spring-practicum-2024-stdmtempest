#include "CityDataExtractor.h"
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

CityDataExtractor::CityDataExtractor()
{
  csv_array.clear();
  CityDataExtractor::populateArray();
  CityDataExtractor::CSVcleanup();
}

CityDataExtractor::~CityDataExtractor()
{
}

int CityDataExtractor::CSVlength() {
  string csv_file_name = "city-data/City Data.csv";
  ifstream csv_file(csv_file_name);
  if (!csv_file.is_open()) {
    cout << "Error opening file" << endl;
  }
  else {
    string line;
    int count = 0;
    while (getline(csv_file, line)) {
      count++;
    }
    csv_file.close();
    return count;
  }
  return -1;
}

void CityDataExtractor::populateArray() {
  csv_array.clear();
  string csv_file_name = "city-data/City Data.csv";
  int length = CSVlength();

  cout << "CSV # Rows: " << length << endl;
  
  string line;
  ifstream csv_file(csv_file_name);
  getline(csv_file, line);
  int num_cols = 1; //starting with 1 because the final column doesn't have a comma after it
  for (int i = 0; i < line.length(); i++) {
    if (line[i] == ',') {
      num_cols++;
    }
  }

  cout << "CSV # Columns: " << num_cols << endl;
  
  csv_file.close();
  csv_file.open(csv_file_name);
  
  for (int i = 0; i < length; i++) {
    vector<string> row;
    getline(csv_file, line);
    for (int j = 0; j < num_cols; j++) {
      if (line[0] != '\"') {
        row.push_back(line.substr(0, line.find(",")));
        line = line.substr(line.find(",") + 1);
      }
      else {
        line = line.substr(1);
        row.push_back(line.substr(0, line.find("\"")));
        line = line.substr(line.find("\"") + 2);
      }
    }
    csv_array.push_back(row);
  }
}

void CityDataExtractor::CSVcleanup() {
  for (int i = 0; i < csv_array.size(); i++) {
    csv_array[i][1].erase(std::remove(csv_array[i][1].begin(), csv_array[i][1].end(), ','), csv_array[i][1].end());
  }
}

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
}