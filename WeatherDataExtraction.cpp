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

int main() {
  cout << CSVlength(3674657) << endl;
}