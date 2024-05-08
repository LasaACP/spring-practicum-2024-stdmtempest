#include <iostream>
#include <fstream>
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

string** CSVarray(int order_num) {
  string csv_file_name = "weather-data/" + to_string(order_num) + ".csv";
  int length = CSVlength(order_num);
  string line;
  string ** output = new string * [length];
  ifstream csv_file(csv_file_name);
  getline(csv_file, line);
  int num_cols = 1; //starting with 1 because the final column doesn't have a comma after it
  for (int i = 0; i < line.length(); i++) {
    if (line[i] == ',') {
      num_cols++;
    }
  }
  for (int i = 0; i < length; i++) {
    output[i] = new string[num_cols];
  }

  //Array has been created, now time to populate
  csv_file.close();
  csv_file.open(csv_file_name);

  for (int i = 0; i < length; i++) {
    
  }
  
  return output;
}

int main() {
  cout << CSVlength(3674657) << endl;
  string ** array = CSVarray(3674657);
}