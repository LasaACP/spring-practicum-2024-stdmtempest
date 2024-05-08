
#ifndef WEATHERDATAEXTRACTOR_H
#define WEATHERDATAEXTRACTOR_H

#include<stdlib.h>  
#include<stdio.h>
#include<string.h>
#include <bits/stdc++.h>
using namespace std;

struct WeatherData {
  int day;
  int month;
  int year;
  double latitude;
  double longitude;
  double elevation;
  double precipitation;
  double tmax;
  double tmin;
};

class WeatherDataExtractor
{
public:
  int order_num;
  vector<vector<string>> csv_array;

  WeatherDataExtractor(int order);
  ~WeatherDataExtractor();

  int CSVlength();
  void populateArray();
  vector<WeatherData> WeatherDataFiveDays();
};

#endif // WEATHERDATAEXTRACTOR_H
