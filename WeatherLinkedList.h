#ifndef WEATHERDATAEXTRACTOR_H
#define WEATHERDATAEXTRACTOR_H

#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <string.h>

using namespace std;

class WeatherData {
public:
  string place;
  double latitude;
  double longitude;
  double elevation;
  int month;
  int day;
  int year;
  double precipitation;
  double tmax;
  double tmin;

  WeatherData();
  WeatherData(string plc, double lat, double lon, double elv, int mon, int day,
              int yr, double prc, double tmx, double tmn);
  ~WeatherData();
  string toString();
};

class node {
public:
  WeatherData *data;
  node *next;
  node(WeatherData *a);
  node(WeatherData *a, node *n);
};

class WeatherLinkedList {
public:
  node *head;

  WeatherLinkedList();
  ~WeatherLinkedList();
  void add(WeatherData value);
  void clear();
  WeatherData get(int mon, int day, string plc);
  bool isEmpty();
  int size();
  string toString();
  void CSVtoLinkedList(string csv_file_name, WeatherLinkedList &list);
};

#endif