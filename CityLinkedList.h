#ifndef CITYLINKEDLIST_H
#define CITYLINKEDLIST_H

#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <string.h>

using namespace std;

class City {
public:
  string cityName;
  int population;
  double latitude;
  double longitude;

  City();
  City(string name, int pop, double lat, double lon);
  ~City();
  string toString();
};

class node {
public:
  City *data;
  node *next;
  node(City *a);
  node(City *a, node *n);
};

class CityLinkedList {
public:
  node *head;

  CityLinkedList();
  ~CityLinkedList();
  void add(City c);
  void clear();
  double getLat(string name);
  double getLon(string name);
  string toString();
};

#endif