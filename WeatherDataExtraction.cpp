#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int CSVlength(int order_num) {
  string csv_file_name = "weather-data/" + to_string(order_num) + ".csv";
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

void CSVarray(int order_num, vector<vector<string>> &v) {
  string csv_file_name = "weather-data/" + to_string(order_num) + ".csv";
  int length = CSVlength(order_num);
  string line;
  ifstream csv_file(csv_file_name);
  getline(csv_file, line);
  int num_cols = 1; //starting with 1 because the final column doesn't have a comma after it
  for (int i = 0; i < line.length(); i++) {
    if (line[i] == ',') {
      num_cols++;
    }
  }
  
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
        line = line.substr(line.find("\"") + 1);
      }
    }
    v.push_back(row);
  }
}

int main() {
  cout << CSVlength(3674657) << endl;
  vector<vector<string>> csv_array;
  CSVarray(3674657, csv_array);
}