
#ifndef CITYDATAEXTRACTOR_H
#define CITYDATAEXTRACTOR_H

#include<stdlib.h>  
#include<stdio.h>
#include<string.h>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class CityDataExtractor
{
public:
  vector<vector<string>> csv_array;

  CityDataExtractor();
  ~CityDataExtractor();

  int CSVlength();
  void populateArray();
  void CSVcleanup();
};

#endif // CITYDATAEXTRACTOR_H
