
#ifndef WEATHERDATAEXTRACTOR_H
#define WEATHERDATAEXTRACTOR_H

#include<stdlib.h>  
#include<stdio.h>
#include<string.h>
#include <bits/stdc++.h>
using namespace std;

class WeatherDataExtractor
{
public:
  int order_num;
  vector<vector<string>> csv_array;

  WeatherDataExtractor(int order);
  ~WeatherDataExtractor();

  int CSVlength();
  void populateArray();

};

#endif // WEATHERDATAEXTRACTOR_H
