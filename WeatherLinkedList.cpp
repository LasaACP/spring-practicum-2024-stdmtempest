

void CSVtoLinkedList(string csv_file_name, WeatherLinkedList& list) {
  ifstream csv_file(csv_file_name);
  if (!csv_file.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return;
  }

  string line;
  while (getline(csv_file, line)) {
    stringstream ss(line);
    string token;

    WeatherData data;

    getline(ss, token, ',');
    data.id = stoi(token);

    getline(ss, token, ',');
    data.name = token;

    list.insert(data);
  }

  file.close();
}